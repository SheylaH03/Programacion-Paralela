#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//Envia el usuario su nombre desde la linea de comandos
//  al servidor y recibe un saludo.
int main(int argc, char *argv[]){

int mi_socket = 0;
int puerto = 0;
int estado = 0;
char Usuario[70] = "";
char Contra[70] = "";
char Mensaje[250] = "";
struct hostent *hostinfo;
struct sockaddr_in dir;

if(argc != 5){
   printf("Use: %s <servidor> <puerto>  <valor1>  <valor2>\n", argv[0]);
   exit(1);

}//fin del if

//crear un  socket
mi_socket = socket(AF_INET, SOCK_STREAM, 0);

if(mi_socket == -1){
	printf("No es posible crear socket!!\n");
	exit(1);
}
else{

	printf("Socket creado\n");

}//fin del if

//Recupera el numero de puerto para escuchar
puerto = atoi(argv[2]);

//establece valores a la estructura de direccion
dir.sin_family = AF_INET;
//convertir las cadenas a numeros
hostinfo = gethostbyname(argv[1]);

if(hostinfo == NULL)
	return 1;

  dir.sin_addr = *((struct in_addr *) hostinfo->h_addr);
  dir.sin_port = htons(puerto);

//conectar la direccion y puerto a nuestro socket
estado = connect(mi_socket, (struct sockaddr *)&dir, sizeof(dir));


if(estado == 0){
	printf("Conexion establecida con exito!!!\n");
}else
{
	printf("No es posible conectar a la direccion!! %s\n", argv[1]);
	close(mi_socket);
	exit(1);
}//fin del if

//envia el mensaje al  servidor

estado = write(mi_socket, argv[3], sizeof(Usuario));

if(estado <= 0){
	printf("Error al enviar mensaje al servidor");
}

estado = write(mi_socket, argv[4], sizeof(Contra));

if(estado <= 0){
	printf("Error al enviar segundo mensaje al servidor");
}

//recibe mensaje del servidor
estado = read(mi_socket, &Mensaje, sizeof(Mensaje));

if(estado > 0){
	printf("%s \n", Mensaje);
}else
{
	printf("Error al recibir mensaje del servidor\n");
}//fin del if

close(mi_socket);

return 0;
}//fin del main|