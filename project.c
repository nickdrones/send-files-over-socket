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


void encryptFile()
{
    char *encryptCommand = "./run_des -e keyfile.key recv.txt encryptedfile.enc";
    system(encryptCommand);
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



      char buffer[1024];
      FILE *fp;
      read(acceptConnection1,buffer,1024);
      fp=fopen("recv.txt","w");
      fprintf(fp,"%s",buffer);
      fclose(fp);
      printf("the file was received successfully\n");

        encryptFile();

        printf("File encrypted\n");

      int read_fd;
      read_fd = open ("encryptedfile.enc", O_RDONLY);
      struct stat stat_buf;
      fstat(read_fd, &stat_buf);
      sendfile(acceptConnection1, read_fd, 0, stat_buf.st_size);

        return 0;

}