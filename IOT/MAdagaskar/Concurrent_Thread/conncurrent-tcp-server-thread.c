/*
Concurrent Server
Bi-Directional & Full Duplex chat application 
using threads

*/

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
#include <string.h>  //strcmp
#include<pthread.h>
int connfd; 
char sendbuffer[1024];
char recvbuffer[1024];
/*
Error Handler/routine
*/
void error(char *msg)
{
	perror(msg);
	exit(1);
}


void *read_op(void *ptr)
{
        //pthread_t thread1, thread2;

 while(1)
   {
	bzero(&recvbuffer, sizeof(recvbuffer));
	// Receive the data from client and print 
	recv(connfd,recvbuffer,sizeof(recvbuffer),0);
    	   printf("Client Msg: %s\t",recvbuffer);
   }
          
}
void *write_op(void *ptr)
{
        while(1)
  {
	bzero(&sendbuffer, sizeof(sendbuffer));
	// Send the data from from server to client 
        printf("Enter the message : ");	
	
	fgets(sendbuffer,1024,stdin);
	

send(connfd,sendbuffer,strlen(sendbuffer)+1,0);

//printf("Msg sent successfull");
  }
}


/* main function - driver code */
int main(int argc, char *argv[])
{
	/*
	master socket descriptor
	*/	
	int sockfd; 
	/*Socket descriptor for accept system 		call*/
	
/* server port number and client address len declaration */	
	int portnumber, clilen;  

/* buffer to send and Receive the data */	
	
/*-----------Thread Declarations---*/

pthread_t thread1, thread2;


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

int ret = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));


if (ret < 0)
{
	error("Error in bindind");
	exit(1);
}

/* listen to maximum backlog connections
	-> listen system call
*/
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
connfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if (connfd < 0 )
{
	error("error in Accepting the request");
}

/* Thread creation and join - main process to wait until they complete its execution */


int ret2 = pthread_create(&thread1,NULL,read_op,NULL);
printf("Return value from Thread 1 %d\n",ret1);
int ret3 = pthread_create(&thread2,NULL,write_op,NULL);
printf("Return value from Thread2 %d\n", ret2);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

//close(sockfd);
}




