#include "crs_cl_strudef.h"

//*****************************************************************************************//
//********************* 语音对聊包(开始请求、应答和停止) *******************************//
//*****************************************************************************************//
//语音对聊请求包：
int STRU_CL_CRS_VOICE_CHAT_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																																										
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_VOICE_CHAT_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_CL_CRS_VOICE_CHAT_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																																											
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							

int STRU_CL_CRS_VOICE_CHAT_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64SelfUserId);
	aoStandardSerialize.Serialize(mi64DestUserId);
	return 1;
}

/**********************************************************************************/
//语音对聊应答包：

int STRU_CL_CRS_VOICE_CHAT_RS::Pack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_VOICE_CHAT_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_CL_CRS_VOICE_CHAT_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																																													
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																									
}																							


int STRU_CL_CRS_VOICE_CHAT_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64SelfUserId);
	aoStandardSerialize.Serialize(mi64DestUserId);
	return 1;
}

/**********************************************************************************/
//服务器语音对聊应答包：

int STRU_CL_CRS_VOICE_CHAT_SERVER_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_VOICE_CHAT_SERVER_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_VOICE_CHAT_SERVER_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_CL_CRS_VOICE_CHAT_SERVER_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mi64RQUserId);
	aoStandardSerialize.Serialize(mi64RSUserId);
	return 1;
}

/**********************************************************************************/
//语音对聊停止通知

int STRU_CL_CRS_VOICE_CHAT_STOP_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_VOICE_CHAT_STOP_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_VOICE_CHAT_STOP_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_VOICE_CHAT_STOP_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64SelfUserId);
	aoStandardSerialize.Serialize(mi64DestUserId);
	return 1;
}
//UDP登录房间前请求Token值	

int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_UDPFIRSTLOGIN_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ::Serialize(CStandardSerialize& aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	return 1;
}

int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_UDPFIRSTLOGIN_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(mulToken);
	return 1;

}

//请求对应信息报 用于避免初始化房间乱序


int STRU_UC_CL_CRS_LOGIN_INFO_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGIN_INFO_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGIN_INFO_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_LOGIN_INFO_RQ::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(muLoginPhase); //信息包ID

	return 1;
}

int STRU_UC_CL_CRS_LOGIN_INFO_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGIN_INFO_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGIN_INFO_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			


}																							



int STRU_UC_CL_CRS_LOGIN_INFO_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(muLoginPhase); //信息包ID

	return 1;
}
//存活包

int STRU_UC_CL_CRS_ALIVE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_ALIVE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_ALIVE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_ALIVE_RQ::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mlHallID);

	return 1;
}

int STRU_UC_CL_CRS_ALIVE_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_ALIVE_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_ALIVE_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							


	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_ALIVE_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(mi64LastTime);

	return 1;
}
//退出房间请求

int STRU_UC_CL_CRS_LOGOUT::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGOUT; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGOUT::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_LOGOUT::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mlHallID);

	return 1;
}

int STRU_UC_CL_CRS_LOGOUT_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGOUT_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGOUT_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_LOGOUT_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(miErrorCode);
	aoStandardSerialize.Serialize(mszErrorInfo, ERROR_BUFFER_LENGTH + 1);

	return 1;
}
//聊天室登录请求
STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO::STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO()
{
	menumAttributeType = AT_BYTE_REDMEMBER;
	mnDateLen = 0;
	mPbVal = NULL;
}

int STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{

	int liAType = menumAttributeType;
	aoStandardSerialize.Serialize(liAType);		//Serialize不支持枚举类型
	aoStandardSerialize.Serialize(mnDateLen);

	if ((aoStandardSerialize.mbyType == CStandardSerialize::LOAD))
	{
		if(mnDateLen <= 0)
		{
			return -1;
		}

		menumAttributeType = (LoginAttributeType)liAType;

		mPbVal = new char[mnDateLen];
		if(mPbVal == NULL)
		{
			return -1;
		}
	}
	aoStandardSerialize.Serialize(mPbVal,mnDateLen + 1);

	return 1;

}

STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007::~STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007()
{
	if(mpAttributeInfo != NULL)
	{
		delete [] mpAttributeInfo;
		mpAttributeInfo = NULL;
	}
}


int STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGIN_HALL_RQ_2007; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																	
} 																							

int STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																							
}																							


int STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007::Serialize( CStandardSerialize & aoStandardSerialize )
{
	aoStandardSerialize.Serialize(macVersion , VERSION_LEN + 1);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(macNickName , NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(macPassword , UC_HALL_PWD_LEN + 1);
	aoStandardSerialize.Serialize(mbySource);
	aoStandardSerialize.Serialize(mlUserState);
	aoStandardSerialize.Serialize(macUserPwd  , MD5_LEN + 1);
	aoStandardSerialize.Serialize(mbyUserLanguage);
	aoStandardSerialize.Serialize(mbyAttributeCount);

	if ((aoStandardSerialize.mbyType == CStandardSerialize::LOAD))
	{
		if(mbyAttributeCount <= 0)
		{
			return 1;
		}

		mpAttributeInfo = new STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO[mbyAttributeCount];
		if (!mpAttributeInfo)
			return -1;
	}
	for(int i = 0; i < mbyAttributeCount; i++)
	{
		if (mpAttributeInfo[i].Serialize(aoStandardSerialize) == -1)
		{
			return -1;
		}
	}
	return 1;
}

//聊天室登录应答

int STRU_UC_CL_CRS_LOGIN_HALL_RS_2007::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGIN_HALL_RS_2007; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGIN_HALL_RS_2007::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CL_CRS_LOGIN_HALL_RS_2007::Serialize(CStandardSerialize & aoStandardSerialize)   
{

	aoStandardSerialize.Serialize(mulToken);
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(mlRoomMaxPlayer);
	aoStandardSerialize.Serialize(macErrInfo,ERR_BUF_LEN + 1);
	aoStandardSerialize.Serialize(mszVoiceIp , 64 );
	aoStandardSerialize.Serialize(musVoicePort);
	aoStandardSerialize.Serialize(macTopic , UC_CHATROOM_TOPIC_LEN + 1);
	aoStandardSerialize.Serialize(macSalutatory , UC_CHATROOM_SALUTATORY_LEN + 1);
	aoStandardSerialize.Serialize(macPwd,UC_HALL_PWD_LEN + 1);
	aoStandardSerialize.Serialize(macImvName,CHATROOM_IMV_NAME_LEN+1);
	aoStandardSerialize.Serialize(mlHallProperty);
	aoStandardSerialize.Serialize(mlHallState);
	aoStandardSerialize.Serialize(mbyMicNum);
	aoStandardSerialize.Serialize(macWUserURL,ERR_BUF_LEN + 1);

	return 1;
}

//聊天室登录应答

int STRU_UC_CL_CRS_LOGIN_HALL_RS_2009::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LOGIN_HALL_RS_2009; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LOGIN_HALL_RS_2009::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_LOGIN_HALL_RS_2009::Serialize(CStandardSerialize & aoStandardSerialize)   
{

	aoStandardSerialize.Serialize(mulToken);
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mlHallID);
	aoStandardSerialize.Serialize(mlRoomMaxPlayer);
	aoStandardSerialize.Serialize(macErrInfo,ERR_BUF_LEN + 1);
	aoStandardSerialize.Serialize(mszVoiceIp , 64 );
	aoStandardSerialize.Serialize(musVoicePort);
	aoStandardSerialize.Serialize(macTopic , UC_CHATROOM_TOPIC_LEN + 1);
	aoStandardSerialize.Serialize(macSalutatory , UC_CHATROOM_SALUTATORY_LEN + 1);
	aoStandardSerialize.Serialize(macPwd,UC_HALL_PWD_LEN + 1);
	aoStandardSerialize.Serialize(macImvName,CHATROOM_IMV_NAME_LEN+1);
	//aoStandardSerialize.Serialize(mlHallProperty);
	aoStandardSerialize.Serialize(mlHallState);
	aoStandardSerialize.Serialize(mbyMicNum);
	aoStandardSerialize.Serialize(macWUserURL,ERR_BUF_LEN + 1);

	aoStandardSerialize.Serialize(mi64HallProperty);

	return 1;
}



