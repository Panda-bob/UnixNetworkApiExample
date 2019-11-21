/*************************************************************************
	> File Name: example1.cpp
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Tue 19 Nov 2019 02:05:31 PM CST
 ************************************************************************/
#include "example1.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
//#include <cstdint>
using namespace std;

namespace example{

	EchoServer::EchoServer(const uint16_t port):m_port(port)
	{
		m_sfd = socket(AF_INET,SOCK_STREAM,0);//TCP SOCKET
		
	}
	EchoServer::~EchoServer()
	{
		close(m_sfd);
		close(m_cfd);
	}

	bool EchoServer::init()
	{
		if(m_sfd < 0)
		{
			cout<<"socket error: "<< strerror(errno)<<endl;
			return false;
		}
		struct sockaddr_in serveraddr;
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port = htons(m_port);
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int ret = bind(m_sfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		if(ret != 0)
		{
			cout<<"bind error: "<<strerror(errno)<<endl;
			return false;
		}
		ret = listen(m_sfd,128);//backlog=128 is max length queue of pending connection for m_fd may grow
		if(ret != 0)
		{
			cout<<"listen error: "<< strerror(errno)<<endl;
			return false;
		}
		struct sockaddr_in clientaddr;
		bzero(&clientaddr,sizeof(clientaddr));
		socklen_t len = sizeof(clientaddr);	
		m_cfd = accept(m_sfd,(struct sockaddr *)&clientaddr,&len);
		if(m_cfd < 0)
		{
			cout<<"accept error: "<<strerror(errno);
			return false;
		}
		cout<<"accept a connect: ip "<<inet_ntoa(clientaddr.sin_addr)<<" ,port "<< ntohs(clientaddr.sin_port)<<endl;	
		return true;
	}
	
	void EchoServer::receive_message()
	{
		cout<<"the client message is :"<<endl;	
		while(1)
		{
			int ret;
			char buf[256];
			if((ret = read(m_cfd,buf,sizeof(buf)-1))>0)
			{
				buf[ret] = 0x00;
			//cout<<"message revice:"<<endl;
				cout<<buf;

			}
		}
	}
	EchoClient::EchoClient(const char* ip_addr,const uint16_t port):m_ip(ip_addr),m_port(port)
	{
		m_sfd = socket(AF_INET,SOCK_STREAM,0);	
	}
	EchoClient::~EchoClient()
	{
		close(m_sfd);	
	}

	bool EchoClient::connect_server()
	{
		struct sockaddr_in serveraddr;
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(m_port);
		inet_pton(AF_INET,m_ip,&serveraddr.sin_addr.s_addr);
		if(connect(m_sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
		{
			cout<<"connect failed: "<<strerror(errno);
			return false;
		}
		return true;
	}
	void EchoClient::send_message(const char* buf,uint32_t len)
	{
		//cout<< "send the message"<<endl;
		if(write(m_sfd,buf,len)<0)
		{
			cout<< "send message filed!"<<endl;
		}	
	}


}
