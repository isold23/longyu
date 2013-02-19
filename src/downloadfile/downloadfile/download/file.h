#ifndef _FILE_H_
#define _FILE_H_
#pragma once

#include <fstream>
#include <string>
using namespace std;

class CFileBase
{
public:
	CFileBase(void);
	CFileBase(const char *name);
	CFileBase(std::string &name);
	~CFileBase(void);

	int Read(char *buffer, int length);
	int Write(const char *buffer, const int length);

	int GetFileSize(const char *pFileName);
	int GetFileSize(std::string &strFileName);
	int GetFileSize(void);

	bool IsExist(std::string &strFileName);
	bool IsExist(const char *pFileName);
	
	bool Delete(std::string &strFileName);
	bool Delete(const char *pFileName);

	bool Open(std::string &strFileName);
	bool Open(const char *pFileName);

	bool Close(void);

private:
	std::fstream m_File;
};
#endif //_FILE_H_