int STRU_CHATROOM_USER_INFO_2007::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN+1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(mbyPower);
	aoStandardSerialize.Serialize(mlUserState);
	aoStandardSerialize.Serialize(mbyVoiceState);
	aoStandardSerialize.Serialize(mbyUserLanguage);
	aoStandardSerialize.Serialize(miRedMemTime);
	return 1;
}

STRU_UC_CL_CRS_USER_INFO_ID_2007::~STRU_UC_CL_CRS_USER_INFO_ID_2007()
{
	if(mpUserIDList != NULL)
	{
		delete [] mpUserIDList;
		mpUserIDList = NULL;
	}
}


int STRU_UC_CL_CRS_USER_INFO_ID_2007::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_INFO_ID_2007; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_INFO_ID_2007::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_USER_INFO_ID_2007::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mwUserCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		mpUserIDList = NULL;
		if (mwUserCount > 0)
		{
			mpUserIDList = new STRU_CHATROOM_USER_INFO_2007[mwUserCount];
		}
	}
	for(int i = 0; i < mwUserCount; i++)
	{
		mpUserIDList[i].Serialize(aoStandardSerialize);
	}
	return 1;
}


int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_ENTRY_OTHERUSER_ID_400; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(mbyPower);
	aoStandardSerialize.Serialize(mlUserState);
	//添加语言类型
	aoStandardSerialize.Serialize(mbyUserLanguage);
	aoStandardSerialize.Serialize(miRedMemTime);
	return 1;
}

int STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LEAVE_OTHERUSER_ID_350; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mbyCancelType);
	aoStandardSerialize.Serialize(macReason,REASON_LEN + 1);
	return 1;

}																	


int STRU_UC_CL_CRS_MIC_INFO_LIST_ID::STRU_UC_CL_CRS_MIC_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mbyOperateType);
	aoStandardSerialize.Serialize(mbyMicIndex);
	if(CHG_TYPE_DELETE != mbyOperateType)
	{
		aoStandardSerialize.Serialize(mbSupportVideo);
		mstruAudioConfig.Serialize(aoStandardSerialize);
		if(mbSupportVideo)
		{
			mstruVideoConfig.Serialize(aoStandardSerialize);
		}
		aoStandardSerialize.Serialize(mwMicStatue);
		aoStandardSerialize.Serialize(mwMicTimeLen);
		aoStandardSerialize.Serialize(mi64ManagerID);
		aoStandardSerialize.Serialize(mlDeltaSpeakTime);
	}
	return 1;
}

STRU_UC_CL_CRS_MIC_INFO_LIST_ID::~STRU_UC_CL_CRS_MIC_INFO_LIST_ID()
{
	if(mpMicInfoList != NULL)
	{
		delete [] mpMicInfoList;
		mpMicInfoList = NULL;
	}
}

int STRU_UC_CL_CRS_MIC_INFO_LIST_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MIC_INFO_LIST_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_MIC_INFO_LIST_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CL_CRS_MIC_INFO_LIST_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mwMicCount);
	if (CStandardSerialize::LOAD == aoStandardSerialize.mbyType)
	{
		mpMicInfoList = new STRU_UC_CL_CRS_MIC_INFO[mwMicCount];
	}
	for(int i=0; mwMicCount>i; ++i)
	{
		(mpMicInfoList + i)->Serialize(aoStandardSerialize);
	}
	return 1;

}


int STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::STRU_UC_CL_CRS_SPEAKER_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mbyMicIndex);
	aoStandardSerialize.Serialize(mi64SpeakerUserID);
	if(mi64SpeakerUserID)
	{
		aoStandardSerialize.Serialize(mbContainAudioInfo);
		if(mbContainAudioInfo)
		{
			mstrAudioInfo.Serialize(aoStandardSerialize);
		}
		aoStandardSerialize.Serialize(mbContainVideoInfo);
		if(mbContainVideoInfo)
		{
			mstrVideoInfo.Serialize(aoStandardSerialize);
		}
	}
	return 1;
}

STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::~STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID()
{
	if(mpSpeakerUserInfo != NULL)
	{
		delete [] mpSpeakerUserInfo;
		mpSpeakerUserInfo = NULL;
	}
}


int STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_SPEAKER_INFO_LIST_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mbySpeakerNum);
	if (CStandardSerialize::LOAD == aoStandardSerialize.mbyType)
	{
		mpSpeakerUserInfo = new STRU_UC_CL_CRS_SPEAKER_INFO[mbySpeakerNum];
	}
	for(int i=0; i<mbySpeakerNum; ++i)
	{
		(mpSpeakerUserInfo + i)->Serialize(aoStandardSerialize);
	}
	return 1;

}


int STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mbyCount);
	if ((aoStandardSerialize.mbyType == CStandardSerialize::LOAD) && (mbyCount >0))
	{
		mpUserIdList = new int64_t[mbyCount];
	}

	for(int i = 0; i < mbyCount; i++)
	{
		aoStandardSerialize.Serialize(mpUserIdList[i]);
	}

	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}
STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID::~STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID()
{
	if(mpUserIdList != NULL)
	{
		delete [] mpUserIdList;
		mpUserIdList = NULL;
	}
}

