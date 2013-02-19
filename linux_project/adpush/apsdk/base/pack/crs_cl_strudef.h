#ifndef _CRS_CL_STRUDEF_H_
#define _CRS_CL_STRUDEF_H_

#include "../include.h"
#include "../constdef.h"
#include "MediaInfo.h"

#define VERSION_LEN					10		//版本信息		
#define MAX_USER_ID_NUM				20		///用户请求详细信息的ID 列表最大个数
//*************************************************************************************************//
//***************************  以下定义包类型用于GAS和语音聊天室使用  *****************************//
//*************************************************************************************************//
#define CRS_PACK_BASE						5300

#define UC_CL_CRS_DATA_HEAD							CRS_PACK_BASE+26	//聊天室数据包头

#define UC_CL_CRS_UDPFIRSTLOGIN_RQ                  CRS_PACK_BASE+300		
#define UC_CL_CRS_UDPFIRSTLOGIN_RS                  CRS_PACK_BASE+301
#define UC_CL_CRS_LOGIN_INFO_RQ                     CRS_PACK_BASE+302
#define UC_CL_CRS_ALIVE_RQ                          CRS_PACK_BASE+303
#define UC_CL_CRS_ALIVE_RS                          CRS_PACK_BASE+304
#define UC_CL_CRS_LOGOUT                            CRS_PACK_BASE+305
#define UC_CL_CRS_LOGIN_INFO_RS                     CRS_PACK_BASE+306
#define UC_CL_CRS_LOGOUT_RS							CRS_PACK_BASE+307	//服务器要求退出


/****************************  最高版本报类型及分类**************************
//登录
#define UC_CL_CRS_LOGIN_HALL_RQ_2007					CRS_PACK_BASE+72    //登录请求包 CL->CRS
#define UC_CL_CRS_LOGIN_HALL_RS_2007					CRS_PACK_BASE+126   //红人登录应答包 CRS->CL

//房间属性 普通用户
#define UC_CL_CRS_HOST_INFO_ID600						CRS_PACK_BASE+124 	//网络地址通知包 CRS->CL
#define UC_CL_CRS_CHATROOM_TOPIC_ID						CRS_PACK_BASE+79	//主题欢迎词通知包 CRS->CL
#define UC_CL_CRS_CHATROOM_PROPERTY_ID					CRS_PACK_BASE+78   	//属性改变通知包 CRS->CL
//房间属性 管理员
#define UC_CL_CRS_HALL_STAT_CHG_ID						CRS_PACK_BASE+110	//更改聊天室属性(献花、公聊)更改 CL<->CRS	
#define UC_CL_CRS_CHATROOM_PROPERTY_CHG_RQ				CRS_PACK_BASE+77	//聊天室属性修改(加锁等)请求包 CL->CRS

//语音视频 普通用户
#define UC_CL_CRS_MIC_INFO_LIST_ID						CRS_PACK_BASE+113   //麦状态信息列表通知 CRS->CL
#define UC_CL_CRS_SPEAKER_INFO_LIST_ID					CRS_PACK_BASE+115   //发言信息列表 CRS<->CL
#define UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID			CRS_PACK_BASE+48    //麦序通知包 CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID		CRS_PACK_BASE+54	//发言时长限制通知包 CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID		CRS_PACK_BASE+52	//麦序管理通知包CRS->CL
#define UC_CL_CRS_BEGIN_SPEAK_ID						CRS_PACK_BASE+114   //开始发言通知 CRS->CL
#define UC_CL_CRS_CHATROOM_STOP_SPEAK_RQ				CRS_PACK_BASE+47    //用户停止发言通知包 CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID	CRS_PACK_BASE+49	//给麦通知包 CRS->CL
#define UC_CL_CRS_MICROPHONE_MANAGER_RS					CRS_PACK_BASE+119	//管理员对麦操作情况广播 CRS->CL
#define UC_CL_CRS_USER_RECV_STATE_CHG_ID				CRS_PACK_BASE+121	//用户打开关闭具体麦CL->CRS 
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ			CRS_PACK_BASE+40	//排麦请求包 CL->CRS
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS			CRS_PACK_BASE+41	//排麦应答包 CRS->CL
//语音视频 普通用户 语音对聊
#define UC_CL_CRS_VOICE_CHAT_RQ							CRS_PACK_BASE+30	//语音对聊请求包 CL<->CRS
#define UC_CL_CRS_VOICE_CHAT_RS							CRS_PACK_BASE+31	//语音对聊应答包 CRS->CL
#define UC_CL_CRS_VOICE_CHAT_SERVER_RS					CRS_PACK_BASE+32	//服务器语音对聊应答包 通知AB开始语音聊天CRS->CL
#define UC_CL_CRS_VOICE_CHAT_STOP_ID					CRS_PACK_BASE+33	//语音对聊停止通知 CRS<->CL
//语音视频 管理员
#define UC_CL_CRS_CHATROOM_MANAGER_GET_MICROPHONE_RQ	CRS_PACK_BASE+42	//收麦请求包 CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_RQ	CRS_PACK_BASE+43	//给麦请求包 CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ		CRS_PACK_BASE+50	//申请或取消麦克风管理请求包 CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS		CRS_PACK_BASE+51	//申请或取消麦克风管理应答包 CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ		CRS_PACK_BASE+53	//修改聊天室发言时长限制请求包 CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROPHONE_RQ		CRS_PACK_BASE+55	//往指定位置插入麦 CL->CRS
#define UC_CL_CRS_MICROPHONE_MANAGER_RQ					CRS_PACK_BASE+118			//管理员管麦请求包 CL->CRS
//语音视频 管理员发送，所有人接受
#define UC_CL_CRS_MIC_STATE_CONTROL_ID					CRS_PACK_BASE+120			//关麦\关闭房间视频\管理麦\允许放歌CL<->CRS

//用户功能 普通用户
#define UC_CL_CRS_USER_BE_OPERATED_ID					CRS_PACK_BASE+70   	//用户被处理通知包 CRS->CL
#define UC_CL_CRS_USER_POWER_CHG_ID						CRS_PACK_BASE+71	//用户级别变化通知包 CRS->CL
#define UC_CL_CRS_VOICE_STATE_CHG_ID					CRS_PACK_BASE+74	//用户麦状态变化通知(麦上\对聊等) CRS->CL
#define UC_CL_CRS_USER_INFO_ID_2007						CRS_PACK_BASE+128	//用户列表通知包   CRS->CL
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_400				CRS_PACK_BASE+81	//用户进入通知  CRS->CL
#define UC_CL_CRS_LEAVE_OTHERUSER_ID_350				CRS_PACK_BASE+82	//用户离开通知 CRS->CL
#define UC_CL_CRS_DATA_ID_350							CRS_PACK_BASE+83	//聊天信息包 CRS<->CL
#define UC_CL_CRS_GENERAL_PACK_350						CRS_PACK_BASE+84	//聊天室控制信息包（透明转发） CRS<->CL
#define UC_CL_CRS_FLOWERS_ID							CRS_PACK_BASE+108   //用户献花包CRS<->CL
//用户功能 用户状态请求包 用户状态应答包一般用来请求麦上用户是否允许录音录像等
#define UC_CL_CRS_USER_STATE_RQ							CRS_PACK_BASE+111	//用户状态请求包	CL->CRS
#define UC_CL_CRS_USER_STATE_RS							RS_PACK_BASE+112	//用户状态应答包	CRS->CL
//用户功能 糅杂 视频控制（如是否允许鲜花、是否允许录像）
#define UC_CL_CRS_USER_STATE_CHG_ID_390					CRS_PACK_BASE+103	//用户状态改变通知 CL<->CRS
//用户功能 节目单
#define UC_CL_CRS_PLAYBILL_RQ							CRS_PACK_BASE+90	//节目单请求包		CL->CRS
#define UC_CL_CRS_PLAYBILL_ID							CRS_PACK_BASE+91	//节目单通知包		CRS->CL
#define UC_CL_CRS_PLAYBILL_CHANGED_ID					CRS_PACK_BASE+92	//节目单变化通知包 CRS->CL 
//用户功能 管理员
#define UC_CL_CRS_CHATROOM_BROADCAST_RQ     			CRS_PACK_BASE+60	//管理员进行系统广播 CRS<->CL
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ			CRS_PACK_BASE+61	//管理员对用户进行操作请求包 CL->CRS
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS			CRS_PACK_BASE+62	//管理员对用户进行操作应答包 CRS->CL
#define UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID			CRS_PACK_BASE+63	//管理员状态改变通知包（如隐身）CRS<->CL
#define UC_CL_CRS_BLACK_QUERY_RQ						CRS_PACK_BASE+85	//临时黑名单请求包 CL->CRS
#define UC_CL_CRS_TIME_BLACK_LIST						CRS_PACK_BASE+86	//临时黑名单列表包 CRS->CL
#define UC_CL_CRS_BLACKIP_LIST_RQ  						CRS_PACK_BASE+87	//IP黑名单请求包 CL->CRS
#define UC_CL_CRS_BLACKIP_LIST_RS  						CRS_PACK_BASE+88	//IP黑名单列表包 CRS->CL

******************************************************************************/
//************************************************//
//*****  常设聊天室通讯包 ****************************//
//************************************************//
//ChatRoom Server = CRS

#define UC_CL_CRS_LOGIN_RQ					CRS_PACK_BASE+1		//(停用)聊天室登录请求包
#define UC_CL_CRS_LOGIN_RS					CRS_PACK_BASE+2		//(停用)聊天室登录应答包

#define UC_CL_CRS_USER_INFO_ID				CRS_PACK_BASE+3		//(停用)聊天室用户信息

#define UC_CL_CRS_ENTRY_OTHERUSER_ID		CRS_PACK_BASE+5		//(停用)聊天室其他用户进入通知
#define UC_CL_CRS_LEAVE_OTHERUSER_ID		CRS_PACK_BASE+6		//(停用)聊天室其他用户离开通知

#define UC_CL_CRS_MANAGER_OPERATION_RQ      CRS_PACK_BASE+20	//聊天室特权命令操作请求包
#define UC_CL_CRS_MANAGER_OPERATION_RS      CRS_PACK_BASE+21    //管理员操作应答包

#define UC_CL_CRS_DATA_ID					CRS_PACK_BASE+23	//(停用)聊天室数据包
#define UC_CL_CRS_SYS_INFO_ID		        CRS_PACK_BASE+24	//聊天室系统信息包
#define UC_CL_CRS_GENERAL_PACK		        CRS_PACK_BASE+25	//(停用)聊天室一般信息包

#define UC_CL_CRS_DATA_HEAD					CRS_PACK_BASE+26	//聊天室数据包头

#define UC_COM_GAS_VISITOR_INFO_RQ			CRS_PACK_BASE+35	//游客信息请求包
#define UC_COM_GAS_VISITOR_INFO_RS			CRS_PACK_BASE+36	//游客信息应答包

#define UC_COM_GAS_APPLY_WEBKEY_RQ			CRS_PACK_BASE+37	//密钥请求包
#define UC_COM_GAS_APPLY_WEBKEY_RS			CRS_PACK_BASE+38	//密钥应答包
//语音对聊包(开始请求、应答和停止)
//***********************************************************//
//*****  语音对聊包(开始请求、应答和停止)********************//
//***********************************************************//
#define UC_CL_CRS_VOICE_CHAT_RQ								CRS_PACK_BASE+30	//语音对聊请求包
#define UC_CL_CRS_VOICE_CHAT_RS								CRS_PACK_BASE+31	//语音对聊应答包
#define UC_CL_CRS_VOICE_CHAT_SERVER_RS						CRS_PACK_BASE+32	//服务器语音对聊应答包
#define UC_CL_CRS_VOICE_CHAT_STOP_ID						CRS_PACK_BASE+33	//语音对聊停止通知

