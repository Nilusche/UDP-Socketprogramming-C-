#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")


using namespace std;

void main(int argc, char* argv[]) 
{

	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	// Start WinSock
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		// Not ok! Get out quickly
		cout << "Can't start Winsock! " << wsOk;
		return;
	}

	sockaddr_in server;
	server.sin_family = AF_INET; 
	server.sin_port = htons(54000); // Little to big endian conversion
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	// Write out to that socket
	std::cout << "Send message to Server:\n\n";
	while (true) {
		string s("Input message");
		std::getline(std::cin, s);
		int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));

		if (sendOk == SOCKET_ERROR)
		{
			cout << "That didn't work! " << WSAGetLastError() << endl;
		}
	}
	

	// Close the socket
	closesocket(out);

	// Close down Winsock
	WSACleanup();
}