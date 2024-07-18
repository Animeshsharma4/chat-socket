## Chat Socket Server and Client in C++ (Winsock)
This project is a simple chat application implemented using C++ and the Winsock library for Windows. It consists of a server and a client application that can communicate with each other over a TCP/IP socket connection.

## Features

# Server:

1 Listens for incoming client connections on a specified port.
2 Handles multiple client connections simultaneously.
3 Broadcasts messages received from one client to all other connected clients.

# Client:

1 Connects to the server on a specified IP address and port.
2 Sends messages to the server, which are then broadcasted to all other connected clients.
3 Receives and displays messages from other clients.
## Prerequisites
1 Windows operating system
2 C++ compiler (e.g., Visual Studio, MinGW, or Clang)
3 Winsock library (included in Windows)
## Usage
# Compile the server and client applications:

Compile the server code using a C++ compiler.
Compile the client code using a C++ compiler.
# Run the server:

Execute the server application.
The server will start listening for incoming client connections on the specified port.
# Run the clients:

Execute the client application.
Each client will connect to the server and can start sending and receiving messages.
