#pragma once
#include <iostream>
#pragma warning(disable : 4996)
#include <winsock2.h>
#include "C:\Users\User1\Documents\μιξεγν ιγ\C++\IAI\shared\IDD.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;
/// <summary>
/// the socket to connect between components
/// </summary>
class UDPsocket
{
    WSADATA wsa;
    SOCKET my_socket;

public:
  
	/// <summary>
	/// initialize
	/// </summary>
	/// <param name="PORT"></param>
	UDPsocket() {
        system("title UDP Server");
        // initialise winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        {
            cout << "Failed. Error Code: " << WSAGetLastError();
            exit(0);
        }

        // create a socket
        if ((my_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
        {
            cout << "Could not create socket: " << WSAGetLastError();
        }
        // prepare the sockaddr_in structure
	}

    void Bind(unsigned short PORT) {
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);
        if (bind(my_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        {
            cout << "Bind failed with error code : " << WSAGetLastError();
            exit(EXIT_FAILURE);
        }
    }

	/// <summary>
	/// send message to a certain port-component
	/// </summary>
	/// <param name="message"></param>
	/// <param name="port"></param>
	/// <returns></returns>
	int Send(ControlMessage message, unsigned short port) {
        sockaddr_in client;
        client.sin_family = AF_INET;
        client.sin_addr.s_addr = inet_addr("127.0.0.1");
        client.sin_port = htons(port);
        int status = sendto(my_socket, (char*)&message, sizeof(ControlMessage), 0, (sockaddr*)&client, sizeof(sockaddr_in));
        if (status == -1)
            cout<<WSAGetLastError()<<endl;
        return( status!= SOCKET_ERROR);
	}

	/// <summary>
	/// get message from any component and return a struct of port and message
	/// </summary>
	/// <returns></returns>
	sendedMessage Get() {
        fflush(stdout);
        sockaddr_in client;
        int slen = sizeof(sockaddr_in);
        sendedMessage sm;
        ControlMessage message;
        int message_len;
        if (message_len = recvfrom(my_socket, (char*)&message,sizeof(message), 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
             cout << "problem with get message in socket, error code: " << WSAGetLastError() << endl;
        }
        sm.port = client.sin_port;
        sm.message = message;
        return sm;
	}

    ~UDPsocket(){
        closesocket(my_socket);
        WSACleanup();
    }
   
};

