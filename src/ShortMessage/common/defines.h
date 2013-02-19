#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <string>
#include <strstream>
#include <fstream>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

static const int uplen = 20;//user or password length
static const string configfile = "serverconfig.xml";


/////////////////////////////////////////////////
namespace cds//client data struct
{
	////////////////////////
	class CUserInfo
	{
	public:
		CUserInfo(void){ Init(); }
		~CUserInfo(void){ Init(); }
	private:
		void Init(void);
	public:
		string m_ServerIp;
		short m_sServerPort;
		int uid;
		string m_UserName;
		string m_UserPassword;
		int m_LastTime;
	};

	__inline void CUserInfo::Init(void)
	{
		m_ServerIp = "";
		m_sServerPort = 0;
		uid = 0;
		m_UserName = "";
		m_UserPassword = "";
		m_LastTime = 0;
	}
	/////////////////////////////////////////////////
	//class db_infobase
	class db_clientinfo
	{
	public:
		explicit db_clientinfo(void){ Init(); }
		db_clientinfo(const db_clientinfo &info)
		{
			memcpy(m_ClientName, info.m_ClientName, uplen);
			memcpy(m_ClientTelphone, info.m_ClientTelphone, 11);
		}
		~db_clientinfo(void) { Init(); }
		db_clientinfo& operator = (const db_clientinfo &info)
		{
			if (this != &info)
			{
				memcpy(m_ClientName, info.m_ClientName, uplen);
				memcpy(m_ClientTelphone, info.m_ClientTelphone, 11);
			}
			return *this;
		}
	private:
		void Init()
		{
			memset(m_ClientName, 0, uplen);
			memset(m_ClientTelphone, 0, 11);
		}
	public:
		char m_ClientName[uplen];
		char m_ClientTelphone[11];
	};
	//////////////////////////////////////////////////
	class db_userinfo
	{
	public:
		explicit db_userinfo(void){ Init(); }
		db_userinfo(const db_userinfo &info)
		{
			memcpy(m_UserName, info.m_UserName, uplen);
			memcpy(m_UserPassword, info.m_UserPassword, uplen);
		}
		~db_userinfo(void){ Init(); }

		db_userinfo& operator= (const db_userinfo &info)
		{
			if (this != &info)
			{
				memcpy(m_UserName, info.m_UserName, uplen);
				memcpy(m_UserPassword, info.m_UserPassword, uplen);
			}
			return *this;
		}
	private:
		void Init()
		{
			memset(m_UserName, 0, uplen);
			memset(m_UserPassword, 0, uplen);
		}
	public:
		char m_UserName[uplen];
		char m_UserPassword[uplen];
	};
	//////////////////////////////////////////////////
	class db_history
	{
	public: 
		db_history(void){ Init(); }
		~db_history(void){ Init(); }
	private:
		void Init()
		{
			memset(m_UserName, 0, uplen);
			memset(m_Content, 0, 200);
			memset(m_Data, 0, 50);
		}
	public:
		char m_UserName[uplen];
		char m_Content[200];
		char m_Data[50];

	};
}//end of namespace cds
/////////////////////////////////////////////////

#endif //_DEFINE_H_