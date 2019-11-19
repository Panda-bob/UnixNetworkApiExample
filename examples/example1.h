/*************************************************************************
	> File Name: example1.h
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Tue 19 Nov 2019 02:03:38 PM CST
 ************************************************************************/
#ifndef EXAMPLE1_H
#define EXAMPLE1_H
#include "example.h"
#include <stdint.h>
namespace example
{
	class EchoServer: public noncopyable
	{
		public:
			EchoServer(const uint16_t port);
			~EchoServer();
			bool init();
			void receive_message();
		private:
			uint16_t m_port;
			int m_sfd;//server fd
			int m_cfd;// client fd
	};
	class EchoClient :public noncopyable
	{
		public:
			EchoClient(const char* ip_addr,const uint16_t port);
			~EchoClient();
			bool connect_server();
			void send_message(const char* buf,uint32_t len);
		private:
		int m_sfd;//server fd	
		uint16_t m_port;
		const char* m_ip;//connect ip 
	};
}
#endif
