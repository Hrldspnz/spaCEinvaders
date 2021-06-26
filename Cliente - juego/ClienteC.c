// IPv4 AF_INET sockets:
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include<winsock2.h>

#define PORT 25556



#pragma comment(lib,"ws2_32.lib") //Winsock Library

char * leerTXT();
void escribirTXT(char cadena[]);

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	int recv_size;
  struct hostent *Host;


	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

  	Host = gethostbyname ("localhost");

	printf("Socket created.\n");
	
	
	server.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) == -1)
	{
		puts("connect error");
		return -1;
	}
	
	puts("Connected");
  	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , sizeof(server_reply) , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	
	puts("Reply received\n");
	//Add a NULL terminating character to make it a proper string before printing
	puts(server_reply);
  	escribirTXT(server_reply);
	
	//Send some data
	//message = "Hola dfdsf fd fdsfdsf sdf dsf dsfdsf dsf dsf\n";
	if( send(s , leerTXT(), strlen(leerTXT()) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	


	return 0;
}

char * leerTXT(){
	FILE *archivo;
	char caracter;
	static char data[10000];
	int i= 0;
	
	archivo = fopen("DatoR.txt","r");
	
	if (archivo == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
            while((caracter = fgetc(archivo)) != EOF)
	    {
		data[i] = caracter;
		i++;
	    }
        }

        fclose(archivo);

		data[i] = '\n';

		return data;

		
}

void escribirTXT(char cadena[]){
	FILE *fp;
 
 		
 	fp = fopen ( "DatoE.txt", "w" ); //parámetro para escritura al final y para file tipo texto
 	
 	printf("\nIntroduce un texto al DatoE: ");

 	fwrite(cadena, sizeof(char), strlen(cadena), fp );
 	
 	fclose ( fp );
}