int STRU_WAITING_USER_INFO::Serialize(CStandardSerialize & aoStandardSerialize) 
{ 
	aoStandardSerialize.Serialize(mi64UserID); 
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN+1); 
	aoStandardSerialize.Serialize(mlHallID); aoStandardSerialize.Serialize(mlPicIndex); 
	aoStandardSerialize.Serialize(mwVersion);
	aoStandardSerialize.Serialize(mbyGrade);
	aoStandardSerialize.Serialize(mlUserState);
	return 1;
}

/**********************************************************************************/
//当前麦克风发言顺序包(GAS服务器向所有客户端发送)

int STRU_SINASHOW_MICROPHONE_ORDER_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_SINASHOW_MICROPHONE_ORDER_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_SINASHOW_MICROPHONE_ORDER_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_SINASHOW_MICROPHONE_ORDER_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mbyCount);
	if ((aoStandardSerialize.mbyType == CStandardSerialize::LOAD) && (mbyCount >0))
	{
		mpUserIdList = new STRU_WAITING_USER_INFO[mbyCount];
	}

	for(int i = 0; i < mbyCount; i++)
	{
		mpUserIdList[i].Serialize(aoStandardSerialize);
	}

	return 1;
}


int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mwSpeakOrder);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}


int STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mi64UserId);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MICROPHONE_MANAGER_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerID);
	aoStandardSerialize.Serialize(mwType);
	aoStandardSerialize.Serialize(mi64DesUserID);
	aoStandardSerialize.Serialize(mbyMicIndex);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}

int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MICROPHONE_MANAGER_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerID);
	aoStandardSerialize.Serialize(mwType);
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mi64DesUserID);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}

int STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROPHONE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(miInsertIndex);
	return 1;
}

int STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_STOP_SPEAK_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserId);
	return 1;

}


int STRU_UC_CL_CRS_BEGIN_SPEAK_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_BEGIN_SPEAK_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_BEGIN_SPEAK_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CL_CRS_BEGIN_SPEAK_ID::Serialize(CStandardSerialize & aoStandardSerialize) 
{
	//try
	//{
	aoStandardSerialize.Serialize(mbyMicIndex);
	aoStandardSerialize.Serialize(mi64UserID);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mbyMinute);
	//}
	//catch(...)
	//{
	//    return -1;
	//}

	aoStandardSerialize.Serialize(mbyMicIndex);

	return 1;
}


int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mbyMinute);
	aoStandardSerialize.Serialize(mbyMicIndex);
	return 1;
}


int STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CNG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyMinute);
	aoStandardSerialize.Serialize(mi64ManagerId);
	//}
	//catch(...)
	//{
	//    return -1;
	//}

	aoStandardSerialize.Serialize(mbyMicIndex);

	return 1;
}


int STRU_CL_CRS_OPERATION_ON_USER_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_OPERATION_ON_USER_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_OPERATION_ON_USER_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mbyType);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mlOtherParam);
	aoStandardSerialize.Serialize(mstrDescribe,UC_MANAGER_USER_DESCRIBE_LEN + 1);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mbyType);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mstrDescribe,UC_MANAGER_USER_DESCRIBE_LEN + 1);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_MIC_STATE_CONTROL_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID::Serialize(CStandardSerialize &aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerID);
	aoStandardSerialize.Serialize(mbyMicIndex);
	aoStandardSerialize.Serialize(mbOperateType);
	aoStandardSerialize.Serialize(mwValue);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_RECV_STATE_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mbyMicIndex);
	aoStandardSerialize.Serialize(mbyMediaType);
	aoStandardSerialize.Serialize(mbyState);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_CL_CRS_USER_BE_OPERATED_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_BE_OPERATED_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_USER_BE_OPERATED_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_USER_BE_OPERATED_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyType);
	aoStandardSerialize.Serialize(mstrDescribe,UC_MANAGER_USER_DESCRIBE_LEN + 1);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_CL_CRS_USER_POWER_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_POWER_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_USER_POWER_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_USER_POWER_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyPower);
	return 1;
}

int STRU_CL_CRS_VOICE_STATE_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_VOICE_STATE_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_VOICE_STATE_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_VOICE_STATE_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyState);
	return 1;
	//}catch(...)
	//{
	//    return -1;
	//}
}


int STRU_UC_CL_CRS_BLACK_QUERY_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_BLACK_QUERY_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_BLACK_QUERY_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_BLACK_QUERY_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId); //请求者ID
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_BLACKIP_LIST_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_BLACKIP_LIST_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_BLACKIP_LIST_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_BLACKIP_LIST_RQ::Serialize (CStandardSerialize& aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}
int STRU_UC_CL_CRS_TIME_BLACK_LIST::STRU_TIME_KICKOUT_USER::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try{
	aoStandardSerialize.Serialize(mi64UserID); //用户ID
	aoStandardSerialize.Serialize(mlNoComeInTime); //限制时间
	aoStandardSerialize.Serialize(mlResidualTime); //剩余时间
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}


int STRU_UC_CL_CRS_TIME_BLACK_LIST::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_TIME_BLACK_LIST; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_TIME_BLACK_LIST::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_TIME_BLACK_LIST::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId); //请求者ID
	aoStandardSerialize.Serialize(msUserCount); //用户数目

	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		mpBlackList = NULL;

		if (msUserCount > 0)
			mpBlackList = new STRU_TIME_KICKOUT_USER[msUserCount];
	}

	for(int i = 0; i < msUserCount; i++)
	{
		//if (mpBlackList[i].Serialize(aoStandardSerialize) == -1)
		//    return -1;
		//change by fanyunfeng 2006-01-24
		mpBlackList[i].Serialize(aoStandardSerialize);
	}

	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}

}



int STRU_UC_CL_CRS_BLACKIP_LIST_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_BLACKIP_LIST_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_BLACKIP_LIST_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_BLACKIP_LIST_RS::STRU_BLACK_IP_INFO::Serialize(CStandardSerialize& aoStandardSerialize)
{
	aoStandardSerialize.Serialize (mi64UserID);
	aoStandardSerialize.Serialize (mulIP);
	aoStandardSerialize.Serialize (mlNoComeInTime);
	aoStandardSerialize.Serialize (mlResidualTime);
	return 1;
}

STRU_UC_CL_CRS_BLACKIP_LIST_RS::~STRU_UC_CL_CRS_BLACKIP_LIST_RS()
{
	if(mpBlackList != NULL)
	{
		delete [] mpBlackList;
		mpBlackList = NULL;
	}
}										



