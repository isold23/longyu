

#include "Common.h"

uint32 CCommon::GetProcessId()
{
	pid_t pid = getpid();
	uint32 id = pid;
	return id;
}

uint32 CCommon::GetProcessParentId()
{
	pid_t pid = getppid();
	uint32 id = pid;
	return id;
}

void CCommon::SetOpenFiles(uint32 max_file_opens_number)
{
	//修改core文件大小限制和进程最大文件句柄数
	struct rlimit rlimit_file_new;
	struct rlimit rlimit_file_old;
	if (getrlimit(RLIMIT_NOFILE, &rlimit_file_old)==0) 
	{
		rlimit_file_new.rlim_cur = max_file_opens_number;
		rlimit_file_new.rlim_max = max_file_opens_number;
		if (setrlimit(RLIMIT_NOFILE, &rlimit_file_new)!=0) 
		{
			int errorcode = errno;
			if (errorcode == EFAULT)
			{
				return;
			}
			else if(errorcode==EINVAL)
			{
				return;
			}
			else if(errorcode==EPERM)
			{
				return;
			}
			rlimit_file_new.rlim_cur = rlimit_file_old.rlim_cur;
			rlimit_file_new.rlim_max = rlimit_file_old.rlim_max;
			setrlimit(RLIMIT_NOFILE, &rlimit_file_new);
		}
	}
}


//得到当前应用程序的路径
void CCommon::GetAppPath(char* apPath, int aiLen)
{
	memset(apPath, 0, aiLen);

#ifdef WIN32
	GetModuleFileName(NULL, (LPSTR)apPath, aiLen);
#else	
	char lcAppPath[256+1] = ""; 
	sprintf(lcAppPath, "/proc/self/exe");
	readlink(lcAppPath, apPath, aiLen-1);
#endif
}

//创建路径
void CCommon::CreatePath(char* apPath)
{
#ifdef WIN32
	CreateDirectory(apPath, NULL);
#else	
	//mkdir函数的第二个参数用于设置创建文件夹的权限，
	//权限采用8进制，设置为777表示所有用户都可以查看
	mkdir(apPath, 511);
#endif
}


uint64 CCommon::get_current_time()
{
	struct timeb loTimeb;
	memset(&loTimeb, 0 , sizeof(timeb));
	ftime(&loTimeb); 
	return ((uint64)loTimeb.time * 1000) + loTimeb.millitm;
}

uint64 CCommon::escape_time(uint64 last_time)
{
	return 0;
}

string CCommon::get_now()
{
	string strCurrentTime = "";

	struct timeb loSystemTime;
	ftime(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime.time);

	stringstream lstrTimeNow;
	lstrTimeNow.fill('0');
	lstrTimeNow<<setw(4)<<1900+lptm->tm_year<<"-"<<
		setw(2)<<1+lptm->tm_mon<<"-"<<
		setw(2)<<lptm->tm_mday<<" "<<
		setw(2)<<lptm->tm_hour<<":"<<
		setw(2)<<lptm->tm_min<<":"<<
		setw(2)<<lptm->tm_sec<<":"<<
		setw(3)<<loSystemTime.millitm<<ends;

	strCurrentTime = lstrTimeNow.str();

	return strCurrentTime;
}

//检测是否超时
bool CCommon::CheckTimeOut(const INT64 &ai64LastTime, const INT64 &ai64TimeInterval)
{
	INT64 now = CCommon::get_current_time();
	if(now > ai64LastTime + ai64TimeInterval)
	{
		return true;
	}
	return false;
}

//根据IP地址和包序号计算主键
INT64 CCommon::MakeIpPortKey(const sockaddr_in& addr, const uint16_t awPackSerial)
{
#ifdef WIN32
	return (INT64)addr.sin_addr.S_un.S_addr * 0x100000000 + \
		(INT64)addr.sin_port * 0x10000 + awPackSerial;
#else
	return (INT64)addr.sin_addr.s_addr * 0x100000000LL + \
		(INT64)addr.sin_port * 0x10000 + awPackSerial;
#endif
}

//通过sockaddr_in得到int型的IP地址
unsigned int CCommon::GetSocketAddr(const sockaddr_in& addr)
{
#ifdef WIN32
	return addr.sin_addr.S_un.S_addr;
#else
	return addr.sin_addr.s_addr;
#endif
}

//把int型的IP地址设置到sockaddr_in结构体中
void CCommon::SetSocketAddr(sockaddr_in& addr, unsigned int alAddr)
{
#ifdef WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif
}

void CCommon::SetSocketAddr(sockaddr_in& addr, unsigned int alAddr, unsigned short alPort)
{
	addr.sin_family = AF_INET;
	addr.sin_port = alPort;
#ifdef WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif
}

//从int型的IP地址得到字符串类型的IP地址
char* CCommon::GetIPAddr(unsigned int alAddr)
{
	sockaddr_in addr;

#ifdef WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif	

	return inet_ntoa(addr.sin_addr);
}

//从time_t类型取得日期和时间的字符串形式
char* CCommon::Getctime(time_t *apTime)
{
	static char lszTime[20];
	strftime(lszTime, 20, "%Y-%m-%d %H:%M:%S", localtime(apTime));
	return lszTime;
}


//封装输出调用堆栈的功能
void CCommon::DumpStack()
{
	void * larray[25];
	int liSize = backtrace(larray, 25);
	char ** lszSymbols = backtrace_symbols(larray, liSize);

	for (int i = 0; i < liSize; i++)
	{
		TRACE(1, "CUCTools::DumpStack " << lszSymbols[i]);
	}
	if(lszSymbols)
		free(lszSymbols);
}


