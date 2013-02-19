#include "stdafx.h"
#include "PackDef.h"

int CPackLoginRQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	aoStandardSerialize.Serialize(mszUserPassword, PASSWORD_LEN);
	return 1;
}

int CPackLoginRS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	aoStandardSerialize.Serialize(miReturn);
	return 1;
}

int CPackKeepAliveRQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	return 1;
}

int CPackKeepAliveRS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	return 1;
}

int CPackLogoutRQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	return 1;
}

int CPackLogoutRS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miUserID);
	return 1;
}