int STRU_UC_CL_CRS_BLACKIP_LIST_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize (mi64ManagerId);
	aoStandardSerialize.Serialize (msCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		if (msCount > 0)
			mpBlackList = new STRU_BLACK_IP_INFO[msCount];
		//else
		//	mpBlackList = NULL;
	}
	//PSTRU_BLACK_IP_INFO lpstruTemp;
	for(int i = 0; i < msCount; i++)
	{
		//lpstruTemp = mpBlackList + i;
		//lpstruTemp->Serialize(aoStandardSerialize);

		mpBlackList[i].Serialize(aoStandardSerialize);
	}
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_UC_CL_CRS_USER_STATE_CHG_ID_390::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_STATE_CHG_ID_390; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_STATE_CHG_ID_390::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_USER_STATE_CHG_ID_390::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mwChgType);
	aoStandardSerialize.Serialize(mbyChgVal);
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_FLOWERS_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_FLOWERS_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_FLOWERS_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_FLOWERS_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mi64SrcUserID);
	aoStandardSerialize.Serialize(mbyIsPrivate);
	aoStandardSerialize.Serialize(mlFlowerType);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}
//add by qufeng 2008-06-12-----------------------------------------

int STRU_CL_CRS_OFFER_BROW_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_NEW_OFFER_BROW_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_OFFER_BROW_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_OFFER_BROW_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mi64SrcUserID);
	aoStandardSerialize.Serialize(mbyBrowType);	
	aoStandardSerialize.Serialize(mbyIsPrivate);
	aoStandardSerialize.Serialize(mwOfferBrowLen);
	aoStandardSerialize.Serialize(macOfferBrowName, mwOfferBrowLen,UC_NEW_OFFER_BROW_NAME_LEN + 1);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}
//--------------------------------------------------------------------------



int STRU_UC_CL_CRS_USER_STATE_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_STATE_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_STATE_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_USER_STATE_RS::Serialize(CStandardSerialize& aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mlState);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}


int STRU_UC_CL_CRS_USER_STATE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_STATE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_STATE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_USER_STATE_RQ::Serialize(CStandardSerialize& aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}
int STRU_UC_CL_CRS_CHAT_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mwMoodLen);
	aoStandardSerialize.Serialize(mstrMood,mwMoodLen,CRS_DATA_LEN+1);  
	aoStandardSerialize.Serialize(mwControlLen);
	aoStandardSerialize.Serialize(mstrControl,mwControlLen,CRS_DATA_LEN+1);  
	if(CStandardSerialize::LOAD ==aoStandardSerialize.mbyType)
		aoStandardSerialize.Serialize(mstrContent,mwLen-GetSubLen(),CRS_DATA_LEN+1); 
	else
		aoStandardSerialize.Serialize(mstrContent,mwContentLen,CRS_DATA_LEN+1); 
	aoStandardSerialize.Serialize(mi64FromId);    
	aoStandardSerialize.Serialize(mi64ToId);  
	aoStandardSerialize.Serialize(mbyChatType);
	return 1;
}

int STRU_UC_CL_CRS_DATA_ID_350::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_DATA_ID_350; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_DATA_ID_350::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CL_CRS_DATA_ID_350::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mwDataLen);

	mChatInfo.mwLen = mwDataLen;
	mChatInfo.Serialize(aoStandardSerialize);

	//aoStandardSerialize.Serialize(mData,mwDataLen,CRS_DATA_LEN+1);        
	aoStandardSerialize.Serialize(mi64SrcUserID);        
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_DATA_ID_LONG::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType = UC_CL_CRS_DATA_ID_LONG; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_DATA_ID_LONG::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CL_CRS_DATA_ID_LONG::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mwDataLen);

	mChatInfo.mwLen = mwDataLen;
	mChatInfo.Serialize(aoStandardSerialize);

	//aoStandardSerialize.Serialize(mData,mwDataLen,CRS_DATA_LEN+1);        
	aoStandardSerialize.Serialize(mi64SrcUserID);        
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}

int STRU_UC_CL_CRS_GENERAL_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64FromId);
	aoStandardSerialize.Serialize(mi64ToId);  
	aoStandardSerialize.Serialize(mwType);
	aoStandardSerialize.Serialize(mstrContent,mwContentLen,CRS_DATA_LEN+1); 

	return 1;
}

int STRU_UC_CL_CRS_GENERAL_PACK_350::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_GENERAL_PACK_350; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_GENERAL_PACK_350::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_GENERAL_PACK_350::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mlChatRoomID);
	aoStandardSerialize.Serialize(mi64DstUserID);
	aoStandardSerialize.Serialize(mwDataLen);
	if(CStandardSerialize::LOAD ==aoStandardSerialize.mbyType) //save外部设置
	{
		mGENERALInfo.mwContentLen = mwDataLen - mGENERALInfo.GetSubLen();
	}      
	mGENERALInfo.Serialize(aoStandardSerialize);
	aoStandardSerialize.Serialize(mi64SrcUserID);        
	return 1;
	//}
	//catch(...)
	//{
	//    return -1;
	//}
}



int STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																							
}																							



int STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyState);
	aoStandardSerialize.Serialize(mbNewVal);
	return 1;
	//}
	//catch(...)
	//{
	//	return -1;
	//}
}



int STRU_UC_CL_CRS_HALL_STAT_CHG_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_HALL_STAT_CHG_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_HALL_STAT_CHG_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																																											
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_HALL_STAT_CHG_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerID);
	aoStandardSerialize.Serialize(mlChatHallID);
	aoStandardSerialize.Serialize(mwProperty);
	aoStandardSerialize.Serialize(mlNewValue);
	aoStandardSerialize.Serialize(mwOtherDataLen);
	aoStandardSerialize.Serialize(mpzOthreData,mwOtherDataLen,256);
	return 1;
	//}
	//catch(...)
	//{
	//   return -1;
	//}
}



int STRU_CL_CRS_CHATROOM_BROADCAST_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_BROADCAST_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_BROADCAST_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_CHATROOM_BROADCAST_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(mwDataLen);
	aoStandardSerialize.Serialize(macBroadcaseMsg,mwDataLen,UC_MANAGER_BROADCAST_LEN+1);
	return 1;
	//}catch(...)
	//{
	//    return -1;
	//}
}



int STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_PROPERTY_CHG_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(macTopic,UC_CHATROOM_TOPIC_LEN + 1);
	aoStandardSerialize.Serialize(macSalutatory,UC_CHATROOM_SALUTATORY_LEN + 1);
	aoStandardSerialize.Serialize(macPassword,UC_HALL_PWD_LEN + 1);
	aoStandardSerialize.Serialize(mbIsLockHall);
	return 1;
	//}catch(...)
	//{
	//    return -1;
	//}
}


int STRU_CL_CRS_CHATROOM_PROPERTY_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_PROPERTY_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_PROPERTY_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							




