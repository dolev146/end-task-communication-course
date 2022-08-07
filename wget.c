
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define SIM_LENGTH 10
#define PORT 80

// from parsing
#include <stdlib.h>
#include <stdio.h>
#include "parseurl.h"

// from nslookup
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    // parsing
    url_data_t *url; // url_data_t is a struct that contains the parsed url

    if (argc != 2) // if there is no argument, print error and exit
    {
        fprintf(stderr, "Usage: %s url\n", argv[0]);
        exit(1);
    }

    url = malloc(sizeof(url_data_t)); // allocate memory for the url_data_t struct

    if (url == NULL) // if there is no memory, print error and exit
    {
        perror("Could not allocate space for url data structure");
        exit(1);
    }

    if (0 != parse_url(url, argv[1])) // parse the url and store the parsed data in the url_data_t struct
    {
        perror("Error: Could not parse URL\n");
        exit(1);
    }

    printf("URL: %s\n", url->url); // print the url
    printf("Protocol: %s\n", url->protocol); // print the protocol
    printf("Hostname: %s\n", url->hostname); // print the hostname
    printf("Port: %d\n", url->port); // print the port
    printf("Path: %s\n", url->path); // print the path
    // end parsing

    // nslookup
    struct addrinfo *res; // struct addrinfo is a struct that contains a linked list of struct addrinfo (from nslookup.c)
    char *hostname; // hostname is the first argument
    char *hostaddr; // hostaddr is the IP address of the server
    struct sockaddr_in *saddr; // saddr is the server socket address structure

    hostname = url->hostname; // hostname is the first argument

    if (0 != getaddrinfo(hostname, NULL, NULL, &res)) // getaddrinfo is a function that returns a struct addrinfo* that  contains a linked list of struct addrinfo (from nslookup.c)
    {
        fprintf(stderr, "Error in resolving hostname %s\n", hostname);
        exit(1);
    }

    saddr = (struct sockaddr_in *)res->ai_addr; // get the address of the server socket address structure (from nslookup.c)
    hostaddr = inet_ntoa(saddr->sin_addr);     // get the IP address of the server (from nslookup.c)

    printf("Address for %s is %s\n", hostname, hostaddr); // print the IP address of the server
    // end nslookup 

    // net_client
    int sock;                    // socket descriptor
    struct sockaddr_in cli_name; // client socket address structure

    printf("Client is alive and establishing socket connection.\n"); // print message

    sock = socket(AF_INET, SOCK_STREAM, 0); // create a socket (from net_client.c)
    if (sock < 0) // if there is an error, print error and exit
    {
        perror("Error in creating socket");
        exit(1);
    }

    bzero(&cli_name, sizeof(cli_name)); // set the client socket address structure to 0 (from net_client.c)
    cli_name.sin_family = AF_INET; // set the family to AF_INET (from net_client.c)
    // cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    cli_name.sin_addr.s_addr = inet_addr(hostaddr); // set the IP address of the server (from net_client.c)
    cli_name.sin_port = htons(url->port); // set the port of the server (from net_client.c)

    if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0) // connect to the server (from net_client.c)
    {
        perror("Error establishing communications");
        close(sock);
        exit(1);
    }

    // make a string to send to the server
    char *send_string = malloc(sizeof(char) * (strlen(hostname) + SIM_LENGTH)); // allocate memory for the string
    if (strlen(url->path) > 0) // send the request , check if we have a path or not
    {
        sprintf(send_string, "GET /%s  HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", url->path, hostname); // if we have a path, send the request
    }
    else
    {
        sprintf(send_string, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", hostname); // if we don't have a path, send the request
    }

    // const char *request = "GET / HTTP/1.0\r\nHost: {hostaddr}\r\nConnection: close\r\n\r\n";
    int n;
    printf("Sending request to server.\n%s\n", send_string); // print the request
    n = write(sock, send_string, strlen(send_string)); // send the request to the server (from net_client.c)
    if (n < 0) // if there is an error , print error
    {
        perror("Error writing to socket");
        close(sock);
        exit(1);
    }
    char buffer[4096]; // buffer to store the response from the server

    while (1) // 
    {
        bzero(buffer, 4096); // set the buffer to 0

        n = recv(sock, buffer, 4095, 0); // receive the response from the server (from net_client.c)
        if (n < 0) //  if there is an error print error
        {
            printf("ERROR reading from socket\n");
            break;
        } 
        if (n == 0) // if there is no response , break
        {
            printf("Server closed the connection\n");
            break;
        }
        printf("%d\n", n);
        printf("%s\n", buffer);
    }
    printf("Exiting now.\n"); // print message
    close(sock); // close the socket
    free_url_data(url); // free the url_data_t struct
    free(url); // free the url_data_t struct
    free(send_string); // free the send_string
    exit(0); // exit

    // end net_client
}