//语音聊天室对麦克风管理包(要麦、改时长、收麦、给麦、添加和停止通知)
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ				CRS_PACK_BASE+40	//要麦请求包
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS				CRS_PACK_BASE+41	//要麦应答包
#define UC_CL_CRS_CHATROOM_MANAGER_GET_MICROPHONE_RQ		CRS_PACK_BASE+42	//收麦请求包
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_RQ		CRS_PACK_BASE+43	//给麦请求包
#define UC_CL_CRS_CHATROOM_MANAGER_INSERT_MICROPHONE_RQ		CRS_PACK_BASE+44	//添加到发言队列请求包
#define UC_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CNG_RQ		CRS_PACK_BASE+45	//改变发言时长请求包
#define UC_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CNG_ID		CRS_PACK_BASE+46	//改变发言时长通知包
#define UC_CL_CRS_CHATROOM_STOP_SPEAK_RQ					CRS_PACK_BASE+47	//用户停止发言通知包
#define UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID				CRS_PACK_BASE+48	//GAS向发送的新麦序
#define UC_SINASHOW_MICROPHONE_ORDER_ID						CRS_PACK_BASE+135	//SinaShow服务器发送麦序通知包
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID		CRS_PACK_BASE+49	//给麦通知包

//管理员对麦克风管理包(管理请求、应答、通知，新麦序通知、要麦通知)
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ			CRS_PACK_BASE+50	//申请或取消麦克风管理请求包
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS			CRS_PACK_BASE+51	//申请或取消麦克风管理应答包
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID			CRS_PACK_BASE+52	//申请或取消麦克风管理通知包
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ			CRS_PACK_BASE+53	//修改聊天室发言时长限制请求包
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID			CRS_PACK_BASE+54	//修改聊天室发言时长限制通知包

//管理员进行管理包(广播、处理用户请求、应答、状态改变通知)
#define UC_CL_CRS_CHATROOM_BROADCAST_RQ     				CRS_PACK_BASE+60	//管理员进行系统广播
//#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ				CRS_PACK_BASE+61	//管理用户请求
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS				CRS_PACK_BASE+62	//管理用户应答
#define UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID				CRS_PACK_BASE+63	//管理员状态改变通知包

//聊天室与用户通讯包(被处理通知、级别变化通知、登录请求、登录应答、状态变化通知)
#define UC_CL_CRS_USER_BE_OPERATED_ID						CRS_PACK_BASE+70	//用户被处理通知
#define UC_CL_CRS_USER_POWER_CHG_ID							CRS_PACK_BASE+71	//级别变化通知
#define UC_CL_CRS_LOGIN_HALL_RQ_2007						CRS_PACK_BASE+72	//2007大厅登录请求
#define UC_CL_CRS_LOGIN_HALL_RS_350							CRS_PACK_BASE+73	//(停用)大厅登录应答
#define UC_CL_CRS_VOICE_STATE_CHG_ID						CRS_PACK_BASE+74	//状态变化通知
#define UC_CL_CRS_LOGIN_HALL_RQ_380							CRS_PACK_BASE+75	//(停用)大厅登录请求(380)

//聊天室属性通知包(属性修改请求包、属性通知包、主题通知包)
#define UC_CL_CRS_CHATROOM_PROPERTY_CHG_RQ					CRS_PACK_BASE+77	//属性修改请求包
#define UC_CL_CRS_CHATROOM_PROPERTY_ID						CRS_PACK_BASE+78	//属性通知包
#define UC_CL_CRS_CHATROOM_TOPIC_ID							CRS_PACK_BASE+79	//主题通知包

#define UC_CL_CRS_USER_INFO_ID_350							CRS_PACK_BASE+80	//(停用)聊天室用户信息
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_400					CRS_PACK_BASE+81	//用户进入通知
#define UC_CL_CRS_LEAVE_OTHERUSER_ID_350					CRS_PACK_BASE+82	//用户离开通知
#define UC_CL_CRS_DATA_ID_350								CRS_PACK_BASE+83	//聊天信息包
#define UC_CL_CRS_GENERAL_PACK_350							CRS_PACK_BASE+84	//聊天室控制信息包
#define UC_CL_CRS_BLACK_QUERY_RQ							CRS_PACK_BASE+85	//查询临时黑名单请求包
#define UC_CL_CRS_TIME_BLACK_LIST							CRS_PACK_BASE+86	//临时黑名单列表包

#define UC_CL_CRS_BLACKIP_LIST_RQ  							CRS_PACK_BASE+87	//查询IP黑名单请求包
#define UC_CL_CRS_BLACKIP_LIST_RS  							CRS_PACK_BASE+88	//IP黑名单列表包

#define UC_CL_CRS_PLAYBILL_RQ								CRS_PACK_BASE+90	//查询节目单请求包
#define UC_CL_CRS_PLAYBILL_ID								CRS_PACK_BASE+91	//节目单通知包
#define UC_CL_CRS_PLAYBILL_CHANGED_ID					    CRS_PACK_BASE+92	//节目单变化通知包
#define UC_CL_CRS_VISITOR_INFO_ID							CRS_PACK_BASE+93	//游客ID号段通知包

#define UC_CL_CRS_LOGIN_HALL_RQ_390							CRS_PACK_BASE+100	//(停用)登录请求（版本390）
#define UC_CL_CRS_LOGIN_HALL_RS_390							CRS_PACK_BASE+101	//(停用)登录应答（版本390）
#define UC_CL_CRS_HOST_INFO_ID							    CRS_PACK_BASE+102	//主页地址通知包
#define UC_CL_CRS_USER_STATE_CHG_ID_390						CRS_PACK_BASE+103	//用户状态改变通知（390）
#define UC_CL_CRS_USER_INFO_ID_390							CRS_PACK_BASE+104	//(停用)聊天室用户信息（390）
#define UC_CL_CRS_LOGIN_HALL_RQ_391							CRS_PACK_BASE+105	//(停用)登录请求（版本391）

//400新增加的包类型
#define UC_CL_CRS_USER_INFO_ID_400							CRS_PACK_BASE+106	//聊天室用户信息(400)
#define UC_CL_CRS_LOGIN_HALL_RQ_400							CRS_PACK_BASE+107	//(停用)登录请求（版本400）
#define UC_CL_CRS_FLOWERS_ID								CRS_PACK_BASE+108	//Flowers
#define UC_CL_CRS_LOGIN_HALL_RS_400							CRS_PACK_BASE+109	//(停用)登录应答（版本400）
#define UC_CL_CRS_HALL_STAT_CHG_ID							CRS_PACK_BASE+110	//更改聊天室状态

#define UC_CL_CRS_USER_STATE_RQ							CRS_PACK_BASE+111	//登录应答（版本400）
#define UC_CL_CRS_USER_STATE_RS							CRS_PACK_BASE+112	//更改聊天室状态

//500新定义的数据包 **********************
#define UC_CL_CRS_MIC_INFO_LIST_ID							CRS_PACK_BASE+113	//麦状态信息列表
#define UC_CL_CRS_BEGIN_SPEAK_ID							CRS_PACK_BASE+114	//开始发言通知
#define UC_CL_CRS_SPEAKER_INFO_LIST_ID						CRS_PACK_BASE+115	//发言信息列表
#define UC_CL_CRS_LOGIN_HALL_RQ_500							CRS_PACK_BASE+116	//新的登录包
#define UC_CL_CRS_LOGIN_HALL_RS_500							CRS_PACK_BASE+117	//
#define UC_CL_CRS_MICROPHONE_MANAGER_RQ						CRS_PACK_BASE+118	//管理员管麦请求包
#define UC_CL_CRS_MICROPHONE_MANAGER_RS						CRS_PACK_BASE+119	//管麦应答包
#define UC_CL_CRS_MIC_STATE_CONTROL_ID						CRS_PACK_BASE+120	//麦状态信息列表
#define UC_CL_CRS_USER_RECV_STATE_CHG_ID					CRS_PACK_BASE+121	//用户改变接收状态

//510新定义的数据包
#define UC_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROPHONE_RQ		CRS_PACK_BASE+55	//往指定位置插入麦

//600新定义的数据包
#define UC_CL_CRS_LOGIN_HALL_RQ_600						    CRS_PACK_BASE+122	//600的登录请求包
#define UC_CL_CRS_LOGIN_HALL_RS_600						    CRS_PACK_BASE+123	//600的登录应答包
#define UC_CL_CRS_HOST_INFO_ID600							CRS_PACK_BASE+124	//主页地址通知包(版本600)

//700新定义的数据包
#define UC_CL_CRS_LOGIN_HALL_RQ_700						    CRS_PACK_BASE+125	//700的登录请求包
#define UC_CL_CRS_LOGIN_HALL_RS_2007						CRS_PACK_BASE+126	//700的登录应答包

#define UC_CL_CRS_USER_INFO_ID_2007							CRS_PACK_BASE+128	//聊天室用户信息(2007)

//add by qufeng 2008-06-12
#define UC_CL_CRS_NEW_OFFER_BROW_ID                         CRS_PACK_BASE + 129 //新聊天表情包  
#define UC_CL_CRS_USER_INFO_RS								CRS_PACK_BASE+130   //用户请求自己详细信息
#define UC_CL_CRS_USER_INFO_RQ                              CRS_PACK_BASE+131   //用户请求个别用户详细信息

//Show新加			
#define UC_CL_CRS_USER_INFO_ID_SINASHOW_2008				CRS_PACK_BASE+137	//用户列表
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW_2008			CRS_PACK_BASE+136	//用户进入通知
//////////////////////////////////////////////////////////////////////////


#define UC_CL_CRS_USE_PROP_RQ								CRS_PACK_BASE+200	//使用道具请求
#define UC_CL_CRS_USE_PROP_RS								CRS_PACK_BASE+201	//使用道具应答
#define UC_CL_CRS_USE_PROP_ID								CRS_PACK_BASE+202	//使用道具通知
#define UC_CL_CRS_USE_PROP_FAILED_ID						CRS_PACK_BASE+203	//使用道具失败通知
#define UC_CRS_CL_PROP_CHECK_RQ								CRS_PACK_BASE+205	//道具使用验证请求
#define UC_CRS_CL_PROP_CHECK_RS								CRS_PACK_BASE+206	//道具使用验证应答
//////////////////////////////////////////////////////////////////////////
#define UC_COM_RAS_APPLY_KEY_RQ								CRS_PACK_BASE+207	//密钥请求包
#define UC_COM_RAS_APPLY_KEY_RS								CRS_PACK_BASE+208	//密钥应答包

#define UC_ENDECRYPT_FUN									CRS_PACK_BASE+209	//加密包

#define UC_CRS_CL_GET_MIC_PROP_CHECK_RQ						CRS_PACK_BASE+210	//上麦同时提交当前装扮列表
#define UC_CRS_CL_GET_MIC_PROP_CHECK_RS						CRS_PACK_BASE+211	//上麦时提交装扮列表的结果

#define UC_CL_CRS_INSERT_MIC_ID								CRS_PACK_BASE+212	//插麦通知

#define UC_CL_CRS_PROP_QUICK_BUY_RQ							CRS_PACK_BASE+213	//快速购买道具请求
#define UC_CL_CRS_PROP_QUICK_BUY_RS							CRS_PACK_BASE+214	//快速购买道具应答
#define UC_CL_CRS_DO_USE_PROP_ID							CRS_PACK_BASE+215	//渲染命令包
#define UC_CL_CRS_LOGIN_HALL_RS_2009						CRS_PACK_BASE+216	//2009的登录应答包

#define UC_CL_CRS_TD_CALL_RQ_2009							CRS_PACK_BASE+217	//呼叫请求包
#define UC_CL_CRS_TD_CALL_RS_2009							CRS_PACK_BASE+218	//呼叫应答包


#define UC_CL_CRS_ENTRY_OTHERUSER_ID_2009 					CRS_PACK_BASE+219	//进入房间通知**1.3新增
#define UC_CL_CRS_USER_INFO_ID_2009							CRS_PACK_BASE+220	//聊天室用户信息(2009)**1.3新增

//#define UC_CL_CRS_ENTRY_OTHERUSER_ID_2009_2					CRS_PACK_BASE+221	//进入房间通知**1.3新增，已废除
//#define UC_CL_CRS_USER_INFO_ID_2009_2						CRS_PACK_BASE+222	//聊天室用户信息(2009)**1.3新增，已废除

#define UC_CL_CRS_ACTION_ID                                 CRS_PACK_BASE + 221  //活动信息通知包 cl<->crs
#define UC_CL_CRS_USER_ATTR_EX						        CRS_PACK_BASE+222	 //扩展属性包(2009)**1.3新增

