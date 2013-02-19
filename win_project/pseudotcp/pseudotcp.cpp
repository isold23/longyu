// pseudotcp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>

#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
#include <cassert>
using namespace std;

#include "libpseudotcp/PseudoTcpChannel.h"
using namespace wzy;

CNet net;

void client()
{
	CPseudoTcpChannel c;
	c.Start("192.168.150.128", 6000, "192.168.150.128", 5000);
	c.Connect();
		
	while(true)
	{
		//int nRet = c.TcpReadPack();
				
		while(c.GetState()!=SS_OPEN);
		cout <<"mbCanWrite"<<endl;
		
		sleep(3);
		if(!c.mbTcpClose)
		{									
			for (int i=0; i<3; i++)		
			{
				string str = "";
				fstream ff;
				ff.open("test.txt", ios::in|ios::binary);
				while(getline(ff, str))
				{
					size_t * written = new size_t;
					int * error = new int;
		
					StreamResult result = c.Write(str.c_str(), str.length(), written, error);
					cout <<"written=" << *written <<endl;
																
					delete written;
					delete error;
					
					ff.close();
				}
				sleep(3);
			}											
			break;
		}
	}
	
	sleep(3);
	cout <<"Closing"<<endl;
	c.Close();	
	while(c.GetState()!=SS_CLOSED);
	cout <<"SS_CLOSED"<<endl;
}

void server()
{
	CPseudoTcpChannel s;
	s.Start("192.168.150.128", 5000, "192.168.150.128", 6000);
	fstream out;
	out.open("recv.txt", ios::out|ios::binary|ios::app);

	while(true)
	{		
		if(s.mbCanRead)
		{
			char buffer[MAX_PACKET_SIZE];
			memset(buffer, 0, MAX_PACKET_SIZE);
			size_t buffer_len = MAX_PACKET_SIZE;
			size_t *read = new size_t;
			int *error = new int;
			
			if(SR_SUCCESS == s.Read(buffer, buffer_len, read, error))
			{
				out<<buffer<<ends;
				out.flush();
				cout<<"read : "<<buffer<<" length : "<<*read<<endl;
			}
									
			delete read;
			delete error;
		}
	}
	out.close();
	s.Close();
}

int main(int argc, char* argv[])
{
	if(argc >= 2)
	{
		switch(*argv[1])
		{
		case 'c':
			{
				cout<<"-------------client start------------------------"<<endl;
				client();
				cout<<"-------------client end---------------------------"<<endl;
				break;
			}
		case 's':
			{
				cout<<"-------------server start------------------------"<<endl;
				server();
				cout<<"-------------server end------------------------"<<endl;
				break;
			}
		default:
			{
				break;
			}
		}
	}	
	return 0;
}

