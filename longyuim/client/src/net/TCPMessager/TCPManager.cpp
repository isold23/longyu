#include "stdafx.h"
#include "TCPManager.h"
#include <algorithm>
#include "PackManager.cpp"


class FindConnection
{
public:
	FindConnection(long alHallID):mlHallID(alHallID){}
	bool operator()(CUCPackManager* apPackManager)
	{
		return (long)apPackManager->GetUserParam() == mlHallID;
	}
private:
	long mlHallID;
};

CTCPManager::CTCPManager()
{
	mlRefCount = 0;
}

HRESULT __stdcall CTCPManager::QueryInterface(const _GUID & guid , void ** lpp)
{
	return S_FALSE;
}

ULONG  __stdcall CTCPManager::AddRef()
{
	return InterlockedIncrement(&mlRefCount);
}

ULONG  __stdcall CTCPManager::Release()
{
	if (InterlockedDecrement(&mlRefCount) <=0 )
	{
		delete this;
		return 0;
	}
	return mlRefCount;
}

bool __stdcall CTCPManager::OpenTCPSession(GUID &aFunGuid,long &alHallID,const char* astrServerAddr,WORD awServerPort)
{
	CUCPackManager* pUCPackManager = new CUCPackManager();
	pUCPackManager->Init(m_hWndWindow, (void*)alHallID);
	if(mTcpTransfer.ConnectToSever(astrServerAddr, awServerPort, pUCPackManager))
	{
		mConnectionList.push_back(pUCPackManager);
		//PostMessage(mpSystemMsg->GetSystemHandle(), WM_USER + 1005, 0, 0);
		PostMessage(m_hWndWindow, WM_SOCKET_OPEN_RESULT, 1, alHallID);
		return true;
	}
	delete pUCPackManager;
	PostMessage(m_hWndWindow, WM_SOCKET_OPEN_RESULT, 0, alHallID);
	return false;
}

void __stdcall CTCPManager::CloseTCPSession(GUID &aFunGuid, long &alHallID)
{
	vector<CUCPackManager*>::iterator iter;
	iter = find_if(mConnectionList.begin(), mConnectionList.end(), FindConnection(alHallID));
	if(iter != mConnectionList.end())
	{
		CUCPackManager* lpPackManager = *iter;
		mConnectionList.erase(iter);
		mTcpTransfer.CloseTcpSeesion(lpPackManager);
		delete lpPackManager;
	}
}

int	 __stdcall CTCPManager::SendTCPData(GUID &aFunGuid,long &alHallID,char *apData,WORD awDataLen)
{
	vector<CUCPackManager*>::iterator iter;
	iter = find_if(mConnectionList.begin(), mConnectionList.end(), FindConnection(alHallID));
	if(iter != mConnectionList.end())
	{
		return (*iter)->AddSendData(apData, awDataLen)?1:-1;
	}
	return -1;
}

LRESULT CTCPManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_SOCKET_CLOSE:
		CloseTCPSession(mguid, lParam);
		mpSystemMsg->OnErrTCPSession(-1, mguid, lParam);
		break;
	case WM_SOCKET_ERROR:
		CloseTCPSession(mguid, lParam);
		mpSystemMsg->OnErrTCPSession(wParam, mguid, lParam);
		break;
	case WM_RECV_PACK:
		{
			PSTRU_PACK_INFO pStruPack = PSTRU_PACK_INFO(wParam);
			mpSystemMsg->SolveTCPPackage(mguid, lParam, pStruPack->mpBuffer, pStruPack->mwBuffLen);
			delete pStruPack;
		}
		break;
	case WM_SOCKET_OPEN_RESULT:
		{
			if(wParam == 1)
				mpSystemMsg->OnOpenTCPSession(mguid, lParam);
			else
				mpSystemMsg->OnErrTCPSession(-1, mguid, lParam);
		}
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}