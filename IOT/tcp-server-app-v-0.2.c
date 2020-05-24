#include <stdio.h>
/*
Socket Header files
*/
#include <sys/types.h>          
#include <sys/socket.h>
#include <strings.h>		//bzero API(s)
#include <unistd.h>		//read system call
#include <stdlib.h>	//exit
#include <netinet/in.h>	//structure member

/*
Error Handler/routine
*/
void error(char *msg)
{
	perror(msg);
	exit(1);
}

/* main function - driver code */
int main(int argc, char *argv[])
{
//printf("hello\n");

	/*
	master socket descriptor
	*/	
	int sockfd; 
	/*Socket descriptor for accept system 		call*/
	int connfd; 
/* server port number and client address len declaration */	
	int portnumber, clilen;  
	/* buffer to read and write the data */		
	char buffer[1024];
/* server/client structure declaration */
	struct sockaddr_in serv_addr, cli_addr;
/* read bytes from server */	
	int readbytes;


/* condition check for commandline argument*/
	if (argc < 2)
	{
		printf("Error !! Enter Port Number\n");
		exit(1);
	}

/* Creation of Master Socket for bind, listen and accept system calls
-> refer man socket(2) for details
AF_INET - IPv4 Internetprotocols         
SOCK_STREAM - TCP based stream 
0 - protcol (decided by system/kernel/OS)
 */

	printf("socket\n");

sockfd = socket(AF_INET,SOCK_STREAM, 0);
/* condition check for socket return type*/
if(sockfd < 0)
{
	error("Socket is not created");
	exit(1);
}

/* clear the structure buffer
with - 
either bzero or memset
*/
bzero((char *)&serv_addr, sizeof(serv_addr));
/*
port number - integer - atoi())
entred from command line
./filename <portnumber>
*/
portnumber = atoi(argv[1]);

/*
Initialize the sturucture members
*/

serv_addr.sin_family = AF_INET; //IPV4 Internet family


/*
INADDR_ANY - binds to all the available
interfaces of host machine/work station
else specific interfaces can be initialized
like :
localhost
127.0.0.1
Wifi - interface - eg. "192.168.75.1"
layman termi: client can connect to server
with all interfaces of server
*/
serv_addr.sin_addr.s_addr = INADDR_ANY;
/* htons - host to network byte order(short)
	network byte order - BigEndian
*/
serv_addr.sin_port = htons(portnumber);
/* bind the socket with server address
with bind system call
*/
printf("bind\n");

int ret = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));


if (ret < 0)
{
	error("Error in bindind");
	exit(1);
}

/* listen to maximum backlog connections
	-> listen system call
*/printf("listen\n");

int backlog = 5;
int ret1 = listen(sockfd, backlog);
if(ret1 < 0)
{
	error("listen failed to accept requests");
}
clilen = sizeof(cli_addr);
/* Accept system call - 
to fetch pending requests from the queue
*/
printf("before accept\n");
connfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
printf("connfd%d\n",connfd);
if (connfd < 0 )
{
	error("error in Accepting the request");
}
connfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
printf("connfd%d\n",connfd);
if (connfd < 0 )
{
        error("error in Accepting the request");
}

printf("before while\n");
while(1)
{
 bzero(buffer, sizeof(buffer));	
 /*
Read the data of server and 
copy in to buffer
*/
 printf("before read\n");
 read(connfd, buffer, sizeof(buffer));
 printf(" Data from client: %s ", buffer);
 printf("Enter the msg. to client\t");
 bzero(buffer, sizeof(buffer));	

 int buffer_count = 0;
 /*
  write data in buffer using getchar
*/

 while((buffer[buffer_count++] =getchar()) != '\n');
 // send the data to client
 write(connfd, buffer, sizeof(buffer));
}

close(sockfd);

}




