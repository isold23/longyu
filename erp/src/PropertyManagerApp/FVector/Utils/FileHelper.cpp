#include "stdafx.h"
#include "FileHelper.h" 
namespace Fh
{

inline BOOL IsSlash(TCHAR ch)
{
	return ch==_T('/') || ch==_T('\\');
}

inline BOOL IsDot(TCHAR ch)
{
	return ch == _T('.');
}

LPCTSTR RFindPathSlash(LPCTSTR pcszFilePath)
{
	LPCTSTR pSlash = NULL;
	while (*pcszFilePath != _T('\0'))
	{
		if (IsSlash(*pcszFilePath))
			pSlash = pcszFilePath;
		++pcszFilePath;
	}
	return pSlash;
}

////////////////////////////////////////////////////////////////////////
// Function: Get name of a file
// Params:
//      LPCTSTR pcszFilePath : path of the file
// Return: file name of the file
////////////////////////////////////////////////////////////////////////
CString GetFileName(LPCTSTR pcszFilePath)
{
	LPCTSTR pcsz = RFindPathSlash(pcszFilePath);
	return (pcsz == NULL ? pcszFilePath : pcsz+1);
}



////////////////////////////////////////////////////////////////////////
// Function: Get name without extension of a file
// Params:
//      LPCTSTR pcszFilePath : path of the file
// Return: file name without extension of the file
////////////////////////////////////////////////////////////////////////
CString GetFileNameWithoutExt(LPCTSTR  pcszFilePath)
{
	LPCTSTR pcszName = RFindPathSlash(pcszFilePath);
	LPCTSTR pcszDot = _tcsrchr((LPTSTR)pcszFilePath,_T('.'));
	
	if (pcszName==NULL && pcszDot==NULL)
		return pcszFilePath;
	if (pcszDot == NULL)
		return pcszName + 1;
	if (pcszName == NULL)
		return CString(pcszFilePath,(int)(pcszDot-pcszFilePath));

	return CString(pcszName+1,(int)(pcszDot-pcszDot-1));
}



////////////////////////////////////////////////////////////////////////
// Function: Get extension of a file
// Params:
//      LPCTSTR pcszFilePath : path of the file
// Return: file extension of the file
////////////////////////////////////////////////////////////////////////
CString GetFileExt(LPCTSTR pcszFilePath)
{
	LPCTSTR pcszDot = _tcsrchr((LPCTSTR)pcszFilePath,_T('.'));
	return (pcszDot == NULL ? CString() : pcszDot + 1); 	
}


////////////////////////////////////////////////////////////////////////
// Function: Get path of a file 
// Params:
//      LPCTSTR pcszFilePath : path of the file
// Return: folder of the file
////////////////////////////////////////////////////////////////////////
CString GetFolderPath(LPCTSTR pcszFilePath)
{
	LPCTSTR pcszName = RFindPathSlash(pcszFilePath);
	return CString(pcszFilePath,(int)(pcszName-pcszFilePath)); 
}







////////////////////////////////////////////////////////////////////////
// Function: Get relative path of an absolute path according to the referenced path
// Params:
//      LPCTSTR pcszSrc : absolute path to convert
//		LPCTSTR pcszRef : referenced absolute path
//		CString &str    : the returned relative path
// Return: TRUE : conversion has be done 
//		   FALSE : conversion cann't be done
////////////////////////////////////////////////////////////////////////
BOOL GetRelativePath(LPCTSTR pcszSrc,LPCTSTR pcszRef,CString &str)
{
	str.Empty();

	// If the two path is not in the same disk
	// then path conversion is not possible
	if(tolower(*pcszSrc) != tolower(*pcszRef))
	{
		str =  pcszSrc;
		return FALSE;
	}

	LPCTSTR s;
	LPCTSTR d;

	// Get position of the last '/' before which the two string are equal 
	while (*pcszSrc!=_T('\0') && *pcszRef!=_T('\0') 
		&& (tolower(*pcszSrc)==tolower(*pcszRef) ||
			IsSlash(*pcszSrc) && IsSlash(*pcszRef)))
	{
		if (IsSlash(*pcszSrc))
			s = pcszSrc, d = pcszRef;
		pcszSrc++, pcszRef++;
	}

	// '\0' and '/' are equivalent 
	if ((*pcszSrc==_T('\0') && *pcszRef==_T('\0')) 
		|| (*pcszSrc==_T('\0') && IsSlash(*pcszRef)) 
		|| (IsSlash(*pcszSrc) && *pcszRef==_T('\0')) )
		s = pcszSrc, d = pcszRef;

	// If d is not the end of pcszRef, '/' is not needed is s
	// else '/' is needed in s
	if (*d != _T('\0'))
		s++;

	// Convert path to dots
	while (*d != _T('\0'))
	{
		if (IsSlash(*d))
			str += _T("..\\");
		d++;
	}

	// add s path to dots
	if (str.IsEmpty() && IsSlash(s[0]))
		str.AppendChar(_T('.'));
	str += s;
	str.Replace(_T('\\'),_T('/'));
	return TRUE;
}







////////////////////////////////////////////////////////////////////////
// Function: Get absolute path of a relative path according to the referenced path
// Params:
//      LPCTSTR pcszSrc : relative path to convert
//		LPCTSTR pcszRef : referenced absolute path
//		CString &str    : the returned absolute path
// Return: TRUE : conversion has be done 
//		   FALSE : conversion cann't be done
////////////////////////////////////////////////////////////////////////
BOOL GetAbsolutePath(LPCTSTR pcszSrc,LPCTSTR pcszRef,CString &str)
{
	// If pcszSrc is a absolute path, just return FALSE
	if (*(pcszSrc+1) == _T(':'))
	{
		str = pcszSrc;
		return FALSE;
	}

	// Seek to the end of pcszRef
	LPCTSTR p = pcszRef + _tcslen(pcszRef);

	// Seek in pcszRef to previous '/' according to dots 
	while (*pcszSrc!=_T('\0') 
		&& IsDot(*(pcszSrc)) 
		&& IsDot(*(pcszSrc+1)) 
		&& IsSlash(*(pcszSrc+2)))
	{
		pcszSrc += 3;
		do {p--;} while (p>=pcszRef && !IsSlash(*p));
		if (p <pcszRef) return FALSE; 
	}	

	str = pcszRef;

	// If p is at the end of pcszRef, a '/' is needed in return string
	if (*p==_T('\0') && !IsSlash(*pcszSrc))
		str += _T('/');

	// Add remaining pcszSrc to it's directory 
	str = str.Mid(0,(int)(p-pcszRef)+1) + pcszSrc;
	str.Replace(_T('\\'),_T('/'));
	return TRUE;
}






////////////////////////////////////////////////////////////////////////
// Function: Get the last drive of a computer
// Params:
//      LPTSTR pszDrive : buffer to store the result
////////////////////////////////////////////////////////////////////////
void GetLastDrive(LPTSTR pszDrive)
{
	TCHAR i;
	TCHAR szDrive[] = _T("A:/");
	DWORD dwConst = 0x1;
	DWORD dwFlag = GetLogicalDrives();

	while (dwConst != 0)
	{
		if ((dwFlag & dwConst) && (::GetDriveType(szDrive) == DRIVE_FIXED))
			i = szDrive[0] - _T('A');

		dwConst <<= 1;
		szDrive[0]++;
	}
	_tcscpy(pszDrive,_T("A:/"));
	pszDrive[0] += i;
}







////////////////////////////////////////////////////////////////////////
// Function: Create a directory if it doesn't exist
// Params:
//      LPCTSTR pcszDir : path of the directory to create
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL CreateDir(LPCTSTR pcszDir)
{
	// If the directory exists, return directly
	if (IsDirectoryExist(pcszDir))
		return TRUE;

	// This class ensures lazy evaluation and singleton
	// If this method is never called "shell32.dll" will never be loaded by this method
	// And "shell32.dll" library will only be loaded once
	static class CLoadHelper
	{
	public:
		int (WINAPI* SHCreateDirectory)( HWND, LPCTSTR pszPath, SECURITY_ATTRIBUTES *psa);

		CLoadHelper(void)
		{
			m_hShell32Dll = ::LoadLibrary(_T("shell32.dll"));
			ASSERT(m_hShell32Dll != NULL);

#ifdef _UNICODE
			(FARPROC&)SHCreateDirectory= ::GetProcAddress(m_hShell32Dll, ("SHCreateDirectoryExW"));
#else
			(FARPROC&)SHCreateDirectory= GetProcAddress(m_hShell32Dll, ("SHCreateDirectoryExA"));
#endif
			
			ASSERT(SHCreateDirectory != NULL);
		}
		~CLoadHelper(void)
		{
			::FreeLibrary(m_hShell32Dll);
		}

	private:
		HMODULE m_hShell32Dll;

	}helper;

	return (helper.SHCreateDirectory(NULL,pcszDir,NULL) == ERROR_SUCCESS);
}



////////////////////////////////////////////////////////////////////////
// Function: Log if file exists
// Params:
//      LPCTSTR pcszPathName : path of the file to test
////////////////////////////////////////////////////////////////////////
BOOL IsFileExist(LPCTSTR pcszPathName)
{
	HANDLE hFile = ::CreateFile(pcszPathName,
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else
	{
		::CloseHandle(hFile);
		return TRUE;
	}
} 







////////////////////////////////////////////////////////////////////////
// Function: Log if directory exists
// Params:
//      LPCTSTR pcszPathName : path of the directory to test
////////////////////////////////////////////////////////////////////////
BOOL IsDirectoryExist(LPCTSTR pcszDirPath)
{
	HANDLE hDir = ::CreateFile(pcszDirPath,
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);

	if (hDir == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else
	{
		::CloseHandle(hDir);
		return TRUE;
	}

} 






////////////////////////////////////////////////////////////////////////
// Function: Rename a file or directory
// Params:
//      LPCTSTR pcszSrcFileName : path of file or directory to rename
//      LPCTSTR pcszDstFileName : the destination name
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL RenameFile(LPCTSTR pcszSrcFileName,LPCTSTR pcszDstFileName)
{
	SHFILEOPSTRUCT fileOP;

	TCHAR szSrc[MAX_PATH];
	TCHAR szDst[MAX_PATH];

	ZeroMemory(szSrc,sizeof(szSrc));
	_tcscpy(szSrc,pcszSrcFileName);

	ZeroMemory(szSrc,sizeof(pcszDstFileName));
	_tcscpy(szDst,szDst);

	fileOP.hwnd = NULL;
	fileOP.wFunc = FO_RENAME;
	fileOP.pFrom = szSrc;
	fileOP.pTo = pcszDstFileName;
	fileOP.fFlags = FOF_SILENT | 
		FOF_NOCONFIRMATION |
		FOF_NOCONFIRMMKDIR |
		FOF_NOERRORUI|
		FOF_NOCONFIRMATION;
	fileOP.fAnyOperationsAborted =FALSE;
	fileOP.hNameMappings = NULL;
	fileOP.lpszProgressTitle = NULL;

	return (::SHFileOperation(&fileOP) == 0);

} 






////////////////////////////////////////////////////////////////////////
// Function: Delete directory recursively
// Params:
//      LPCTSTR pcszDir : path of the directory to delete
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL DeleteDirectory(LPCTSTR pcszDir)
{
	SHFILEOPSTRUCT fileOP;


	TCHAR szDir[MAX_PATH];
	ZeroMemory(szDir,sizeof(pcszDir));
	_tcscpy(szDir,pcszDir);

	fileOP.hwnd = NULL;
	fileOP.wFunc = FO_DELETE;
	fileOP.pFrom = szDir;
	fileOP.pTo = NULL;
	fileOP.fFlags = FOF_SILENT | 
		FOF_NOCONFIRMATION |
		FOF_NOCONFIRMMKDIR |
		FOF_NOERRORUI|
		FOF_NOCONFIRMATION;
	fileOP.fAnyOperationsAborted =FALSE;
	fileOP.hNameMappings = NULL;
	fileOP.lpszProgressTitle = NULL;

	return (::SHFileOperation(&fileOP) == 0);
}






////////////////////////////////////////////////////////////////////////
// Function: Copy a file or directory to another directory
// Params:
//      LPCTSTR pcszSrc : file or diretory to copy
//		LPCTSTR pcszDstDir : destionation directory
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL CopyFileOrDir(LPCTSTR pcszSrc, LPCTSTR pcszDstDir)
{
	SHFILEOPSTRUCT fileOP;

	TCHAR szSrc[MAX_PATH];
	TCHAR szDst[MAX_PATH];

	ZeroMemory(szSrc,sizeof(szSrc));
	_tcscpy(szSrc,pcszSrc);

	ZeroMemory(szSrc,sizeof(szDst));
	_tcscpy(szDst,pcszDstDir);

	fileOP.hwnd = NULL;
	fileOP.wFunc = FO_COPY;
	fileOP.pFrom = szSrc;
	fileOP.pTo = szDst;
	fileOP.fFlags =0; FOF_SILENT | 
		FOF_NOCONFIRMATION |
		FOF_NOCONFIRMMKDIR |
		FOF_NOERRORUI|
		FOF_NOCONFIRMATION;
	fileOP.fAnyOperationsAborted =FALSE;
	fileOP.hNameMappings = NULL;
	fileOP.lpszProgressTitle = NULL;

	return (::SHFileOperation(&fileOP) == 0);
}


////////////////////////////////////////////////////////////////////////
// Function: Save buffer to file
// Params:
//      LPVOID *pBuf : buffer to write
//		UINT cb      : count of bytes to write
//      LPCTSTR pcszFilePath : path of file to write
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL SaveAsFile(LPCVOID pBuf,UINT cb,LPCTSTR pcszFilePath)
{
	HANDLE hFile = ::CreateFile(pcszFilePath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwWritten;
	BOOL bOK = ::WriteFile(hFile,pBuf,cb,&dwWritten,NULL);
	::CloseHandle(hFile);

	return bOK;
}


////////////////////////////////////////////////////////////////////////
// Function: Get file last write/access/create time
// Params:
//		LPCTSTR pcszFilePath		: path of file
//		SYSTEMTIME *pLastWriteTime  : last write time
//		SYSTEMTIME *pLastAccessTime : last access time 
//		SYSTEMTIME *pCreateTime		: create time
// Return: TRUE : Operation succeeded
//		   FALSE: Operation failed
////////////////////////////////////////////////////////////////////////
BOOL GetFileTime(LPCTSTR pcszFilePath,
				 SYSTEMTIME *pLastWriteTime,
				 SYSTEMTIME *pLastAccessTime,
				 SYSTEMTIME *pCreateTime)
{
	HANDLE hFile = CreateFile(pcszFilePath,GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
		NULL,OPEN_EXISTING,0,NULL);

	if (hFile == NULL)
		return FALSE;

	FILETIME temp;
	FILETIME tmWrite,tmAccess,tmCreate;
	FILETIME *pTmWrite = (pLastWriteTime==NULL ? NULL : &tmWrite);
	FILETIME *pTmAccess = (pLastAccessTime==NULL ? NULL : &tmAccess);
	FILETIME *pTmCreate = (pCreateTime==NULL ? NULL : &tmCreate);

	if (!::GetFileTime(hFile,pTmCreate,pTmAccess,pTmWrite))
	{
		::CloseHandle(hFile);
		return FALSE;
	}	

	if (pLastWriteTime != NULL)
	{
		::FileTimeToLocalFileTime(pTmWrite,&temp);
		::FileTimeToSystemTime(&temp,pLastWriteTime);
	}

	if (pLastAccessTime != NULL)
	{
		::FileTimeToLocalFileTime(pTmAccess,&temp);
		::FileTimeToSystemTime(&temp,pLastAccessTime);
	}

	if (pCreateTime != NULL)
	{
		::FileTimeToLocalFileTime(pTmCreate,&temp);
		::FileTimeToSystemTime(&temp,pCreateTime);
	}

	::CloseHandle(hFile);
	return TRUE;
}

} 