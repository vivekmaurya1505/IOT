/******************CLIENT SOCKET************************/

#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>  
#include <netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>





/*Buffer for read and write operation*/
#define BUFFER_SIZE 1024

/***Write Operation***/
/*PORT number of server is listening*/
#define PORT 4000  


/*Read and write operation BUFFER*/
char sendbuffer[1024];
char recvbuffer[1024];

/*Fork system call return catcher*/
       pid_t cpid;


/*Error handler*/
void error(char *msg){

	error(msg);
	exit(1);
}


int main(int argc, char *argv[]){
	
/*Detailed Information about Socket Structure:Refer man 7 ip*/
	struct sockaddr_in serv_addr,cli_addr;
	int sockfd;

/*Creation of socket*/
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
	
		perror("Socket creation failed\n");
	
	}
	else{
	
		perror("Socket Created Successfully\n");
	}


/*Clear/Flush the structure memory*/
	bzero(&serv_addr,sizeof(serv_addr));


/*Assigning the IP address and PORT*/
	serv_addr.sin_family = AF_INET;


/*Refer:
 * man 3 inet_addr
 * Convert IPv4 dotted decimal format into binary format*/
	serv_addr.sin_addr.s_addr=inet_addr("192.168.75.51");


/*Hard coded PORT assigned in MACROS*/
	serv_addr.sin_port=htons(PORT);


/*Connect the client socket to the server socket*/
	int retcon=connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	


	if(retcon <0){
	
		perror("Connection in server socket failed\n");
	}
	else{
	
		perror("Connected to the server successfully");
	}


	/*Fork system call to create child process*/
	cpid=fork();
	if(cpid>0){
	
		while(1){
			
			bzero(&recvbuffer,sizeof(recvbuffer));
		
			
		/*Receive the data from client and print*/
			recv(sockfd,recvbuffer,sizeof(recvbuffer),0);
			printf("Client Msg: %s\t",recvbuffer);
		}
	}
	if(cpid==0){
	
		while(1){

			bzero(&recvbuffer,sizeof(recvbuffer));
			

		/*send the data from the client*/
			printf("Enter the message:\n");
			fgets(sendbuffer,1024,stdin);
			send(sockfd,sendbuffer,sizeof(sendbuffer)+1,0);
			printf("Msg sent successfully !!");
		}
	}

	close(sockfd);

}