int STRU_CL_CRS_CHATROOM_PROPERTY_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	//try
	//{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(macTopic,UC_CHATROOM_TOPIC_LEN + 1);
	aoStandardSerialize.Serialize(macSalutatory,UC_CHATROOM_SALUTATORY_LEN + 1);
	aoStandardSerialize.Serialize(macPassword,UC_HALL_PWD_LEN + 1);
	aoStandardSerialize.Serialize(mbIsLocked);
	return 1;
	//}catch(...)
	//{
	//    return -1;
	//}
}


int STRU_CL_CRS_CHATROOM_TOPIC_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_CHATROOM_TOPIC_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_CL_CRS_CHATROOM_TOPIC_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_CL_CRS_CHATROOM_TOPIC_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64ManagerId);
	aoStandardSerialize.Serialize(macTopic,UC_CHATROOM_TOPIC_LEN + 1);
	aoStandardSerialize.Serialize(macWelcome,UC_CHATROOM_SALUTATORY_LEN+1); //聊天室的欢迎词
	return 1;
}

int STRU_UC_CL_CRS_USER_INFO_ID_2008::Pack( char* apBuffer , int alLen ) 											
{ 																							
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_INFO_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_INFO_ID_2008::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																																			

int STRU_CHATROOM_USER_INFO_2008::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN+1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(mbyPower);
	aoStandardSerialize.Serialize(mlUserState);
	aoStandardSerialize.Serialize(mbyVoiceState);
	aoStandardSerialize.Serialize(mbyUserLanguage);
	aoStandardSerialize.Serialize(miRedMemTime);
	return 1;
}

int STRU_UC_CL_CRS_USER_INFO_ID_2008::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mwUserCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		mpUserIDList = NULL;
		if (mwUserCount > 0)
		{
			mpUserIDList = new STRU_CHATROOM_USER_INFO_2008[mwUserCount];
		}
	}

	for(int i = 0; i < mwUserCount; i++)
	{
		mpUserIDList[i].Serialize(aoStandardSerialize);
	}
	return 1;
}


int STRU_USER_ID_LIST_RQ_2008::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_INFO_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_USER_ID_LIST_RQ_2008::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_USER_ID_LIST_RQ_2008::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(miUserCount);
	if (miUserCount > MAX_USER_ID_NUM)
	{
		//TRACE(1, "STRU_USER_ID_LIST_RQ_2008::Serialize 个数超过限制了");
		return 0;
	}
	for(int i = 0; i < miUserCount; i++)
	{
		aoStandardSerialize.Serialize(mvUserIdList[i]);
	}
	return 1;

}

//////////////////////////////////////////////////////////////////////////

STRU_UC_CL_CRS_HOST_INFO::STRU_UC_CL_CRS_HOST_INFO()
{
	memset(mszhostName,0,HOMEPAGE_DISPLAY_LEN+1);
	memset(mszhostAddr,0,URL_LINK_LEN+1);
}

int STRU_UC_CL_CRS_HOST_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mszhostName, HOMEPAGE_DISPLAY_LEN+1);
	aoStandardSerialize.Serialize(mszhostAddr, URL_LINK_LEN+1);
	return 1;
} 

STRU_UC_CL_CRS_HOST_INFO_ID600::~STRU_UC_CL_CRS_HOST_INFO_ID600()
{
	if(mpHostInfoList != NULL)
	{
		delete [] mpHostInfoList;
		mpHostInfoList = NULL;
	}

	if(mpInnerPageList != NULL)
	{
		delete [] mpInnerPageList;
		mpInnerPageList = NULL;
	}
}

//主页地址通知包
int STRU_UC_CL_CRS_HOST_INFO_ID600::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_HOST_INFO_ID600; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_HOST_INFO_ID600::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CL_CRS_HOST_INFO_ID600::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(macBgBmpName,CHATROOM_BMP_NAME_LEN+1);
	aoStandardSerialize.Serialize(mwListCount);
	aoStandardSerialize.Serialize(mwInnerPageListCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		if(mwListCount >0)
		{
			mpHostInfoList = new STRU_UC_CL_CRS_HOST_INFO[mwListCount];
		}
		if(mwInnerPageListCount >0)
		{
			mpInnerPageList = new STRU_UC_CL_CRS_HOST_INFO[mwInnerPageListCount];
		}
	}

	for(int i = 0; i < mwListCount; i++)
	{
		mpHostInfoList[i].Serialize(aoStandardSerialize);
	}
	for(int i = 0; i < mwInnerPageListCount; i++)
	{
		mpInnerPageList[i].Serialize(aoStandardSerialize);
	}
	return 1;
} 


//////////////////////////////////////////////////////////////////////////
//by: wxy
//RSA请求

int STRU_RSA_INFO_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_COM_RAS_APPLY_KEY_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_RSA_INFO_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_RSA_INFO_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(nType);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(nSize);
	aoStandardSerialize.Serialize(nLen);
	aoStandardSerialize.Serialize(mszPublicKey, nLen);

	return 1;
}

int STRU_RSA_INFO_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_COM_RAS_APPLY_KEY_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_RSA_INFO_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_RSA_INFO_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(nType);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(byRet);
	aoStandardSerialize.Serialize(nSize);
	aoStandardSerialize.Serialize(nLen);

	if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
		mszPublicKey = new uint8_t[nLen];

	aoStandardSerialize.Serialize(mszPublicKey, nLen);

	return 1;
}

int STRU_ENDECRYPT_FUN::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_ENDECRYPT_FUN; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_ENDECRYPT_FUN::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_ENDECRYPT_FUN::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(nLen);

	if(aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
		mszEncrypt = new char[nLen];

	aoStandardSerialize.Serialize(mszEncrypt, nLen, WHOLE_PACK_DATA_LEN);

	return 1;
}

int STRU_UC_CL_CRS_INSERT_MIC_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_INSERT_MIC_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CL_CRS_INSERT_MIC_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																																										
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_CL_CRS_INSERT_MIC_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64ManagerID);
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyIndex);
	return 1;
}

//SinaShow1.3版新加的

