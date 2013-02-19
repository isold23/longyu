/***************************************************************************
 *   Copyright (C) 2006 by taofei   *
 *   gudu2005@126.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <windows.h>
//#include <wininet.h>



#include <iostream>
#include <string>

#include "stdafx.h"

#include "upnpnat.h"
#include "utils.h"
#include "xmlParser.h"

#define MAX_BUFF_SIZE 102400

/******************************************************************
** Discovery Defines                                                 *
*******************************************************************/
#define HTTPMU_HOST_ADDRESS "239.255.255.250"
#define HTTPMU_HOST_PORT 1900
//#define SEARCH_REQUEST_DEVICE "urn:schemas-upnp-org:service:%s"
#define SEARCH_REQUEST_STRING "M-SEARCH * HTTP/1.1\r\n"            \
                              "ST:UPnP:rootdevice\r\n"             \
							  "MX: 3\r\n"  						   \
							  "Man:\"ssdp:discover\"\r\n"          \
                              "HOST: 239.255.255.250:1900\r\n"     \
							  "\r\n"
#define HTTP_OK "200 OK"
#define DEFAULT_HTTP_PORT 80


/******************************************************************
** Device and Service  Defines                                                 *
*******************************************************************/

#define DEVICE_TYPE_1 	"urn:schemas-upnp-org:device:InternetGatewayDevice:1"
#define DEVICE_TYPE_2	"urn:schemas-upnp-org:device:WANDevice:1"
#define DEVICE_TYPE_3	"urn:schemas-upnp-org:device:WANConnectionDevice:1"

#define SERVICE_WANIP  "urn:schemas-upnp-org:service:WANIPConnection:1"
#define SERVICE_WANPPP "urn:schemas-upnp-org:service:WANPPPConnection:1" 




/******************************************************************
** Action Defines                                                 *
*******************************************************************/
#define HTTP_HEADER_ACTION "POST %s HTTP/1.1\r\n"                         \
                           "HOST: %s:%u\r\n"                                  \
                           "SOAPACTION:\"%s#%s\"\r\n"                           \
                           "CONTENT-TYPE: text/xml ; charset=\"utf-8\"\r\n"\
                           "Content-Length: %d \r\n\r\n"

#define SOAP_ACTION  "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"     \
                     "<s:Envelope xmlns:s="                               \
                     "\"http://schemas.xmlsoap.org/soap/envelope/\" "     \
                     "s:encodingStyle="                                   \
                     "\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n" \
                     "<s:Body>\r\n"                                       \
                     "<u:%s xmlns:u=\"%s\">\r\n%s"         \
                     "</u:%s>\r\n"                                        \
                     "</s:Body>\r\n"                                      \
                     "</s:Envelope>\r\n"

#define PORT_MAPPING_LEASE_TIME "0"
#define PORT_MAPPING_DESCRIPTION "UPNP PORT MAPPING TOOL"

#define ADD_PORT_MAPPING_PARAMS "<NewRemoteHost></NewRemoteHost>\r\n"      \
                                "<NewExternalPort>%u</NewExternalPort>\r\n"\
                                "<NewProtocol>%s</NewProtocol>\r\n"        \
                                "<NewInternalPort>%u</NewInternalPort>\r\n"\
                                "<NewInternalClient>%s"                    \
                                "</NewInternalClient>\r\n"                 \
                                "<NewEnabled>1</NewEnabled>\r\n"           \
                                "<NewPortMappingDescription>"              \
                                PORT_MAPPING_DESCRIPTION                   \
                                "</NewPortMappingDescription>\r\n"         \
                                "<NewLeaseDuration>"                       \
                                PORT_MAPPING_LEASE_TIME                    \
                                "</NewLeaseDuration>\r\n"

#define DEL_PORT_MAPPING_PARAMS "<NewRemoteHost></NewRemoteHost>\r\n" \
                                   "<NewExternalPort>%u"                 \
                                   "</NewExternalPort>\r\n"              \
								   "<NewProtocol>%s</NewProtocol>\r\n"        \


