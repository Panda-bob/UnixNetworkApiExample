/*************************************************************************
	> File Name: example2.cpp
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Thu 21 Nov 2019 10:07:11 PM CST
 ************************************************************************/
#include "example2.h"
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include<iostream>
#include <fcntl.h>
using namespace std;

namespace example
{
	ZeroCopyEchoServer::ZeroCopyEchoServer(const uint16_t port):m_port(port)
	{
		m_sfd = socket(AF_INET,SOCK_STREAM,0);
	}
	ZeroCopyEchoServer::~ZeroCopyEchoServer()
	{
		close(m_sfd);
		close(m_cfd);
	}
	bool ZeroCopyEchoServer::init()
	{
		if(m_sfd < 0)
		{
			cout<< "create socket failed: "<<strerror(errno)<<endl;
			return false;
		}
		sockaddr_in server_addr;
		bzero(&server_addr,sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(m_port);
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if(0 !=	bind(m_sfd,(sockaddr *)&server_addr,sizeof(server_addr)))
		{
			cout<< "bind failed: "<<strerror(errno)<<endl;
			return false;
		}
		if(0 != listen(m_sfd,128))
		{
			cout<<"listen failed: "<<strerror(errno)<<endl;
			return false;
		}
		struct sockaddr_in client_addr;
		bzero(&client_addr,sizeof(client_addr));
		socklen_t len = sizeof(client_addr);
		if((m_cfd = accept(m_sfd,(struct sockaddr *)&client_addr,&len) )< 0)
		{
			cout<<"accpet filed: "<<strerror(errno)<<endl;
			return false;
		}
		cout<<"the client ip: "<<inet_ntoa(client_addr.sin_addr)<<" port: "<< ntohs(client_addr.sin_port)<<endl;
		return true;
	}
	void ZeroCopyEchoServer::handle_message()
	{
		int pipe_fd[2];
		if(pipe(pipe_fd) < 0)
		{
			cout<<"pipe create faild: "<<strerror(errno)<<endl;
			return ;
		}
		while(true)
		{
			if(splice(m_cfd,NULL,pipe_fd[1],NULL,256,SPLICE_F_MOVE|SPLICE_F_MORE)< 0 )
			{
				cout<< "splice in failed: "<< strerror(errno)<<endl;
				return ;
			}
			if(splice(pipe_fd[0],NULL,m_cfd,NULL,256,SPLICE_F_MOVE|SPLICE_F_MORE)< 0)
			{
				cout<<"splice out failed: "<< strerror(errno)<<endl;
				return ;
			}
		}
	
	}
	ZeroCopyEchoClient::ZeroCopyEchoClient(const char * ip,const uint16_t port):m_ip(ip),m_port(port)
	{
		m_sfd = socket(AF_INET,SOCK_STREAM,0);
	}
	ZeroCopyEchoClient::~ZeroCopyEchoClient()
	{
		close(m_sfd);
	}

	bool ZeroCopyEchoClient::connect_server()
	{
		if(m_sfd < 0)
		{
			cout<<"create socket failed"<<endl;
			return false;
		}
		struct sockaddr_in server_addr;
		bzero(&server_addr,sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(m_port);
		inet_pton(AF_INET,m_ip,&server_addr.sin_addr.s_addr);
		if(connect(m_sfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			cout<<"connect failed:"<<strerror(errno);
			return false;
		}
		return true;
	}
	void ZeroCopyEchoClient::send_message(const char *buf, uint32_t len)
	{
		int fd = dup2(m_sfd,STDOUT_FILENO);
		if(fd != STDOUT_FILENO)
		{
			cout<< "dup filed!"<<endl;
			return;
		}
		cout<< buf<<endl;

		if((fd = open("./example2.txt",O_RDWR|O_CREAT,0644) < 0))
		{
			cout<<"open exampl2.txt failed: "<<strerror(errno);
			return ;
		}
		int pipe_fd[2];
		if(pipe(pipe_fd) <0)
		{
			cout<<"pipe failed: "<< strerror(errno);
			return ;
		}
		if(splice(m_sfd,NULL,pipe_fd[1],NULL,256,SPLICE_F_MOVE|SPLICE_F_MORE)< 0 )
		{
			cout<< "splice in failed: "<< strerror(errno)<<endl;
			return ;
		}
		if(splice(pipe_fd[0],NULL,fd,NULL,256,SPLICE_F_MOVE|SPLICE_F_MORE)< 0)
		{
			cout<<"splice out failed: "<< strerror(errno)<<endl;
			return ;
		}

	}



}