int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009::Pack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_ENTRY_OTHERUSER_ID_2009; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009::UnPack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(mbyPower);
	aoStandardSerialize.Serialize(mlUserState);	
	aoStandardSerialize.Serialize(mbyUserLanguage); //添加语言类型
	aoStandardSerialize.Serialize(miRedMemTime);

	aoStandardSerialize.Serialize(mstrUniName,DEF_USER_UNINAME_LEN+1);
	aoStandardSerialize.Serialize(mstrUserMood,DEF_USER_MOOD_LENGTH+1);
	aoStandardSerialize.Serialize(mstrUserImageURL,URL_LINK_LEN+1);
	aoStandardSerialize.Serialize(mbyUserSex);
	aoStandardSerialize.Serialize(miUserOnLineTime);
	aoStandardSerialize.Serialize(miUserCharm);
	aoStandardSerialize.Serialize(miUserWealth);
	aoStandardSerialize.Serialize(miUserActivity);
	aoStandardSerialize.Serialize(mlVipRooomID);
	aoStandardSerialize.Serialize(mbyShowBar);
	aoStandardSerialize.Serialize(mstrUserBirthDay,DEF_USER_BIRTHDAY_LEN+1);
	//aoStandardSerialize.Serialize(mbyShopUser);

	return 1;
}

int STRU_CHATROOM_USER_INFO_2009::Serialize( CStandardSerialize & aoStandardSerialize )
{
	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(macNickName,NICK_NAME_LEN+1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	aoStandardSerialize.Serialize(mbyPower);
	aoStandardSerialize.Serialize(mlUserState);
	aoStandardSerialize.Serialize(mbyVoiceState);
	aoStandardSerialize.Serialize(mbyUserLanguage);
	aoStandardSerialize.Serialize(miRedMemTime);

	//aoStandardSerialize.Serialize(macVersion,VERSION_LEN+1);
	aoStandardSerialize.Serialize(mstrUniName,DEF_USER_UNINAME_LEN+1);
	aoStandardSerialize.Serialize(mstrUserMood,DEF_USER_MOOD_LENGTH+1);
	aoStandardSerialize.Serialize(mstrUserImageURL,URL_LINK_LEN+1);
	aoStandardSerialize.Serialize(mbyUserSex);
	aoStandardSerialize.Serialize(miUserOnLineTime);	
	aoStandardSerialize.Serialize(miUserCharm);	
	aoStandardSerialize.Serialize(miUserWealth);	
	aoStandardSerialize.Serialize(miUserActivity);	
	aoStandardSerialize.Serialize(mlVipRooomID);	
	aoStandardSerialize.Serialize(mbyShowBar);	
	aoStandardSerialize.Serialize(mstrUserBirthDay,DEF_USER_BIRTHDAY_LEN+1);
	//aoStandardSerialize.Serialize(mbyShopUser);

	return 1;
}


int STRU_UC_CL_CRS_USER_INFO_ID_2009::Pack( char* apBuffer , int alLen ) 											
{ 																																											
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_INFO_ID_2009; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CL_CRS_USER_INFO_ID_2009::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_CL_CRS_USER_INFO_ID_2009::Serialize( CStandardSerialize & aoStandardSerialize )
{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mwUserCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		mpUserIDList = NULL;
		if (mwUserCount > 0)
		{
			mpUserIDList = new STRU_CHATROOM_USER_INFO_2009[mwUserCount];
		}
	}
	for(int i = 0; i < mwUserCount; i++)
	{
		mpUserIDList[i].Serialize(aoStandardSerialize);
	}
	return 1;
}

STRU_UC_CL_CRS_USER_INFO_ID_2009::~STRU_UC_CL_CRS_USER_INFO_ID_2009()
{
	if(mpUserIDList)
	{
		delete [] mpUserIDList;
		mpUserIDList = NULL;
	}
}

//使用礼物请求



int STRU_UC_CL_CRS_GIFT_PROP_USE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_GIFT_PROP_USE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CL_CRS_GIFT_PROP_USE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_CL_CRS_GIFT_PROP_USE_RQ::Serialize(CStandardSerialize &aoStandardSerialize)	 
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mi64DestID);
	aoStandardSerialize.Serialize(miContentID);
	aoStandardSerialize.Serialize(mszContentName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(miUseCount);

	return 1;
}

//使用礼物应答

int STRU_UC_CL_CRS_GIFT_PROP_USE_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_GIFT_PROP_USE_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CL_CRS_GIFT_PROP_USE_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																																											
	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_CL_CRS_GIFT_PROP_USE_RS::Serialize(CStandardSerialize &aoStandardSerialize)	 
{
	aoStandardSerialize.Serialize(mbyResult);
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mi64DestID);
	aoStandardSerialize.Serialize(miContentID);		
	aoStandardSerialize.Serialize(mszContentName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(miUseCount);
	aoStandardSerialize.Serialize(miResidualValue);

	return 1;
}

//使用礼物通知包



int STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_GIFT_PROP_USE_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																	
} 																							

int STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mi64DestID);
	aoStandardSerialize.Serialize(miContentID);		
	aoStandardSerialize.Serialize(mszContentName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(miUseCount);

	aoStandardSerialize.Serialize(miRecvCount);
	aoStandardSerialize.Serialize(miPackMark);		
	aoStandardSerialize.Serialize(miPackBeginNum);
	aoStandardSerialize.Serialize(miPackUseNum);

	aoStandardSerialize.Serialize(mszUserName, NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mszDestName, NICK_NAME_LEN + 1);
	return 1;
}

//使用大礼物通知包

int STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(mszUserName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(mi64DestID);
	aoStandardSerialize.Serialize(mszDestName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(miContentID);		
	aoStandardSerialize.Serialize(mszContentName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(miUseCount);
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mstruRoomName,DEF_CONTENT_NAME_LEN+1);
	aoStandardSerialize.Serialize(mstruTimeStamp);

	aoStandardSerialize.Serialize(miHallIP);      //房间IP
	aoStandardSerialize.Serialize(miHallPort);      //房间PORT
	aoStandardSerialize.Serialize(miHallProperty);     //房间属性
	aoStandardSerialize.Serialize(miHallPropertyEx);    //房间扩展属性

	aoStandardSerialize.Serialize(mbyShowStar);     //秀星级别，1~6级，0为非秀星
	aoStandardSerialize.Serialize(mbyNobleman);     //贵族级别，1~3级，0为非贵族
	aoStandardSerialize.Serialize(mbyManager);      //管理员级别
	aoStandardSerialize.Serialize(mbyWeekStar);     //周星，1~3周星
	aoStandardSerialize.Serialize(mbySell);      //官方销售，0不是销售，1是销售
	aoStandardSerialize.Serialize(mbyDstShowStar);     //目标用户秀星级别，1~6级，0为非秀星
	aoStandardSerialize.Serialize(mbyDstNobleman);     //目标用户贵族级别，1~3级，0为非贵族
	aoStandardSerialize.Serialize(mbyDstManager);     //目标用户管理员级别
	aoStandardSerialize.Serialize(mbyDstWeekStar);     //目标用户周星，1~3周星
	aoStandardSerialize.Serialize(mbyDstSell);      //目标用户官方销售，0不是销售，1是销售

	aoStandardSerialize.Serialize(miReserved1);     //预留1
	aoStandardSerialize.Serialize(miReserved2);     //预留2

	return 1;
}

//u点更新通知包

int STRU_UC_CRS_CL_BALANCE_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CRS_CL_BALANCE_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CRS_CL_BALANCE_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CRS_CL_BALANCE_NOTIFY::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(miResidualValue);
	aoStandardSerialize.Serialize(mbyUseType);		
	aoStandardSerialize.Serialize(miSecond);

	return 1;
}