#define GET_GEN_PARAMS          "<NewPortMappingIndex>%i</NewPortMappingIndex>" \
								"<NewRemoteHost></NewRemoteHost>\r\n"      \
                                "<NewExternalPort></NewExternalPort>\r\n"\
                                "<NewProtocol></NewProtocol>\r\n"        \
                                "<NewInternalPort></NewInternalPort>\r\n"\
                                "<NewInternalClient>"                    \
                                "</NewInternalClient>\r\n"                 \
                                "<NewEnabled>1</NewEnabled>\r\n"           \
                                "<NewPortMappingDescription>"              \
                                "</NewPortMappingDescription>\r\n"         \
                                "<NewLeaseDuration>"                       \
                                "</NewLeaseDuration>\r\n"

#define ACTION_ADD	 "AddPortMapping"
#define ACTION_DEL   "DeletePortMapping"
#define ACTION_GET_SPE "GetSpecificPortMappingEntry"
#define ACTION_GET_GEN "GetGenericPortMappingEntry"

#define MAPPING_INFO "%s/%s[%s]-->%s:%s\r\n"

//*********************************************************************************




bool UPNPNAT::init(int time,int inter)
{
	time_out=time;
	interval=inter;
	status=NAT_INIT;
	WSADATA     WSAData ;
        WSAStartup (MAKEWORD(2,2), &WSAData);
	return true;
}
bool UPNPNAT::get_localIP()
{
	struct sockaddr_in addr;
	int len = sizeof(addr);
	getsockname(tcp_socket_fd,(struct sockaddr*)&addr, &len);
	local_ip = inet_ntoa(addr.sin_addr);
	return true;
}
bool UPNPNAT::tcp_connect(const char * _host,unsigned short int _port)
{
	int ret,i;
	tcp_socket_fd=static_cast<int>(socket(AF_INET,SOCK_STREAM,0));
	struct sockaddr_in r_address;
        r_address.sin_family = AF_INET;
	r_address.sin_port=htons(_port);
        r_address.sin_addr.s_addr=inet_addr(_host);
//    if (ret<0)
//    {
//		status=NAT_ERROR;
//		last_error="Fail to convert IP.\n";
//		return false;
//    }
	for(i=1;i<=time_out;i++)
	{	
		//if(i>1);
			//sleep(interval);
		
		ret=connect(tcp_socket_fd,(const struct sockaddr *)&r_address,sizeof(struct sockaddr) );
		if(ret==0)
		{
			status=NAT_TCP_CONNECTED;
			return true;
		}
	}
	status=NAT_ERROR;
	char temp[100];
	sprintf(temp,"Fail to connect to %s:%i (using TCP)\n",_host,_port);
	last_error=temp;
	return false;
		
}

bool UPNPNAT::discovery()
{
    udp_socket_fd=static_cast<int>(socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP));
    int i,ret;
    std::string send_buff=SEARCH_REQUEST_STRING;
    std::string recv_buff;
    char buff[MAX_BUFF_SIZE+1]; //buff should be enough big
   
    struct sockaddr_in r_address;
    r_address.sin_family=AF_INET;
    r_address.sin_port=htons(HTTPMU_HOST_PORT);
    r_address.sin_addr.s_addr=inet_addr(HTTPMU_HOST_ADDRESS);
//    if (ret<0)
//    {
//		status=NAT_ERROR;
//		last_error="Fail to convert IP.\n";
//		return false;
//    }
    bool bOptVal = true;
    int bOptLen = sizeof(bool);
    //int iOptVal;
    int iOptLen = sizeof(int);
    ret=setsockopt(udp_socket_fd, SOL_SOCKET, SO_BROADCAST, (char*)&bOptVal, bOptLen); 
	
	struct timeval timeo = {3, 0};
	int timelen = sizeof(timeval);
	timeo.tv_sec = 20;
	int nRet = setsockopt(udp_socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeo, timelen);
	if (nRet < 0)
	{
		closesocket(udp_socket_fd);
		return false;
	}
	nRet = setsockopt(udp_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeo, timelen);
	if (nRet < 0)
	{
		closesocket(udp_socket_fd);
		return false;
	}

//    if (ret!=SOCKET_ERROR)
//    {
//    	std::cout<<"Set SO_BROADCAST: ON\n";
//    }
    ret=sendto(udp_socket_fd,send_buff.c_str(),
		static_cast<int>(send_buff.size()),0,
		(struct sockaddr*)&r_address,sizeof(struct sockaddr_in));
