#include "calendar.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno,n;
	char buffer[1000];
	socklen_t clilen;	
	struct sockaddr_in serv_addr, cli_addr;
	 
	if (argc < 2)
	{
		fprintf(stderr,"error!!!  port number not given\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) 
		error("cannot open the socket!!!");
		
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("Unable to bind!!");
		
	while(1)
	{
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
				 
				
		if (newsockfd < 0) 
			error("unable to accept!!");

		bzero(buffer,1000);
		n = read(newsockfd,buffer,1000);
		
		while(n !=0 )
		{
			if (n < 0) 
				error("Unable to read from socket");

			char* token = strtok(buffer,"\n");
			string to_send="";
			vector<string> input_data;
					
			if(token != NULL)
			{
				do
				{
					input_data.push_back(token);
				}while( (token = strtok(NULL,"\n")) );
			}
			else input_data.push_back(buffer);

			for (unsigned int i=0;i<input_data.size();i++){	
				to_send += maintain_calendar(input_data[i]) + "\n";
			}
			n = write(newsockfd,to_send.c_str(),to_send.size());
			if (n < 0) error("ERROR writing to socket");

			bzero(buffer,1000);
			n = read(newsockfd,buffer,1000);
		}
		close(newsockfd);
	}
	close(sockfd);
	return 0; 
}

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