#define UC_CL_CRS_GIFT_PROP_USE_RQ						    CRS_PACK_BASE+223	 //礼物道具请求包
#define UC_CL_CRS_GIFT_PROP_USE_RS						    CRS_PACK_BASE+224	 //礼物道具应答包
#define UC_CL_CRS_GIFT_PROP_USE_NOTIFY                      CRS_PACK_BASE+225	 //礼物道具广播包
#define UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY         			CRS_PACK_BASE+228  //使用大礼物广播
#define UC_CRS_CL_BALANCE_NOTIFY                            CRS_PACK_BASE+229  //U点更新通知

#define UC_CRS_CL_LOUDSPEAKER_NOTIFY						CRS_PACK_BASE + 230    //喇叭的使用通知   20100423(zdm)
#define UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS						CRS_PACK_BASE + 231		//大小喇叭广播应答 20100423(zdm)
#define UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX					CRS_PACK_BASE + 234  //大小喇叭广播应答扩展 20100818(xq)

#define UC_CL_CRS_AWARD_USE_NOTIFY         			        CRS_PACK_BASE + 235  //幸运礼物广播  2010-11-24  fangkm
#define UC_CL_CRS_FIREWORKS_USE_NOTIFY         		    	CRS_PACK_BASE + 236  //烟花道具广播  2010-11-24  fangkm
#define UC_CL_CRS_LUCK_PROP_USE_INFO                        CRS_PACK_BASE + 237  //幸运道具次数(旧版不用此包) 2011-03-10

#define UC_CRS_CL_USER_LOSTRATE_RQ							CRS_PACK_BASE + 232    //丢包率请求
#define UC_CRS_CL_USER_LOSTRATE_RS							CRS_PACK_BASE + 233    //丢包率应答
#define UC_CL_VIP_ENTER_NOTIFY_EX							CRS_PACK_BASE + 240		//VIP用户信息通知包
#define UC_CRS_CL_USER_AVS_INFO_ID							CRS_PACK_BASE + 241		//AVS信息通知包
#define UC_CL_CRS_USER_AVS_CHANGE_ID						CRS_PACK_BASE + 242     //用户AVS信息变化通知包

#define UC_CL_CRS_FLOWERS_ID_NO_LIMIT   					CRS_PACK_BASE+250	 //用户献花包  无时间限制
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ				CRS_PACK_BASE+251	//管理用户请求 隐身
#define UC_CL_CRS_DATA_ID_HERMIT							CRS_PACK_BASE+252	 //聊天信息包 隐身
#define UC_CL_CRS_DATA_ID_LONG								CRS_PACK_BASE+253	 //聊天信息包
#define UC_CL_CRS_CHG_USER_INFO_ID							CRS_PACK_BASE+254	 //修改用户信息通知

//*************************************************************************************************//
//***********************  以下定义宏和枚举类型用于GAS和语音聊天室使用  ***************************//
//*************************************************************************************************//
//服务器对聊应答结果
#define UC_VOICE_CHAT_RESULE_AGREE				0					//服务器应答同意语音对聊
#define UC_VOICE_CHAT_RESULE_DISAGREE			1					//服务器应答不同意语音对聊

//管理员对麦克风管理要进行的操作
#define UC_MANAGER_MICROPHONE_APPLY				0					//请求麦克风管理
#define UC_MANAGER_MICROPHONE_CANCEL			1					//取消麦克风管理

//服务器对麦克风管理申请的应答
#define UC_MANAGER_MICROPHONE_RESULT_SUCCESS	0					//请求麦克风管理成功
#define UC_MANAGER_MICROPHONE_RESULT_NO_SUCCESS	1					//请求麦克风管理不成功

#define UC_MANAGER_USER_DESCRIBE_LEN			256					//管理员当前操作的描述
#define UC_MANAGER_BROADCAST_LEN				512 				//管理员发送广播的长度
#define UC_CRS_NOTIFY_MSG_LEN					1024 				//管理员发送广播的长度

#define	ERROR_BUFFER_LENGTH						256					//被服务器踢出错误长度

//管理员对麦克风管理要进行的操作
//#define UC_MANAGER_RECORD_ACTION_APPLY			0					//开始录音
//#define UC_MANAGER_RECORD_ACTION_CANCEL			1					//结束录音
//#define UC_CHATROOM_RECORD_DATA_LEN				512					//录音包数据的长度

//用户登录大厅应答结果
#define UC_LOGIN_HALL_RESULT_AGREE				0					//同意登录
#define UC_LOGIN_HALL_RESULT_PASSWORD_ERROR		1					//密码错误

//聊天室各项属性的长度
#define UC_CHATROOM_TOPIC_LEN					512					//主题的长度
#define UC_CHATROOM_SALUTATORY_LEN				512					//欢迎词的长度
#define UC_HALL_PWD_LEN			128					//密码长度

#define UC_LOGIN_HALL_USER_VIDEO_STATE          0x01				//用户有视频设备

#define UC_NEW_OFFER_BROW_NAME_LEN              50                  //新增发送礼物、动漫名字长度

#define DEF_CONTENT_NAME_LEN					255					//道具名称长度
#define UC_RSA_KEY_LEN							1024 				//RSA传送长度

#define USER_INTRO_LEN							200

#define UC_HALL_AVS_NAME_LEN					50
//add by Fanyunfeng
//STRU_UC_CL_CRS_FLOWERS_ID.mbyIsPrivate
//STRU_UC_CL_CRS_DATA_ID_350.mi64IsPrivate
//消息类型
#define DEF_MESSAGE_PUBLIC		0
#define DEF_MESSAGE_PRIVATE		~NULL

//聊天室状态 STRU_UC_CL_CRS_HALL_STAT_CHG_ID.mwProperty 中的属性
#define DEF_HALL_STATE_ALLOW_PRESENT_FLOWERS 		0
#define DEF_HALL_STATE_ALLOW_PUBLIC_MESSAGE			1
#define DEF_HALL_STATE_TRANS_VIDEO					2

//麦序管理操作
#define DEF_MIC_MANAGE_SEIZE	1//		占用
#define DEF_MIC_MANAGE_GET		2//		拿麦
#define DEF_MIC_MANAGE_PUT		3//		给麦
#define DEF_MIC_MANAGE_PREP		4//		准备接麦

//麦克管理操作定义
#define DEF_CHG_MIC_STAT		1//		开/关闭麦
#define DEF_CHG_VIDEO_STAT		2//		麦上的视频转发
#define DEF_CHG_MANAGE_STAT		3//		开始/结束管理员管麦
#define DEF_CHG_SWITCH_STAT		4//		限制使用，自动进行切麦
#define DEF_CHG_PLAY_STAT		5//		限制使用，自动进行切麦
/*********************************************************************************************/
//****************************语音对聊包(开始请求、应答和停止)*******************************//
/*********************************************************************************************/
/*********************************************************************************************/
//语音对聊请求包 
//用途:用户邀请与其他用户进行语音私聊。
/*********************************************************************************************/

//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_RQ
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//自己用户ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//目标用户ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_RQ * PSTRU_CL_CRS_VOICE_CHAT_RQ;

/*********************************************************************************************/
//语音对聊应答
//用途:邀请人同意与发起人私聊。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_RS
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//自己用户ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//目标用户ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_RS * PSTRU_CL_CRS_VOICE_CHAT_RS;

/*********************************************************************************************/
//服务器语音对聊应答包
//用途:服务器创建私聊关系成功后，通知私聊的邀请方和发起方私聊建立成功。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_SERVER_RS
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_SERVER_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_SERVER_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t		mbyResult;				//应答结果	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64RQUserId;			//请求对聊用户ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64RSUserId;			//应答用户用户ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_SERVER_RS * PSTRU_CL_CRS_VOICE_CHAT_SERVER_RS;

/*********************************************************************************************/
//语音对聊停止通知
//用途:私聊的双方主动退出时，通知服务器撤销私聊关系；服务器通知令一方，撤销私聊关系。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_STOP_ID
{
	int Pack(char *apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_STOP_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_STOP_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//自己用户ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//目标用户ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_STOP_ID * PSTRU_CL_CRS_VOICE_CHAT_STOP_ID;

/*********************************************************************************************/
//***** 语音聊天室对麦克风管理包(要麦、改时长、收麦、给麦、添加、停止通知和麦序通知)  *******//
/*********************************************************************************************/
/*********************************************************************************************/
//用户申请要麦的请求包
//用途:用户申请发言时发送此数据包。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//申请发言的用户ID STRU_MIC_OPERATE::mi64SourceUserId
};
typedef struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ * PSTRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ;

/*********************************************************************************************/
//用户申请要麦的应答包
//用途:通知用户的麦序。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//申请发言的用户ID	STRU_MIC_OPERATE::mi64SourceUserId
	//用户申请到的麦克风顺序(从1开始)，如申请不成功返回0
	uint16_t		mwSpeakOrder;	//STRU_MIC_OPERATE::mbyIndex	
};
typedef struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS* PSTRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS;

//管理员强制收麦请求请求包
struct STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//被收麦的用户ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ;

//管理员把麦给某个用户请求包
struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//被给麦的用户ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ;

//管理员把麦给某个用户通知包
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;		//被给麦的用户ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID;

//管理员把某个用户插入到发言队列请求包
struct STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//被添加到发言队列的用户ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ;

//增加：何江海 2006-11-21 below
//管理员把某个用户插入到发言队列指定位置请求包
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;		//被添加到发言队列的用户ID	STRU_MIC_OPERATE::mi64DestUserId
	uint8_t		miInsertIndex;  //插入的位置	STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ;
//增加：何江海 2006-11-21 above
/*********************************************************************************************/
//改变当前用户的发言时长请求包
//用途:由管理员操作。
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//改变的用户ID
	uint8_t		mbyMinute;		//允许发言分钟数
	uint8_t		mbyMicIndex;	//麦克索引
};
typedef struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ* PSTRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ;

/*********************************************************************************************/
//改变当前用户的发言时长请求包
//用途:改变当前用户的发言时长成功后，通知大厅中所有用户。
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//改变的用户ID
	uint8_t		mbyMinute;		//允许发言分钟数	
	int64_t		mi64ManagerId;	//
	uint8_t		mbyMicIndex;	//麦克索引
};
typedef struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID* PSTRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID;

/*********************************************************************************************/
//用户发言停止通知包
//用途:用户提前停止发言,或者停止排麦是通知服务器。
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//停止发言的用户ID		STRU_MIC_OPERATE::mi64SourceUserId
};
typedef struct STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID * PSTRU_CL_CRS_CHATROOM_STOP_SPEAK_ID;

/*********************************************************************************************/
//当前麦克风发言顺序包
//用途:包含当前在排麦的前N个用户。
/*********************************************************************************************/
//聊天室麦克风发言顺序包
struct STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
	~STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID();

	uint8_t		mbyCount;			//list的个数
	int64_t *	mpUserIdList;		//用户ID的指针列表
} ;
typedef struct STRU_CL_CRS_MICROPHONE_ORDER_ID * PSTRU_CL_CRS_MICROPHONE_ORDER_ID;
//SinaShow麦克风发言顺序包
struct STRU_WAITING_USER_INFO
{
	int64_t	 	mi64UserID;
	char		macNickName[NICK_NAME_LEN+1];
	int		mlHallID;
	int		mlPicIndex;
	uint16_t		mwVersion;
	uint8_t		mbyGrade;	//用户级别   
	int		mlUserState; //用户状态 
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

struct STRU_SINASHOW_MICROPHONE_ORDER_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_SINASHOW_MICROPHONE_ORDER_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t						mbyCount;			//list的个数
	STRU_WAITING_USER_INFO*		mpUserIdList;		//用户ID的指针列表
} ;
//**********************************************************************************//
//*******  管理员对麦克风管理包(管理请求、应答、通知，新麦序通知、要麦通知)	 *******//
//**********************************************************************************//
/*********************************************************************************************/
//管理员申请或取消麦克风管理请求包
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=申请麦的管理；1＝取消麦的管理
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ;

/*********************************************************************************************/
//管理员申请或取消麦克风管理应答包
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=申请麦的管理；1＝取消麦的管理
	//结果， 如果有其他人正在管理此麦，返回其他人正在管理此麦
	uint8_t		mbyResult;
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS;

/*********************************************************************************************/
//管理员申请或取消麦克风管理通知包
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID();

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=开始麦的管理；1=停止麦的管理
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID;

