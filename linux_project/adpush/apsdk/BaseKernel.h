#ifndef BaseKernel_h__
#define BaseKernel_h__

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"
#include "base/pack/crs_cl_strudef.h"

class CBaseKernel: public IRoomKernel, public IBaseKernel
{
public:
	CBaseKernel(){
		m_bHaveVideo = false;
	}
private:
	//初始化                   客户端版本号      是否有摄像头       登录来源客户端标识
	virtual void  Initialize(char* apszVersion, bool abHaveVideo, uint8_t abyLoginSource);

	//登录房间
	virtual void  LoginRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort, const char* pszRoomPsw, const char* pszMachineCode );

	//退出房间
	virtual void  LogOut(int32_t alRoomId);	

	//献花
	virtual void  SendFlower(int64_t ai64SendTo, uint8_t abyFlowerIndex); 

	//发送聊天信息
	virtual void  SendChat(uint8_t byChatType, int64_t ai64SendTo, char* apszMood, char* apszContrl, char* apszContent);
	
	//隐身
	virtual void  ChangeHermitState(bool bHermit);  

	//管理用户
	virtual void  ManageUser(int64_t ai64UserID, uint8_t byType, int32_t otherParam, char* strText);

	//请求用户黑名单 限管理员
	virtual void  GetBlackList();	

	//请求IP黑名单  限管理员
	virtual void  GetBlackIPList();	

	//更改房间状态请求
	/*
	#define DEF_ALLOW_FLOWER				0//允许献花
	#define DEF_ALLOW_PUBCHAT				1//允许公聊
	*/
	virtual void  ModifyRoomStateRQ(uint16_t wProperty, bool abValue);

	//房间广播 限管理员
	virtual void  SendBroadCast(char* astrText);

	//修改房间属性 加锁、密码、主题、欢迎词
	virtual void  ModifyRoomProperty(bool bLocked, char* strPSW, char* strTopic, char* strSalutatory);	

	//用户一般信息 服务器透明转发
	/*
	const uint16_t REFUSE_PRIVATE 		= 0x1006;		//拒绝接收私聊信息
	const uint16_t REFUSE_CHAT			= 0x1007;		//拒绝任何聊天信息
	const uint16_t REFUSE_PUBLIC		= 0x100D;		//屏蔽公聊提示对方
	const uint16_t REFUSE_PRICHAT		= 0x1010;		//拒绝对聊
	*/
	virtual void  SendGeneralInfo(int64_t ai64UserID, uint16_t wType);

	//更改用户信息
	virtual void  ModifyUserInfo(PRKN_STRU_MD_USER_INFO_ITEM apItemList, uint8_t abyItemCount);
public:
	void LoginRoom();

private:
	string m_strPsw;

	string m_strVersion;

	bool m_bHaveVideo;

	uint8_t m_byLoginSource;
    
    string m_strMachineCode;
};
#endif // BaseKernel_h__