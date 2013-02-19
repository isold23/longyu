#pragma once



////////////////////////////////////////////////////////////////////////
// Module : FileHelper
// Comment : This module contains utility functions to facilitate file operation
// Author: Sungj
// Date  : 2007/8/12
////////////////////////////////////////////////////////////////////////

namespace Fh
{
	////////////////////////////////////////////////////////////////////////
	// Function: Get name of a file
	// Params:
	//      LPCTSTR pcszFilePath : path of the file
	// Return: file name of the file
	////////////////////////////////////////////////////////////////////////
	CString GetFileName(LPCTSTR pcszFilePath);




	////////////////////////////////////////////////////////////////////////
	// Function: Get name without extension of a file
	// Params:
	//      LPCTSTR pcszFilePath : path of the file
	// Return: file name without extension of the file
	////////////////////////////////////////////////////////////////////////
	CString  GetFileNameWithoutExt(LPCTSTR pcszFilePath);



	////////////////////////////////////////////////////////////////////////
	// Function: Get extension of a file
	// Params:
	//      LPCTSTR pcszFilePath : path of the file
	// Return: file extension of the file
	////////////////////////////////////////////////////////////////////////
	CString GetFileExt(LPCTSTR pcszFilePath);





	////////////////////////////////////////////////////////////////////////
	// Function: Get path of a file 
	// Params:
	//      LPCTSTR pcszFilePath : path of the file
	// Return: folder of the file
	////////////////////////////////////////////////////////////////////////
	CString GetFolderPath(LPCTSTR pcszFilePath);






	////////////////////////////////////////////////////////////////////////
	// Function: Get relative path of an absolute path according to the referenced path
	// Params:
	//      LPCTSTR pcszSrc : absolute path to convert
	//		LPCTSTR pcszRef : referenced absolute path
	//		CString &str    : the returned relative path
	// Return: TRUE : conversion has be done 
	//		   FALSE : conversion cann't be done
	////////////////////////////////////////////////////////////////////////
	BOOL GetRelativePath(LPCTSTR pcszSrc,LPCTSTR pcszRef,CString &str);




	////////////////////////////////////////////////////////////////////////
	// Function: Create a directory if it doesn't exist
	// Params:
	//      LPCTSTR pcszDir : path of the directory to create
	// Return: TRUE : Operation succeeded
	//		   FALSE: Operation failed
	////////////////////////////////////////////////////////////////////////
	BOOL CreateDir(LPCTSTR pcszDir);




	////////////////////////////////////////////////////////////////////////
	// Function: Get absolute path of a relative path according to the referenced path
	// Params:
	//      LPCTSTR pcszSrc : relative path to convert
	//		LPCTSTR pcszRef : referenced absolute path
	//		CString &str    : the returned absolute path
	// Return: TRUE : conversion has be done 
	//		   FALSE : conversion cann't be done
	////////////////////////////////////////////////////////////////////////
	 BOOL GetAbsolutePath(LPCTSTR pcszSrc,LPCTSTR pcszRef,CString &str);




	////////////////////////////////////////////////////////////////////////
	// Function: Get the last drive of a computer
	// Params:
	//      LPTSTR pszDrive : buffer to store the result
	////////////////////////////////////////////////////////////////////////
	void GetLastDrive(LPTSTR pszDrive);





	////////////////////////////////////////////////////////////////////////
	// Function: Log if file exists
	// Params:
	//      LPCTSTR pcszPathName : path of the file to test
	////////////////////////////////////////////////////////////////////////
	BOOL IsFileExist(LPCTSTR pcszPathName);






	////////////////////////////////////////////////////////////////////////
	// Function: Log if directory exists
	// Params:
	//      LPCTSTR pcszPathName : path of the directory to test
	////////////////////////////////////////////////////////////////////////
	BOOL IsDirectoryExist(LPCTSTR pcszDirPath);





	////////////////////////////////////////////////////////////////////////
	// Function: Rename a file or directory
	// Params:
	//      LPCTSTR pcszSrcFileName : path of file or directory to rename
	//      LPCTSTR pcszDstFileName : the destination name
	// Return: TRUE : Operation succeeded
	//		   FALSE: Operation failed
	////////////////////////////////////////////////////////////////////////
	BOOL RenameFile(LPCTSTR pcszSrcFileName,LPCTSTR pcszDstFileName);





	////////////////////////////////////////////////////////////////////////
	// Function: Delete directory recursively
	// Params:
	//      LPCTSTR pcszDir : path of the directory to delete
	// Return: TRUE : Operation succeeded
	//		   FALSE: Operation failed
	////////////////////////////////////////////////////////////////////////
	BOOL DeleteDirectory(LPCTSTR pcszDir);




	////////////////////////////////////////////////////////////////////////
	// Function: Copy a file or directory to another directory
	// Params:
	//      LPCTSTR pcszSrc : file or directory to copy
	//		LPCTSTR pcszDstDir : destination directory
	// Return: TRUE : Operation succeeded
	//		   FALSE: Operation failed
	////////////////////////////////////////////////////////////////////////
	BOOL CopyFileOrDir(LPCTSTR pcszSrc, LPCTSTR pcszDstDir);



	////////////////////////////////////////////////////////////////////////
	// Function: Save buffer to file
	// Params:
	//      LPVOID *pBuf : buffer to write
	//		UINT cb      : count of bytes to write
	//      LPCTSTR pcszFilePath : path of file to write
	// Return: TRUE : Operation succeeded
	//		   FALSE: Operation failed
	////////////////////////////////////////////////////////////////////////
	BOOL SaveAsFile(LPCVOID pBuf,UINT cb,LPCTSTR pcszFilePath);




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
		SYSTEMTIME *pLastWriteTime = NULL,
		SYSTEMTIME *pLastAccessTime = NULL,
		SYSTEMTIME *pCreateTime = NULL);

};