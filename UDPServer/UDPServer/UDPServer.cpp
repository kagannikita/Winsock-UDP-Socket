#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
void main()
{
	setlocale(LC_ALL, "Russian");
	struct timeval tv;
	fd_set fd;
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Winsock doesn't work" << wsOk;
		return;
	}

	cout << "Server open 5 seconds" << endl;
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000);
	if (bind(in, (sockaddr*)& serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can not bind socket" << WSAGetLastError() << endl;
		return;
	}
	sockaddr_in client;
	int clientLength = sizeof(client);
	char buf[1024];
	while (true)
	{
		FD_ZERO(&fd);
		FD_SET(in, &fd);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		if (select(0, &fd, NULL, NULL, &tv) > 0)
		{
			ZeroMemory(&client, clientLength);
			ZeroMemory(buf, 1024);
			int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)& client, &clientLength);
			if (bytesIn == SOCKET_ERROR)
			{
				cout << "Error" << WSAGetLastError() << endl;
				continue;
			}
			char clientIp[256];
			ZeroMemory(clientIp, 256);
			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
			cout << "Message received from" << clientIp << " : " << buf << endl;
		}
		else {
			cout << "Timeout" << endl;
			closesocket(in);
			WSACleanup();
			//Sleep(13000);
			main();

		}

	}
}