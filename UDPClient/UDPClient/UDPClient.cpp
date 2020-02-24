#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
void main(int argc, char* argv[])
{
	WSADATA data;
	setlocale(LC_ALL, "Russian");
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Winsock doesn't work " << wsOk;
		return;
	}
	sockaddr_in server;
	server.sin_family = AF_INET; 
	server.sin_port = htons(54000); 
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); 
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	string s(argv[1]);
	cout << "Enter message: ";
	getline(cin, s);
	int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)& server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		cout << "Doesn't Work" << WSAGetLastError() << endl;
	}
	else  {
		cout << "Message received" << endl;
	}
	closesocket(out);
	WSACleanup();
}
