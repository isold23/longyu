#if !defined(AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_)
#define AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSms window
#include "cnComm.h"

class CSms : public CWnd
{
// Construction
public:
	LRESULT On_Receive(WPARAM wp, LPARAM lp);
	CSms();
	int Open_Com(int port, int baud_rate);
	void Close_Com();
	void Set_Wnd(HWND hWnd);
	int Send_ATCmd(char* ATCmd,char* result);
	int Send_Msg(char* PhoneID,char* SmsContent);
	int Delete_Msg(int index);
	int Read_Msg(int index,char* PhoneID,char* SmsContent,char* Date);
	int Get_Smsc(char* smsc);
	int Set_Smsc(char* smsc);
	int Read_AllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);
	int SMS_Init();
	int Set_SendModle(int modle);
	int Get_SmCapacity(char* smCapacity);
// Attributes
public:
	CString strResult;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSms)
	//}}AFX_VIRTUAL

// Implementation
public:
	cnComm com;//阻塞
	virtual ~CSms();

	// Generated message map functions
protected:
	
	//_thread_com com;
	//_sync_com com;
	//_asyn_com com;
	//{{AFX_MSG(CSms)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// 短消息参数结构，编码/解码共用
// 其中，字符串以'\0'结尾
typedef struct {
	char SCA[16];			// 短消息服务中心号码(SMSC地址)
	char TPA[16];			// 目标号码或回复号码(TP-DA或TP-RA)
	char TP_PID;			// 用户信息协议标识(TP-PID)
	char TP_DCS;			// 用户信息编码方式(TP-DCS)
	char TP_SCTS[16];		// 服务时间戳字符串(TP_SCTS), 接收时用到
	char TP_UD[160];		// 原始用户信息(编码前或解码后的TP-UD)
	short index;			// 短消息序号，在读取时用到
} SM_PARAM;
// 用户信息编码方式
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

// 应答状态
#define GSM_WAIT		0		// 等待，不确定
#define GSM_OK			1		// OK
#define GSM_ERR			-1		// ERROR

// 读取应答的缓冲区
typedef struct {
	int len;
	char data[16384];
} SM_BUFF;

int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst);

int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList();
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_)
