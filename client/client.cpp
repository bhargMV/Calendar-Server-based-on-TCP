#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

using namespace std;

void error(const char *msg);


int main(int argc, char *argv[])
{
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;	
	int sockfd, n;	
	int portno = atoi(argv[2]);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("error while opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"no such host exists \n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("error!! in connecting");

	
	for(int k=0;k<10;k++)
	{
		sleep(1);
		strcpy(buffer,"vmourya add 1128 1128 1321 ab");
		printf("%s\n",buffer);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("error!!! writing to socket");

		bzero(buffer,256);
		n = read(sockfd,buffer,256);
		if (n < 0) 
			error("error!! reading from socket");
		printf("%s",buffer);
	}
	close(sockfd);
	return 0;
}

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