// 喇叭请求和通知包


int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CRS_CL_LOUDSPEAKER_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							


int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64FromUserID);
	aoStandardSerialize.Serialize(mszUserName, NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mi64ToUserID);
	aoStandardSerialize.Serialize(mszDestName, NICK_NAME_LEN + 1);
	aoStandardSerialize.Serialize(mbyType);		

	aoStandardSerialize.Serialize(mbyShowStar);
	aoStandardSerialize.Serialize(mbyNobleman);
	aoStandardSerialize.Serialize(mbyManager);		
	aoStandardSerialize.Serialize(mbyWeekStar);
	aoStandardSerialize.Serialize(mbySell);

	aoStandardSerialize.Serialize(mwMessageLen);
	mChatInfo.mwLen = mwMessageLen;
	mChatInfo.Serialize(aoStandardSerialize);

	return 1;
}

// 喇叭应答包
int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType = UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mbyResult);
	return 1;
}

// 喇叭应答扩展包
int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							

int STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(m_nResult);
	aoStandardSerialize.Serialize(m_szReason, sizeof(m_szReason));
	return 1;
}

// 幸运道具广播包
int STRU_UC_CL_CRS_AWARD_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_AWARD_USE_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_AWARD_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}

int STRU_UC_CL_CRS_AWARD_NOTIFY::Serialize(CStandardSerialize & StandardSerialize)
{
	StandardSerialize.Serialize(m_nPackMark);
	StandardSerialize.Serialize(m_i64UserID);
	StandardSerialize.Serialize(m_szUserName, NICK_NAME_LEN + 1);
	StandardSerialize.Serialize(m_nContentID);
	StandardSerialize.Serialize(m_nMaxTimes);
	StandardSerialize.Serialize(m_nExtraDataCount);

	int nBufferLen = m_nExtraDataCount * sizeof(STRU_EXTRA_DATA);
	char* pBytes = new char[nBufferLen];
	StandardSerialize.Serialize(pBytes, nBufferLen, nBufferLen);

	m_pExtraData = (STRU_EXTRA_DATA*)pBytes;

	return 1;
}

// 幸运道具统计信息包 
int STRU_UC_CL_CRS_AWARD_INFO::Pack( char* apBuffer , int alLen ) 											
{ 																							
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_LUCK_PROP_USE_INFO; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_AWARD_INFO::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}

int STRU_UC_CL_CRS_AWARD_INFO::Serialize(CStandardSerialize & StandardSerialize)
{
	StandardSerialize.Serialize(miPackMark);
	StandardSerialize.Serialize(mi64UserID);
	StandardSerialize.Serialize(mszUserName, NICK_NAME_LEN + 1);
	StandardSerialize.Serialize(miContentID);
	StandardSerialize.Serialize(miMaxTimes);
	StandardSerialize.Serialize(miExtraDataCount);

	int nBufferLen = miExtraDataCount * sizeof(STRU_EXTRA_DATA);
	char* pBytes = new char[nBufferLen];
	StandardSerialize.Serialize(pBytes, nBufferLen, nBufferLen);

	m_pExtraData = (STRU_EXTRA_DATA*)pBytes;

	return 1;
}

// 烟花道具广播包
int STRU_UC_CL_CRS_FIREWORKS_NOTIFY::Pack( char* apBuffer , int alLen ) 											
{ 																							
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_FIREWORKS_USE_NOTIFY; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_FIREWORKS_NOTIFY::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}

int STRU_UC_CL_CRS_FIREWORKS_NOTIFY::Serialize(CStandardSerialize & StandardSerialize)
{
	StandardSerialize.Serialize(m_i64UserID);    // 发送用户的ID
	StandardSerialize.Serialize(m_szUserName, NICK_NAME_LEN + 1);  //用户名称
	StandardSerialize.Serialize(m_nContentID);  // 道具ID
	StandardSerialize.Serialize(m_nUseCount);   // 使用数量
	StandardSerialize.Serialize(m_i64GainPoint);  // 奖励的U点值

	return 1;
}

//VIP用户信息通知包
int STRU_UC_CL_VIP_ENTER_NOTIFY_EX::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_VIP_ENTER_NOTIFY_EX; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																	
} 																							

int STRU_UC_CL_VIP_ENTER_NOTIFY_EX::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_CL_VIP_ENTER_NOTIFY_EX::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mui8VIPType);
	aoStandardSerialize.Serialize(mui8NotifyType);
	aoStandardSerialize.Serialize(mi64UserID);		
	aoStandardSerialize.Serialize(mui32Reserve);
	aoStandardSerialize.Serialize(mui32Reserve2);
	aoStandardSerialize.Serialize(mui32Reserve3);
	return 1;
}

STRU_UC_CL_CRS_USER_AVSINFO_ID::STRU_UC_CL_CRS_USER_AVSINFO_ID()
{
	memset(mszAvsName, 0, sizeof(mszAvsName));
}

STRU_UC_CL_CRS_USER_AVSINFO_ID::~STRU_UC_CL_CRS_USER_AVSINFO_ID()
{

}

int STRU_UC_CL_CRS_USER_AVSINFO_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mszAvsName, UC_HALL_AVS_NAME_LEN+1);
	aoStandardSerialize.Serialize(miAvsIp);
	aoStandardSerialize.Serialize(miVoicePort);
	return 1;
}

STRU_UC_CRS_CL_USER_AVS_INFO_ID::STRU_UC_CRS_CL_USER_AVS_INFO_ID()
{
	miAvsId = 0;
	miAvsCount = 0;
	miAvsInfoList = NULL;
}
STRU_UC_CRS_CL_USER_AVS_INFO_ID::~STRU_UC_CRS_CL_USER_AVS_INFO_ID()
{
	if(miAvsInfoList != NULL)
	{
		delete[] miAvsInfoList;
		miAvsInfoList = NULL;
	}
}

int  STRU_UC_CRS_CL_USER_AVS_INFO_ID::Pack(char *   apBuffer ,int    alLen)
{

	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::STORE);
	memset(apBuffer,0,alLen);
	uint16_t lwPackType = UC_CRS_CL_USER_AVS_INFO_ID;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return loSerialize.getDataLen();

}
int  STRU_UC_CRS_CL_USER_AVS_INFO_ID::UnPack(char * apBuffer,int    alLen)
{

	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::LOAD);
	uint16_t lwPackType ;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return 1;

}

