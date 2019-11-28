# The Unix Network Socket API Example
## example 1
* the socket client connect the server, then client send the data to server
* the server print the client data in stdout
## example 2
* the zero copy echo server,dup socket fd to STDOUT_FILENO clinet 
* use splice sendfile vmsplice tee and dup2
## example 3
* reactor pattern and proactor pattern with select and epoll   