/*********************************************************************************************/
//管理员修改聊天室发言时长限制请求包
//用途:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ));
	}

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMinute;		//允许发言分钟数	STRU_MIC_OPERATE::mlTime
	uint8_t		mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ;

/*********************************************************************************************/
//管理员修改聊天室发言时长限制通知包
//用途:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID()
	{
		memset(this, 0,sizeof(STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID));
	}

	int64_t		mi64ManagerId;	//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMinute;		//允许发言分钟数	STRU_MIC_OPERATE::mlTime
	uint8_t		mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID;

//**********************************************************************************//
//*******  管理员进行管理包(广播、处理用户请求、应答、录音请求和录音数据)	********//
//**********************************************************************************//
/*********************************************************************************************/
//房间广播包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_CHATROOM_BROADCAST_RQ
{
	STRU_CL_CRS_CHATROOM_BROADCAST_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_BROADCAST_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	//STRU_USER_OPERATE::mi64SourceUserId
	uint16_t        mwDataLen;		//STRU_USER_OPERATE::mlValue
	char		macBroadcaseMsg[UC_MANAGER_BROADCAST_LEN + 1];//广播的内容	//STRU_USER_OPERATE::mpContent
};
typedef struct STRU_CL_CRS_CHATROOM_BROADCAST_RQ* PSTRU_CL_CRS_CHATROOM_BROADCAST_RQ;

/*********************************************************************************************/
//管理员管理用户的处理请求包
//用途:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_OPERATION_ON_USER_RQ
{
	STRU_CL_CRS_OPERATION_ON_USER_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_OPERATION_ON_USER_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//管理员ID	STRU_MIC_OPERATE::mi64SourceUserId
	//STRU_MIC_OPERATE::mbyType
	//处理类型：任命(免除)临时管理员:10(11);禁止(解除)用户发言:12(13);临时(限时)(永久)踢出用户14(15)(16);
	//恢复限时踢出用户:17;  限时(永久)禁止IP:29(30);恢复限时禁止IP用户:31;
	//#define DEF_MANAGER_OPERATION_ADD_SHOWBAR     32//增加秀吧成员;
	//#define DEF_MANAGER_OPERATION_DELETE_SHOWBAR  33//删除秀吧成员
	uint8_t		mbyType;			
	int64_t		mi64UserId;			//被处理用户ID	STRU_MIC_OPERATE::mi64DestUserId
	int     	mlOtherParam;		//当限时踢出用户时，代表时间	STRU_MIC_OPERATE::mlTime
	//当前操作的描述(踢人的话，就是踢人原因)	STRU_MIC_OPERATE::mpContent
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];		
};
typedef struct STRU_CL_CRS_OPERATION_ON_USER_RQ * PSTRU_CL_CRS_OPERATION_ON_USER_RQ ;

/*********************************************************************************************/
//管理员管理用户的处理应答包
//用途:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS
{
	STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t		mbyResult;			//操作结果 零表示成功 非零表示失败	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64ManagerId;		//管理员ID		STRU_MIC_OPERATE::mi64SourceUserId
	//STRU_MIC_OPERATE::mbyType
	uint8_t		mbyType;			//处理类型：任命临时管理员；免除临时管理员；禁止用户发言；临时踢出用户；限时踢出用户；
	int64_t		mi64UserId;			//被处理用户ID	STRU_MIC_OPERATE::mi64DestUserId
	//当前操作的描述(踢人的话，就是踢人原因)
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];	//STRU_MIC_OPERATE::mpContent	
} ;
typedef struct STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS * PSTRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS ;

/*********************************************************************************************/
//用户状态改变通知包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID));
	}

	int64_t mi64UserId; //用户ID		STRU_USER_OPERATE::mi64SourceUserId
	uint8_t mbyState;      //要修改的状态项		STRU_USER_OPERATE::mbyType
	bool mbNewVal;      //新的状态值			STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID * PSTRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID;

//*************************************************************************************************//
//******  聊天室与用户通讯包(被处理通知、级别变化通知、登录请求、登录应答、状态变化通知) **********//
//*************************************************************************************************//
/*********************************************************************************************/
//用户被处理通知包
//管理员修改聊天室发言时长限制通知包
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_USER_BE_OPERATED_ID
{
	STRU_CL_CRS_USER_BE_OPERATED_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_USER_BE_OPERATED_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//管理员ID	STRU_USER_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;			//被处理用户ID	STRU_USER_OPERATE::mi64DestUserId
	//被处理操作类型：任命(免除)临时管理员:10(11);禁止(解除)用户发言:12(13);临时(限时)(永久)踢出用户14(15)(16);
	//恢复限时踢出用户:17;  限时(永久)禁止IP:29(30); 恢复限时禁止IP用户:31; 收麦:40; 100:因有红有进入被踢出
	uint8_t		mbyType;			//	STRU_USER_OPERATE::mbyType
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];		//处理信息的描述	STRU_USER_OPERATE::mpContent
} ;
typedef struct STRU_CL_CRS_USER_BE_OPERATED_ID * PSTRU_CL_CRS_USER_BE_OPERATED_ID;

/*********************************************************************************************/
//用户级别变化通知包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_USER_POWER_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_USER_POWER_CHG_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//用户ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyPower;			//变换后的级别	STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_USER_POWER_CHG_ID * PSTRU_CL_CRS_USER_POWER_CHG_ID ;

/*********************************************************************************************/
//用户语音状态变化通知包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_VOICE_STATE_CHG_ID
{
	STRU_CL_CRS_VOICE_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_STATE_CHG_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//用户ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyState;			//变化后的状态	STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_USER_STATE_CHG_ID * PSTRU_CL_CRS_USER_STATE_CHG_ID;

//**********************************************************************************//
//**********  聊天室属性通知包(属性修改请求包、属性通知包、主题通知包)	************//
//**********************************************************************************//
/*********************************************************************************************/
//聊天室属性修改请求包
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ
{
	STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ));
	}

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int	   Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];				//聊天室的主题
	char		macSalutatory[UC_CHATROOM_SALUTATORY_LEN + 1];		//聊天室的欢迎词
	char		macPassword[UC_HALL_PWD_LEN + 1];		//聊天室的密码
	bool		mbIsLockHall;										//对聊天室是否加锁
} ;
typedef struct STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ * PSTRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ;

/*********************************************************************************************/
//聊天室的属性通知包(用来通知所有管理员)
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_PROPERTY_ID
{
	STRU_CL_CRS_CHATROOM_PROPERTY_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_PROPERTY_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;										//修改者ID
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];				//聊天室的主题
	char		macSalutatory[UC_CHATROOM_SALUTATORY_LEN + 1];		//聊天室的欢迎词
	char		macPassword[UC_HALL_PWD_LEN + 1];		//聊天室的密码
	bool		mbIsLocked;											//是否加锁
};
typedef struct STRU_CL_CRS_CHATROOM_PROPERTY_ID * PSTRU_CL_CRS_CHATROOM_PROPERTY_ID;

/*********************************************************************************************/
//聊天室主题通知
//用途:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_TOPIC_ID
{
	STRU_CL_CRS_CHATROOM_TOPIC_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_TOPIC_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;										//修改者ID
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];	        	//聊天室的主题
	char        macWelcome[UC_CHATROOM_SALUTATORY_LEN+1];           //聊天室的欢迎词    
} ;
typedef struct STRU_CL_CRS_CHATROOM_TOPIC_ID * PSTRU_CL_CRS_CHATROOM_TOPIC_ID;

/*********************************************************************************************/
//聊天室其他用户进入通知
//修改人：	Fanyunfeng
//时间：	2004－12－28
//内容：	RA:聊天室用户信息(版本400) 由390改为400 同时增加用户语言类型
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400
{
	int mlChatroomID;					//大厅id
	int64_t	mi64UserID;					//用户ID
	char macNickName[NICK_NAME_LEN + 1];	//用户昵称
	uint16_t mwPhotoNum;					//用户头像
	uint8_t mbyPower;						//用户权限
	int mlUserState;					//用户状态

	uint8_t mbyUserLanguage; 			//用户语言类型
	int	 miRedMemTime;					//红人资格

	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400* PSTRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400; 

/*********************************************************************************************/
//聊天室其他用户离开通知
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350
{
	int mlChatroomID;//大厅id	
	int64_t	mi64UserID; //用户ID	//STRU_USER_OPERATE::mi64SourceUserId
	uint8_t mbyCancelType;//0 普通退出 1。需要显示原因		//STRU_USER_OPERATE::mbyType
	char	macReason[REASON_LEN + 1];//退出原因	//STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350 * PSTRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350;

/*********************************************************************************************/
//聊天室信息通知包
//用途:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_CHAT_INFO
{
	int64_t mi64FromId;
	int64_t mi64ToId;
	uint8_t	mbyChatType;
	uint16_t	mwMoodLen;
	uint16_t	mwControlLen;
	uint16_t	mwContentLen;//通讯报不含字段
	char	mstrMood[CRS_DATA_LEN+1];
	char	mstrControl[CRS_DATA_LEN+1];
	char	mstrContent[CRS_DATA_LEN+1];
	uint16_t    mwLen;		//总长度用于解包时通过计算mwContentLen
	STRU_UC_CL_CRS_CHAT_INFO()
	{
		mwLen = 0;
		mi64FromId = 0;
		mi64ToId= 0;
		mbyChatType= 0;
		mwMoodLen  = 0;
		mwControlLen = 0;
		mwContentLen = 0;
		memset(mstrMood, 0, CRS_DATA_LEN+1);
		memset(mstrControl, 0,CRS_DATA_LEN+1);
		memset(mstrContent, 0,CRS_DATA_LEN+1);

	}
	int GetSubLen()
	{
		return sizeof(mi64FromId) * 2 +sizeof(uint8_t) + sizeof(uint16_t)*2 +mwMoodLen + mwControlLen;//mi64FromId+mi64ToId+mbyChatType+mwMoodLen+mwControlLen
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

};
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_DATA_ID_350
{
	int	mlChatroomID;			//大厅id
	int64_t	mi64DstUserID;			//公共信息标识	STRU_USER_OPERATE::mi64DestUserId
	uint16_t	mwDataLen;				//信息大小		STRU_USER_OPERATE::mlValue
	//char	mData[CRS_DATA_LEN+1];	//信息			STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;
	int64_t	mi64SrcUserID;			//来源用户ID	STRU_USER_OPERATE::mi64SourceUserId


	///int64_t mi64DstUserID;			//目的用户ID 2005II 开始增加

	STRU_UC_CL_CRS_DATA_ID_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_DATA_ID_350));
	}

	int Pack(char* apBuffer , int alLen);
	int UnPack(char* apBuffer, int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_DATA_ID_350 * PSTRU_UC_CL_CRS_DATA_ID_350;

struct	STRU_UC_CL_CRS_DATA_ID_LONG
{
	long	mlChatroomID;			//大厅id
	int64_t	mi64DstUserID;			//公共信息标识	STRU_USER_OPERATE::mi64DestUserId
	uint16_t	mwDataLen;				//信息大小		STRU_USER_OPERATE::mlValue
	//char	mData[CRS_DATA_LEN+1];	//信息			STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;
	int64_t	mi64SrcUserID;			//来源用户ID	STRU_USER_OPERATE::mi64SourceUserId


	///INT64 mi64DstUserID;			//目的用户ID 2005II 开始增加

	STRU_UC_CL_CRS_DATA_ID_LONG()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_DATA_ID_LONG));
	}

	int Pack(char* apBuffer, int alLen);
	int UnPack(char* apBuffer, int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_DATA_ID_LONG * PSTRU_UC_CL_CRS_DATA_ID_LONG;


//聊天室控制信息
struct STRU_UC_CL_CRS_GENERAL_INFO
{
	int64_t mi64FromId;
	int64_t mi64ToId;
	uint16_t	mwType;
	uint16_t	mwContentLen;
	char	mstrContent[CRS_DATA_LEN+1];
	int GetSubLen()
	{
		return sizeof(mi64FromId) * 2 +sizeof(uint16_t);//mi64FromId+mi64ToId+mbyChatType+mwMoodLen+mwControlLen
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//客户端通讯用的数据包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_GENERAL_PACK_350
{
	int mlChatRoomID;		
	int64_t mi64DstUserID;	//STRU_USER_OPERATE::mi64DestUserId
	uint16_t mwDataLen;			//STRU_USER_OPERATE::外面不传值
	STRU_UC_CL_CRS_GENERAL_INFO	mGENERALInfo;	//
	//char	macGeneralMsg[INFO_LEN + 1];	//STRU_USER_OPERATE::外面传入mbyType 里面特殊处理
	int64_t	mi64SrcUserID; //来源用户ID		//STRU_USER_OPERATE::mi64SourceUserId

	STRU_UC_CL_CRS_GENERAL_PACK_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GENERAL_PACK_350));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_GENERAL_PACK_350 *PSTRU_UC_CL_CRS_GENERAL_PACK_350;


/*********************************************************************************************/
//查询限时踢出黑名单列表请求包
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_BLACK_QUERY_RQ
{
	int64_t		mi64ManagerId;		//请求者ID  STRU_USER_OPERATE::mi64SourceUserId

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BLACK_QUERY_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACK_QUERY_RQ));
	}
};

