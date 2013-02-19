#ifndef ____sql_sp_call_impl
#define ____sql_sp_call_impl
#include <vector>

#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF", "adoEOF")
#define ____sql_sp_call_try_begin try{____sql_sp_call_clear_err();
#define ____sql_sp_call_catch }catch (_com_error &e) {____sql_sp_call_set_err(e);
#define ____sql_sp_call_end }

#define ____sql_sp_call_errflag (-739934477)

void ____sql_sp_call_clear_err(void);
void ____sql_sp_call_set_err(_com_error &e);
const _com_error&  sperr(void);
 

struct SpComLib
{
	SpComLib(void) { ::CoInitialize(NULL); }
	~SpComLib(void) { ::CoUninitialize(); };
};


class Sp
{
public:
	Sp(void);
	~Sp(void);

	BOOL Open(LPCTSTR lpcszConn,int nTimeout=-1,BOOL bAsync=FALSE);
	void Close(BOOL bCancel);

	BOOL IsConnected(void);


#include "____sql_sp_call_dynamic.h"

protected:
	_ConnectionPtr m_conn;

};


extern Sp g_sp;



#endif
