#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

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

  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);                         // create socket for UDP connection with IPv4 protocol and UDP protocol (SOCK_DGRAM) and no protocol (0) for default protocol (UDP) (IPv4) and return socket file descriptor
  bzero((char *)&dest, sizeof(dest)); /* They say you must do this */ // clear struct sockaddr_in dest (destination)
  hostptr = gethostbyname(argv[1]);                                   // get hostname from command line argument and store in hostptr (struct hostent)
  dest.sin_family = (short)AF_INET;                                   // set family to internet (IPv4) (short)
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr, hostptr->h_length);  // set address from hostname to struct (sin_addr)
  dest.sin_port = htons((u_short)0x3333);                             // set port number (0x3333) to struct (sin_port)

  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); /* IMPORTANT! */ // set body to pid (getpid()) and convert to network byte order (htonl) and store in
                                 // msgbuf (struct)  we send the number in order to know in the computer which process is sending
                                 // the message and if it is still running
  msgbuf.tail = '>';

  sendto(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));


  return 0;
}
