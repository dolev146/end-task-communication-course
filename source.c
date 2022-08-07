#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * @brief
 * •	source.c :  Takes the name of a host on the command line, creates a datagram socket to that host
 *  (each student will be assigned their own port number P to use), then enters an infinite loop in each
 *  iteration of which it sends a datagram onto the socket carrying in its body an integer number, increments
 *  the integer, then sleeps for one second only to repeat the cycle upon waking up. Note that this program is
 * nearly identical to send_udp.c.
 *
 * @param argc
 * @param argc
 * @return int
 */

int main(int argc, char *argv[])
{
    int socket_fd;
    struct sockaddr_in dest;
    struct hostent *hostptr;
    struct
    {
        char head;
        u_long body;
        char tail;
    } msgbuf;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // create socket for UDP connection with IPv4 protocol and UDP protocol (SOCK_DGRAM) and no protocol (0) for default protocol (UDP) (IPv4) and return socket file descriptor
    // check that not failed to create socket
    if (socket_fd < 0)
    {
        perror("socket");
        exit(1);
    }
    bzero((char *)&dest, sizeof(dest)); // clear struct sockaddr_in dest (destination)
    hostptr = gethostbyname(argv[1]);   // get hostname from command line argument and store in hostptr (struct hostent)
    // check that not failed to get hostname
    if (hostptr == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
    dest.sin_family = (short)AF_INET;                                  // set family to internet (IPv4) (short)
    bcopy(hostptr->h_addr, (char *)&dest.sin_addr, hostptr->h_length); // set address from hostname to struct (sin_addr)
    // dest.sin_port = htons((u_short)0x3333);                            // set port number (0x3333) to struct (sin_port)
    dest.sin_port = atoi(argv[2]); // set port number (0x3333) to struct (sin_port)
    int datagram_msg = -1;         // -1 is a placeholder for the message
    while (1)                      // Loop forever until the user presses ctrl+c
    {
        datagram_msg++;                                // Increment the message number
        msgbuf.head = '<';                             // Set the message header
        msgbuf.body = htonl(datagram_msg);             // Set the message body
        msgbuf.tail = '>';                             // Set the message tail
        printf("Sending datagram %d\n", datagram_msg); // Print the message number
        // check that not failed to send message
        if (sendto(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest)) < 0)
        {
            perror("sendto");
            exit(1);
        }
        sleep(1); // Sleep for 1 second
    }

    return 0;
}