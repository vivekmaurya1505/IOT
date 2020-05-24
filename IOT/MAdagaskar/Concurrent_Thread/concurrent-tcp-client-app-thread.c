#include <stdio.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <netinet/in.h>  //Structure
#include <arpa/inet.h>  //inet_addr
#include <unistd.h> // read and write
#include <stdlib.h> //exit
#include <strings.h>  //bzero
#include <string.h> 
#include<pthread.h>
#define BUFFER_SIZE 1024  //buffer for read and write operations
#define PORT 4000   //port number of SERVER, is listening
char sendbuffer[1024];
char recvbuffer[1024];
int sockfd;
/*-----------fork system call return type---*/



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
	recv(sockfd,recvbuffer,sizeof(recvbuffer),0);
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
	

send(sockfd,sendbuffer,strlen(sendbuffer)+1,0);

//printf("Msg sent successfull");
  }
}


int main(int argc, char *argv[])
{
	//int sockfd;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE];
	pthread_t thread1, thread2;
	/*
	detailed information about
	Socket Structure - Refer:
	man 7 ip
	*/
	//Creation of Socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
	error("Socket creation failed");
}
else
{
	printf("socket Created Successfully\n");
}

//clear/flush the strucrure memory
bzero(&serv_addr, sizeof(serv_addr));

/*Assigning IP address and PORT */
serv_addr.sin_family = AF_INET;
/*
man 3 inet_addr
inet_addr : converts IPV4 dotted decimal format
into binary (network byte order)
*/

serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

serv_addr.sin_port = htons(PORT);

/*
connect the client socket to the server Socket
*/

int retcon = connect(sockfd, (struct sockaddr*)
&serv_addr, sizeof(serv_addr));
if(retcon < 0 )
{
	error("Connection to server Socket Failed");
}
else
{
	printf("Connected to Server successfully \n");
}

/* fork system call to create child process */

int ret1 = pthread_create(&thread1,NULL,write_op,NULL);
printf("Return value from Thread 1 %d\n",ret1);
int ret2 = pthread_create(&thread2,NULL,read_op,NULL);
printf("Return value from Thread2 %d\n", ret2);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);




//close the socket file descriptor
//close(sockfd);
}




