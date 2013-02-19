/*
串口基础类库（WIN32）	ver 0.2

编译器 ： BC++ 5; C++ BUILDER 4, 5, 6, X; VC++ 5, 6; VC.NET;  GCC;

使用:

定义
cnComm MyComm1(false, 0);//第1个参数为是否启动监视线程， 第2个参数为阻塞（0）/异步方式（默认）
cnComm MyComm2;//默认启动监视线程， 异步
cnComm MyComm3(true);//监视线程， 阻塞

打开
MyComm1.Open(1);//1-1024  2k支持1024串口
MyComm1.Open(1, 1200);
MyComm1.Open(1, 9600);
MyComm1.Open(1, "9600,8,n,1");//可使用标准的设置字符串
MyComm1.SetBufferSize(1200, 4800)//设置缓冲区大小,可不用设置
MyComm1.SetState("9600,8,n,1")//修改波特率等


读写

MyComm1.Read(buf, 1000);
MyComm1.Write(buf, 200);


窗口句柄
MyComm1.SetWnd(hWnd);

线程控制下面都有注明就不说了

copyright(c) 2005.11 llbird wushaojian@21cn.com
*/

#ifndef	_CN_COMM_H_
#define _CN_COMM_H_

#pragma warning(disable: 4530)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)

#include <assert.h>
#include <stdio.h>
#include <windows.h>

//当接受到数据送到窗口的消息
#define ON_COM_RECEIVE WM_USER + 618	 //	 WPARAM 端口号

