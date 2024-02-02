#include <iostream>
using namespace std;
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#pragma comment(lib,"ws2_32.lib")
#include <thread>
/*
initialize winsock
create socket
connect to the server
send/recv
close the socket



*/


bool initialize() {
	WSADATA  data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;

 }
void sendMessage(SOCKET s) {
	cout << "ENTER YOUR CHAT NAME" << endl;
	string name;
	cin >> name;
	string message;
	while (1) {
		getline(cin,message);
		string msg = name + " : " + message;
		
		int bytessent= send(s, msg.c_str(), msg.length(), 0);
		if (bytessent == SOCKET_ERROR) {
			cout << "error sending message" << endl;
			break;
		}
		if (message == "quit") {
			cout << "stopping the application" << endl;
			break;                                
		}
	}
	closesocket(s);
	WSACleanup();

}
void recieveMessage(SOCKET s) {
	char buffer[4096];
	int recvlength;
	string msg = "";
	while (1) {
		recvlength=recv(s, buffer, sizeof(buffer), 0);
		if (recvlength <= 0) {
			cout << "disconnected from the server" << endl;
			break;
		}
		else {
			msg = string(buffer, recvlength);
			cout << msg << endl;
		}
	}
	closesocket(s);
	WSACleanup();

}
int main() {

	if (!initialize()) {
		cout << "initialize winsock failed" << endl;
		return 1;
	}
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == INVALID_SOCKET) {
		cout << "invalid  socket created" << endl;
		return 1;

	}
	string serveraddress = "127.0.0.1";
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));
	if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout<<"not able to connect to server"<<endl;
		closesocket(s);
		WSACleanup();
		return 1;
	}
	cout << "successfully connected to server" << endl;
	thread senderthread(sendMessage, s);
	thread reciever(recieveMessage, s);
	senderthread.join();
	reciever.join();
	                                                 
	return 0;
}