//    for(i=1;i<=time_out;i++)
//    { 
//	ret=sendto(udp_socket_fd,send_buff.c_str(),send_buff.size(),0,(struct sockaddr*)&r_address,sizeof(struct sockaddr_in));
//    	if (ret!=SOCKET_ERROR)
//			break;
//	else
//	{
//		int error=WSAGetLastError();
//		switch (error)
//		{
//		case WSANOTINITIALISED: std::cout<<"WSANOTINITIALISED";break;
//		case WSAENOTSOCK:std::cout<<"WSAENOTSOCK";break;
//		case WSAENETDOWN:std::cout<<"WSAENETDOWN";break;
//		}
//	}
//    }
	
    for(i=1;i<=time_out;i++)
    {
//		if(i>1) ;
		//	sleep(interval);
	//std::string response;
        ret=recvfrom(udp_socket_fd,buff,MAX_BUFF_SIZE,0,NULL,NULL);
        if(ret==SOCKET_ERROR)
            continue;
        //buff[ret]=0;
        //找出描述URL
	recv_buff=buff;
        ret=static_cast<int>(recv_buff.find(HTTP_OK));
        if(ret==std::string::npos)
		continue;                       //不是合法的回应
        std::string::size_type begin=recv_buff.find("http://");
        if(begin==std::string::npos)
            continue;                       //不是合法的回应
        std::string::size_type end=recv_buff.find("\r",begin);
        if(end==std::string::npos)
	    continue;                       //不是合法的回应
	describe_url=describe_url.assign(recv_buff,begin,end-begin);
        closesocket(udp_socket_fd);
	status=NAT_FOUND;					//找到发现UPNP 设备 
	return true ;
    }
	status=NAT_ERROR;
	last_error="Fail to find an UPNP NAT.\n";
        return false;                               //没有发现UPNP 设备 

}

bool UPNPNAT::get_description()
{
	std::string host,path;
	unsigned short int port;
	int ret=parseUrl(describe_url.c_str(),host,&port,path);
	if(!ret)
	{
		status=NAT_ERROR;
		last_error="Fail to parseURl: "+describe_url+"\n";
		return false;
	}
	
	//connect 
	ret=tcp_connect(host.c_str(),port);
	if(!ret)
		return false;
	
	char request[200];
	sprintf (request,"GET %s HTTP/1.1\r\nHost: %s:%d\r\n\r\n",path.c_str(),host.c_str(),port); 
	std::string http_request=request;
	
	//send request
	ret=send(tcp_socket_fd,http_request.c_str(),static_cast<int>(http_request.size()),0);
	//get description xml file
	char buff[MAX_BUFF_SIZE+1]; 	
		//buff should be enough big	
	std::string response;	
	while ( ret=recv(tcp_socket_fd,buff,MAX_BUFF_SIZE,0) >0) 
	{
		//buff[ret+1]=0;
		response+=buff;
	}
	//ptr+=ret;
	//ret=recv(tcp_socket_fd,description,MAX_BUFF_SIZE,MSG_WAITALL);//MSG_WAITALL);
//	if(ret<0)
//	{
//		status=NAT_ERROR;
//		last_error="Fail to get device describe XML File from "+describe_url+"\n";
//		return false;
//	}
	//*(ptr+ret)=0;
	description_info=response;
//	std::cout<<"description url:"<<describe_url<<std::endl;
//	std::cout<<"description:"<<description<<std::endl;
//	system("pause");
	return true;
}