/*********************************************************************************************/
//限时踢出黑名单列表
//用途:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_TIME_BLACK_LIST
{
	struct STRU_TIME_KICKOUT_USER
	{
		int64_t mi64UserID;			//用户ID
		int   mlNoComeInTime;		//限制时间
		int   mlResidualTime;		//剩余时间
		int Serialize(CStandardSerialize & aoStandardSerialize);
	};

	int64_t		mi64ManagerId;								//请求者ID
	short		msUserCount;								//黑名单个数
	struct STRU_TIME_KICKOUT_USER * mpBlackList;			//黑名单列表

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_TIME_BLACK_LIST()
	{
		memset(this, 0,sizeof(STRU_UC_CL_CRS_TIME_BLACK_LIST));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//用户级别变化通知包
//用途:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_POWER_CHANGED_ID
{
	STRU_UC_CL_CRS_POWER_CHANGED_ID();
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char * apBuffer,int alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t mi64ManagerId; //管理员ID
	int64_t mi64UserId; //被处理用户ID
	uint8_t mbyNewPower; //新的级别
	char mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1]; //处理信息的描述
} ;
typedef struct STRU_UC_CL_CRS_POWER_CHANGED_ID * PSTRU_UC_CL_CRS_POWER_CHANGED_ID;

/*********************************************************************************************/
//登录应答（版本390）
//用途:
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RS_390         
{
	STRU_UC_CL_CRS_LOGIN_HALL_RS_390();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t				mbyResult;											//0是同意,其它是拒绝，
	int				mlHallID;							//大厅id
	int				mlRoomMaxPlayer;					//房间最大人数	
	char				macErrInfo[ERR_BUF_LEN + 1];			//错误信息
	char				mszVoiceIp[64];						//语音中转的IP
	unsigned short		musVoicePort;							//语音中转的端口
	char				macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;//聊天室的主题
	char				macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		//聊天室的欢迎词	
	char				macPwd[UC_HALL_PWD_LEN + 1];			//大厅密码(只告诉管理员)
	int64_t				mi64CurManageMic;			//当前是谁在管理麦序
	unsigned int		mulUserSpeakTime;				//当前发言时长	
	char				macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int				mlHallProperty;             //大厅属性                               
};

/*********************************************************************************************/
//修改人：	Fanyunfeng
//时间：	2005－01－10
//内容：	C:登录应答（版本401） 增加大厅状态
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RS_400         
{
	uint8_t				mbyResult;						//0是同意,其它是拒绝，
	int				mlHallID;						//大厅id
	int				mlRoomMaxPlayer;				//房间最大人数	
	char				macErrInfo[ERR_BUF_LEN + 1];	//错误信息
	char				mszVoiceIp[64];					//语音中转的IP
	unsigned short		musVoicePort;					//语音中转的端口
	char				macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//聊天室的主题
	char				macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//聊天室的欢迎词	
	char				macPwd[UC_HALL_PWD_LEN + 1];	//大厅密码(只告诉管理员)
	int64_t				mi64CurManageMic;				//当前是谁在管理麦序
	unsigned int		mulUserSpeakTime;				//当前发言时长	
	char				macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int				mlHallProperty;					//大厅属性
	int				mlHallState;					//大厅状态

	STRU_UC_CL_CRS_LOGIN_HALL_RS_400()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//主页地址信息
//用途:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_HOST_INFO
{
	STRU_UC_CL_CRS_HOST_INFO();
	char mszhostName[HOMEPAGE_DISPLAY_LEN+1];
	char mszhostAddr[URL_LINK_LEN+1];
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//主页地址通知包
//用途:
/*********************************************************************************************/
struct  STRU_UC_CL_CRS_HOST_INFO_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_HOST_INFO_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	char macBgBmpName[CHATROOM_BMP_NAME_LEN+1];		//背景图片名称
	uint16_t mwListCount;
	STRU_UC_CL_CRS_HOST_INFO *mpHostInfoList;
};

/*********************************************************************************************/
//主页地址通知包600
//用途:
/*********************************************************************************************/
struct  STRU_UC_CL_CRS_HOST_INFO_ID600
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_HOST_INFO_ID600()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_HOST_INFO_ID600));
	}
	~STRU_UC_CL_CRS_HOST_INFO_ID600();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	char macBgBmpName[CHATROOM_BMP_NAME_LEN+1];		//背景图片名称
	uint16_t mwListCount;
	uint16_t mwInnerPageListCount;
	STRU_UC_CL_CRS_HOST_INFO *mpHostInfoList;
	STRU_UC_CL_CRS_HOST_INFO *mpInnerPageList;		//内嵌网页信息列表，结构与主页列表一样
};

/*********************************************************************************************/
//用户状态改变通知（390）
//用途:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_USER_STATE_CHG_ID_390         
{
	STRU_UC_CL_CRS_USER_STATE_CHG_ID_390()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_CHG_ID_390));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//用户ID    STRU_USER_OPERATE::mi64SourceUserId
	uint16_t        mwChgType;			//控制的类型	STRU_USER_OPERATE::mbyType
	uint8_t		mbyChgVal;          //控制的状态 0表示无1表示有		STRU_USER_OPERATE::mbyValue
};
//添加： 张亚伟 2004－06－30 above

/*********************************************************************************************/
//聊天室用户信息结构
//修改人：	HJH
//时间：	2007－12－17
//内容：	C:聊天室用户信息结构（版本2007） 增加语言类型
/*********************************************************************************************/
struct	STRU_CHATROOM_USER_INFO_2007
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//用户权限
	int    mlUserState;				//用户状态
	uint8_t	mbyVoiceState ;				//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;            //用户语言类型
	int		miRedMemTime;				//红人资格
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_2007()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2007));
	}
};
typedef	STRU_CHATROOM_USER_INFO_2007* PSTRU_CHATROOM_USER_INFO_2007 ;

/*********************************************************************************************/
//聊天室用户信息
//修改人：	HJH
//时间：	2007－12－17
//内容：	C:聊天室用户信息（版本2007） 使用2007的用户信息
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_USER_INFO_ID_2007
{
	int mlChatroomID;      //大厅id
	uint16_t mwUserCount;       //用户数
	PSTRU_CHATROOM_USER_INFO_2007 mpUserIDList;//用户信息列表
	//STRU_UC_CL_CRS_USER_INFO_ID_2007();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CL_CRS_USER_INFO_ID_2007()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2007));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	~STRU_UC_CL_CRS_USER_INFO_ID_2007();
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_2007* PSTRU_UC_CL_CRS_USER_INFO_ID_2007;

/*********************************************************************************************/
//聊天室用户信息结构
//修改人：	Fanyunfeng
//时间：	2004－12－28
//内容：	C:聊天室用户信息结构（版本400） 增加语言类型
/*********************************************************************************************/
struct	STRU_CHATROOM_USER_INFO_400
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//用户权限
	int    mlUserState;				//用户状态
	uint8_t	mbyVoiceState ;				//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;            //用户语言类型
	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_CHATROOM_USER_INFO_400()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_CHATROOM_USER_INFO_400* PSTRU_CHATROOM_USER_INFO_400 ;

/*********************************************************************************************/
//聊天室用户信息
//修改人：	Fanyunfeng
//时间：	2004－12－28
//内容：	C:聊天室用户信息（版本400） 使用400的用户信息
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_USER_INFO_ID_400
{
	int mlChatroomID;      //大厅id
	uint16_t mwUserCount;       //用户数
	PSTRU_CHATROOM_USER_INFO_400 mpUserIDList;//用户信息列表
	//STRU_UC_CL_CRS_USER_INFO_ID_400();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);


	STRU_UC_CL_CRS_USER_INFO_ID_400()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_400* PSTRU_UC_CL_CRS_USER_INFO_ID_400;

/*********************************************************************************************/
//聊天室献花数据包
//修改人：	Fanyunfeng
//时间：	2005－01－10
//内容：	A:献花时使用的数据包
/*********************************************************************************************/
// $_CODE_CHANGE 2005-03-23 fyf 修改：包结构更改
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_FLOWERS_ID
{
	int		mlChatroomID;		//大厅ID	
	int64_t		mi64DstUserID; 		//目标用户ID	STRU_USER_OPERATE::mi64DestUserId
	int64_t		mi64SrcUserID; 		//来源用户ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyIsPrivate;		//STRU_USER_OPERATE::mbyType
	int		mlFlowerType;		//STRU_USER_OPERATE::mlValue

	int    Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CL_CRS_FLOWERS_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_FLOWERS_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//*******************************************************************************************
//新聊天室表情数据包（送礼物、动漫）
//添加人：屈峰
//时间：2008-06-12
//*******************************************************************************************
//STRU_USER_OPERATE
struct STRU_CL_CRS_OFFER_BROW_ID
{
	int64_t		mi64DstUserID; 		//目标用户ID	STRU_USER_OPERATE::mi64DestUserId
	int64_t		mi64SrcUserID; 		//来源用户ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t        mbyBrowType;        //0:送礼物 1:动漫	STRU_USER_OPERATE::mbyType
	uint8_t		mbyIsPrivate;		//公聊、私聊状态	STRU_USER_OPERATE::mbyValue
	uint16_t		mwOfferBrowLen;		//表情长度
	char		macOfferBrowName[UC_NEW_OFFER_BROW_NAME_LEN + 1];//表情名称//STRU_USER_OPERATE::mpContent

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_OFFER_BROW_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_OFFER_BROW_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

/*********************************************************************************************/
//聊天室管理员更改大厅状态数据包
//修改人：	Fanyunfeng
//时间：	2005－01－10
//内容：	A:更改聊天室状态
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_HALL_STAT_CHG_ID
{
	int64_t 	mi64ManagerID;		//管理员ID		STRU_USER_OPERATE::mi64SourceUserId
	int		mlChatHallID;		//大厅ID
	//STRU_USER_OPERATE::mbyType
	uint16_t		mwProperty;			//0献花		
	//1共聊
	//2停止视频转发  已经不使用
	//STRU_USER_OPERATE::mbyValue
	int		mlNewValue;			//1	TRUE;	
	//0	FALSE;
	uint16_t   	mwOtherDataLen;		//STRU_USER_OPERATE::mlValue
	char   	mpzOthreData[256];	//STRU_USER_OPERATE::mpContent

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_HALL_STAT_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_HALL_STAT_CHG_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

/*********************************************************************************************/
//管理员取封IP列表请求
//修改人：	Fanyunfeng
//时间：	2005－03－10
//内容：	A:更改聊天室状态
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_BLACKIP_LIST_RQ
{
	int64_t		mi64ManagerId;		//请求者ID		STRU_USER_OPERATE::mi64SourceUserId

	int Pack(char *   apBuffer ,int    alLen);
	int UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BLACKIP_LIST_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACKIP_LIST_RQ));
	}
};

/*********************************************************************************************/
//封IP列表 应答管理员发送的STRU_UC_CL_CRS_BLACKIP_QUERY_RQ 
//修改人：	Fanyunfeng
//时间：	2005－03－10
//内容：	A:更改聊天室状态
/*********************************************************************************************/
struct STRU_UC_CL_CRS_BLACKIP_LIST_RS
{
	struct STRU_BLACK_IP_INFO
	{
		int64_t					mi64UserID;			//用户ID
		unsigned int			mulIP;				//IP
		int   					mlNoComeInTime;		//限制时间
		int   					mlResidualTime;		//剩余时间
		int Serialize(CStandardSerialize& aoStandardSerialize);
		STRU_BLACK_IP_INFO()
		{
			memset(this, 0, sizeof(STRU_BLACK_IP_INFO));
		}
	};
	typedef STRU_BLACK_IP_INFO* PSTRU_BLACK_IP_INFO ;

	int64_t						mi64ManagerId;		//请求者ID
	short						msCount;			//黑名单个数
	struct STRU_BLACK_IP_INFO *  mpBlackList;		//黑名单列表

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_BLACKIP_LIST_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACKIP_LIST_RS));
	}
	~STRU_UC_CL_CRS_BLACKIP_LIST_RS();
};

