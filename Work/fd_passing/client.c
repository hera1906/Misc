#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#define BUFLEN 256

// \brief Write a message to stderr with perror, then exit the program
// \param str The string to write to  stderr
void die(char * str)
{
    perror(str);
    exit(1);
}

void writestring(int fd, char *str)
{

    write(fd, str, strlen(str));
}
// \brief send a request to a fd server 
// \param socket Send the request on this socket
// \param addr The server has this address.
static
void send_request(int socket, struct sockaddr_un *addr)  // send request by socket
{
    struct msghdr msg = { 0 };
    char buf[CMSG_SPACE(BUFLEN)];
    memset(buf, '\0', sizeof(buf));

    sprintf(buf, "Hej, må jeg få en socket?");

    /* On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    struct iovec io = { .iov_base = "", .iov_len = 1 };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);
    msg.msg_name = addr;
    msg.msg_namelen = sizeof(struct sockaddr_un);

    // Hack: do not send this
    int fd; 
    fd = 2;
    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    memmove(CMSG_DATA(cmsg), &fd, sizeof(fd));

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(socket, &msg, 0) < 0)
        die("sendmsg");
} // send_request

// \brief Wait for the message containing the fd, then return it
// \param The fd will be incoming on this socket.
static
int receive_fd(int socket)  // receive fd from socket
{
    int status;
    struct msghdr msg = {0};

    /* On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    char m_buffer[1];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    char c_buffer[256];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);

    if ((status = recvmsg(socket, &msg, 0)) <= 0)
        die("recvmsg");
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    if (cmsg == NULL)
    {
        printf("CMSG_FIRSTHDR is NULL\n");
        exit(1);
    }

    int fd;
    memmove(&fd, CMSG_DATA(cmsg), sizeof(fd));

    return fd;
} // receive_fd

int main(int argc, char **argv)
{
    int s;
    struct sockaddr_un server_addr, client_addr;
    int status;

    // Create client and server addresses
    const char *client_path = "/tmp/fd-passing.client(1";
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, client_path);
    unlink(client_path);

    const char *server_path = "/tmp/fd-passing";
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server_path);

    if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
        die("socket");

    // Bind this socket to client address.
    // This is needed for the server to reply to us
    if (bind(s, (struct sockaddr*) &client_addr, sizeof(client_addr)) == -1)
        die("bind");

    // Send request to the server

    printf("Sending request...");
    send_request(s, &server_addr);  // send request by socket

    // Receive requested file descriptor from server
    int fd = receive_fd(s);
    printf(" Got answer, fd is %d!\n", fd);
    writestring(fd, "\n\nHello, this is your client.\n");
    writestring(fd, "Now echoing everything from the socket\n");
    char buffer[BUFLEN+1];
    ssize_t nbytes;

    while ((nbytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, nbytes);
        write(fd, buffer, nbytes);
    }
    if (nbytes < 0)
        die("read");

    printf("Done!\n");
    writestring(fd,"\nDone!\n");

    close(fd);
    close(s);

        return 0;
}
