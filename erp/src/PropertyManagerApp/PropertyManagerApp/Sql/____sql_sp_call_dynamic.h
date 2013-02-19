#ifndef ____sql_sp_call_impl
#error "sp.h must be included ____sql_sp_call_impl!!!!
#else


// STORED PROCEDURE NAME:RRGetGroupOps
// PARAMETERS:
//	_RecordsetPtr &rst
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RRGetGroupOps(_RecordsetPtr &rst,int UserId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RRGetGroupOps";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	rst = cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RRGetOps
// PARAMETERS:
//	_RecordsetPtr &rst
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RRGetOps(_RecordsetPtr &rst,int UserId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RRGetOps";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	rst = cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RRGetUserOps
// PARAMETERS:
//	_RecordsetPtr &rst
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
// RETURN:int
inline int RRGetUserOps(_RecordsetPtr &rst,int UserId)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RRGetUserOps";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	rst = cmd->Execute(NULL,NULL,adCmdStoredProc);
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RRGetUsers
// PARAMETERS:
//	_RecordsetPtr &rst
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RRGetUsers(_RecordsetPtr &rst,int UserId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RRGetUsers";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	rst = cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVAddGroup
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Intro	NAME:Intro	TYPE:varchar	DIRECTION:in	LENGTH:256
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVAddGroup(int UserId,int GroupId,CString Name,CString Intro,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVAddGroup";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramIntro = cmd->CreateParameter(L"@Intro",adVarChar,adParamInput,256,Intro.GetString());
	cmd->Parameters->Append(paramIntro);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVAddGroupOp
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OpId	NAME:OpId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVAddGroupOp(int UserId,int GroupId,int OpId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVAddGroupOp";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramOpId = cmd->CreateParameter(L"@OpId",adInteger,adParamInput,4,OpId);
	cmd->Parameters->Append(paramOpId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVAddOp
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Id	NAME:Id	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Intro	NAME:Intro	TYPE:varchar	DIRECTION:in	LENGTH:256
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVAddOp(int UserId,int Id,CString Name,CString Intro,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVAddOp";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramId = cmd->CreateParameter(L"@Id",adInteger,adParamInput,4,Id);
	cmd->Parameters->Append(paramId);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramIntro = cmd->CreateParameter(L"@Intro",adVarChar,adParamInput,256,Intro.GetString());
	cmd->Parameters->Append(paramIntro);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVAddUser
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Pwd	NAME:Pwd	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVAddUser(int UserId,CString Name,CString Pwd,int GroupId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVAddUser";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramPwd = cmd->CreateParameter(L"@Pwd",adVarChar,adParamInput,32,Pwd.GetString());
	cmd->Parameters->Append(paramPwd);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVCheckUser
// PARAMETERS:
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Pwd	NAME:Pwd	TYPE:varchar	DIRECTION:in	LENGTH:32
// RETURN:int
inline int RVCheckUser(CString Name,CString Pwd)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVCheckUser";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramPwd = cmd->CreateParameter(L"@Pwd",adVarChar,adParamInput,32,Pwd.GetString());
	cmd->Parameters->Append(paramPwd);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVDelGroup
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVDelGroup(int UserId,int GroupId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVDelGroup";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVDelGroupOp
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OpId	NAME:OpId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVDelGroupOp(int UserId,int GroupId,int OpId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVDelGroupOp";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramOpId = cmd->CreateParameter(L"@OpId",adInteger,adParamInput,4,OpId);
	cmd->Parameters->Append(paramOpId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVDelOp
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Id	NAME:Id	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVDelOp(int UserId,int Id,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVDelOp";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramId = cmd->CreateParameter(L"@Id",adInteger,adParamInput,4,Id);
	cmd->Parameters->Append(paramId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVDelUser
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OpedId	NAME:OpedId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVDelUser(int UserId,int OpedId,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVDelUser";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramOpedId = cmd->CreateParameter(L"@OpedId",adInteger,adParamInput,4,OpedId);
	cmd->Parameters->Append(paramOpedId);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVUpdateGroup
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Intro	NAME:Intro	TYPE:varchar	DIRECTION:in	LENGTH:256
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVUpdateGroup(int UserId,int GroupId,CString Name,CString Intro,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVUpdateGroup";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramIntro = cmd->CreateParameter(L"@Intro",adVarChar,adParamInput,256,Intro.GetString());
	cmd->Parameters->Append(paramIntro);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVUpdateGroupUser
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OpedId	NAME:OpedId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Password	NAME:Password	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVUpdateGroupUser(int UserId,int OpedId,int GroupId,CString Password,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVUpdateGroupUser";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramOpedId = cmd->CreateParameter(L"@OpedId",adInteger,adParamInput,4,OpedId);
	cmd->Parameters->Append(paramOpedId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamInput,4,GroupId);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramPassword = cmd->CreateParameter(L"@Password",adVarChar,adParamInput,32,Password.GetString());
	cmd->Parameters->Append(paramPassword);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVUpdateOp
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OldOpId	NAME:OldOpId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Id	NAME:Id	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@Name	NAME:Name	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Intro	NAME:Intro	TYPE:varchar	DIRECTION:in	LENGTH:256
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVUpdateOp(int UserId,int OldOpId,int Id,CString Name,CString Intro,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVUpdateOp";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramOldOpId = cmd->CreateParameter(L"@OldOpId",adInteger,adParamInput,4,OldOpId);
	cmd->Parameters->Append(paramOldOpId);
	_ParameterPtr paramId = cmd->CreateParameter(L"@Id",adInteger,adParamInput,4,Id);
	cmd->Parameters->Append(paramId);
	_ParameterPtr paramName = cmd->CreateParameter(L"@Name",adVarChar,adParamInput,32,Name.GetString());
	cmd->Parameters->Append(paramName);
	_ParameterPtr paramIntro = cmd->CreateParameter(L"@Intro",adVarChar,adParamInput,256,Intro.GetString());
	cmd->Parameters->Append(paramIntro);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:RVUpdateUserPwd
// PARAMETERS:
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@OldPassword	NAME:OldPassword	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@Password	NAME:Password	TYPE:varchar	DIRECTION:in	LENGTH:32
//	SQLNAME:@ErrDesc	NAME:ErrDesc	TYPE:varchar	DIRECTION:out	LENGTH:128
// RETURN:int
inline int RVUpdateUserPwd(int UserId,CString OldPassword,CString Password,CString &ErrDesc)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"RVUpdateUserPwd";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramRetValue = cmd->CreateParameter("@RetValue",adInteger,adParamReturnValue,4);
	cmd->Parameters->Append(paramRetValue);
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramOldPassword = cmd->CreateParameter(L"@OldPassword",adVarChar,adParamInput,32,OldPassword.GetString());
	cmd->Parameters->Append(paramOldPassword);
	_ParameterPtr paramPassword = cmd->CreateParameter(L"@Password",adVarChar,adParamInput,32,Password.GetString());
	cmd->Parameters->Append(paramPassword);
	_ParameterPtr paramErrDesc = cmd->CreateParameter(L"@ErrDesc",adVarChar,adParamOutput,128,VT_NULL);
	cmd->Parameters->Append(paramErrDesc);
	cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramErrDesc->Value.vt != VT_NULL) ErrDesc = (CString)paramErrDesc->Value;
	return (int)paramRetValue->Value;
	____sql_sp_call_catch
		return ____sql_sp_call_errflag;
	____sql_sp_call_end
}


// STORED PROCEDURE NAME:VRGetUserGroup
// PARAMETERS:
//	_RecordsetPtr &rst
//	SQLNAME:@UserId	NAME:UserId	TYPE:int	DIRECTION:in	LENGTH:4
//	SQLNAME:@GroupId	NAME:GroupId	TYPE:int	DIRECTION:out	LENGTH:4
//	SQLNAME:@GroupName	NAME:GroupName	TYPE:varchar	DIRECTION:out	LENGTH:32
//	SQLNAME:@GroupIntro	NAME:GroupIntro	TYPE:varchar	DIRECTION:out	LENGTH:256
// RETURN:void
inline void VRGetUserGroup(_RecordsetPtr &rst,int UserId,int &GroupId,CString &GroupName,CString &GroupIntro)
{
	____sql_sp_call_try_begin
		_CommandPtr cmd(__uuidof(Command));
	cmd->CommandText = L"VRGetUserGroup";
	cmd->ActiveConnection = m_conn;
	cmd->CommandType = adCmdStoredProc;
	_ParameterPtr paramUserId = cmd->CreateParameter(L"@UserId",adInteger,adParamInput,4,UserId);
	cmd->Parameters->Append(paramUserId);
	_ParameterPtr paramGroupId = cmd->CreateParameter(L"@GroupId",adInteger,adParamOutput,4,VT_NULL);
	cmd->Parameters->Append(paramGroupId);
	_ParameterPtr paramGroupName = cmd->CreateParameter(L"@GroupName",adVarChar,adParamOutput,32,VT_NULL);
	cmd->Parameters->Append(paramGroupName);
	_ParameterPtr paramGroupIntro = cmd->CreateParameter(L"@GroupIntro",adVarChar,adParamOutput,256,VT_NULL);
	cmd->Parameters->Append(paramGroupIntro);
	rst = cmd->Execute(NULL,NULL,adCmdStoredProc);
	if (paramGroupId->Value.vt != VT_NULL) GroupId = (int)paramGroupId->Value;
	if (paramGroupName->Value.vt != VT_NULL) GroupName = (CString)paramGroupName->Value;
	if (paramGroupIntro->Value.vt != VT_NULL) GroupIntro = (CString)paramGroupIntro->Value;
	____sql_sp_call_catch
		____sql_sp_call_end
}


#endif