#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "..\..\common\defines.h"
#include "ado2.h"

namespace database
{
	////////////////////////////////////////
	class CDataBase
	{
	public:
		enum action{ADD = 1, DEL, UPDATE, SELECT};
		explicit CDataBase(void);
		~CDataBase(void);

		bool CDataBase::GetClientInfos(const char *sql, 
			std::vector<cds::db_clientinfo> &clientInfos);

		int GetTableCount(const char *tablename);
		bool Execute(const char *sql, CDataBase::action act);
		
	private:
		CADODatabase m_AdoDatabase;
		//CADOCommand m_AdoCommand;
		CADOException m_AdoException;
		//CADOParameter m_AdoParameter;
		//CADORecordset m_AdoRecordset;
		const string m_dbfilename;

	};
	////////////////////////////////////////

};//end of namespace database
#endif //_DATABASE_H_