bool UPNPNAT::parser_description()
{
	XMLNode node=XMLNode::parseString(description_info.c_str(),"root");
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="The device descripe XML file is not a valid XML file. Cann't find root element.\n";
		return false;
	}
	
	XMLNode baseURL_node=node.getChildNode("URLBase",0);
	if(!baseURL_node.getText())
	{
		std::string::size_type index=describe_url.find("/",7);
		if(index==std::string::npos )
		{
			status=NAT_ERROR;
			last_error="Fail to get base_URL from XMLNode \"URLBase\" or describe_url.\n";
			return false;
		}
		base_url=base_url.assign(describe_url,0,index);
	}
	else
		base_url=baseURL_node.getText();
	
	/* get the serviceType child that has the service type as it's data */

    /* get urn:schemas-upnp-org:device:InternetGatewayDevice:1
     and it's devicelist */
	//const char * deviceType;
	int num,i;
	XMLNode device_node,deviceList_node,deviceType_node;
	num=node.nChildNode("device");
	for(i=0;i<num;i++)
	{
		device_node=node.getChildNode("device",i);
		if(device_node.isEmpty())
			break;
		deviceType_node=device_node.getChildNode("deviceType",0);
		if(strcmp(deviceType_node.getText(),DEVICE_TYPE_1)==0)
			break;
	}
	if(device_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to find device \"urn:schemas-upnp-org:device:InternetGatewayDevice:1 \"\n";
		return false;
	}	

	deviceList_node=device_node.getChildNode("deviceList",0);
	if(deviceList_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error=" Fail to find deviceList of device \"urn:schemas-upnp-org:device:InternetGatewayDevice:1 \"\n";
		return false;
	}

	// get urn:schemas-upnp-org:device:WANDevice:1 and it's devicelist 

	num=deviceList_node.nChildNode("device");
	for(i=0;i<num;i++)
	{
		device_node=deviceList_node.getChildNode("device",i);
		if(device_node.isEmpty())
			break;
		deviceType_node=device_node.getChildNode("deviceType",0);
		if(strcmp(deviceType_node.getText(),DEVICE_TYPE_2)==0)
			break;
	}
	if(device_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to find device \"urn:schemas-upnp-org:device:WANDevice:1 \"\n";
		return false;
	}	
	deviceList_node=device_node.getChildNode("deviceList",0);
	if(deviceList_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error=" Fail to find deviceList of device \"urn:schemas-upnp-org:device:WANDevice:1 \"\n";
		return false;
	}


	// get urn:schemas-upnp-org:device:WANConnectionDevice:1 and it's servicelist 
	
	num=deviceList_node.nChildNode("device");
	for(i=0;i<num;i++)
	{
		device_node=deviceList_node.getChildNode("device",i);
		if(device_node.isEmpty())
			break;
		deviceType_node=device_node.getChildNode("deviceType",0);
		if(strcmp(deviceType_node.getText(),DEVICE_TYPE_3)==0)
			break;
	}
	if(device_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to find device \"urn:schemas-upnp-org:device:WANConnectionDevice:1\"\n";
		return false;
	}	
	
	XMLNode serviceList_node,service_node,serviceType_node;
	serviceList_node=device_node.getChildNode("serviceList",0);
	if(serviceList_node.isEmpty())
	{
		status=NAT_ERROR;
		last_error=" Fail to find serviceList of device \"urn:schemas-upnp-org:device:WANDevice:1 \"\n";
		return false;
	}	
	num=serviceList_node.nChildNode("service");
	const char * serviceType;
	bool is_found=false;
	for(i=0;i<num;i++)
	{
		service_node=serviceList_node.getChildNode("service",i);
		if(service_node.isEmpty())
			break;
		serviceType_node=service_node.getChildNode("serviceType");
		if(serviceType_node.isEmpty())
			continue;
		serviceType=serviceType_node.getText();
		if(strcmp(serviceType,SERVICE_WANIP)==0||strcmp(serviceType,SERVICE_WANPPP)==0)
		{
			is_found=true;
			break;
		}
	}
	if(!is_found)
	{
		status=NAT_ERROR;
		last_error="can't find  \" SERVICE_WANIP \" or \" SERVICE_WANPPP \" service.\n";
		return false;
	}

	this->service_type=serviceType;

	
	XMLNode controlURL_node=service_node.getChildNode("controlURL");
	control_url=controlURL_node.getText();

	//make the complete control_url;
	if(control_url.find("http://")==std::string::npos&&control_url.find("HTTP://")==std::string::npos)
		control_url=base_url+control_url;
	if(service_describe_url.find("http://")==std::string::npos&&service_describe_url.find("HTTP://")==std::string::npos)
		service_describe_url=base_url+service_describe_url;
	
	closesocket(tcp_socket_fd);
	status=NAT_GETCONTROL;
	return true;	
}


