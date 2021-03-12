#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>

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


  int read_fd;
  read_fd = open ("filetosendforencryption.txt", O_RDONLY);
  struct stat stat_buf;
  fstat(read_fd, &stat_buf);
  sendfile(socketState, read_fd, 0, stat_buf.st_size);
        printf("File sent to server successfully\n");



 char buffer[1024];
      FILE *fp;
      read(socketState,buffer,1024);
      fp=fopen("recveived_file.enc","w");
      fprintf(fp,"%s",buffer);
      fclose(fp);
      printf("Received encrypted file from server, exiting...\n");

return 0;
}