//AVS变化通知包
int STRU_UC_CRS_CL_USER_AVS_INFO_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(miAvsId);
	aoStandardSerialize.Serialize(miAvsCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		if (miAvsCount > 0)
			miAvsInfoList = new STRU_UC_CL_CRS_USER_AVSINFO_ID[miAvsCount];
		else
			miAvsInfoList = NULL;
	}

	for(int i = 0; i < miAvsCount; i++)
	{
		miAvsInfoList[i].Serialize(aoStandardSerialize);
	}
	return 1;
	return 1;
}

//用户avs信息变化通知包

int STRU_UC_CL_CRS_USER_AVS_CHANGE_ID::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CL_CRS_USER_AVS_CHANGE_ID; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_CL_CRS_USER_AVS_CHANGE_ID::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							


int STRU_UC_CL_CRS_USER_AVS_CHANGE_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(muAvsIp);
	aoStandardSerialize.Serialize(muVoicePort);	
	return 1;
}

//丢包率请求

int STRU_USER_LOSTRATE_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CRS_CL_USER_LOSTRATE_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_USER_LOSTRATE_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_USER_LOSTRATE_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	return 1;
}

//丢包率应答

int STRU_USER_LOSTRATE_RS::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_CRS_CL_USER_LOSTRATE_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_USER_LOSTRATE_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																						
}																							


int STRU_USER_LOSTRATE_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mi64UserID);
	aoStandardSerialize.Serialize(miLostRate);
	return 1;
}

int STRU_MODIFIED_USER_INFO_FIELD::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mbyFieldName);
	aoStandardSerialize.Serialize(macValue,USER_INTRO_LEN+1);
	return 1;

}
STRU_MODIFIED_USER_INFO_FIELD::STRU_MODIFIED_USER_INFO_FIELD()
{
	mbyFieldName = 0;
	memset(macValue,0,USER_INTRO_LEN+1);
}
int  STRU_UC_CL_CRS_CHG_USER_INFO_ID::Pack(char *   apBuffer ,int    alLen)
{

	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::STORE);
	memset(apBuffer,0,alLen);
	uint16_t lwPackType = UC_CL_CRS_CHG_USER_INFO_ID;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return loSerialize.getDataLen();
}
int  STRU_UC_CL_CRS_CHG_USER_INFO_ID::UnPack(char * apBuffer,int    alLen)
{
	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::LOAD);
	uint16_t lwPackType ;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return 1;
}
int STRU_UC_CL_CRS_CHG_USER_INFO_ID::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64UserId);
	aoStandardSerialize.Serialize(mbyCount);
	if (aoStandardSerialize.mbyType == CStandardSerialize::LOAD)
	{
		if (mbyCount > 0)
			mpModifyList = new STRU_MODIFIED_USER_INFO_FIELD[mbyCount];
		else
			mpModifyList = NULL;
	}
	PSTRU_MODIFIED_USER_INFO_FIELD lpstruTemp;
	for(int i = 0; i < mbyCount; i++)
	{
		lpstruTemp = mpModifyList + i;
		lpstruTemp->Serialize(aoStandardSerialize);
	}
	return 1;
}
STRU_UC_CL_CRS_CHG_USER_INFO_ID::STRU_UC_CL_CRS_CHG_USER_INFO_ID()
{
	mi64UserId = 0;
	mbyCount = 0;
	mpModifyList = NULL;
}
STRU_UC_CL_CRS_CHG_USER_INFO_ID::~STRU_UC_CL_CRS_CHG_USER_INFO_ID()
{
	if(mpModifyList != NULL)
	{
		delete[] mpModifyList;
		mpModifyList = NULL;
	}
}


//申请游客ID请求包 --此包用来向聊天室服务器申请一个游客的ID号


int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ::Pack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_COM_GAS_VISITOR_INFO_RQ; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 													

} 																							

int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																			

}																							



int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(macVersion, VERSION_LEN+1);
	return 1;

}
//---------------------------------------------------------------------------
//申请游客ID应答包--聊天室服务器对游客

int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS::Pack( char* apBuffer , int alLen ) 											
{ 																																												
	CStandardSerialize loSerialize(apBuffer, alLen, CStandardSerialize::STORE );		
	uint16_t lwPackType=UC_COM_GAS_VISITOR_INFO_RS; 											
	loSerialize.Serialize( lwPackType ); 												
	if( Serialize(loSerialize) == -1 ) 													
	{ 																					
		return -1; 																	
	} 																					
	return loSerialize.getDataLen(); 																																		
} 																							

int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS::UnPack( char* apBuffer , int alLen ) 											
{ 																							

	CStandardSerialize loSerialize( apBuffer, alLen, CStandardSerialize::LOAD );		
	uint16_t lwPackType ; 																	
	loSerialize.Serialize(lwPackType); 													
	if ( Serialize(loSerialize) == -1 ) 												
	{ 																					
		return -1; 																		
	} 																					
	return 1; 																																								
}																							



int STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS::Serialize(CStandardSerialize & aoStandardSerialize)
{

	aoStandardSerialize.Serialize(mi64VisitorID);
	aoStandardSerialize.Serialize(macVisitorName, NICK_NAME_LEN+1);
	aoStandardSerialize.Serialize(mwPhotoNum);
	return 1;

}

//TCP包头
int  STRU_UC_CL_TCP_CRS_DATA_HEAD::Pack(char *   apBuffer ,int    alLen)
{
	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::STORE);
	memset(apBuffer, 0, alLen);
	uint16_t lwPackType = UC_CL_CRS_DATA_HEAD;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return loSerialize.getDataLen();
}

int  STRU_UC_CL_TCP_CRS_DATA_HEAD::UnPack(char * apBuffer,int    alLen)
{

	CStandardSerialize loSerialize(apBuffer,alLen, CStandardSerialize::LOAD);
	uint16_t lwPackType ;
	loSerialize.Serialize(lwPackType);
	if(Serialize(loSerialize) == -1)
		return -1;
	return 1;
}
int STRU_UC_CL_TCP_CRS_DATA_HEAD::Serialize(CStandardSerialize & aoStandardSerialize)
{
	aoStandardSerialize.Serialize(mlChatroomID);
	aoStandardSerialize.Serialize(mwDataLen);
	aoStandardSerialize.Serialize(mpData,mwDataLen,ROOM_PACK_DATA_LEN);
	return 1;
}

STRU_UC_CL_TCP_CRS_DATA_HEAD::STRU_UC_CL_TCP_CRS_DATA_HEAD()
{
	mlChatroomID=0;
	mwDataLen =0;
	memset(mpData,0,1);    
}
