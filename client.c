#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void send_file(FILE *fp, int sockfd){
  int n;
  char data[1024] = {0};

  while(fgets(data, 1024, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, 1024);
  }
}

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recvEncrypted.enc";
  char buffer[1024];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, 1024, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 1024);
  }
  return;
}

int main(int argc, char *argv[])
{
	// ./client <ipaddr> <portnum>

	char *fileBuffer;
	
	char *IPaddr=argv[1];
	int portNum=atoi(argv[2]);
	
	struct sockaddr_in serverToConnect;
	
	int socketState=socket(AF_INET, SOCK_STREAM, 0);
	if(socketState<0)
    {
		printf("Failed to create socket, exiting...\n");
        exit(0);
    }
	
	serverToConnect.sin_family = AF_INET;
    serverToConnect.sin_port = htons(portNum);
	
	int inetAddr = inet_pton(AF_INET, IPaddr, &serverToConnect.sin_addr);
	if(inetAddr<0)
    {
		printf("Failed to init connection, exiting...\n");
        exit(0);
    }
	
	int connectToServer = connect(socketState,(struct sockaddr *)&serverToConnect, sizeof(serverToConnect));
	if(connectToServer<0)
    {
		printf("Failed to connect to server, exiting...\n");
        exit(0);
    }
	FILE *fileToSend;
    fileToSend = fopen("filetosendforencryption.txt", "r");

	send_file(fileToSend, socketState);
	printf("File sent\n");
	
	write_file(socketState);
	printf("Encrypted file received\n");
}