class cnComm	  
{
public:
	cnComm(bool fAutoBeginThread = true, DWORD dwIOMode = FILE_FLAG_OVERLAPPED)
		: _dwIOMode(dwIOMode), _fAutoBeginThread(fAutoBeginThread)
	{
		Init();	
	}
	virtual ~cnComm()
	{
		Close();	
		UnInit();
	}
	//打开串口 缺省 9600, 8, n, 1
	inline bool Open(DWORD dwPort)
	{
		return Open(dwPort, 9600);
	}
	//打开串口 缺省 baud_rate, 8, n, 1
	inline bool Open(DWORD dwPort, DWORD dwBaudRate)
	{
		if(dwPort < 1 || dwPort > 1024)
			return false;

		BindCommPort(dwPort);

		if(!OpenCommPort())
			return false;

		if(!SetupPort())
			return false;

		return SetState(dwBaudRate);
	}
	//打开串口, 使用类似"9600, 8, n, 1"的设置字符串设置串口
	inline bool Open(DWORD dwPort, char *szSetStr)
	{
		if(dwPort < 1 || dwPort > 1024)
			return false;

		BindCommPort(dwPort);

		if(!OpenCommPort())
			return false;

		if(!SetupPort())
			return false;

		return SetState(szSetStr);
	}
	//判断串口是或打开
	inline bool IsOpen()
	{
		return _hCommHandle != INVALID_HANDLE_VALUE;
	}
	//获得串口句炳
	inline HANDLE GetHandle()
	{
		return _hCommHandle;
	}
	//设置串口参数：波特率，停止位，等 支持设置字符串 "9600, 8, n, 1"
	bool SetState(char *szSetStr)	
	{
		if(IsOpen())
		{
			if(!::GetCommState(_hCommHandle, &_DCB))
				return false;
			if(!::BuildCommDCB(szSetStr, &_DCB))
				return false;
			return ::SetCommState(_hCommHandle, &_DCB) == TRUE;
		}
		return false;
	}
	//设置串口参数：波特率，停止位
	bool SetState(DWORD dwBaudRate, DWORD dwByteSize = 8, DWORD dwParity = NOPARITY, DWORD dwStopBits = ONESTOPBIT)
	{
		if(IsOpen())
		{
			if(!::GetCommState(_hCommHandle, &_DCB))
				return false;
			_DCB.BaudRate = dwBaudRate;
		    _DCB.ByteSize = dwByteSize;
		    _DCB.Parity   = dwParity;
			_DCB.StopBits = dwStopBits;
			return ::SetCommState(_hCommHandle, &_DCB) == TRUE;
		}
		return false;
	}
	//设置串口的I/O缓冲区大小
	bool SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize)
	{
		if(IsOpen())
			return ::SetupComm(_hCommHandle, dwInputSize, dwOutputSize);
		return false;	
	}
	//读取串口 dwBufferLength - 1 个字符到 szBuffer 返回实际读到的字符数
	DWORD Read(char *szBuffer, DWORD dwBufferLength, DWORD dwWaitTime = 20)
	{
		if(!IsOpen())
			return 0;

		szBuffer[0] = '\0';

		COMSTAT  Stat;
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, &Stat) && dwError > 0)	//清除错误
		{
			::PurgeComm(_hCommHandle, PURGE_RXABORT | PURGE_RXCLEAR); /*清除输入缓冲区*/
			return 0;
		}

		if(!Stat.cbInQue)// 缓冲区无数据
			return 0;

		unsigned long uReadLength = 0;

		dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;

		if(!::ReadFile(_hCommHandle, szBuffer, dwBufferLength, &uReadLength, &_ReadOverlapped)) //2000 下 ReadFile 始终返回 True
		{
			if(::GetLastError() == ERROR_IO_PENDING) // 结束异步I/O
			{
				WaitForSingleObject(_ReadOverlapped.hEvent, dwWaitTime);	//等待20ms
				if(!::GetOverlappedResult(_hCommHandle, &_ReadOverlapped, &uReadLength, false))
				{
					if(::GetLastError() != ERROR_IO_INCOMPLETE)//其他错误
							uReadLength = 0;
				}
			}
			else
				uReadLength = 0;
		}
			
		szBuffer[uReadLength] = '\0';
		return uReadLength;
	}
	//写串口 szBuffer
	DWORD Write(char *szBuffer, DWORD dwBufferLength)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//清除错误
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, &_WriteOverlapped))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;

		return uWriteLength;
	}
	//写串口 szBuffer
	inline DWORD Write(char *szBuffer)
	{
		assert(szBuffer);

		return Write(szBuffer, strlen(szBuffer));
	}
	//强制同步写
	inline DWORD WriteSync(char *szBuffer, DWORD dwBufferLength)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//清除错误
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, NULL))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;

		return uWriteLength;
	}
	//写串口 szBuffer 可以输出格式字符串
	DWORD Write(char *szBuffer, DWORD dwBufferLength, char * szFormat, ...)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//清除错误
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		va_list va;
		va_start(va, szFormat);
		_vsnprintf(szBuffer, dwBufferLength, szFormat, va);
		va_end(va);

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, &_WriteOverlapped))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;

		return uWriteLength;
	}
	//关闭串口
	inline virtual void Close()
	{
		if(IsOpen())		
		{
			EndThread();
			::CloseHandle(_hCommHandle);

			_hCommHandle = INVALID_HANDLE_VALUE;
		}
	}
	//设定发送通知, 接受字符最小值
	inline void SetNotifyNum(int iNum)
	{
		_dwNotifyNum = iNum;
	}
	//送消息的窗口句柄
	inline void SetWnd(HWND hWnd)
	{
		_hNotifyWnd = hWnd;
	}
	//辅助线程控制 建监视线程
	bool BeginThread() 
	{
		if(!IsThreadRunning()) 
		{
			_fRunFlag = true;
			_hThreadHandle = NULL;

			DWORD id;

			_hThreadHandle = ::CreateThread(NULL, 0, CommThreadProc, this, 0, &id); //兼容98 故使用&ID

			return (_hThreadHandle != NULL); //辅助线程
		}
		return false;
	}
	//线程是否运行
	inline bool IsThreadRunning()
	{
		return _hThreadHandle != NULL;
	}
	//获得线程句柄
	inline HANDLE GetThread()
	{
		return _hThreadHandle;
	}
	//暂停监视线程
	inline bool SuspendThread()
	{
		return IsThreadRunning() ? ::SuspendThread(_hThreadHandle) != 0xFFFFFFFF : false;
	}
	//恢复监视线程
	inline bool ResumeThread()
	{
		return IsThreadRunning() ? ::ResumeThread(_hThreadHandle) != 0xFFFFFFFF : false;
	}
	//终止线程
	bool EndThread(DWORD dwWaitTime = 100)
	{
		if(IsThreadRunning()) 
		{
			_fRunFlag = false;
			::SetCommMask(_hCommHandle, 0);
			::SetEvent(_WaitOverlapped.hEvent);
			if(::WaitForSingleObject(_hThreadHandle, dwWaitTime) != WAIT_OBJECT_0)
				if(!::TerminateThread(_hThreadHandle, 0))
					return false;

			::CloseHandle(_hThreadHandle);
			::ResetEvent(_WaitOverlapped.hEvent);

			_hThreadHandle = NULL;

			return true;
		}
		return false;
	}
