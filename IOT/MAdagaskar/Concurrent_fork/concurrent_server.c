/********************Concurrent Server*****************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
/*
 * socket header files\
 */

#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>         
#include<netinet/in.h>     /*bzero API:zero a byte string*/


/* Error Handler/routine*/
void error(char *msg){

	perror(msg);
	exit(1);
}

			/*main function*/

int main(int argc,char *argv[]){

/*master socket descriptor*/
	int sockfd; 
	
/*socket descriptor for accept*/
	int connfd;  


/*server port number and client address len declaration*/
	int portnumber,clilen; 


/*Buffer to send and receive the data*/
	char sendbuffer[1024];
	char recvbuffer[1024];


/*Fork system call return catcher*/
       pid_t cpid;	


/*Server/client Structure Declration*/
	struct sockaddr_in serv_addr,cli_addr;

	/*read bytes from server*/
	int readbytes;

/*Condition cheack for command line argument*/
	if(argc < 2){
	
		printf("Error !! No command line value entered");
		exit(1);
	}


/* Creation of master socket to bind,listen and accept system calls\
 * ->refer man socket(2) for details
 *   Param1: AF_INET - IPv4 INternetprotocols
 *   param2: SOCK_STREAM - TCP bases stream(two-way connection)
 *   param3: 0 protocol (decided by the kernel/system/OS) 
 */
	sockfd=socket(AF_INET,SOCK_STREAM,0);


/*Condition cheack for socket return type*/
	if(sockfd<0){
	
		perror("Socket is not needed");
		exit(1);
	}


/*Clear the structure buffer with bzero and memset*/
	bzero((char*)&serv_addr, sizeof(serv_addr));


/*port number -interger -atoi())
 * Entered from command line
 * ./filename <PORTNAME>:Getting as an String form
 */
	portnumber=atoi(argv[1]);


/*initialize the structure members*/
	serv_addr.sin_family=AF_INET;      //IPv4 Internet family


/*INADDR_ANY --> Binds to all available interfaces of host machine/
 * work station else specific interfaces can be initialized likee
 *Example::127.0.0.1
 *wifi interface-Example: "192.168.75.115"
 *Layman terminal: Client can connect t server with all interfaces
 *of server*/
	serv_addr.sin_addr.s_addr = INADDR_ANY;


/*htons Host to n/w byte order(short) network byte order:
 * BIGINDIAN**/
	serv_addr.sin_port = htons(portnumber);


/*Bind the socket with server address with bind server system call*/
	int ret=bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	if(ret <0){
	
		perror("Error in Binding!!");
		exit(1);
	}


/* Listen to maximum backlog connection -->
 * LISTEN syec call*/
	int backlog=5;
	int ret1=listen(sockfd,backlog);

	if(ret1 < 0){
		perror("Listen to failed to accept request");

	}
	clilen=sizeof(cli_addr);


/*ACCEPT system call: To fetch pending request from the queue*/
	connfd = accept(sockfd,(struct sockaddr *)&cli_addr, &clilen);
	if(connfd < 0){
	
		perror("Error in Accepting the request");
	}


/*Fork system call to create child process*/
	cpid=fork();
	if(cpid==0){
		while(1){
			
			bzero(&recvbuffer,sizeof(recvbuffer));
		
			
		/*Receive the data from client and print*/
			recv(connfd,recvbuffer,sizeof(recvbuffer),0);
			printf("Client Msg: %s\t",recvbuffer);
		}
	}
	
	if(cpid>0){
	
		while(1){

			bzero(&recvbuffer,sizeof(recvbuffer));
			

		/*send the data from the client*/
			printf("Enter the message:\n");
			fgets(sendbuffer,1024,stdin);
			send(connfd,sendbuffer,sizeof(sendbuffer)+1,0);
			printf("Msg sent successfully !!");
		}
	}

	close(sockfd);
}