bool UPNPNAT::add_port_mapping(unsigned  short int _port,const char * _protocal)
{
	int ret;

	std::string host,path;
	unsigned short int port;
	ret=parseUrl(control_url.c_str(),host,&port,path);
	if(!ret)
	{
		status=NAT_ERROR;
		last_error="Fail to parseURl: "+describe_url+"\n";
		return false;
	}
	
	//connect 
	ret=tcp_connect(host.c_str(),port);
	if(!ret)
		return false;

	get_localIP();//get local ip and put it in this->local_ip;
	
        char buff[MAX_BUFF_SIZE+1];
	sprintf(buff,ADD_PORT_MAPPING_PARAMS,_port,_protocal,_port,local_ip.c_str());
	std::string action_params=buff;
	
	sprintf(buff,SOAP_ACTION,ACTION_ADD,service_type.c_str(),action_params.c_str(),ACTION_ADD);
	std::string soap_message=buff;
    
	sprintf(buff,HTTP_HEADER_ACTION,path.c_str(),host.c_str(),port,service_type.c_str(),ACTION_ADD,soap_message.size());
	std::string action_message=buff;
	
	std::string http_request=action_message+soap_message;
	
	//send request
	ret=send(tcp_socket_fd,http_request.c_str(),static_cast<int>(http_request.size()),0);
	//wait for response 			
	std::string response;
	while (ret=recv(tcp_socket_fd,buff,MAX_BUFF_SIZE,0) >0)
	{
		//buff[ret+1]=0;
		response+=buff;
	}
//	if(ret<0)
//	{
//		status=NAT_ERROR;
//		last_error="Fail to  get response after send add port mapping  request.\n";
//		return false;
//	}
	//std::string response=buff;
	//std::cout<<"add response:\n"<<buff<<std::endl;
	if(response.find(HTTP_OK)==std::string::npos)
	{
		status=NAT_ERROR;
		char temp[100];
		sprintf(temp,"Fail to add port mapping (%s/%u)\n",_protocal,_port);
		last_error=temp;
		return false;
	}
	closesocket(tcp_socket_fd);
	status=NAT_ADD;
	return true;	
}

bool UPNPNAT::del_port_mapping(unsigned  short int _port,const char * _protocal)
{
	int ret;

	std::string host,path;
	unsigned short int port;
	ret=parseUrl(control_url.c_str(),host,&port,path);
	if(!ret)
	{
		status=NAT_ERROR;
		last_error="Fail to parseURl: "+describe_url+"\n";
		return false;
	}
	
	//connect 
	ret=tcp_connect(host.c_str(),port);
	if(!ret)
		return false;

	//get_localIP();//get local ip and put it in this->local_ip;
	
    char buff[MAX_BUFF_SIZE+1];
	sprintf(buff,DEL_PORT_MAPPING_PARAMS,_port,_protocal);
	std::string action_params=buff;
	
	sprintf(buff,SOAP_ACTION,ACTION_DEL,service_type.c_str(),action_params.c_str(),ACTION_DEL);
	std::string soap_message=buff;
    
	sprintf(buff,HTTP_HEADER_ACTION,path.c_str(),host.c_str(),port,service_type.c_str(),ACTION_DEL,soap_message.size());
	std::string action_message=buff;
	
	std::string http_request=action_message+soap_message;
	
	//send request
	ret=send(tcp_socket_fd,http_request.c_str(),static_cast<int>(http_request.size()),0);
	//wait for response 			
	std::string response;
	while (ret=recv(tcp_socket_fd,buff,MAX_BUFF_SIZE,0) >0)
	{
	//	buff[ret+1]=0;
		response+=buff;
	}
//	if(ret<0)
//	{
//		status=NAT_ERROR;
//		last_error="Fail to  get response after send del port mapping  request.\n";
//		return false;
//	}
//	std::string response=buff;

	if(response.find(HTTP_OK)==std::string::npos)
	{
		status=NAT_ERROR;
		char temp[100];
		sprintf(temp,"Fail to del port mapping (%s/%u)\n",_protocal,_port);
		last_error=temp;
		return false;
	}
	
	closesocket(tcp_socket_fd);
	status=NAT_ADD;
	return true;	
}

