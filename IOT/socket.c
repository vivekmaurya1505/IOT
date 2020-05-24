/*n 
 *Header files
 */
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <strings.h>
#include <unistd.h>   
#include <stdlib.h>   //exit()
#include<netinet/in.h>//structure  member
/*
 *error handler/routine
 */
void error(char *msg){

	perror(msg);
	exit(1);
}
/*main function - driver code*/

int main(int argc,char *argv[]){
	
	/*master socket descripter*/
	int sockfd;

	
	/*Socket descriptor for accept System call*/
	int connfd;
	/*server port number and client address length declaration*/
	int portnumber,clilen;
	/*buffer to read and write data*/
	char buffer[1024];
	/*Server/client structure declaration*/
	struct sockaddr_in serv_addr,cli_addr;
	/*read byte from server*/
	int readbytes;
	/*condition check for command line arguments*/
	if(argc<2){
		
		printf("Error !! Enter port number");
		exit(1);
	
	}
/*Creation of Master Socket for bind(),Listen(),accept() system calls
 *-->refer man socket(2) for details
		
 		int socket(int domain, int type, int protocol);

 		1...AF_INET        IPv4 Internet protocols
	   	2...SOCK_STREAM    TCP based stream(based byte streams.)	
		3...	

*/

	sockfd=socket(AF_INET,SOCK_STREAM,0);
printf("1=%d",sockfd);
	/*condition check for socket return type*/
	if(sockfd<0){
		
		error("socket is not created");
		exit(2);
	}

	/*clear the structure buffer with either bzero or memset*/


	bzero((char*)&serv_addr,sizeof(serv_addr));

	/*port number - integer -atoi()
	 * Entered from commandline
	 * ./filename <portnumber>*/

	portnumber=atoi(argv[1]);
	/*initialize the structure members*/
	
	serv_addr.sin_family=AF_INET;//IPV4 interner family

	/*INADDR_ANY -bind to all the available interfaces of host machine/work
	 * station else specific interfaces can be initialized 
	 * like:
	 * localhost
	 * 127.0.0.1
	 * wifi - interface - eg-192.168.75.1
	 * layman termi:client can connect to server with all interfaces of server
	 * */

	serv_addr.sin_addr.s_addr=INADDR_ANY;
	/*
	 *htons - host to network byte order (short)
	 *network byte order -bigendian
	 *
	 * */
	
	serv_addr.sin_port=htons(portnumber);

	/*bind the socket with server address with bind system call
	 * */

	int ret=bind(sockfd, &serv_addr, sizeof(serv_addr));

	if(ret<0){
		
		error("Error in binding");
		exit(3);
	}


	/**listen to maximum backlog connections 
	 * --> listen system call
	 */
	int backlog =5;
	int ret1=listen(sockfd,backlog);
	if(ret1<0){
		
		error("error in listening:::listen failed to accept request");
		exit(4);
	
	}
	
	clilen=sizeof(cli_addr);

	/*Accept system call-to featch pending request from the queue*/

while(1){	
	connfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
printf("%d",connfd);

	if(connfd<0){
		
		error("error in accepting the request");
		exit(5);
	}

	/*clean the buffer using bzero*/
	

	bzero(buffer,sizeof(buffer));
	
	/*read the data from the server end*/

	readbytes=read(connfd,buffer,sizeof(buffer));
	
	if(readbytes<0){
	
		error("No data is read from the server");
	}

	printf("The msg received:%s\n",buffer);
	
	char successmsg[1024]="cheers !! received your msg";
	 
	int writebytes=write(connfd,successmsg,sizeof(successmsg));
	
	/*stdin can be used with write*/

	if(writebytes<0){
	
		error("Error in write");
	}

}
return 0;
}