/*********************************************************************************************/
//用户状态请求
//修改人：	Fanyunfeng
//时间：	2005－03－16
//内容：	A
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_USER_STATE_RQ
{
	int64_t	mi64UserId;		//指定的用户ID		STRU_USER_OPERATE::mi64DestUserId

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_USER_STATE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_RQ));
	}
};

/*********************************************************************************************/
//用户状态应答
//修改人：	Fanyunfeng
//时间：	2005－03－16
//内容：	A
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_USER_STATE_RS
{
	int64_t	mi64UserId;	//指定的用户ID		STRU_USER_OPERATE::mi64DestUserId
	int	mlState;	//用户状态			STRU_USER_OPERATE::mlValue

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_USER_STATE_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_RS));
	}
};
//********************************************** 500 *****************************************

/*********************************************************************************************/
//麦状态信息列表
//用途：登录时通知客户端
/*********************************************************************************************/
struct STRU_UC_CL_CRS_MIC_INFO_LIST_ID
{
	//麦状态信息
	struct STRU_UC_CL_CRS_MIC_INFO
	{
		uint8_t	mbyOperateType;					//0		ADD
		//1		DELETE
		//2		UPDATE

		uint8_t	mbyMicIndex;

		bool				mbSupportVideo;		//支持视频
		STRU_AUDIO_CONFIG	mstruAudioConfig;	//音频配置信息
		STRU_VIDEO_CONFIG	mstruVideoConfig;	//视频配置信息

		uint16_t	mwMicStatue;    				//麦克状态
		//第2位:麦是否打开 第3位:是否关闭视频 第4位:是否被管理 第6位:是否允许放歌
		//(运行/停止 是否支持视频 是否处于管理状态) 
		uint16_t	mwMicTimeLen;  					//麦序时长
		int64_t mi64ManagerID;  				//管理员ID
		int	mlDeltaSpeakTime;				//与麦时的差值

		STRU_UC_CL_CRS_MIC_INFO()
		{
			memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_INFO));
		}
		int Serialize(CStandardSerialize& aoStandardSerialize);
	};

	uint16_t					mwMicCount;			//Mic数量
	STRU_UC_CL_CRS_MIC_INFO *mpMicInfoList;		//列表

	STRU_UC_CL_CRS_MIC_INFO_LIST_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_INFO_LIST_ID));
	}
	~STRU_UC_CL_CRS_MIC_INFO_LIST_ID();
	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//开始发言通知
//用途：服务器通知用户开始发言
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_BEGIN_SPEAK_ID
{
	uint8_t	mbyMicIndex;	//Mic索引	STRU_MIC_OPERATE::mbyIndex
	int64_t 	mi64UserID;		//用户ID    STRU_MIC_OPERATE::mi64SourceUserId


	STRU_UC_CL_CRS_BEGIN_SPEAK_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BEGIN_SPEAK_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//新的登录包
//用途：和以前的包区别用户的版本
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RQ_500
{
	char	macVersion[VERSION_LEN + 1];		//
	int	mlHallID;							//大厅id
	int64_t	mi64UserId;							//用户ID
	char	macNickName[NICK_NAME_LEN + 1];  	//用户昵称
	uint16_t	mwPhotoNum;							//用户头像
	char	macPassword[UC_HALL_PWD_LEN + 1];	//大厅的密码
	uint8_t	mbySource;           				//来源
	int    mlUserState;						//用户状态 0位表示视频状态
	char	macUserPwd[MD5_LEN + 1];			//用户密码
	uint8_t	mbyUserLanguage; 					//用户语言类型
	//	0：简体中文；
	//	1：繁体中文； 
	//	2：英文
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_500()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RQ_500));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//登录应答包
//用途：新的应答包,增加麦的数量
/*********************************************************************************************/
struct STRU_UC_CL_CRS_LOGIN_HALL_RS_500
{
	uint8_t			mbyResult;							//0是同意,其它是拒绝，
	int			mlHallID;							//大厅id
	int			mlRoomMaxPlayer;					//房间最大人数	
	char			macErrInfo[ERR_BUF_LEN + 1];		//错误信息
	char			mszVoiceIp[64];						//语音中转的IP
	unsigned short	musVoicePort;						//语音中转的端口
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//聊天室的主题
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//聊天室的欢迎词	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//大厅密码(只告诉管理员)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int			mlHallProperty;						//大厅属性 From DataBase
	int			mlHallState;						//大厅状态 Dynamic Data

	uint8_t			mbyMicNum;							//大厅中麦的数量

	STRU_UC_CL_CRS_LOGIN_HALL_RS_500()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_500));
	}

	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_600
{
	unsigned int	mulToken;							//用户Token值
	uint8_t			mbyResult;							//0是同意,其它是拒绝，
	int			mlHallID;							//大厅id
	int			mlRoomMaxPlayer;					//房间最大人数	
	char			macErrInfo[ERR_BUF_LEN + 1];		//错误信息
	char			mszVoiceIp[64];						//语音中转的IP
	unsigned short	musVoicePort;						//语音中转的端口
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//聊天室的主题
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//聊天室的欢迎词	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//大厅密码(只告诉管理员)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int			mlHallProperty;						//大厅属性 From DataBase
	int			mlHallState;						//大厅状态 Dynamic Data

	uint8_t			mbyMicNum;							//大厅中麦的数量


	STRU_UC_CL_CRS_LOGIN_HALL_RS_600()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_600));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_2007
{
	unsigned int	mulToken;							//用户Token值
	uint8_t			mbyResult;							//0是同意,其它是拒绝，
	int			mlHallID;							//大厅id
	int			mlRoomMaxPlayer;					//房间最大人数	
	char			macErrInfo[ERR_BUF_LEN + 1];		//错误信息
	char			mszVoiceIp[64];						//语音中转的IP
	unsigned short	musVoicePort;						//语音中转的端口
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//聊天室的主题
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//聊天室的欢迎词	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//大厅密码(只告诉管理员)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int			mlHallProperty;						//大厅属性 From DataBase
	int			mlHallState;						//大厅状态 Dynamic Data

	uint8_t			mbyMicNum;							//大厅中麦的数量
	char			macWUserURL[ERR_BUF_LEN + 1];		//错误信息


	STRU_UC_CL_CRS_LOGIN_HALL_RS_2007()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_2007));
	}

	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_2009
{
	unsigned int	mulToken;							//用户Token值
	uint8_t			mbyResult;							//0是同意,其它是拒绝，
	int			mlHallID;							//大厅id
	int			mlRoomMaxPlayer;					//房间最大人数	
	char			macErrInfo[ERR_BUF_LEN + 1];		//错误信息
	char			mszVoiceIp[64];						//语音中转的IP
	unsigned short	musVoicePort;						//语音中转的端口
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//聊天室的主题
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//聊天室的欢迎词	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//大厅密码(只告诉管理员)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //聊天室场景
	int			mlHallState;						//大厅状态 Dynamic Data

	uint8_t			mbyMicNum;							//大厅中麦的数量
	char			macWUserURL[ERR_BUF_LEN + 1];		//错误信息

	uint64_t           mi64HallProperty;					//大厅属性 From DataBase

	STRU_UC_CL_CRS_LOGIN_HALL_RS_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_2009));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
