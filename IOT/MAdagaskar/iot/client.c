/******************CLIENT SOCKET************************/

#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>  
#include <netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


/*Read and write operation BUFFER*/
char BUFFER[1024];


/*Buffer for read and write operation*/
#define BUFFER_SIZE 1024

/***Write Operation***/
/*PORT number of server is listening*/
#define PORT 4000  


/*Read and write operation BUFFER*/
char BUFFER[1024];


/*Error handler*/
void error(char *msg){

	error(msg);
	exit(1);
}


int main(int argc, char *argv[]){
	
/*Detailed Information about Socket Structure:Refer man 7 ip*/
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[BUFFER_SIZE];
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
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");


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

	
	
	 FILE *f;
    
    int words = 0;
    int c;
     f=fopen("iot.txt","r");
if(f==NULL){

printf("file not created\n");
exit(0);

}

       
    int ch ;
       while(ch != EOF)
      {
		
		fscanf(f , "%s" , BUFFER);
	
		write(sockfd,BUFFER,512);
		ch = fgetc(f);
      }
	printf(" Cheers !! The file was sent successfully\n");
    
    close(sockfd);
    return 0;

	

}
