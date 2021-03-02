# COSC 3342 Fall 2020 - Socket Project

This is my code for the socket project for Networking class.

======================================

Compile the server code:
> gcc -g -o socket project.c randperm.c

Compile the client code:
> gcc -o client client.c

Run the server code:
> ./socket (port number)

Run client code to connect
> ./client (ip addr of server) (port number)

### Basic Idea:
Client connects to the server over a socket connection. The client then sends the command "deal" to the server (currently done automatically). The server responds by sending an int array containing numbers 0-51 randomized, each representing a card in the deck. The client then parses the array and prints out the actual value of each card (ie: Four of Diamonds).