#include "StdAfx.h"
#include ".\file.h"

CFileBase::CFileBase(void)
{
}

CFileBase::~CFileBase(void)
{
}

CFileBase::CFileBase(const char *name)
{
	Open(name);
}
CFileBase::CFileBase(std::string &name)
{
	Open(name);
}
bool CFileBase::Open(std::string &strFileName)
{
	m_File.open(strFileName.c_str(), ios::in | ios::out | ios::binary | ios::app);
	if (m_File.bad())
	{
		return false;
	}
	else
	{
		return true;
	}

}
bool CFileBase::Open(const char *pFileName)
{
	m_File.open(pFileName, ios::in | ios::out | ios::binary | ios::app);
	if (m_File.bad())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int CFileBase::Read(char *buffer, int length)
{
	if (m_File.good())
	{
		m_File.read(buffer, length);
		if (m_File.bad())
		{
			return false;
		}
	}
	return true;
}
int CFileBase::Write(const char *buffer, const int length)
{
	if (m_File.good())
	{
		m_File.write(buffer, length);
		if (m_File.bad())
		{
			return false;
		}
	}
	return true;
}

bool CFileBase::Delete(std::string &strFileName)	
{
	int nReturn = remove(strFileName.c_str());
	if (nReturn == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CFileBase::Delete(const char *pFileName)
{
	int nReturn = remove(pFileName);
	if (nReturn == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CFileBase::Close(void)
{
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}

int CFileBase::GetFileSize(void)
{
	int size = 0;
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
	}
	return size;
}

int CFileBase::GetFileSize(const char *pFileName)
{
	int size = 0;
	m_File.open(pFileName, ios::in | ios::binary);
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
		m_File.close();
	}
	return size;
}

int CFileBase::GetFileSize(std::string &strFileName)
{
	int size = 0;
	m_File.open(strFileName.c_str(), ios::in | ios::binary);
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
		m_File.close();
	}
	return size;
}

bool CFileBase::IsExist(std::string &strFileName)
{
	m_File.open(strFileName.c_str(), ios::in | ios::binary);
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}
bool CFileBase::IsExist(const char *pFileName)
{
	m_File.open(pFileName, ios::in | ios::binary);
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}
