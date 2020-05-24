#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
/*
 * socket header files\
 */

#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>         /*bzero API:zero a byte string*/
#include<netinet/in.h>


/* Error Handler/routine*/
void error(char *msg){

	perror(msg);
	exit(1);
}

			/*main function*/

int main(int argc,char *argv[]){

/*master socket descriptor*/
	int sockid; 
	
/*socket descriptor for accept*/
	int connfd;  
	
/*server port number and client address len declaration*/
	int portnumber,clilen; 
      	
	/*Buffer to read and write the data*/
	char buffer[1024];


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
	sockid=socket(AF_INET,SOCK_STREAM,0);


/*Condition cheack for socket return type*/
	if(sockid<0){
	
		error("Socket is not needed");
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
	int ret=bind(sockid,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	if(ret <0){
	
		error("Error in Binding!!\n");
		exit(1);
	}


/* Listen to maximum backlog connection -->
 * LISTEN syec call*/
	int backlog=5;
	int ret1=listen(sockid,backlog);

	if(ret1 < 0){
		error("Listen to failed to accept request\n");

	}
	clilen=sizeof(cli_addr);


/*ACCEPT system call: To fetch pending request from the queue*/
	connfd = accept(sockid,(struct sockaddr *)&cli_addr, &clilen);
	if(connfd < 0){
	
		error("Error in Accepting the request\n");
	}
	
	bzero(buffer,sizeof(buffer));
while(1){
	readbytes=read(connfd,buffer,sizeof(buffer));

	if(readbytes<0){
		error("Error in reading the bytes");
	}


	printf("Message is received:%s\n",buffer);
	//char successmsg[1024]="Yes, treceived";
	int writebytes;
	int buffer_count =0;
                while((buffer[buffer_count++]=getchar())!='\n');
	{	
	writebytes=write(connfd,buffer,sizeof(buffer));
	}
	if(writebytes<0){
		error("Error in writing\n");
	}
}
	return 0;
}


