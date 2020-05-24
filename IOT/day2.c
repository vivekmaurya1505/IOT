#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<strings.h>
#include<netinet/in.h>
#include<arpa/inet.h>   //inet addr
#include<unistd.h>    // to read and write
#define BUFFER_SIZE 1024 //
#define PORT 4000
void error(char *msg){

  perror(msg);
  exit(1);


}

int main(){

int sockfd;
struct sockaddr_in serv_addr,cli_addr;
char buffer[BUFFER_SIZE];
/*detailed information about Socket Structure-Refer :man 7 ip*/
//creation of socket

sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0){
	error("socket creation failed");
	}
else{		
	printf("socket created successfully");
	}

//clear/flush the structure memory
bzero(&serv_addr,sizeof(serv_addr));

/*Assigning IP and PORT */

serv_addr.sin_family = AF_INET;


/*man 3 inet_addr 
 * inet_addr : conver IPV4 dotted decimal format  into binary (network byte order)*/

serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

serv_addr.sin_port = htons(PORT);

/*
 * connect the client socket to the server socket
 */

int retcon =connect(sockfd,(struct  sockaddr_in *)&serv_addr,sizeof(serv_addr));
if(retcon <0){
	error("connection to server Socket failed");
}
else{
	printf("Connected to server successfully\n");
}

while(1){
bzero(buffer,sizeof(buffer));
	/*
	 * Read the data of server and copy in the buffer*/
//	read(connfd,buffer,sizeof(buffer));
//	printf("Data from client : %s",buffer);
//	printf("Enter the msg to client \t");
	bzero(buffer,sizeof(buffer));

	printf("Enter the Msg: ");
/*
 * 
 */
	int buffer_count=0;
	while((buffer[buffer_count++]=getchar())!='\n');
	//write the data in buffer 
	write(sockfd,buffer,sizeof(buffer));
	bzero(buffer,sizeof(buffer));
	//Receive data in buffer from server
	read(sockfd,buffer,sizeof(buffer));
	print("Data from server : %s",buffer);
}
//close the socket file descriptor
close(sockfd);


}








