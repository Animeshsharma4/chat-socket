#include <iostream>
using namespace std;
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")


/*

initialize winsock library 

create the socket

get ip and port

bind the ip/port with the socket

listen on the socket

accept

recieve and send 
                           



*/

bool initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void interactWithClient(SOCKET clientsocket,vector<SOCKET>clients) {
	cout << "client connected" << endl;

	char buffer[4096];
	while (1) {
		int bytesrec = recv(clientsocket, buffer, sizeof(buffer), 0);
		if (bytesrec == 0) {
			cout << "client disconnected" << endl;
			break;
		}
		string message(buffer, bytesrec);
		cout << "message from client : " << message << endl;
		for (auto client : clients) {
			if (client != clientsocket) {
				send(client, message.c_str(), message.length(), 0);
			}                      
		}
	}
	auto it = find(clients.begin(), clients.end(), clientsocket);
	if (it != clients.end()) {
		clients.erase(it);
	}
	
	closesocket(clientsocket);
}
int main() {
	if (!initialize()) {
		cout << "winsock initialization failed" << endl;
	}
	cout << "server program" << endl;

	SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listensocket == INVALID_SOCKET) {
		cout << "socket creation failed" << endl;
		return 1;
	}
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting address structure failed" << endl;
		closesocket(listensocket);
		WSACleanup;
		return 1;
	
	};
	if(bind(listensocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr))==SOCKET_ERROR) {
		cout << "bind failed" << endl;
		closesocket(listensocket);
		WSACleanup;
		return 1;
	}
	if (listen(listensocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "listen failed" << endl;
		closesocket(listensocket);
		WSACleanup;
		return 1;
	}
	cout << "server has started listening on port : " << port << endl;
	vector<SOCKET>clients;
	while (1) {
		SOCKET clientsocket = accept(listensocket, nullptr, nullptr);
		if (clientsocket == INVALID_SOCKET) {
			cout << "invalid client socket" << endl;
		}
		clients.push_back(clientsocket);
		thread t1(interactWithClient, clientsocket,ref(clients));
		t1.detach();
	}
	
	closesocket(listensocket);
	WSACleanup();
	return 0;
}