#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SIM_LENGTH 10
#define PORT 9999

int main(void)
{
  int sock;                     // socket descriptor
  int connect_sock;             // socket descriptor for the connection
  struct sockaddr_in serv_name; // server socket address structure
  socklen_t len;                // length of the socket address structure
  int count;                    // number of bytes received

  sock = socket(AF_INET, SOCK_STREAM, 0); // create a socket
                                          // check if the socket is valid
  if (sock < 0)
  {
    perror("Error opening channel");
    exit(1);
  }
  // initialize the server socket address structure
  bzero(&serv_name, sizeof(serv_name)); // clear the structure
  serv_name.sin_family = AF_INET;       // set the family to Internet
  serv_name.sin_port = htons(PORT);     // set the port number

  // check if the bind is successful
  if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0) // bind the socket to the server address
  {
    perror("Error on binding");
    exit(1);
  }

  // listen for connections
  if (listen(sock, 1) < 0) // listen for connections on the socket
  {
    perror("Error on listening");
    exit(1);
  }

  len = sizeof(serv_name); // get the length of the socket address structure

  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len); // accept a connection on the socket
                                                                    // check if the connection is valid
  if (connect_sock < 0)
  {
    perror("Error on accepting");
    exit(1);
  }
  for (count = 1; count <= SIM_LENGTH; count++) // loop to send the data
  {
    write(connect_sock, &count, 4);                      // send the data
    printf("Server has written %d to socket.\n", count); // print the data
  }

  close(connect_sock); // close the connection
  close(sock);         // close the socket
}
