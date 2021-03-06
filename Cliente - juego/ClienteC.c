// IPv4 AF_INET sockets:
#include <stdlib.h>
#include <pthread.h>
#include<stdio.h>
#include <string.h>
#include<winsock2.h>


#pragma comment(lib,"ws2_32.lib") //Winsock Library

char * leerTXT();
void escribirTXT(char cadena[]);
void escribirTXTInicial();
static void* sockets();
static void* juego();
int port[4] = {25556, 25557, 25558, 25559};


/**
 * Funcion principal que inicia el juego y la conexion por sockets en hilos separados 
*/
int main(int argc , char *argv[])
{
	
	pthread_t hilo1;
	pthread_t hilo2;

	pthread_create(&hilo1,NULL,&sockets,NULL);
	pthread_create(&hilo2,NULL,&juego,NULL);

	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);

}

/**
 * Funcion que se encarga de realizar la coneccion entre en cliente y el servidor, ademas de enviar y recibir los archivos
*/
static void* sockets(){
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	int recv_size;
  	struct hostent *Host;
	boolean concec;
	concec = TRUE;
	FILE *archivo;
    char linea[32];
    char *token;
	int indice = 0;
	
	printf("hola");
	escribirTXTInicial();
    while (concec == TRUE)
	{
		
			archivo = fopen("DatoE.txt","r");
			if (archivo == NULL){
				printf("\nError de apertura del archivo. \n\n");
			}
			else{
				fgets(linea, 32,(FILE*) archivo);
				/*token = strtok(linea, " ");
				token = strtok(NULL, " ");
				if(token != NULL){*/
					printf("\nInitialising Winsock...");
					if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
					{
						printf("Failed. Error Code : %d",WSAGetLastError());
						concec = FALSE;

					}
					
					printf("Initialised.\n");


					//Crea el socket
					if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
					{
						printf("Could not create socket : %d" , WSAGetLastError());
						concec = FALSE;
					}

					Host = gethostbyname ("localhost");

					printf("Socket created.\n");
					
					
					server.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
					server.sin_family = AF_INET;
					server.sin_port = htons(port[indice]);

					//Conecta con el servidor
					if (connect(s , (struct sockaddr *)&server , sizeof(server)) == -1)
					{
						puts("connect error");
						
						concec = FALSE;
						
					}
					
					puts("Connected");
					//Recibe la respuesta del servidor
					if((recv_size = recv(s , server_reply , sizeof(server_reply) , 0)) == SOCKET_ERROR)
					{
						puts("recv failed");
						//concec = FALSE;
					}
					
					puts("Reply received\n");
					//Adiciona un NULL al final del string
					puts(server_reply);
					escribirTXT(server_reply);
					
					//Envio de datos
					if( send(s , leerTXT(), strlen(leerTXT()) , 0) < 0)
					{
						puts("Send failed");
					}
					puts("Data Send\n");
					Sleep(0.05);
				//}
			}
			fclose(archivo);
		
	}
}

/**
 * Funcion encarda de llamar el ejecutable que inicia el juego
*/
static void* juego(){
	system("spaCE.exe");
}

/**
 * Funcion que permite leer un archivo txt para poder enviar su contenido al servidor
*/
char * leerTXT(){
	FILE *archivo;
	char caracter;
	static char data[10000];
	int i= 0;
	
	archivo = fopen("DatoE.txt","r");
	
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
		printf("datos observer %s",data);
		data[i] = '\n';

		return data;
}

/**
 * Funcion que permite escribir en un archivo txt para almacenar los datos que provienen del servidor
 * @param cadena Recibe como entrada la cadena de caracteres que se desea escribir en el archivo
*/
void escribirTXT(char cadena[]){
	FILE *fp;
 
 	fp = fopen ( "DatoR.txt", "w" ); //par??metro para escritura al final y para file tipo texto	

 	fputs(cadena,  fp);
 	
 	fclose ( fp );
}
/**
 * Funcion que permite escribir en un archivo txt para almacenar los datos que provienen del servidor
 * @param cadena Recibe como entrada la cadena de caracteres que se desea escribir en el archivo
*/
void escribirTXTInicial(){
	FILE *fp;
	
	char cadena[1500] = "";
	

    strcat(cadena, "JPosx: 463 JHP: 3\n");
    strcat(cadena, "PosX: 313 PosY: 52\n");
	strcat(cadena, "PosX: 393 PosY: 52\n");
	strcat(cadena, "PosX: 473 PosY: 52\n");
	strcat(cadena, "PosX: 553 PosY: 52\n");
	strcat(cadena, "PosX: 633 PosY: 52\n");
	strcat(cadena, "PosX: 713 PosY: 52\n");
	strcat(cadena, "PosX: 793 PosY: 52\n");
	strcat(cadena, "PosX: 873 PosY: 52\n");
	strcat(cadena, "PosX: 313 PosY: 102\n");
	strcat(cadena, "PosX: 393 PosY: 102\n");
	strcat(cadena, "PosX: 473 PosY: 102\n");
	strcat(cadena, "PosX: 553 PosY: 102\n");
	strcat(cadena, "PosX: 633 PosY: 102\n");
	strcat(cadena, "PosX: 713 PosY: 102\n");
	strcat(cadena, "PosX: 793 PosY: 102\n");
	strcat(cadena, "PosX: 873 PosY: 102\n");
	strcat(cadena, "PosX: 313 PosY: 152\n");
	strcat(cadena, "PosX: 393 PosY: 152\n");
	strcat(cadena, "PosX: 473 PosY: 152\n");
	strcat(cadena, "PosX: 553 PosY: 152\n");
	strcat(cadena, "PosX: 633 PosY: 152\n");
	strcat(cadena, "PosX: 713 PosY: 152\n");
	strcat(cadena, "PosX: 793 PosY: 152\n");
	strcat(cadena, "PosX: 873 PosY: 152\n");
	strcat(cadena, "PosX: 313 PosY: 202\n");
	strcat(cadena, "PosX: 393 PosY: 202\n");
	strcat(cadena, "PosX: 473 PosY: 202\n");
	strcat(cadena, "PosX: 553 PosY: 202\n");
	strcat(cadena, "PosX: 633 PosY: 202\n");
	strcat(cadena, "PosX: 713 PosY: 202\n");
	strcat(cadena, "PosX: 793 PosY: 202\n");
	strcat(cadena, "PosX: 873 PosY: 202\n");
	strcat(cadena, "PosX: 313 PosY: 252\n");
	strcat(cadena, "PosX: 393 PosY: 252\n");
	strcat(cadena, "PosX: -1 PosY: -1\n");
	strcat(cadena, "PosX: 553 PosY: 252\n");
	strcat(cadena, "PosX: -1 PosY: -1\n");
	strcat(cadena, "PosX: 713 PosY: 252\n");
	strcat(cadena, "PosX: 793 PosY: 252\n");
	strcat(cadena, "PosX: 873 PosY: 252\n");
	strcat(cadena, "HP: 3\n");
	strcat(cadena, "HP: 1\n");
	strcat(cadena, "HP: 3\n");
	strcat(cadena, "HP: 1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "ABalaPosx: -1 ABalaPosy: -1\n");
	strcat(cadena, "BalaPosx: -1 BalaPosy: -1\n");
	strcat(cadena, "BalaPosx: -1 BalaPosy: -1\n");
	strcat(cadena, "BalaPosx: -1 BalaPosy: -1\n");

 	fp = fopen ( "DatoE.txt", "w" ); //par??metro para escritura al final y para file tipo texto	

 	fputs(cadena,  fp);
 	
 	fclose ( fp );
}




