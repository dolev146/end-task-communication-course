#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief
 *
 *  gateway.c : Takes the name of a host on the command line and creates a datagram socket to that host
 *  (using port number P+1), it also creates another datagram socket where it can receive datagrams from any
 *  host on port number P; next, it enters an infinite loop in each iteration of which it receives a datagram
 * from port P, then samples a random number using ((float)random())/((float)RAND_MAX) - if the number obtained
 * is greater than 0.5, the datagram received is forwarded onto the outgoing socket to port P+1, otherwise the
 *  datagram is discarded and the process goes back to waiting for another incoming datagram. Note that this
 * gateway will simulate an unreliable network that loses datagrams with 50% probability. Note: in order to be
 * able to witness always the same behavior in the gateway, you should seed the random number generator before
 * you make any calls to random(), that is, call srandom(seed) first for some hardcoded value of seed.
 *
 * @param argc
 * @param argc
 * @return int
 */

int main(int argc, char *argv[])
{
    int socket_fd;
    int cc;
    socklen_t fsize;
    struct
    {
        char head;
        u_long body;
        char tail;
    } msgbuf;

    struct sockaddr_in s_in, from, send_out;
    bzero((char *)&s_in, sizeof(s_in));
    bzero((char *)&from, sizeof(from));

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // create socket for UDP connection with IPv4 protocol and UDP protocol
    //(SOCK_DGRAM) and no protocol (0) for default protocol (UDP) (IPv4) and return socket file descriptor
    // check that not failed to create socket
    if (socket_fd < 0)
    {
        perror("socket");
        exit(1);
    }
    // initialize socket address structure s_in with IP address of host and port number P
    s_in.sin_family = AF_INET;              // set family to internet (IPv4)
    s_in.sin_port = atoi(argv[2]); // set port number to struct (sin_port)
    s_in.sin_addr.s_addr = INADDR_ANY;      // set address to struct (sin_addr)

    // bind socket to address s_in
    send_out.sin_family = AF_INET;              // set family to internet (IPv4)
    send_out.sin_port = atoi(argv[3]); // set port number to struct (sin_port)
    send_out.sin_addr.s_addr = INADDR_ANY;      // set address to struct (sin_addr)
    // check that not failed to bind socket to port
    if (bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)) < 0)
    {
        perror("bind");
        exit(1);
    }

    srand(time(NULL)); // seed random number generator
    while (1)
    {
        fsize = sizeof(from);                                                                   // set size of struct (from)
        bzero((char *)&msgbuf, sizeof(msgbuf));                                                 // set all bytes of struct (msgbuf) to 0
        cc = recvfrom(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&from, &fsize); // receive datagram from socket
        if (cc < 0)                                                                             // check that not failed to receive datagram
        {
            perror("recvfrom");
            exit(1);
        }
        printf("Received datagram from %s:%d\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port)); // print address and port of datagram sender
        if (((float)random()) / ((float)RAND_MAX) > 0.5)                                          // check if random number is greater than 0.5
        {
            cc = sendto(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&send_out, sizeof(send_out)); // send datagram to socket
            if (cc < 0)                                                                                         // check that not failed to send datagram
            {
                perror("sendto");
                exit(1);
            }
        }
    }

    close(socket_fd);

    return 0;

}