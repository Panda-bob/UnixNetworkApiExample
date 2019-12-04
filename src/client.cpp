/*************************************************************************
	> File Name: client.cpp
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Wed 20 Nov 2019 12:24:35 AM CST
 ************************************************************************/
#include "example1.h"
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <example2.h>
#include <string>
using namespace std;
using namespace example;
int main(int argc,char * argv [])
{
	if(argc < 3)
	{
		cout<<"Usage: client [server_ip] [server_port]"<<endl;
		exit(-1);
	}
	ZeroCopyEchoClient client(argv[argc-2],atoi(argv[argc-1]));
	if(!client.connect_server())
	{
		cout<<"client connect server faild!"<<endl;
		exit(-1);
	}
	string str("send message to server!!!!\n");
	
	while(true){
		client.send_message(str.c_str(),str.size());
	}
#ifdef EXAMPLE1_TEST
	EchoClient client(argv[argc-2],atoi(argv[argc-1]));
	if(!client.connect_server())
	{
		cout<<"client connect server faild!"<<endl;
		exit(-1);
	}
	cout<<"input message to send server:"<<endl;
	char buf[256];
	while(fgets(buf,sizeof(buf),stdin))
	{
		client.send_message(buf,strlen(buf));
	}
#endif
	return 0;
}
