#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "..\..\common\defines.h"
using namespace cds;

namespace protocol
{

static const int PACKLEN = 1024;
static const char PREFIX = 0x89;

#pragma pack(1)
enum 
{
	COM_ERROR = 0,
	COM_LOGIN,
	COM_LOGIN_RET,
	COM_LOGOUT,
	COM_LOGOUT_RET
};
	//////////////////////////////////////////////////
	class CMsgBuffer
	{
	public:
		CMsgBuffer(void)
		{
			m_pBuffer = NULL;
			m_pBuffer = new char[PACKLEN];
			m_nBufferLen = 0;
		}
		CMsgBuffer(int size)
		{
			if (size < PACKLEN)
				throw "the buffer is small";
			m_pBuffer = NULL;
			m_pBuffer = new char[size];
			m_nBufferLen = 0;
		}
		CMsgBuffer(char *buf, int size)
		{
			if (size > PACKLEN)
				throw "the buffer is too big";
			m_pBuffer = NULL;
			m_nBufferLen = size + 1;
			m_pBuffer = new char[m_nBufferLen];
			memcpy(m_pBuffer, buf, size);
		}
		CMsgBuffer(CMsgBuffer &buf)
		{
			m_pBuffer = new char[PACKLEN];
			m_nBufferLen = 0;
			memcpy(m_pBuffer, buf.m_pBuffer, buf.m_nBufferLen);
			m_nBufferLen = buf.m_nBufferLen;
		}
		~CMsgBuffer(void)
		{
			if (NULL != m_pBuffer)
			{
				delete [] m_pBuffer;
				m_pBuffer = NULL;
			}
			m_nBufferLen = 0;
		}

		CMsgBuffer& operator = (CMsgBuffer& buf)
		{
			if (this != &buf)
			{
				delete [] m_pBuffer;
				m_pBuffer = NULL;
				m_nBufferLen = 0;
				m_pBuffer = new char[PACKLEN];
				memcpy(m_pBuffer, buf.m_pBuffer, buf.m_nBufferLen);
				m_nBufferLen = buf.m_nBufferLen;
			}
			return *this;
		}

		CMsgBuffer& operator+=(CMsgBuffer &buf)
		{
			assert((m_nBufferLen + buf.m_nBufferLen) < PACKLEN);
			memcpy(m_pBuffer, buf.m_pBuffer, buf.m_nBufferLen);
			m_nBufferLen += buf.m_nBufferLen;
			return *this;
		}
	public:
		char *m_pBuffer;//
		int m_nBufferLen;
	};
	//////////////////////////////////////
	class CHeader
	{
	public:
		CHeader(void){ Init(); }
		~CHeader(void){ Init(); }
	private:
		void Init(void);
	public:
		char prefix;//protocol start
		int notype;//no use
		int cmd;//command
		int length;//pack length
		int uid;//user id
	};

	__inline void CHeader::Init(void)
	{
		prefix = PREFIX;
		notype = 0x00;
		cmd = 0x00;
		length = 0x00;
		int fuid = 0x00;
		int tuid = 0x00;
	}
	//////////////////////////////////////
	class CReturn : public CHeader
	{
	public:
		CReturn(void){ Init(); }
		~CReturn(void){ Init(); }
	private:
		void Init(void);
	public:
		int m_RetCode;//server return code
	};

	__inline void CReturn::Init(void)
	{
		m_RetCode = 0x00;
	}
	//////////////////////////////////////
	class CProBase
	{
		virtual void ToBuffer(CMsgBuffer &buf) = 0;
		virtual void BufferTo(CMsgBuffer &buf) = 0;
	};
	/////////////////////////////////////
	class CLogin : public CProBase
	{
	public:
		CLogin(void){ Init(); }
		~CLogin(void) { Init(); }

		virtual void ToBuffer(CMsgBuffer &buf);
		virtual void BufferTo(CMsgBuffer &buf);
	private:
		void Init(void);
	public:
		char m_UserName[uplen];
		char m_UserPassword[uplen];
		int uid;
		int m_LastTime;//last login time
	};

	__inline void CLogin::Init(void)
	{
		memset(m_UserName, 0, uplen);
		memset(m_UserPassword, 0, uplen);
		uid = 0;
		m_LastTime = 0;
	}

	__inline void CLogin::ToBuffer(CMsgBuffer &buf)
	{
		memcpy(buf.m_pBuffer, this, sizeof(*this));
		buf.m_nBufferLen = sizeof(*this);
	}

	__inline void CLogin::BufferTo(CMsgBuffer &buf)
	{
		memcpy(this, buf.m_pBuffer, sizeof(*this));
	}
	class CLoginRtn : public CLogin, 
		public CReturn
	{
	public:
		CLoginRtn(void){}
		~CLoginRtn(void){}

		void ToBuffer(CMsgBuffer &buf);
		void BufferTo(const CMsgBuffer &buf);
	private:

	};

	__inline void CLoginRtn::ToBuffer(CMsgBuffer &buf)
	{
		
	}

	__inline void CLoginRtn::BufferTo(const CMsgBuffer &buf)
	{

	}
	//////////////////////////////////////
	class CLogout : public CProBase
	{
	public:
		CLogout(void) { Init(); }
		~CLogout(void) { Init(); }

		void ToBuffer(CMsgBuffer &buf);
		void BufferTo(CMsgBuffer &buf);
	private:
		void Init(void);
	public:
		int uid;//user id
		int m_LastTime;//last login time
	};

	__inline void CLogout::Init(void)
	{
		uid = 0;
		m_LastTime = 0;
	}

	__inline void CLogout::ToBuffer(CMsgBuffer &buf)
	{

	}

	__inline void CLogout::BufferTo(CMsgBuffer &buf)
	{

	}

	class CLogoutRtn : public CLogout, public CReturn
	{
	public:
		CLogoutRtn(void){}
		~CLogoutRtn(void){}

		void ToBuffer(CMsgBuffer &buf);
		void BufferTo(CMsgBuffer &buf);
	private:

	};

	__inline void CLogoutRtn::ToBuffer(CMsgBuffer &buf)
	{

	}

	__inline void CLogoutRtn::BufferTo(CMsgBuffer &buf)
	{

	}
	#pragma pack()
	/////////////////////////////////////
	class CShortMessage : public CProBase
	{
	public:
		CShortMessage(void){ Init(); }
		~CShortMessage(void) { Init(); }

		void ToBuffer(CMsgBuffer &buf);
		void BufferTo(CMsgBuffer &buf);
	private:
		void Init(void);
	public:
		int m_UserNum;//用户数目
		vector<string> m_PeerIdList;//对方的电话号码
		string m_ShortMessageContent;//短信内容
	};
	//////////////////////////////////////////////////
	class CSendMsg
	{
	public:
		CSendMsg(void){}
		~CSendMsg(void){}
	public:
		CHeader *m_Header;
		CProBase *m_pProBase;
	};
	//////////////////////////////////////////////////
	class CRecvMsg
	{
	public:
		CRecvMsg(void){}
		~CRecvMsg(void){}
	public:
		CReturn *m_Return;
		CProBase *m_pProBase;
	};

	/////////////////////////////////////////////////
};
#endif //_PROTOCOL_H_