#pragma once
#include "TcpTransfer.h"
#include "UCPackManager.h"
#include "WndBase.h"


class CTCPManager:public ITCPMessager,public CWndBase
{
public:
	CTCPManager();

	virtual HRESULT __stdcall QueryInterface(const _GUID & guid , void ** lpp);
	virtual ULONG  __stdcall AddRef();
	virtual ULONG  __stdcall Release();

	virtual bool __stdcall Open(){return true;};
	virtual void __stdcall Close(){};
	virtual bool __stdcall IsClosed(){return true;};
	virtual GUID __stdcall getGUID(){return mguid;};

	virtual int  __stdcall Init(){return 1;};
	virtual void __stdcall adviseSystemInterface(LPVOID * apVoid){mpSystemMsg = *(ISystemMSG**)apVoid;};

	virtual void __stdcall setNetInfo(int netType,const char* proxyIP, int proxyPort,const char* proxyUser,const char* proxyPwd){};
	virtual bool __stdcall OpenTCPSession(GUID &aFunGuid,long &alHallID,const char* astrServerAddr,WORD awServerPort);
	virtual void __stdcall CloseTCPSession(GUID &aFunGuid,long &alHallID);
	virtual int	 __stdcall SendTCPData(GUID &aFunGuid,long &alHallID,char *apData,WORD awDataLen);
	virtual void __stdcall SendTCPLivePack(){};

	virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	CTcpTransfer mTcpTransfer;
	vector<CUCPackManager*> mConnectionList;
	GUID mguid;
	ISystemMSG* mpSystemMsg;
	long mlRefCount;
};