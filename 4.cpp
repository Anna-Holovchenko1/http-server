#include "stdafx.h" 
#include "windows.h" 
#include "winsock.h" 
#pragma comment(lib, "ws2_32.lib") 
#define DEFAULT_PORT    5001 
#define DEFAULT_PROTO    SOCK_STREAM 
#define DEFAULT_BUFFER_LEN 4096 
#define WINSOCK_VERSION   0x0101 
char Buffer[DEFAULT_BUFFER_LEN]={0}; 
int main(int argc, char* argv[]) 
{int retval=0, i=0; 
sockaddr_in service; 
SOCKET ListenSocket=INVALID_SOCKET; 
SOCKET AcceptSocket=INVALID_SOCKET; 
SOCKADDR_IN socketclientaddr; 
int length=sizeof(SOCKADDR); 
char senddata[]="Welcome to my server!\r\n"; 
WSADATA wsaData; // ³������ ���� ��������� 
// ����������� Winsock 
if (WSAStartup(WINSOCK_VERSION, &wsaData) != 
NO_ERROR) { 
printf("Error at WSAStartup()\n"); 
} else { 
// ��������� SOCKET ��� ��������������� 
// ������� ������ �� �䒺������ 
ListenSocket = socket(AF_INET, DEFAULT_PROTO, 
IPPROTO_TCP); 
if (ListenSocket == INVALID_SOCKET) { 
printf("Error at socket(): %ld\n", 
WSAGetLastError()); 
WSACleanup(); 
return 1;} 
// ��������� sockaddr_in, �� ����� ��������� 
// �������� ��'������: 
// - ������� ���������� ���������; 
service.sin_family = AF_INET; 
// - ������� IP �����; 
// (����-��� IP ������) 
service.sin_addr.s_addr = INADDR_ANY; 
// - ����� ���� ��� ��'������� �� ������. 
service.sin_port = htons(DEFAULT_PORT); 
// ��'�������� ������ � ��������� ������� 
if (bind( ListenSocket, (SOCKADDR*) &service, 
sizeof(service)) == SOCKET_ERROR) { 
printf("bind() failed.\n"); 
closesocket(ListenSocket); 
return 1;} 
// ��������������� ������� ������ �� 
// ��'������� �� ���������� ������ 
if (listen( ListenSocket, 1 ) == 
INVALID_SOCKET) { 
printf("Error listening on socket.\n"); 
} else { 
printf("Listening on socket...\n"); 
// ��������� ������ ��� ������� ������ 
printf("Waiting for client connections.\n"); 
AcceptSocket = accept( ListenSocket, 
(LPSOCKADDR)&socketclientaddr, 
(LPINT) &length); 
if(AcceptSocket != INVALID_SOCKET) { 
// ���������� ���������� �볺��� 
send(AcceptSocket,senddata, 
sizeof(senddata),0); 
printf("Client to accept.\n"); 
printf("Received data:\n"); 
do{ 
// ��������� ����� �� �볺��� ���� 
// �� �� ��'�������� 
retval=recv(AcceptSocket, Buffer, 
sizeof(Buffer), 0); 
// �������� ������� �'������� 
if(!retval) break; 
// ��������� �� ������ ��������� ����� 
for(i=0;i<retval;i++) 
printf("%c",Buffer[i]); 
}while(Buffer[0]!='Q'); 
// ���������� ����� 
if (!retval) 
printf("\nConnection is closed.\n"); 
else 
printf("\nClient disconnected.\n"); 
closesocket(AcceptSocket);} 
closesocket(ListenSocket);} 
WSACleanup();} 
return 0;} 
