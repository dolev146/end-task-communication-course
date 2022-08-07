
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10
// #define IP_ADDRESS "127.0.0.1" // from the last part we put this in comment and resolve it with gethostbyname
#define PORT 9999

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in cli_name;
  int count;
  int value;
  char *hostname;
  char *hostaddr;
  struct addrinfo *res;
  struct sockaddr_in *saddr;
  printf("Client is alive and establishing socket connection.\n");
  printf("%d  %s\n", argc, argv[1]);
  if (argc != 2)
  {
    perror("Usage: hostnamelookup <hostname> error \n");
    exit(1);
  }

  hostname = argv[1]; // hostname is the first argument
  printf("Hostname is %s\n", hostname);

  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) // getaddrinfo is a function that returns a struct addrinfo* that
  // contains a linked list of struct addrinfo (from nslookup.c)
  {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("Error opening channel");
    close(sock);
    exit(1);
  }

  saddr = (struct sockaddr_in *)res->ai_addr; // get the address of the server socket address structure (from nslookup.c)
  hostaddr = inet_ntoa(saddr->sin_addr);      // get the IP address of the server (from nslookup.c)

  bzero(&cli_name, sizeof(cli_name));
  cli_name.sin_family = AF_INET;
  cli_name.sin_addr.s_addr = inet_addr(hostaddr); // set the IP address of the client (from nslookup.c)
  cli_name.sin_port = htons(PORT);

  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
  {
    perror("Error establishing communications");
    close(sock);
    exit(1);
  }

  for (count = 1; count <= SIM_LENGTH; count++)
  {
    read(sock, &value, 4);
    printf("Client has received %d from socket.\n", value);
  }

  printf("Exiting now.\n");

  close(sock);
  exit(0);
}
