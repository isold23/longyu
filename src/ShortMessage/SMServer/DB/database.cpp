#include "stdafx.h"
#include "database.h"

using namespace database;

///////////////////////////////////////////////////
CDataBase::CDataBase(void)
:m_dbfilename("ssm.mdb")
{
	assert(!m_dbfilename.empty());
	CString DatabaseFileName(m_dbfilename.c_str());
	BOOL bRet = m_AdoDatabase.Open(DatabaseFileName.GetBuffer(0), _T(""), _T(""));
	assert(bRet);
}

CDataBase::~CDataBase(void)
{
	if (m_AdoDatabase.IsOpen())
		m_AdoDatabase.Close();
}

int CDataBase::GetTableCount(const char *tablename)
{
	assert(tablename != NULL);
	assert(m_AdoDatabase.IsOpen());
	int count = 0;
	CString SQL("");
	SQL.Format("SELECT * FROM %s", tablename);
	CADORecordset recordset(&m_AdoDatabase);
	BOOL bRet = recordset.Open(SQL.GetBuffer(0));
	assert(bRet);
	count =  recordset.GetRecordCount();
	recordset.Close();
	return count;
}

bool CDataBase::GetUserInfos(const char *sql, vector<cds::db_userinfo> &userinfos)
{
	CADORecordset recordset(&m_AdoDatabase);
	CString SQL(sql);
	BOOL bRet = recordset.Open(SQL.GetBuffer(0));
	assert(bRet);
	while(!recordset.IsEOF())
	{
		db_userinfo info;
		CString str = "";
		recordset.GetFieldValue(1, str);
		assert(str.GetLength() < uplen);
		memcpy(info.m_UserName, str.GetBuffer(0), str.GetLength());
		recordset.GetFieldValue(2, str);
		assert(str.GetLength() < uplen);
		memcpy(info.m_UserPassword, str.GetBuffer(0), str.GetLength());
		recordset.MoveNext();
		userinfos.push_back(info);
	}
	recordset.Close();
	return bRet ? true : false;
}

bool CDataBase::GetHistoryMsg(const char *sql, std::vector<cds::db_history> &historys)
{
	CADORecordset recordset(&m_AdoDatabase);
	CString SQL(sql);
	BOOL bRet = recordset.Open(SQL.GetBuffer(0));
	assert(bRet);
	while(!recordset.IsEOF())
	{
		cds::db_history history;
		CString str = "";
		recordset.GetFieldValue(1, str);
		assert(str.GetLength() < uplen);
		memcpy(history.m_UserName, str.GetBuffer(0), str.GetLength());
		recordset.GetFieldValue(2, str);
		assert(str.GetLength() < 200);
		memcpy(history.m_Content, str.GetBuffer(0), str.GetLength());
		recordset.GetFieldValue(3, str);
		assert(str.GetLength() <= 50);
		memcpy(history.m_Data, str.GetBuffer(0), str.GetLength());
		recordset.MoveNext();
		historys.push_back(history);
	}
	recordset.Close();
	return bRet ? true : false;
}

bool CDataBase::Execute(const char *sql, CDataBase::action act)
{
	assert(sql != NULL);
	assert(m_AdoDatabase.IsOpen());
	BOOL bRet = FALSE;
	try
	{
		switch(act)
		{
		case ADD:
			{
				CADORecordset recordset(&m_AdoDatabase);
				CString SQL(sql);
				bRet = recordset.Open(SQL.GetBuffer(0));
				assert(bRet);
				recordset.Close();
				break;
			}
		case DEL:
			{
				CADORecordset recordset(&m_AdoDatabase);
				CString SQL(sql);
				bRet = recordset.Open(SQL.GetBuffer(0));
				assert(bRet);
				recordset.Close();
				break;
			}
		case UPDATE:
			{
				CADORecordset recordset(&m_AdoDatabase);
				CString SQL(sql);
				bRet = recordset.Open(SQL.GetBuffer(0));
				assert(bRet);
				recordset.Close();
				break;
			}
		default:
			{
				throw "unknow db action";
			}
		}
	}
	catch(char *exception)
	{
		PrintLog(_LOG_LEVEL_DEBUG, exception);
	}
	catch(...)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "operate datebase error");
		return false;
	}
	return bRet ? true : false;
}
////////////////////////////////////////////////////
