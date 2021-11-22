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
WSADATA wsaData; // Відомості щодо реалізації 
// Ініціалізація Winsock 
if (WSAStartup(WINSOCK_VERSION, &wsaData) != 
NO_ERROR) { 
printf("Error at WSAStartup()\n"); 
} else { 
// Створення SOCKET для прослуховування 
// вхідних запитів на під’єднання 
ListenSocket = socket(AF_INET, DEFAULT_PROTO, 
IPPROTO_TCP); 
if (ListenSocket == INVALID_SOCKET) { 
printf("Error at socket(): %ld\n", 
WSAGetLastError()); 
WSACleanup(); 
return 1;} 
// Структура sockaddr_in, що описує параметри 
// обмежень під'єднань: 
// - множина дозволених протоколів; 
service.sin_family = AF_INET; 
// - множина IP адрес; 
// (будь-яка IP адреса) 
service.sin_addr.s_addr = INADDR_ANY; 
// - номер порт для під'єднання до сокету. 
service.sin_port = htons(DEFAULT_PORT); 
// зв'язування сокету з локальною адресою 
if (bind( ListenSocket, (SOCKADDR*) &service, 
sizeof(service)) == SOCKET_ERROR) { 
printf("bind() failed.\n"); 
closesocket(ListenSocket); 
return 1;} 
// Прослуховування вхідних запитів на 
// під'єднання до створеного сокету 
if (listen( ListenSocket, 1 ) == 
INVALID_SOCKET) { 
printf("Error listening on socket.\n"); 
} else { 
printf("Listening on socket...\n"); 
// Створення сокету для прийому запитів 
printf("Waiting for client connections.\n"); 
AcceptSocket = accept( ListenSocket, 
(LPSOCKADDR)&socketclientaddr, 
(LPINT) &length); 
if(AcceptSocket != INVALID_SOCKET) { 
// Надсилання запрошення клієнту 
send(AcceptSocket,senddata, 
sizeof(senddata),0); 
printf("Client to accept.\n"); 
printf("Received data:\n"); 
do{ 
// Приймання даних від клієнта поки 
// він не від'єднається 
retval=recv(AcceptSocket, Buffer, 
sizeof(Buffer), 0); 
// Перевірка розриву з'єднання 
if(!retval) break; 
// Виведення до екрану отриманих даних 
for(i=0;i<retval;i++) 
printf("%c",Buffer[i]); 
}while(Buffer[0]!='Q'); 
// Припинення обміну 
if (!retval) 
printf("\nConnection is closed.\n"); 
else 
printf("\nClient disconnected.\n"); 
closesocket(AcceptSocket);} 
closesocket(ListenSocket);} 
WSACleanup();} 
return 0;} 