protected:

	volatile DWORD _dwPort;	 //串口号
	volatile HANDLE _hCommHandle;//串口句柄
	char _szCommStr[20];

	DCB _DCB;			  //波特率，停止位，等
	COMMTIMEOUTS _CO;     //超时结构

	DWORD _dwIOMode; // 0 同步  默认 FILE_FLAG_OVERLAPPED 重叠I/O 异步
	OVERLAPPED _ReadOverlapped, _WriteOverlapped; //	重叠I/O

	//线程用
	volatile HANDLE _hThreadHandle;	//辅助线程
	volatile HWND _hNotifyWnd; // 通知窗口
	volatile DWORD _dwNotifyNum;//接受多少字节(>_dwNotifyNum)发送通知消息
	volatile bool _fRunFlag; //线程运行循环标志
	bool _fAutoBeginThread;//Open() 自动 BeginThread();
	OVERLAPPED _WaitOverlapped; //WaitCommEvent use

	//线程收到消息自动调用, 如窗口句柄有效, 送出消息, 包含窗口编号
	virtual void OnReceive()
	{
		if(_hNotifyWnd)
			::PostMessage(_hNotifyWnd, ON_COM_RECEIVE, WPARAM(_dwPort), LPARAM(0));
	}
	void Init()	//初始化
	{
		memset(_szCommStr, 0, 20);
		memset(&_DCB, 0, sizeof(_DCB));
		_DCB.DCBlength = sizeof(_DCB);
		_hCommHandle = INVALID_HANDLE_VALUE;

		memset(&_ReadOverlapped, 0, sizeof(_ReadOverlapped));
		memset(&_WriteOverlapped, 0, sizeof(_WriteOverlapped));

		_ReadOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_ReadOverlapped.hEvent != INVALID_HANDLE_VALUE); 
		
		_WriteOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_WriteOverlapped.hEvent != INVALID_HANDLE_VALUE);

		_dwNotifyNum = 0;
		_hNotifyWnd = NULL;
		_hThreadHandle = NULL;

		memset(&_WaitOverlapped, 0, sizeof(_WaitOverlapped));
		_WaitOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_WaitOverlapped.hEvent != INVALID_HANDLE_VALUE);	
	}		
	void UnInit()
	{
		if(_ReadOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_ReadOverlapped.hEvent);

		if(_WriteOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_WriteOverlapped.hEvent);

		if(_WaitOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_WaitOverlapped.hEvent);
	}
	//绑定串口
	inline void BindCommPort(DWORD dwPort)
	{
		assert(dwPort >= 1 && dwPort <= 1024);

		char p[5];

		_dwPort = dwPort;
		strcpy(_szCommStr, "\\\\.\\COM");	
		ltoa(_dwPort, p, 10);
		strcat(_szCommStr, p);
	}
	//打开串口
	virtual bool OpenCommPort()
	{
		if(IsOpen())
			Close();

		_hCommHandle = ::CreateFile(
			_szCommStr,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | _dwIOMode,	
			NULL
			);

		if(_fAutoBeginThread)
		{
			if(IsOpen() && BeginThread())
				return true;
			else
			{
				Close(); //创建线程失败
				return false;
			}
		}
		return IsOpen();//检测串口是否成功打开
	}
	//设置串口
	virtual bool SetupPort()
	{
		if(!IsOpen())
			return false;

		//设置推荐缓冲区
		if(!::SetupComm(_hCommHandle, 4096, 4096))
			return false;	

		//设置超时时间
		if(!::GetCommTimeouts(_hCommHandle, &_CO))
			return false;
		_CO.ReadIntervalTimeout = 0xFFFFFFFF;
		_CO.ReadTotalTimeoutMultiplier = 0;
		_CO.ReadTotalTimeoutConstant = 0;
		_CO.WriteTotalTimeoutMultiplier = 0;
		_CO.WriteTotalTimeoutConstant = 2000;
		if(!::SetCommTimeouts(_hCommHandle, &_CO))
			return false;	

		//清空串口缓冲区
		if(!::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ))
			return false;	

		return true;
	}			
	
private:
	//监视线程
	static DWORD WINAPI CommThreadProc(LPVOID lpPara)
	{
		cnComm *pComm = (cnComm *)lpPara;	
		

        if(!::SetCommMask(pComm->_hCommHandle, EV_RXCHAR | EV_ERR))
			return 1;

		COMSTAT Stat;
		DWORD dwError;

		for(DWORD dwLength, dwMask = 0; pComm->_fRunFlag && pComm->IsOpen(); dwMask = 0)
		{
			if(!::WaitCommEvent(pComm->_hCommHandle, &dwMask, &pComm->_WaitOverlapped))
			{
				if(::GetLastError() == ERROR_IO_PENDING)
				{
					::GetOverlappedResult(pComm->_hCommHandle, &pComm->_WaitOverlapped, &dwLength, TRUE);
				}
			}

			if(dwMask & EV_ERR) // == EV_ERR
				::ClearCommError(pComm->_hCommHandle, &dwError, &Stat);

			if(dwMask & EV_RXCHAR) // == EV_RXCHAR
			{
				::ClearCommError(pComm->_hCommHandle, &dwError, &Stat);
				if(Stat.cbInQue > pComm->_dwNotifyNum)
					pComm->OnReceive();
			}
        }
		return 0;
	}
};

#endif //_CN_COMM_H_
