#include "stdafx.h"
#include "xml.h"

CXmlConfig::CXmlConfig(void)
{

}

CXmlConfig::~CXmlConfig(void)
{

}

void CXmlConfig::GetServerInfo(std::string &ip, short &port)
{
	CMarkupSTL MarkupXml;
	MarkupXml.Load(configfile.c_str());
	ip = MarkupXml.GetData();
}

void CXmlConfig::GetUpLen(int &len)
{
	CMarkupSTL MarkupXml;
}

void CXmlConfig::GetUserInfo(std::string name, std::string password)
{
	CMarkupSTL MarkupXml;
}