bool UPNPNAT::parse_mapping_info()
{
	//std::cout<<"mapping info cstr \n"<<mapping_info.c_str()<<std::endl;
	XMLNode node;
	node=XMLNode::parseString(mapping_info.c_str(),"SOAP-ENV:Envelope");
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"SOAP-ENV:Envelope\" node.)\n";
		return false;		
	}
	node=node.getChildNode("SOAP-ENV:Body");
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"SOAP-ENV:Body\" node.)\n";
		return false;		
	}
	node=node.getChildNode("u:GetGenericPortMappingEntryResponse");
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"u:GetGenericPortMappingEntryResponse\" node.)\n";
		return false;		
	}
	XMLNode child;	
	child=node.getChildNode("NewExternalPort",0);
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"NewExternalPort\" node.)\n";
		return false;		
	}
	std::string NewExternalPort=(child.getText()?child.getText():"");


	child=node.getChildNode("NewProtocol",0);
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"NewProtocol\" node.)\n";
		return false;		
	}
	std::string NewProtocol=(child.getText()?child.getText():"");

	child=node.getChildNode("NewInternalPort",0);
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"NewInternalPort\" node.)\n";
		return false;		
	}
	std::string NewInternalPort=(child.getText()?child.getText():"");

	child=node.getChildNode("NewInternalClient",0);
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"NewInternalClient\" node.)\n";
		return false;		
	}
	std::string NewInternalClient=(child.getText()?child.getText():"");

	child=node.getChildNode("NewPortMappingDescription",0);
	if(node.isEmpty())
	{
		status=NAT_ERROR;
		last_error="Fail to get mapping info from response data.(NO \"NewPortMappingDescription\" node.)\n";
		return false;		
	}
	std::string NewPortMappingDescription=(child.getText()?child.getText():"");


	char temp[100];
	sprintf(temp,MAPPING_INFO,NewExternalPort.c_str(),NewProtocol.c_str(),NewPortMappingDescription.c_str(),NewInternalClient.c_str(),NewInternalPort.c_str());

	std::string info=temp;
 	mapping_infos.push_back(info);
	return true;
}

bool UPNPNAT::get_port_mapping()
{
	int ret,i;
	//connect to NAT
	std::string host,path;
	unsigned short int port;
	ret=parseUrl(control_url.c_str(),host,&port,path);
	if(!ret)
	{
		status=NAT_ERROR;
		last_error="Fail to parseURl: "+describe_url+"\n";
		return false;
	}

        
	i=0;
	char buff[MAX_BUFF_SIZE+1];
	while(true)
	{
		memset(buff,0,MAX_BUFF_SIZE+1);
		//connect 
		ret=tcp_connect(host.c_str(),port);
		if(!ret)
			return false;
		sprintf(buff,GET_GEN_PARAMS,i);
		std::string action_params=buff;
	
		sprintf(buff,SOAP_ACTION,ACTION_GET_GEN,service_type.c_str(),action_params.c_str(),ACTION_GET_GEN);
		std::string soap_message=buff;
	
    	        sprintf(buff,HTTP_HEADER_ACTION,path.c_str(),host.c_str(),port,service_type.c_str(),ACTION_GET_GEN,soap_message.size());
		std::string action_message=buff;
		std::string http_request=action_message+soap_message;

		//send request
		ret=send(tcp_socket_fd,http_request.c_str(),static_cast<int>(http_request.size()),0);
		//sleep(20);
	//	char receiveBuff[MAX_BUFF_SIZE+1];
		//receiveBuff[0]=0;
		//wait for response 			
		std::string response;
		memset(buff,0,MAX_BUFF_SIZE+1);
		while (ret=recv(tcp_socket_fd,buff,MAX_BUFF_SIZE,0) >0)
		{
			//receiveBuff[ret+1]=0;
			response+=buff;
			memset(buff,0,MAX_BUFF_SIZE+1);
		}
//		if(ret<0)
//		{
//			status=NAT_ERROR;
//			last_error="Fail to get response after send get port mapping info request.\n";
//			return false;
//		}
		//buff[ret]=0;
		//std::cout<<"mapping_info"<<response<<std::endl;
		//system("pause");
		mapping_info=response;
		if(mapping_info.find(HTTP_OK)==std::string::npos)
		{
			status=NAT_ERROR;
			char temp[100];
			sprintf(temp,"Totally %i mapping entries.\n",i);
			last_error=temp;
			return true;
		}
		if(!parse_mapping_info())
			return false;
		
		std::cout<<"mapping["<<i<<"]:";
		std::cout<<mapping_infos[i]<<std::endl;
		
		i++;					//get next mapping entries
		status=NAT_GET;
		closesocket(tcp_socket_fd);
	}
	status=NAT_GET;
	return true;	
}


