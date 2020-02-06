#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define BUFLEN 256

// \brief Write a message to stderr with perror, then exit the program
// \param str The string to write to  stderr
static
void die(char * str)
{
    perror(str);
    exit(1);
} // die

void writestring(int fd, char *str)
{
    write(fd, str, strlen(str));
}

// \brief send an open file's descriptor to the given socket and address
// \param socket Send the fd to this DGRAM socket
// \param addr Send it to the client with this address
// \param fd The file descriptor to send. 
static
void send_fd(int socket, struct sockaddr_un *addr, int fd)  // send fd by socket
{
    struct msghdr msg = { 0 };
    char buf[CMSG_SPACE(sizeof(fd))];
    memset(buf, '\0', sizeof(buf));

    /* On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    struct iovec io = { .iov_base = "", .iov_len = 1 };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);
    msg.msg_name = addr;
    msg.msg_namelen = sizeof(struct sockaddr_un);

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    memmove(CMSG_DATA(cmsg), &fd, sizeof(fd));

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(socket, &msg, 0) < 0)
        die("sendmsg");
} // send_fd

// \brief wait for a request (just a DGRAM) from a socket
// \param socket Wait for a request on this socket
// \param addr Address of the client that sent the request (must be allocated by caller)
static
void receive_request(int socket, struct sockaddr_un *addr)  // wait for a request
{
    int status;
    struct msghdr msg = {0};

    /* On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    char m_buffer[1];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    char c_buffer[BUFLEN];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);
    msg.msg_name = addr;
    msg.msg_namelen = sizeof(struct sockaddr_un);

    if ((status = recvmsg(socket, &msg, 0)) <= 0)
        die("recvmsg");

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);

    printf("recvmsg returned %d\n", status);
    printf("CMSG_FIRSTHDR() returned %s\n", cmsg == NULL ? "NULL" : "not NULL");
    printf("msg.msg_controllen = %ld\n", msg.msg_controllen);
    //printf("About to extract fd\n");
    //int fd;
    //memmove(&fd, CMSG_DATA(cmsg), sizeof(fd));
    //printf("Extracted fd %d\n", fd);
    printf("receive_request returning\n");

} // revceive_request

// \brief Set up a server waiting for a single fd request, then answer it
// \param fd the fd to send to the requesting client
void run_fdserver(int fd)
{
    int status;
    struct sockaddr_un server_addr, client_addr;
    int s;

    // Server address:
    const char *server_path = "/tmp/fd-passing";
    memset (&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server_path);

    unlink(server_path);


    if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
        die("socket");

    if (bind(s, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
        die("bind");

    printf("Waiting for request...");
    fflush(stdout);

    receive_request(s, &client_addr);
    printf("\n");

    send_fd(s, &client_addr, fd);

    close(fd);
    close(s);
    unlink(server_path);
} // run_fdserver

// \brief pass the fd of the given file to the client. Read a bit of the file
// first
// \param filename Path of the file
void pass_file(const char *filename)
{
    int status;

    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open file %s for reading\n", filename);
        exit(1);
    }

    // Read some data to demonstrate that file offset is passed
    char buffer[32];
    int nbytes = read(fd, buffer, sizeof(buffer));
    if (nbytes > 0)
        printf("Parent read: [[%.*s]]\n", nbytes, buffer);

    run_fdserver(fd);
    // file is closed by run_fdserver

} // pass_file

// \brief wait for a tcp connection, then pass the socket to the client
void pass_socket()
{
    int status;
    const char* hostname = 0; /* wildcard */
    const char* portname = "8888"; //"daytime";
    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    // AI_PASSIVE: Address is intended for binding to a server socket
    // AI_ADDRCONFIG: ONly return IPvX if server has a IPvX address
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; 

    struct addrinfo* res = 0; // allocated by getadddrinfo

    int err=getaddrinfo(hostname,portname,&hints,&res);
    if (err!=0) {
            printf("getaddrinfo returned %d",err);
            die("getaddrinfo");
    } // if

    int server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_fd == -1)
        die("socket 1");

    // SO_REUSEADDR: Allow the network service to be restarted when there are
    //               connections in the ESTABLISHED or TIME-WAIT state.
    int reuseaddr = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                        &reuseaddr, sizeof(reuseaddr)) == -1)
        die("setsockopt");

    if (bind(server_fd, res->ai_addr, res->ai_addrlen) == -1)
        die("bind 1");

    freeaddrinfo(res); // free memory allocated by getaddrinfo

    if (listen(server_fd, SOMAXCONN))
        die("listen 1");

    // Stop after one connection
    //for (;;)
    {
        printf("Now start \"telnet 127.0.0.1 8888\"\n");
        printf("Waiting for session...");
        int session_fd = accept(server_fd, 0, 0);
        printf("\n");
        if (session_fd == -1)
            die("accept 1");

        writestring(session_fd, "Hello there, this is your server.\n");
        writestring(session_fd, "Now start the client so I can you to it, stand by...");

        run_fdserver(session_fd);
        // file is closed by run_fdserver
    } // for (;;)

} // pass_socket

int main(int argc, char **argv)
{
    const char *filename = "./test.txt";
    int status;

    if (argc > 1)
        pass_file(argv[1]);
    else
        pass_socket();

    return 0;
}
