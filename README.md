# The Unix Network Socket API Example
## example 1
* the socket client connect the server, then client send the data to server
* the server print the client data in stdout
## example 2
* the zero copy echo server,dup socket fd to STDOUT_FILENO clinet 
* use splice sendfile vmsplice tee and dup2
## example 3
* nonblocking i/o echo server and client with select
## example 4 
* nonblocking i/o echo server and client with epoll
## example 5
* half-sync/half-reactive pattern server with epoll
* use task queue dispatcher the read/write event
* the main-thread epoll_wait the event 
* the works-thread deal with handle
## example 6
* high efficiency half-sync/half-async pattern server with epoll
* the main-thread just epoll_wait the listen socket 
* dispatcher the event use pipe to works-thread
* the works-thread epoll_wait read/write event
## example 7
* leader/follower pattern server with epoll
* 
