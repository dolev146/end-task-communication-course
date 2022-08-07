/**
 * @file sink.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 * sink.c : Is almost identical to recv_udp.c, that means, it creates a socket to receive datagrams
 *  from any host on port P+1, then enters an infinite loop where it receives a datagram and prints to the
 * screen the information of where the datagram came from (you can print the IP address in dotted-decimal notation)
 *  and what message it contains.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <sys/types.h>
#include <arpa/inet.h>

void printsin(struct sockaddr_in *s, char *str1, char *str2)
{
    printf("%s\n", str1);
    printf("%s ", str2);
    printf("ip= %s ", inet_ntoa(s->sin_addr));
    printf("port= %d", ntohs(s->sin_port));
    printf("\n");
}

int main(int argc, char *argv[])
{
    int socket_fd;
    socklen_t fsize;               // init socket_fd, cc, fsize
    struct sockaddr_in s_in, from; // init s_in, from
    struct
    {
        char head;
        u_long body;
        char tail;
    } msg; // init msg (struct)

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // create socket

    bzero((char *)&s_in, sizeof(s_in)); /* They say you must do this    */ // init s_in

    s_in.sin_family = (short)AF_INET;                        // set family to AF_INET
    s_in.sin_addr.s_addr = htonl(INADDR_ANY); /* WILDCARD */ // set IP to INADDR_ANY
    s_in.sin_port = atoi(argv[2]);                  // set port to 0x3333

    printsin(&s_in, "RECV_UDP", "Local socket is:");
    fflush(stdout); // flush stdout

    // check if bind was successful
    if (bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)) < 0) // bind socket to s_in
    {
        perror("bind");
        exit(1);
    }

    for (;;) // infinte loop (until ctrl-c)
    {
        /**
         * @brief recvfrom()
         * @param socket_fd
         * @param msg
         * @param sizeof(msg)
         * @param 0
         * @param (struct sockaddr *)&from
         * @param (socklen_t *)&fsize
         *
         * in this loop we are waiting for a message to be sent to our socket
         * and then we print it out
         */

        fsize = sizeof(from);
        int cc = recvfrom(socket_fd, &msg, sizeof(msg), 0, (struct sockaddr *)&from, &fsize);
        if (cc < 0)
        {
            perror("recvfrom");
            exit(1);
        }
        printsin(&from, "recv_udp: ", "Packet from:");
        printf("Got data ::%c%ld%c\n", msg.head, (long)ntohl(msg.body), msg.tail);
        fflush(stdout);
    }

    close(socket_fd);
    

    return 0;
}
