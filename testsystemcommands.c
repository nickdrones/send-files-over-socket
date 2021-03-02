#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{   
    char *encryptCommand = "./run_des -e keyfile.key filetoencrypt.txt encryptedfile.enc";
    char *decryptCommand = "./run_des -d keyfile.key encryptedfile.enc decryptedfile.txt";
    system(encryptCommand);
    printf("Encrypted File\n");
}