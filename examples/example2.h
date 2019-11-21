/*************************************************************************
	> File Name: example2.h
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Thu 21 Nov 2019 09:44:38 PM CST
 ************************************************************************/
//#include<iostream>
//using namespace std;
#ifndef EXAMPLE2_H
#define EXAMPLE2_H
#include "example.h"
#include <stdint.h>

namespace example{
	class ZeroCopyEchoServer:public noncopyable{
		public:
			ZeroCopyEchoServer(const uint16_t port);
			~ZeroCopyEchoServer();
			bool init();
			void handle_message();
		private:
			int m_sfd;
			uint16_t m_port;
			int m_cfd;//client socket fd
	};
	class ZeroCopyEchoClient:public noncopyable{
		public:
			ZeroCopyEchoClient(const char * ip,const uint16_t port);
			~ZeroCopyEchoClient();

			bool connect_server();
			void send_message(const char *buf, uint32_t len);
		private:
			int m_sfd;//server fd
			const char * m_ip;
			uint16_t m_port;//connect server port
	};
}
#endif
