/*************************************************************************
	> File Name: server.cpp
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Wed 20 Nov 2019 12:11:46 AM CST
 ************************************************************************/
#include "example1.h"
#include<iostream>
#include <stdlib.h>
#include <example2.h>
using namespace std;
using namespace example;

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		cout<<"Usage: server [PORT]"<<endl;
		exit(-1);
	}
	ZeroCopyEchoServer server(atoi(argv[argc-1]));	
#ifdef EXAMPLE1_TEST
	EchoServer server(atoi(argv[argc-1]));
 

	if(!server.init())
	{
		cout<<"server init faile!"<<endl;
		exit(-1);
	}

	server.receive_message();
#endif
	if(!server.init())
	{
		cout<<"server init faile!"<<endl;
		exit(-1);
	}
	server.handle_message();
	return 0;
}
