/*************************************************************************
	> File Name: example.h
	> Author: pandabob
	> Mail: 1287928950@qq.com 
	> Created Time: Tue 19 Nov 2019 06:46:17 PM CST
 ************************************************************************/
#ifndef EXAMPLE_H
#define EXAMPLE_H
#include<iostream>
using namespace std;
namespace example
{
	class noncopyable
	{
		protected:
			noncopyable(){}
			~noncopyable(){}
		private:
			noncopyable(const noncopyable&) ;
			const noncopyable& operator = (const noncopyable& ) ;
	};
}


#endif