/*********************************************************************************************/
//管理员管麦请求包
//用途：管理员发起管麦请求
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ
{
	int64_t		mi64ManagerID;			//管理员ID	STRU_MIC_OPERATE::mi64SourceUserId
	//操作类型夺麦:1 、收麦:2、递麦:3、准备接麦:4	STRU_MIC_OPERATE::mbyType
	uint16_t		mwType;					
	int64_t		mi64DesUserID;			//操作的用户	STRU_MIC_OPERATE::mi64DestUserId
	uint8_t		mbyMicIndex;			//MicIndex		STRU_MIC_OPERATE::mbyIndex

	STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//管理员管麦应答包
//用途：管理员管麦的操作结果
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS
{
	int64_t		mi64ManagerID;			//管理员ID	STRU_MIC_OPERATE::mi64SourceUserId
	uint16_t		mwType;					//操作类型	STRU_MIC_OPERATE::mbyType
	uint8_t		mbyResult;				//1	TRUE	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64DesUserID;			//操作的用户	STRU_MIC_OPERATE::mi64DestUserId

	STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//管理员控制MIC
//用途：改变麦的状态
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID
{
	int64_t		mi64ManagerID;		//管理员ID	STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMicIndex;		//Mic索引号		STRU_MIC_OPERATE::mbyIndex
	//STRU_MIC_OPERATE::mbyType
	uint16_t		mbOperateType;		//1	开/关闭麦	
	//2	关闭视频
	//3	开始/结束管理员管麦
	//5 是否允许播放
	//STRU_MIC_OPERATE::mbState
	uint16_t		mwValue;			//0	FALSE
	//1	TRUE

	STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//用户改变接收状态
//用途：用户改变接收状态
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID
{
	int64_t	mi64UserID;		//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t	mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
	uint8_t	mbyMediaType;	//STRU_MIC_OPERATE::mbyType
	bool	mbyState;		//STRU_MIC_OPERATE::mbState

	STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//GGS发送的Mic属性类表
//用途：在大厅启动时通知CRS
//**由于GGS没有使用这个数据包因而作为内部的结构在 GGSFunc和CChatHall之间转达信息
/*********************************************************************************************/
struct STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID
{
	//Mic属性
	struct STRU_UC_GGS_CRS_MIC_PROPERTY
	{
		uint8_t	mbyType;						//0		ADD
		//1		DELETE
		//2		UPDATE
		uint8_t mbyMicIndex;

		bool				mbSupportVideo;		//支持视频
		STRU_AUDIO_CONFIG	mstruAudioConfig;	//音频配置信息
		STRU_VIDEO_CONFIG	mstruVideoConfig;	//视频配置信息

		STRU_UC_GGS_CRS_MIC_PROPERTY()
		{
			memset(this,0, sizeof(STRU_UC_GGS_CRS_MIC_PROPERTY));
		}
		int	Serialize(CStandardSerialize& aoStandardSerialize);
	};

	int	mlHallId;							//大厅ID
	uint16_t	mwMicCount;
	STRU_UC_GGS_CRS_MIC_PROPERTY * mpMicProportyList;

	STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID()
	{
		memset(this,0, sizeof(STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//登录包2007
//改用变化登录请求包
/*********************************************************************************************/


struct STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO
{
	enum LoginAttributeType
	{
		AT_BYTE_REDMEMBER,      //红人标识
		AT_PCHAR_USERUNINAME,   //用户昵称
		AT_PCHAR_USERMOOD,      //用户心情
		AT_PCHAR_USERIMAGEURL,  //用户头像URL
		AT_BYTE_USERSEX,        //用户性别
		AT_INT_USER_ONLINETIME, //用户在线时长
		AT_INT_USER_CHARM,      //用户魅力值
		AT_INT_USER_WEALTH,     //用户财富值
		AT_INT_USER_ACTIVITY,   //用户活跃度
		AT_INT_VIP_ROOMID,      //用户VIP房主房间ID
		AT_BYTE_SHOW_BAR,       //用户秀吧用户标识
		AT_PCHAR_BIRTHDAY,      //用户生日
		AT_BYTE_SHOP_USER,      //用户开通商城用户标识
		AT_PCHAR_MAC,			//MAC地址
		AT_INT_USER_PEER_LEVEL, //贵族级别
		AT_INT_USER_SELLER,     //官方销售
        AT_PCHAR_MACHINE_CODE,
		ATTRIBUTETYPE_MAX       //用户属性结束符
	};

	int					 menumAttributeType;	//房间属性
	int					 mnDateLen;
	char*				 mPbVal;

	int		Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO();
};

struct	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007
{
	char	macVersion[VERSION_LEN + 1];		//
	int	mlHallID;							//大厅id
	int64_t	mi64UserId;							//用户ID
	char	macNickName[NICK_NAME_LEN + 1];  	//用户昵称
	uint16_t	mwPhotoNum;							//用户头像
	char	macPassword[UC_HALL_PWD_LEN + 1];	//大厅的密码
	uint8_t	mbySource;           				//来源
	int    mlUserState;						//用户状态 0位表示视频状态
	char	macUserPwd[MD5_LEN + 1];			//用户密码
	uint8_t	mbyUserLanguage; 					//用户语言类型
	//	0：简体中文；
	//	1：繁体中文； 
	//	2：英文

	uint8_t    mbyAttributeCount;					//附加属性个数
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO *mpAttributeInfo;

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007 ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007));
	}
	~STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007();
};
//---------------------------UDP---------------------------
struct STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ
{
	int64_t 	mi64UserID;		//用户ID
	STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//客户端登录过程中服务器返回给客户端的第一个数据包结构
struct STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS
{
	int64_t 	mi64UserID;		//用户ID
	int	mlHallID;       //大厅ID
	unsigned int mulToken; //用户令牌
	STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//客户端登录过程中发的第一个数据包结构
struct STRU_UC_CL_CRS_LOGIN_INFO_RQ
{
	int64_t	mi64UserId;	     //用户ID
	int		muLoginPhase;	//登录阶段
	STRU_UC_CL_CRS_LOGIN_INFO_RQ();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
struct STRU_UC_CL_CRS_LOGIN_INFO_RS
{
	int64_t	mi64UserId;	     //用户ID
	int		muLoginPhase;	//登录阶段
	STRU_UC_CL_CRS_LOGIN_INFO_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
//keep live  客户端发给服务器的数据包结构
struct STRU_UC_CL_CRS_ALIVE_RQ 
{
	int64_t mi64UserID;					//用户的UC号
	int  mlHallID;						//大厅ID
	STRU_UC_CL_CRS_ALIVE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_ALIVE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//keep live 服务器返回给客户端的数据包结构
struct STRU_UC_CL_CRS_ALIVE_RS
{
	int64_t 	mi64UserID;					//用户的UC号
	int	mlHallID;						//大厅ID
	int64_t	mi64LastTime;					//最近存活时间
	STRU_UC_CL_CRS_ALIVE_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
//推出房间
struct STRU_UC_CL_CRS_LOGOUT
{
	int64_t mi64UserID;					//用户的UC号
	int  mlHallID;						//大厅ID
	STRU_UC_CL_CRS_LOGOUT();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGOUT_RS 
{
	int64_t mi64UserID;					//用户的UC号
	int  mlHallID;						//大厅ID
	int   miErrorCode;                  //错误码
	char  mszErrorInfo[ERROR_BUFFER_LENGTH + 1];//错误信息
	STRU_UC_CL_CRS_LOGOUT_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
//---------------------------------------UDP----------------------------------------------

struct STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID
{
	//发言人信息
	struct STRU_UC_CL_CRS_SPEAKER_INFO
	{
		int64_t			mi64DstUserID;				//0		所有用户
		//		私聊的用户ID
		uint8_t 			mbyMicIndex;				//使用的MicIncex
		int64_t			mi64SpeakerUserID;			//发言用户ID

		bool			mbContainAudioInfo;			//包含音频格式
		STRU_AUDIO_INFO	mstrAudioInfo;				//上面的标识为假跳过，音频格式

		bool			mbContainVideoInfo;			//包含视频信息
		STRU_VIDEO_INFO	mstrVideoInfo;				//上面的标识为假跳过，视频格式信息

		STRU_UC_CL_CRS_SPEAKER_INFO()
		{
			memset(this, 0, sizeof(STRU_UC_CL_CRS_SPEAKER_INFO));
		}
		int Serialize(CStandardSerialize& aoStandardSerialize);
	};

	uint8_t							mbySpeakerNum;
	STRU_UC_CL_CRS_SPEAKER_INFO* 	mpSpeakerUserInfo;

	STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID));
	}
	~STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID();
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
//
struct	STRU_CHATROOM_USER_INFO_2008
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//用户权限
	int    mlUserState;				//用户状态
	uint8_t	mbyVoiceState ;				//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;            //用户语言类型
	int		miRedMemTime;				//红人资格
	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_CHATROOM_USER_INFO_2008()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2008));
	}

};
typedef	STRU_CHATROOM_USER_INFO_2008* PSTRU_CHATROOM_USER_INFO_2008 ;

struct	STRU_UC_CL_CRS_USER_INFO_ID_2008
{
	int mlChatroomID;      //大厅id
	uint16_t mwUserCount;       //用户数
	PSTRU_CHATROOM_USER_INFO_2008 mpUserIDList;//用户信息列表
	//STRU_UC_CL_CRS_USER_INFO_ID_2007();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_USER_INFO_ID_2008()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2008));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_2008* PSTRU_UC_CL_CRS_USER_INFO_ID_2008;

//用户请求好友信息
struct	STRU_USER_ID_LIST_RQ_2008
{
	int miUserCount;  //用户个数
	int64_t mvUserIdList[MAX_USER_ID_NUM];//用户ID 列表 

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_ID_LIST_RQ_2008()
	{
		memset(this, 0, sizeof(STRU_USER_ID_LIST_RQ_2008));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//用户进入大厅时给其它人的通知包
//mwVersion !=0时不显示它
struct	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW2008
{
	int	mlChatroomID;				//大厅id
	int64_t	mi64UserID;					//用户ID
	char macNickName[NICK_NAME_LEN + 1];//用户昵称
	uint16_t mwPhotoNum;					//用户头像
	uint8_t mbyPower;						//用户权限
	int mlUserState;					//用户状态

	uint8_t mbyUserLanguage; 				//用户语言类型
	int	 miRedMemTime;					//红人资格
	uint16_t mwVersion;						//用户类型 

	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW2008();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

//////////////////////////////////////////////
//用户登录时收到的大厅用户列表包
typedef struct	STRU_CHATROOM_USER_INFO_SINASHOW_2008
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//用户权限
	int    mlUserState;				//用户状态
	uint8_t	mbyVoiceState ;				//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;            //用户语言类型
	int		miRedMemTime;				//红人资格
	int		mwVersion;					//用户类型
	int	mlUserHallID; 
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_SINASHOW_2008()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_SINASHOW_2008));
	}

}*PSTRU_CHATROOM_USER_INFO_SINASHOW_2008;

//////////////////////////////////////////////////////////////////////////
typedef struct	STRU_CHATROOM_USER_INFO_SINASHOW_2009
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t  	mbyPower;					//用户权限
	int  	mlUserState;				//用户状态
	uint8_t	mbyVoiceState ;				//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;			//用户语言类型
	uint16_t	mwTypeLen;					//类型个数
	uint8_t*	pmByteUserLevel;				//用户级别#
	int*	pmlUserTime;					//到期时间#
	int		mwVersion;					//用户类型
	int	mlUserHallID;				//用户所在的大厅ID
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_SINASHOW_2009()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_SINASHOW_2009));
	}
}* PSTRU_CHATROOM_USER_INFO_SINASHOW_2009;

//RSA请求
struct STRU_RSA_INFO_RQ
{
	int		nLen;							//密钥长度
	uint8_t*	mszPublicKey;					//公钥
	int		nType;							//加密步骤
	int64_t 	mi64UserID;						//用户ID
	int		nSize;							//原始密钥长度
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_RSA_INFO_RQ()
	{
		memset(this, 0, sizeof(STRU_RSA_INFO_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//RSA应答
struct STRU_RSA_INFO_RS
{
	int		nLen;							//密钥长度
	uint8_t*	mszPublicKey;					//公钥
	int		nType;							//加密步骤
	int64_t 	mi64UserID;						//用户ID
	int		nSize;							//原始密钥长度
	uint8_t	byRet;							//结果
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_RSA_INFO_RS()
	{
		memset(this, 0, sizeof(STRU_RSA_INFO_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//加解密
struct STRU_ENDECRYPT_FUN
{
	int		nLen;							//密文长度
	char *	mszEncrypt;						//密文

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_ENDECRYPT_FUN()
	{
		memset(this, 0, sizeof(STRU_ENDECRYPT_FUN));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//////////////////////////////////////////////////////////////////////////

//插麦通知包 
typedef struct STRU_UC_CL_CRS_INSERT_MIC_ID	
{
	int64_t mi64ManagerID;	//管理员ID
	int64_t mi64UserId;		//插麦对象ID
	uint8_t mbyIndex;			//插入的位置
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_INSERT_MIC_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_INSERT_MIC_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}*PSTRU_UC_CL_CRS_INSERT_MIC_ID;


//SinaShow1.3版新加的
struct STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009
{
	int 	mlChatroomID;						//大厅id
	int64_t	mi64UserID; 						//用户ID
	char 	macNickName[NICK_NAME_LEN + 1];		//用户昵称
	uint16_t 	mwPhotoNum;							//用户头像
	uint8_t 	mbyPower;							//用户权限
	int 	mlUserState;						//用户状态

	uint8_t 	mbyUserLanguage;					//用户语言类型
	int  	miRedMemTime;						//红人资格

	char 	mstrUniName[DEF_USER_UNINAME_LEN+1];//用户统一会员名
	char 	mstrUserMood[DEF_USER_MOOD_LENGTH+1];  //用户心情
	char 	mstrUserImageURL[URL_LINK_LEN+1];  	//用户头像版本号
	uint8_t    mbyUserSex;           				//用户性别：0-未知，1-男，2-女
	int 	miUserOnLineTime;					//用户等级（在线时长）单位为秒，
	int 	miUserCharm;       				    //用户魅力值
	int 	miUserWealth;       				//用户财富值
	int 	miUserActivity;    				    //用户活跃度
	int    mlVipRooomID;      					//用户是否是VIP房主：0-不是VIP房主； 其他值是VIP房主，并且数值为他的VIP房间ID。
	uint8_t    mbyShowBar;          				//用户是否是秀吧用户。0-不是；其它是
	char  mstrUserBirthDay[DEF_USER_BIRTHDAY_LEN+1]; //用户生日 
	//uint8_t    mbyShopUser;          				//用户是否是商城用户。0-不是；其它是

	int	Serialize(CStandardSerialize & aoStandardSerialize);	
	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//客户端请求用户信息应答包(SinaShow1.3)
typedef struct	STRU_CHATROOM_USER_INFO_2009
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;							//用户权限
	int    	mlUserState;						//用户状态
	uint8_t	mbyVoiceState ;						//新添加，语音聊天状态
	uint8_t	mbyUserLanguage;           			//用户语言类型
	int		miRedMemTime;						//红人资格
	//char	macVersion[VERSION_LEN + 1];		//客户端真实版本
	char 	mstrUniName[DEF_USER_UNINAME_LEN+1];//用户统一会员名
	char 	mstrUserMood[DEF_USER_MOOD_LENGTH+1];  //用户心情
	char 	mstrUserImageURL[URL_LINK_LEN+1];  	//用户头像版本号
	uint8_t    mbyUserSex;           				//用户性别：0-未知，1-男，2-女
	int 	miUserOnLineTime;					//用户等级（在线时长）单位为秒，
	int 	miUserCharm;       				//用户魅力值
	int 	miUserWealth;       				//用户财富值
	int		miUserActivity;    				//用户活跃度
	int    mlVipRooomID;      					//用户是否是VIP房主：0-不是VIP房主； 其他值是VIP房主，并且数值为他的VIP房间ID。
	uint8_t   	mbyShowBar;          				//用户是否是秀吧用户。0-不是；其它是
	char    mstrUserBirthDay[DEF_USER_BIRTHDAY_LEN+1]; //用户生日      //用户生日字符串“2009-07-01”
	//uint8_t   	mbyShopUser;          				//用户是否是商城用户。0-不是；其它是

	int 	Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_2009()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2009));
	}
}*PSTRU_CHATROOM_USER_INFO_2009;

typedef struct	STRU_UC_CL_CRS_USER_INFO_ID_2009
{
	int		mlChatroomID;      					//大厅id

	uint16_t 	mwUserCount;       					//用户数
	PSTRU_CHATROOM_USER_INFO_2009 mpUserIDList;	//用户信息列表

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	~STRU_UC_CL_CRS_USER_INFO_ID_2009();
	STRU_UC_CL_CRS_USER_INFO_ID_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2009));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}PSTRU_UC_CL_CRS_USER_INFO_ID_2009;

//非视频道具请求包
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_RQ
{
	int64_t mi64UserID; //用户ID
	int64_t mi64DestID; //使用目标用户ID
	int     miContentID;//道具ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//道具名称
	int     miUseCount;//使用数量

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_RQ,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_RQ;

//非视频道具应答包
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_RS
{
	uint8_t mbyResult; //成功、失败
	int64_t mi64UserID; //用户ID
	int64_t mi64DestID; //使用目标用户ID
	int     miContentID;//道具ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//道具名称
	int     miUseCount;//使用数量
	int     miResidualValue;//剩余数量 

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_RS,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_RS;

//非视频道具广播包
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY
{
	int64_t mi64UserID; //用户ID
	int64_t mi64DestID; //使用目标用户ID
	int     miContentID;//道具ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//道具名称
	int     miUseCount;//使用数量

	int     miRecvCount; //目的用户收到此道具的数量
	int     miPackMark;  //包标识（随即数）
	int     miPackBeginNum;  //包起始数
	int     miPackUseNum;  //包使用数

	char    mszUserName[NICK_NAME_LEN+1]; //用户名称
	char    mszDestName[NICK_NAME_LEN+1]; //目标用户名称

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY;

//大礼物广播包
typedef struct STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY
{
	int64_t 		mi64UserID; //用户ID
	char    	    mszUserName[NICK_NAME_LEN+1];//用户名称
	int64_t 		mi64DestID; //使用目标用户ID
	char    	    mszDestName[NICK_NAME_LEN+1];//目标用户名称
	int        	    miContentID;//道具ID
	char    	    mszContentName[DEF_CONTENT_NAME_LEN+1];//道具名称
	int       	    miUseCount;	//请求使用数量	
	int 		    mlChatroomID;		//大厅id
	char		    mstruRoomName[HALL_NAME_LEN+1];  //房间名称		
	int			    mstruTimeStamp; //00:00:00 UTC, January 1, 1970

	int             miHallIP;      //房间IP
	short           miHallPort;      //房间PORT
	int             miHallProperty;     //房间属性
	int             miHallPropertyEx;    //房间扩展属性

	uint8_t     mbyShowStar;     //秀星级别，1~6级，0为非秀星
	uint8_t     mbyNobleman;     //贵族级别，1~3级，0为非贵族
	uint8_t     mbyManager;      //管理员级别
	uint8_t     mbyWeekStar;     //周星， 0为非周星
	uint8_t     mbySell;      //官方销售，0不是销售，1是销售
	uint8_t     mbyDstShowStar;     //目标用户秀星级别，1~6级，0为非秀星
	uint8_t     mbyDstNobleman;     //目标用户贵族级别，1~3级，0为非贵族
	uint8_t     mbyDstManager;     //目标用户管理员级别
	uint8_t     mbyDstWeekStar;     //目标用户周星， 0为非周星
	uint8_t     mbyDstSell;      //目标用户官方销售，0不是销售，1是销售

	int             miReserved1;     //预留1
	int             miReserved2;     //预留2

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY,*PSTRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY;

//U点更新通知
typedef struct STRU_UC_CRS_CL_BALANCE_NOTIFY
{
	int64_t 		mi64UserID;        //用户ID
	int         miResidualValue;   //现在的U点数
	uint8_t        mbyUseType;        // 0：使用道具  1：收到道具 
	int         miSecond;          // 时间 秒数

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_BALANCE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_BALANCE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_BALANCE_NOTIFY,*PSTRU_UC_CRS_CL_BALANCE_NOTIFY;

//大小喇叭广播包和通知包
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY
{
	int64_t		mi64FromUserID;					//用户ID
	char		mszUserName[NICK_NAME_LEN + 1]; //用户名称
	int64_t		mi64ToUserID;					//目标用户ID
	char		mszDestName[NICK_NAME_LEN + 1]; //目标用户名称
	uint8_t		mbyType;						//喇叭类型 4:小喇叭 5:大喇叭，1~3未使用

	uint8_t		mbyShowStar;					//秀星级别，1~6级，0为非秀星
	uint8_t		mbyNobleman;					//贵族级别，1~3级，0为非贵族
	uint8_t		mbyManager;						//管理员级别
	uint8_t		mbyWeekStar;					//周星，1~3周星
	uint8_t		mbySell;						//官方销售，0不是销售，1是销售

	uint16_t	    mwMessageLen;					//消息长度	


	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY;

//大小喇叭应答包
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS
{
	uint8_t 	mbyResult; 	//成功、失败

	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS));
	}
	int  Pack(char *   apBuffer ,int    alLen);
	int  UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS;


//大小喇叭应答扩展包
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX
{
	uint8_t	m_nResult; 			//1:成功,其他:失败
	char	m_szReason[100];	//失败的原因
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX;

// 幸运道具广播包
typedef struct _STRU_UC_CL_CRS_AWARD_NOTIFY 
{
	int32_t        m_nPackMark;       // 包标志
	int64_t    m_i64UserID;       // 获奖用户的ID
	char       m_szUserName[NICK_NAME_LEN + 1];//用户名称
	int32_t        m_nContentID;   // 道具ID
	int32_t        m_nMaxTimes;       // 最大倍数

	int32_t        m_nExtraDataCount;     // m_pExtraData数组的长度

	struct STRU_EXTRA_DATA
	{
		int32_t        m_nIndex;          // 中奖道具所处的索引
		int32_t        m_nTimes;          // 当前中奖倍数
		int64_t    m_i64GainPoint;    // 奖励的U点值
	}*m_pExtraData;

	int Serialize(CStandardSerialize & StandardSerialize);
	_STRU_UC_CL_CRS_AWARD_NOTIFY()
	{
		memset(this, 0, sizeof(_STRU_UC_CL_CRS_AWARD_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);

}STRU_UC_CL_CRS_AWARD_NOTIFY, *PSTRU_UC_CL_CRS_AWARD_NOTIFY;

// 幸运道具统计信息包  2011-03-10 添加
typedef struct STRU_UC_CL_CRS_AWARD_INFO 
{
	int32_t        miPackMark; //包标识
	int64_t      mi64UserID;       // 获奖用户的ID
	char       mszUserName[NICK_NAME_LEN + 1];//用户名称
	int32_t        miContentID;   // 道具ID
	int32_t        miMaxTimes;       // 最大倍数
	int32_t        miExtraDataCount;

	struct STRU_EXTRA_DATA
	{
		int32_t        miMultiple;          //倍数
		int32_t        miTimes;             //次数
	}*m_pExtraData;
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_AWARD_INFO()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_AWARD_INFO));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_AWARD_INFO,*PSTRU_UC_CL_CRS_AWARD_INFO;

// 烟花道具广播包
typedef struct _STRU_UC_CL_CRS_FIREWORKS_NOTIFY 
{
	int64_t     m_i64UserID;       // 发送用户的ID
	char        m_szUserName[NICK_NAME_LEN + 1];//用户名称
	int32_t         m_nContentID;   // 道具ID
	int32_t         m_nUseCount;      // 使用数量
	int64_t     m_i64GainPoint;    // 奖励的U点值

	int Serialize(CStandardSerialize & StandardSerialize);
	_STRU_UC_CL_CRS_FIREWORKS_NOTIFY()
	{
		memset(this, 0, sizeof(_STRU_UC_CL_CRS_FIREWORKS_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);

}STRU_UC_CL_CRS_FIREWORKS_NOTIFY, *PSTRU_UC_CL_CRS_FIREWORKS_NOTIFY;

//VIP用户信息通知包
typedef struct STRU_UC_CL_VIP_ENTER_NOTIFY_EX
{
	unsigned char mui8VIPType;             //暂定：0为贵族，1为周星 2为官方销售
	unsigned char mui8NotifyType;          //0为新进入用户，1为房间里的用户
	int64_t       mi64UserID;                //用户ID；
	unsigned int mui32Reserve;             //保留字段1，当mui8VIPType为1时，这里保存道具ID；
	//当mui8VIPType为0时，这里保存贵族等级
	unsigned int mui32Reserve2;            //保留字段2,
	unsigned int mui32Reserve3;            //保留字段2，为0
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_VIP_ENTER_NOTIFY_EX()
	{
		memset(this, 0, sizeof(STRU_UC_CL_VIP_ENTER_NOTIFY_EX));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}*PSTRU_UC_CL_VIP_ENTER_NOTIFY_EX;

struct STRU_UC_CL_CRS_USER_AVSINFO_ID
{
	char mszAvsName[UC_HALL_AVS_NAME_LEN+1];
	unsigned int	miAvsIp;
	unsigned short	miVoicePort;
	STRU_UC_CL_CRS_USER_AVSINFO_ID();
	~STRU_UC_CL_CRS_USER_AVSINFO_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

//AVS变化通知包
struct STRU_UC_CRS_CL_USER_AVS_INFO_ID
{
	int	miAvsId;					//初始用户登录下发时为服务器端为用户选择的 avsid 1或者2，当avs变化下发时 avsid=0
	unsigned short miAvsCount;
	STRU_UC_CL_CRS_USER_AVSINFO_ID *miAvsInfoList;					

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_USER_AVS_INFO_ID();
	~STRU_UC_CRS_CL_USER_AVS_INFO_ID();
};

//用户avs信息变化通知包
struct STRU_UC_CL_CRS_USER_AVS_CHANGE_ID
{
	int64_t   mi64UserID;                //用户id                    
	unsigned int  muAvsIp;              //用户自己的avsip
	unsigned short muVoicePort;          //用户自己的avsport

	STRU_UC_CL_CRS_USER_AVS_CHANGE_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_AVS_CHANGE_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};


//丢包率请求
struct STRU_USER_LOSTRATE_RQ
{
	int64_t mi64UserID;
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_LOSTRATE_RQ()
	{
		memset(this, 0, sizeof(STRU_USER_LOSTRATE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//丢包率应答
struct STRU_USER_LOSTRATE_RS
{
	int64_t mi64UserID;
	int miLostRate;
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_LOSTRATE_RS()
	{
		memset(this, 0, sizeof(STRU_USER_LOSTRATE_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

enum emModifyType
{
	EM_FIELD_PHOTO,
	EM_FIELD_NICKNAME,
	EM_FIELD_MAX
};

struct STRU_MODIFIED_USER_INFO_FIELD
{
	uint8_t mbyFieldName; //修改字段类型
	char macValue[USER_INTRO_LEN + 1]; //修改值
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_MODIFIED_USER_INFO_FIELD();
};
typedef struct STRU_MODIFIED_USER_INFO_FIELD * PSTRU_MODIFIED_USER_INFO_FIELD;

struct STRU_UC_CL_CRS_CHG_USER_INFO_ID
{
	int64_t mi64UserId;
	uint8_t    mbyCount; //修改的值链表项个数
	PSTRU_MODIFIED_USER_INFO_FIELD mpModifyList; //修改的值链表
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_CHG_USER_INFO_ID();
	~STRU_UC_CL_CRS_CHG_USER_INFO_ID();
};


//申请游客ID请求包 --此包用来向聊天室服务器申请一个游客的ID号
struct	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ
{
	char macVersion[VERSION_LEN + 1]; //版本


	int Serialize(CStandardSerialize &aoStandardSerialize);

	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//申请游客ID应答包--聊天室服务器对游客
struct	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS
{
	int64_t 	mi64VisitorID;
	char		 macVisitorName[NICK_NAME_LEN+1];
	uint16_t	mwPhotoNum;

	int Serialize(CStandardSerialize &aoStandardSerialize);


	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS()
	{
		memset(this, 0, sizeof(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//TCP房间报头
struct	STRU_UC_CL_TCP_CRS_DATA_HEAD
{
	int	mlChatroomID;//大厅id	
	uint16_t	mwDataLen;//信息大小
	char	mpData[ROOM_PACK_DATA_LEN];//信息

	STRU_UC_CL_TCP_CRS_DATA_HEAD();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_TCP_CRS_DATA_HEAD * PSTRU_UC_CL_TCP_CRS_DATA_HEAD;


#endif //_CRS_CL_STRUDEF_H_