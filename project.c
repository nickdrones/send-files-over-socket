#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void encryptFile()
{
    char *encryptCommand = "./run_des -e keyfile.key recv.txt encryptedfile.enc";
    system(encryptCommand);
}

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
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

void send_file(FILE *fp, int sockfd){
  int n;
  char data[1024] = {0};

  while(fgets(data, 1024, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("Error in sending file.");
      exit(1);
    }
    bzero(data, 1024);
  }
}


int main(int argc, char *argv[])
{
        int firstPort=atoi(argv[1]);

		/////////////////////////////////
		/// Set Up Socket
		/////////////////////////////////
        struct sockaddr_in serverParameters1;
        int addrlen1=sizeof(serverParameters1);
		
        serverParameters1.sin_family = AF_INET;
        serverParameters1.sin_addr.s_addr = INADDR_ANY;
        serverParameters1.sin_port = htons(firstPort);

        int socketState1=socket(AF_INET, SOCK_STREAM, 0);

        int bindState1=bind(socketState1, (struct sockaddr *)&serverParameters1, addrlen1);

        if(bindState1<0)
        {
            printf("Failed to bind Socket 1\n");
            exit(0);
        }
		/////////////////////////////////
		/// Socket Setup Complete
		/////////////////////////////////
		
		//Listen for incoming connection and accept connection
        int listenState1=listen(socketState1, 5);
        int acceptConnection1=accept(socketState1,(struct sockaddr *)&serverParameters1,(socklen_t*)&addrlen1);

        write_file(acceptConnection1);

        printf("Received file, encrypting now\n");

        encryptFile();

        printf("File encrypted, returning to client now\n");

        FILE *fileToSend;
        fileToSend = fopen("encryptedfile.enc", "r");

	    send_file(fileToSend, socketState1);

	    printf("Encrypted file sent, exiting program\n");
}