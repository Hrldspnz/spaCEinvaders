#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/un.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define PORT 25556


int Abre_Conexion_Inet ();

int Lee_Socket (int fd, char *Datos, int Longitud);

int Escribe_Socket (int fd, char *Datos, int Longitud);

char * leerTXT();

void escribirTXT(char cadena[]);

int main ()
{

	int Socket_Con_Servidor;
   int Longitud_Cadena = 0;
   int Aux;
	char Cadena[100000];

    Socket_Con_Servidor = Abre_Conexion_Inet ();

	printf ("Dato: %d\n", Socket_Con_Servidor);

	if (Socket_Con_Servidor == -1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
	}else{

    Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
   Longitud_Cadena = ntohl (Aux);

   /* Se lee la cadena de la longitud indicada */
   Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente C: Recibido %s\n", Cadena);

	escribirTXT(Cadena);
   
	/*
    * Se va a enviar una cadena de 6 caracteres, incluido el \0. Previamente se
    * envia un entero con el 6.
	*/
	strcpy (Cadena, leerTXT());
   Longitud_Cadena = 10000;

   /* Antes de enviar el entero hay que transformalo a formato red */
   Aux = htonl (Longitud_Cadena);
   
   Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));

   /* Se env�a la cadena */
	Escribe_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente C: Enviado %s\n", Cadena);

	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);
	}


}

/**
 * Función para crear la conexión con el servidor con la dirección y el puerto
 * */

int Abre_Conexion_Inet ()
{
	struct sockaddr_in Direccion;
	struct hostent *Host;
	int Descriptor;

	Host = gethostbyname ("localhost");

	Descriptor = socket(AF_INET, SOCK_STREAM, 0);


	if (Host == NULL)
		return -1;

	Direccion.sin_family = AF_INET;
	Direccion.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
	Direccion.sin_port = htons(PORT);
	
	if (Descriptor == -1){
		return -1;}


	if (connect (Descriptor, (struct sockaddr *)&Direccion, sizeof(Direccion)) == -1)
	{
		return -1;
	}

	return Descriptor;
}

/**
 * Función para leer los datos enviados por el servidor
 * @param fd socket
 * @param Datos char para almacenar los datos recividos
 * @param Longitud Tamaño de los datos recividos
 * */

int Lee_Socket (int fd, char *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/* 
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{
				
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}

/**
 * Función para enviar los datos al servidor
 * @param fd socket a enviar los datos
 * @param Datos Char de los datos a enviar al servidor
 * @param Longitud Tamaño de los datos a enviar
 * */

int Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}

/**
 * Función para leer un txt
 * 
 * */

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


		return data;

		
}

/**
 * Escribir en un txt para la comunicación de datos
 * 
 * @param cadena Cadena a escribir en el documento
 * 
 * */

void escribirTXT(char cadena[]){
	FILE *fp;
 
 		
 	fp = fopen ( "DatoR.txt", "a+t" ); //parámetro para escritura al final y para file tipo texto
 	
 	printf("\nIntroduce un texto al DatoE: ");

 	fwrite(cadena, sizeof(char), strlen(cadena), fp );
 	
 	fclose ( fp );
}