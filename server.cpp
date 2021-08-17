#include <iostream>
#include <WS2tcpip.h>


#pragma comment (lib, "ws2_32.lib")

using namespace std;


void main()
{

	WSADATA data;

	WORD version = MAKEWORD(2, 2);

	// Start WinSock
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		
		cout << "Can't start Winsock! " << wsOk;
		return;
	}

	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

	
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET; 
	serverHint.sin_port = htons(54000); 

	// bind the socket to the IP and port
	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in client; 
	int clientLength = sizeof(client); 

	char buf[1024];

	// Enter a loop
	while (true)
	{
		ZeroMemory(&client, clientLength); 
		ZeroMemory(buf, 1024); 


		int bytesIn = recvfrom(in,(char*)buf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		
		
		char clientIp[256]; 
		ZeroMemory(clientIp, 256); 


		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);


		cout << "Message recv from " << clientIp << " : " << buf << endl;
	}

	// Close socket
	closesocket(in);

	// Shutdown winsock
	WSACleanup();
}

