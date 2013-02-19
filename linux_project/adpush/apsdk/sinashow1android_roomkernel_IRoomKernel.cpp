//#include "sinashow1android_jroom_JBaseKernel.h"

#include <jni.h>
#include <android/log.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include "include/SdkKernelDef.h"
#include "include/SdkKernelInterface.h"

#ifndef _Included_sinashow1android_jroom_JBaseKernel
#define _Included_sinashow1android_jroom_JBaseKernel

#ifdef __cplusplus
extern "C" {
#endif

	static ISdkKernel *g_pSdkKernel = NULL;
	static IBaseKernel *g_pBaseKernel = NULL;
	static IMediaKernel *g_pMediaKernel = NULL;
	static IValueAddedKernel *g_pValueAddedKernel = NULL;
	static IMpsKernel *g_pMpsKernel = NULL;

	static JavaVM* g_jvm;
	static JNIEnv* g_slove_msg_env;

	//全局对象
	static jobject g_sdk_process_obj;
	static jobject g_base_process_obj;
	static jobject g_media_process_obj;
	static jobject g_value_added_process_obj;
	static jobject g_room_process_obj;
	static jobject g_mps_process_obj;

	//全局本地方法

	//base method
	static jmethodID onConnetAborted;
	static jmethodID onLoginSucc;
	static jmethodID onLoginFailed;
	static jmethodID onVisitorUserInfo;
	static jmethodID onUserEnter;
	static jmethodID onUserLeave;
	static jmethodID onUserList;
	static jmethodID onFlower;
	static jmethodID onChatMessage;
	static jmethodID onBroadCast;
	static jmethodID onUserBeOperatedNotify;
	static jmethodID onRoomPropertyChangedNotify;
	static jmethodID onRoomBackGroundBmp;
	static jmethodID onBlackList;
	static jmethodID onBlackIPList;
	static jmethodID onRoomStateChangedNotify;
	static jmethodID onUserHermitStateChanged;
	static jmethodID onUserInfoChanged;
	static jmethodID onUserGeneralInfo;
	static jmethodID onLostRateRs;
	static jmethodID onWeekStarNotify;
	static jmethodID onPeerNotify;
	static jmethodID onSellerNotify;
	static jmethodID onChatVerifyCode;
	static jmethodID onManageUserResult;
	//value add method
	static jmethodID onSendGiftResult;
	static jmethodID onGiftNotify;
	static jmethodID onBigGiftNotify;
	static jmethodID onBalanceNotify;
	static jmethodID onLoudSpeakerResult;
	static jmethodID onLoudSpeakerNotify;
	static jmethodID onAwardPropNotify;
	static jmethodID onAwardPropInfo;
	static jmethodID onFireWorksNotify;
	//media method
	static jmethodID onMicOrderList;
	static jmethodID onMicList;
	static jmethodID onSpeakerList;
	static jmethodID onApplyMicRs;
	static jmethodID onBeginSpeak;
	static jmethodID onVoiceChatRQ;
	static jmethodID onVoiceChatRS;
	static jmethodID onVoiceChatStop;
	static jmethodID onInsertMicNotify;
	static jmethodID onGiveMic;
	static jmethodID onMicTimeChanged;
	static jmethodID onUserStateRS;
	static jmethodID onManageMicStateNotify;
	static jmethodID onUserVocieStateChanged;
	static jmethodID onAVSChanged;
	//room method
	static jmethodID onNewTaskEvent;
	//mps method
	static jmethodID onMpsNotify;
	//
	static jmethodID gmidStringGetBytes;
	static jmethodID gmidStringInit;

	int  jstringToPchar(JNIEnv* env, jstring jstr, const char * encoding, char* outbuf, int outlen)
	{
		char* rtn = NULL;
		jstring jencoding;
		if (encoding==NULL)
			jencoding= (env)->NewStringUTF("utf-8");
		else
			jencoding=(env)->NewStringUTF(encoding);
		jbyteArray barr= (jbyteArray)(env)->CallObjectMethod(jstr, gmidStringGetBytes, jencoding);
		jsize alen = (env)->GetArrayLength(barr);
		jbyte* ba = (env)->GetByteArrayElements(barr, JNI_FALSE);
		if (alen > 0)
		{
			if(outlen==0)
				return alen;
			if(outlen<=alen)
				return -1;
			rtn=outbuf;
			memcpy(rtn, ba, alen);
			rtn[alen] = 0;
		}
		(env)->ReleaseByteArrayElements(barr, ba, 0);
		env->DeleteLocalRef(jencoding);
		return alen;
	}


	jstring chartojstring(JNIEnv *env, const char *chars)
	{
		jstring result;
		jint len = strlen(chars);
		if(len <= 0)
		{
			result = env->NewStringUTF("");
			return result;
		}

		jclass stringClass;
		jmethodID cid;
		jbyteArray elemArr;
		jstring jencoding;

		stringClass = env->FindClass("java/lang/String");
		if (stringClass == NULL) {
			return NULL; 
		}

		cid = env->GetMethodID(stringClass,"<init>", "([BLjava/lang/String;)V");
		if (cid == NULL) {
			return NULL; 
		}

		jencoding = env->NewStringUTF("GBK");
		elemArr = env->NewByteArray(len);
		if (elemArr == NULL) {
			return NULL; 
		}
		env->SetByteArrayRegion(elemArr, 0, len, (jbyte*)chars);
		result = (jstring)(env->NewObject(stringClass, cid, elemArr, jencoding));
		env->DeleteLocalRef(elemArr);
		env->DeleteLocalRef(stringClass);
		env->DeleteLocalRef(jencoding);
		return result;
	}


	class CBaseProcess : public IBaseProcess
	{
	private:
		//连接终止			
		virtual void  OnConnetAborted()
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onConnetAborted);
		}

		//登录成功
		virtual void  OnLoginSucc(uint32_t ulToken, int32_t alRoomState, int64_t i64RoomProperty,
			char* pszTopic, char* pszSalutatory, char* pszRoomPsw)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnLoginSucc start");
			JNIEnv* env = g_slove_msg_env;
			jstring topic = chartojstring(env, pszTopic);
			jstring salutatory = chartojstring(env, pszSalutatory);
			jstring room_pwd = chartojstring(env, pszRoomPsw);
			env->CallVoidMethod(g_base_process_obj, onLoginSucc, ulToken, alRoomState, i64RoomProperty, topic, salutatory, room_pwd);
			env->DeleteLocalRef(topic);
			env->DeleteLocalRef(salutatory);
			env->DeleteLocalRef(room_pwd);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnLoginSucc end");
		}

		//登录失败
		virtual void  OnLoginFailed(uint8_t byError, char* pszError)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnLoginFailed start");
			JNIEnv* env = g_slove_msg_env;
			jstring error = chartojstring(env, pszError);
			env->CallVoidMethod(g_base_process_obj, onLoginFailed, byError, error);
			env->DeleteLocalRef(error);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnLoginFailed end");
		}

		//如果是游客登录的话 这里用来返回用户信息
		virtual void  OnVisitorUserInfo(int64_t ai64VisitorID, char* apszNickName, uint16_t ausPhotoNumber)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnVisitorUserInfo start");
			JNIEnv* env = g_slove_msg_env;
			jstring nick = chartojstring(env, apszNickName);
			env->CallVoidMethod(g_base_process_obj, onVisitorUserInfo, ai64VisitorID, nick, ausPhotoNumber);
			env->DeleteLocalRef(nick);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnVisitorUserInfo end");
		}

		//用户进入
		virtual void  OnUserEnter(PRKN_STRU_USER_INFO pUser)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserEnter start");
			jclass cls =  env->FindClass("sinashow1android/info/UserInfo");
			jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
			jobject user_info = env->NewObject(cls,construction_id);
			jfieldID user_id = env->GetFieldID(cls,"m_i64UserID","J");  
			env->SetLongField(user_info,user_id,pUser->m_i64UserID);
			jfieldID user_nick = env->GetFieldID(cls,"mpszNickName","Ljava/lang/String;"); 
			jstring ss = chartojstring(env, pUser->mpszNickName);
			env->SetObjectField(user_info,user_nick,ss);
			jfieldID photo_num = env->GetFieldID(cls,"mwPhotoNum","S");  
			env->SetShortField(user_info,photo_num,pUser->mwPhotoNum);
			jfieldID user_state = env->GetFieldID(cls,"mlUserState","I");  
			env->SetIntField(user_info,user_state,pUser->mlUserState);
			jfieldID vip_level = env->GetFieldID(cls,"miVipLevel","I");  
			env->SetIntField(user_info,vip_level,pUser->miVipLevel);
			jfieldID voice_state = env->GetFieldID(cls,"mbyVoiceState","B");  
			env->SetByteField(user_info,voice_state,pUser->mbyVoiceState);
			jfieldID power = env->GetFieldID(cls,"mbyPower","B");  
			env->SetByteField(user_info,power,pUser->mbyPower);
			jfieldID login_source = env->GetFieldID(cls,"mbyLoginSource","B");  
			env->SetByteField(user_info,login_source,pUser->mbyVoiceState);
			env->CallVoidMethod(g_base_process_obj, onUserEnter, user_info);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(user_info);
			env->DeleteLocalRef(ss);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserEnter end");
		}

		//用户离开
		virtual void  OnUserLeave(int64_t ai64UserID, uint8_t byLeaveType, char* pszReason)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserLeave start");
			JNIEnv* env = g_slove_msg_env;
			jstring reason = chartojstring(env, pszReason);
			env->CallVoidMethod(g_base_process_obj, onUserLeave, ai64UserID, byLeaveType, reason);
			env->DeleteLocalRef(reason);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserLeave end");
		}

		//用户列表
		virtual void  OnUserList(PRKN_STRU_USER_INFO ppUser, uint16_t usCount)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserList start");
			jobjectArray args = 0;  
			jsize size = usCount;
			jclass cls =  env->FindClass("sinashow1android/info/UserInfo");
			args = env->NewObjectArray(size, cls, 0); 
			jfieldID user_id = env->GetFieldID(cls,"m_i64UserID","J");  
			jfieldID user_nick = env->GetFieldID(cls,"mpszNickName","Ljava/lang/String;");  
			jfieldID photo_num = env->GetFieldID(cls,"mwPhotoNum","S");
			jfieldID user_state = env->GetFieldID(cls,"mlUserState","I");  
			jfieldID vip_level = env->GetFieldID(cls,"miVipLevel","I"); 
			jfieldID voice_state = env->GetFieldID(cls,"mbyVoiceState","B");  
			jfieldID login_source = env->GetFieldID(cls,"mbyLoginSource","B");  
			jfieldID power = env->GetFieldID(cls, "mbyPower", "B");

			for(int i=0; i < size; ++i) 
			{
				PRKN_STRU_USER_INFO pUser = ppUser+i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject user_info_obj = env->NewObject(cls,construction_id);
				env->SetLongField(user_info_obj,user_id,pUser->m_i64UserID);
				jstring ss = chartojstring(env, pUser->mpszNickName);
				env->SetObjectField(user_info_obj,user_nick,ss);
				env->SetShortField(user_info_obj,photo_num,pUser->mwPhotoNum);
				env->SetIntField(user_info_obj,user_state,pUser->mlUserState);
				env->SetIntField(user_info_obj,vip_level,pUser->miVipLevel);
				env->SetByteField(user_info_obj,power,pUser->mbyPower);
				env->SetByteField(user_info_obj,voice_state,pUser->mbyVoiceState);
				env->SetByteField(user_info_obj,login_source,pUser->mbyVoiceState);
				env->SetObjectArrayElement(args, i, user_info_obj); 
				env->DeleteLocalRef(user_info_obj);
				env->DeleteLocalRef(ss);
			}  
			env->CallVoidMethod(g_base_process_obj, onUserList, args,size);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserList end");
		}

		//献花
		virtual void  OnFlower(int64_t ai64From, int64_t ai64To, int32_t alFlowerIndex)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnFlower start");
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onFlower, ai64From, ai64To, alFlowerIndex);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnFlower end");
		}

		//聊天信息
		virtual void  OnChatMessage(uint8_t byChatType, int64_t ai64From, int64_t ai64To, char* apszMood, char* apszContrl, char* apszContent)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnChatMessage start");
			JNIEnv* env = g_slove_msg_env;
			jstring mood = chartojstring(env, apszMood);
			jstring control = chartojstring(env, apszContrl);
			jstring content = chartojstring(env, apszContent);
			env->CallVoidMethod(g_base_process_obj, onChatMessage, byChatType, ai64From, ai64To, mood, control, content);
			env->DeleteLocalRef(mood);
			env->DeleteLocalRef(control);
			env->DeleteLocalRef(content);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnChatMessage end");
		}

		//广播
		virtual void  OnBroadCast(int64_t ai64UserID, char* apsCastContent)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBroadCast start");
			JNIEnv* env = g_slove_msg_env;
			jstring cast_content = chartojstring(env, apsCastContent);
			env->CallVoidMethod(g_base_process_obj, onBroadCast, ai64UserID, cast_content);
			env->DeleteLocalRef(cast_content);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBroadCast end");
		}

		//聊天验证码
		virtual void OnChatVerifyCode(char* apszURL)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnChatVerifyCode start");
			JNIEnv* env = g_slove_msg_env;
			jstring url = chartojstring(env, apszURL);
			env->CallVoidMethod(g_base_process_obj, onChatVerifyCode, url);
			env->DeleteLocalRef(url);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnChatVerifyCode end");
		}

		//用户被处理通知
		virtual void  OnUserBeOperatedNotify(int64_t ai64ManagerID, int64_t ai64UserID, uint8_t byOpType, char* apszDescribe)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserBeOperatedNotify start");
			JNIEnv* env = g_slove_msg_env;
			jstring description = chartojstring(env, apszDescribe);
			env->CallVoidMethod(g_base_process_obj, onUserBeOperatedNotify, ai64ManagerID, ai64UserID, byOpType, description);
			env->DeleteLocalRef(description);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnUserBeOperatedNotify end");
		}

		//聊天室主题等属性修改通知
		virtual void  OnRoomPropertyChangedNotify(int64_t ai64ManagerID, char* apszTopic, char* apszSalutatory, char* apszExtPassWord, bool abExtLocked, bool abExtEnabled)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnRoomPropertyChangedNotify start");
			/*JNIEnv* env = g_slove_msg_env;
			jstring topic = chartojstring(env, apszTopic);
			jstring salutatory = chartojstring(env, apszSalutatory);
			jstring pwd = chartojstring(env, apszExtPassWord);
			env->CallVoidMethod(g_base_process_obj, onRoomPropertyChangedNotify, ai64ManagerID, topic, salutatory, pwd, abExtLocked, abExtEnabled);
			env->DeleteLocalRef(topic);
			env->DeleteLocalRef(salutatory);
			env->DeleteLocalRef(pwd);
			*/
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnRoomPropertyChangedNotify end");
		}

		//房间背景
		virtual void  OnRoomBackGroundBmp(char* apszBmp)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnRoomBackGroundBmp start");
			JNIEnv* env = g_slove_msg_env;
			jstring bmp = chartojstring(env, apszBmp);
			env->CallVoidMethod(g_base_process_obj, onRoomBackGroundBmp, bmp);
			env->DeleteLocalRef(bmp);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnRoomBackGroundBmp end");
		}

		//黑名单列表
		virtual void  OnBlackList(uint16_t ausCount, PRKN_STRU_BLACK_USER apBlackList)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBlackList start");
			jobjectArray args = 0;  
			jsize size = ausCount;
			jclass cls =  env->FindClass("sinashow1android/info/BlackUserInfo");
			args = env->NewObjectArray(size, cls, 0);
			jfieldID user_id = env->GetFieldID(cls,"mi64UserID","J"); 
			jfieldID limited_time = env->GetFieldID(cls,"mlLimitedTime","I"); 
			jfieldID residual_time = env->GetFieldID(cls,"mlResidualTime","I"); 
			for(int i=0; i < size; ++i )
			{
				PRKN_STRU_BLACK_USER p_black_user_info = apBlackList + i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject black_info_obj = env->NewObject(cls,construction_id);
				env->SetLongField(black_info_obj,user_id,p_black_user_info->mi64UserID); 
				env->SetIntField(black_info_obj,limited_time,p_black_user_info->mlLimitedTime); 
				env->SetIntField(black_info_obj,residual_time,p_black_user_info->mlResidualTime); 
				env->SetObjectArrayElement(args, i, black_info_obj);
				env->DeleteLocalRef(black_info_obj);
			}  
			env->CallVoidMethod(g_base_process_obj, onBlackList, size, args);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBlackList end");
		}

		//黑IP列表
		virtual void  OnBlackIPList(uint16_t ausCount, PRKN_STRU_BLACK_IP_USER apBlackList)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBlackIPList start");
			jobjectArray args = 0;  
			jsize size = ausCount;
			jclass cls =  env->FindClass("sinashow1android/info/BlackIPUserInfo");
			args = env->NewObjectArray(size, cls, 0);
			jfieldID user_id = env->GetFieldID(cls,"mi64UserID","J"); 
			jfieldID ip = env->GetFieldID(cls,"mulIP","I"); 
			jfieldID limited_time = env->GetFieldID(cls,"mlLimitedTime","I"); 
			jfieldID residual_time = env->GetFieldID(cls,"mlResidualTime","I"); 
			for(int i=0; i < size; ++i )
			{
				PRKN_STRU_BLACK_IP_USER p_black_ip_info = apBlackList + i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject black_ip_obj = env->NewObject(cls,construction_id);
				env->SetLongField(black_ip_obj,user_id,p_black_ip_info->mi64UserID); 
				env->SetIntField(black_ip_obj,limited_time,p_black_ip_info->mulIP); 
				env->SetIntField(black_ip_obj,limited_time,p_black_ip_info->mlLimitedTime); 
				env->SetIntField(black_ip_obj,residual_time,p_black_ip_info->mlResidualTime); 
				env->SetObjectArrayElement(args, i, black_ip_obj);
				env->DeleteLocalRef(black_ip_obj);
			}  
			env->CallVoidMethod(g_base_process_obj, onBlackIPList, size, args);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBlackIPList end");
		}

		//房间状态修改通知
		/*
		#define DEF_ALLOW_FLOWER				0//允许献花
		#define DEF_ALLOW_PUBCHAT				1//允许公聊
		*/
		virtual void  OnRoomStateChangedNotify(int64_t ai64ManagerID, uint16_t ausPropType, bool abValue)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onRoomStateChangedNotify, ai64ManagerID, ausPropType, abValue);
		}

		//用户隐身状态改变通知
		virtual void  OnUserHermitStateChanged(int64_t ai64UserID, bool abHermit)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onUserHermitStateChanged, ai64UserID, abHermit);
		}

		//用户信息修改通知
		virtual void  OnUserInfoChanged(PRKN_STUR_MD_USER_INFO apMdInfo)
		{
			JNIEnv* env = g_slove_msg_env;
		}

		//用户一般信息 服务器透明转发
		/*
		const uint16_t REFUSE_PRIVATE 		= 0x1006;		//拒绝接收私聊信息
		const uint16_t REFUSE_CHAT			= 0x1007;		//拒绝任何聊天信息
		const uint16_t REFUSE_PUBLIC		= 0x100D;		//屏蔽公聊提示对方
		const uint16_t REFUSE_PRICHAT		= 0x1010;		//拒绝对聊
		*/
		virtual void  OnUserGeneralInfo(int64_t ai64UserID, uint16_t ausType)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onUserGeneralInfo, ai64UserID, ausType);
		}

		//丢包率应答
		virtual void  OnLostRateRs(int64_t ai64UserID, int32_t aiLostRate)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onLostRateRs, ai64UserID, aiLostRate);
		}

		//周星通知 aiGiftID:礼物ID  aiCount：连续几周星 bNewUser：表示用户是新进房间还是已经在房间的 abEnd：后面是否还有通知  当双料周星 三料周星时 会有多次通知
		virtual void  OnWeekStarNotify(int64_t ai64UserID, int32_t aiGiftID, int32_t aiCount, bool bNewUser, bool abEnd)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onWeekStarNotify, ai64UserID, aiGiftID, aiCount, bNewUser, abEnd);
		}

		//贵族通知
		virtual void  OnPeerNotify(int64_t ai64UserID, int32_t aiPeerLevel, bool bNewUser)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onPeerNotify, ai64UserID, aiPeerLevel, bNewUser);
		}

		//官方销售
		virtual void  OnSellerNotify(int64_t ai64UserID, bool bNewUser)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_base_process_obj, onSellerNotify, ai64UserID, bNewUser);
		}

		/*-------------------------
		函数名称：管理用户应答
		参数说明：ai64UserID:目标用户id aiOpType:操作类型  DEF_ADMIN_OP_UPGRADE-DEF_ADMIN_OP_UNFORBID
		aiResult:操作结果 0表示成功 反之失败   pszDescription:操作说明
		返回值：无
		-------------------------*/
		virtual void  OnManageUserResult(int64_t ai64UserID, int8_t aiOpType, int8_t aiResult, char* pszDescription)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnManageUserResult start");
			JNIEnv* env = g_slove_msg_env;
			jstring description = chartojstring(env, pszDescription);
			env->CallVoidMethod(g_base_process_obj, onManageUserResult, ai64UserID, aiOpType, aiResult, description);
			env->DeleteLocalRef(description);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnManageUserResult start");
		}
	};


	class CMediaProcess : public IMediaProcess
	{
	private:
		//麦序列表
		virtual void OnMicOrderList(int64_t* apList, uint16_t usCount)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnMicOrderList strat");
			/*jlongArray args = env->NewLongArray(usCount);
			for(int i=0; i < usCount; ++i )
			{
			int64_t c_id = 0;
			memcpy(&c_id, apList+i, 8);
			jlong j_id = c_id;
			env->SetLongArrayRegion(args, i, 1, &j_id);
			}  
			env->CallVoidMethod(g_media_process_obj, onMicOrderList, usCount, args);
			env->DeleteLocalRef(args);
			*/
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnMicOrderList end");
		}

		//麦列表
		virtual void OnMicList(PRKN_STRU_MIC_INFO apMicList, uint16_t usCount)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnMicList strat");
			jobjectArray args = 0;  
			jsize size = usCount;
			jclass cls =  env->FindClass("sinashow1android/info/MicInfo");
			args = env->NewObjectArray(size, cls, 0);
			jfieldID mic_index = env->GetFieldID(cls,"mbyMicIndex","B"); 
			jfieldID support_video = env->GetFieldID(cls,"mbSupportVideo","Z"); 

			//public AudioConfigInfo mstruAudioConfig; // 音频配置信息
			//public VideoConfigInfo mstruVideoConfig; // 视频配置信息

			jfieldID mic_statue = env->GetFieldID(cls,"mwMicStatue","S"); 
			jfieldID mic_time = env->GetFieldID(cls,"mwMicTimeLen","B"); 
			jfieldID manager_id = env->GetFieldID(cls,"mi64ManagerID","J"); 
			jfieldID delta_speak_time = env->GetFieldID(cls,"mlDeltaSpeakTime","I"); 
			for(int i=0; i < size; ++i )
			{
				PRKN_STRU_MIC_INFO p_mic_info = apMicList + i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject mic_info_obj = env->NewObject(cls,construction_id);
				env->SetByteField(mic_info_obj,mic_index,p_mic_info->mbyMicIndex); 
				env->SetBooleanField(mic_info_obj,support_video,p_mic_info->mbSupportVideo); 
				env->SetShortField(mic_info_obj,mic_statue,p_mic_info->mwMicStatue); 
				env->SetByteField(mic_info_obj,mic_time,p_mic_info->mwMicTimeLen); 
				env->SetLongField(mic_info_obj,manager_id,p_mic_info->mi64ManagerID); 
				env->SetIntField(mic_info_obj,delta_speak_time,p_mic_info->mlDeltaSpeakTime); 
				env->SetObjectArrayElement(args, i, mic_info_obj);
				env->DeleteLocalRef(mic_info_obj);
			}  
			env->CallVoidMethod(g_media_process_obj, onMicList, args,size);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnMicList end");
		}

		//发言人列表
		virtual void OnSpeakerList(PRKN_STRU_SPEAKER_INFO apSpeakerList, uint16_t usCount)
		{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnSpeakerList start");
			jobjectArray args = 0;  
			jsize size = usCount;
			jclass cls =  env->FindClass("sinashow1android/info/SpeakerInfo");
			args = env->NewObjectArray(size, cls, 0);
			jfieldID dst_user_id = env->GetFieldID(cls,"mi64DstUserID","J"); 
			jfieldID speaker_user_id = env->GetFieldID(cls,"mi64SpeakerUserID","J"); 
			jfieldID mic_index = env->GetFieldID(cls,"mbyMicIndex","B"); 
			jfieldID contain_audio_info = env->GetFieldID(cls,"mbContainAudioInfo","Z"); 
			jfieldID contain_video_info = env->GetFieldID(cls,"mbContainVideoInfo","Z"); 
			//public SpeakerAudioInfo mstrAudioInfo; // 上面的标识为假跳过，音频格式
			//public SpeakerVideoInfo mstrVideoInfo; // 上面的标识为假跳过，视频格式信息
			for(int i=0; i < size; ++i )
			{
				PRKN_STRU_SPEAKER_INFO p_speaker_info = apSpeakerList + i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject speaker_info_obj = env->NewObject(cls,construction_id);
				env->SetLongField(speaker_info_obj,dst_user_id,p_speaker_info->mi64DstUserID); 
				env->SetLongField(speaker_info_obj,speaker_user_id,p_speaker_info->mi64SpeakerUserID); 
				env->SetByteField(speaker_info_obj,mic_index,p_speaker_info->mbyMicIndex); 
				env->SetBooleanField(speaker_info_obj,contain_audio_info,p_speaker_info->mbContainAudioInfo); 
				env->SetBooleanField(speaker_info_obj,contain_video_info,p_speaker_info->mbContainVideoInfo); 
				env->SetObjectArrayElement(args, i, speaker_info_obj);
				env->DeleteLocalRef(speaker_info_obj);
			} 
			env->CallVoidMethod(g_media_process_obj, onSpeakerList, args,size);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnSpeakerList end");
		}

		//排麦应答
		virtual void OnApplyMicRs(uint8_t abyMicIndex)
		{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onApplyMicRs, abyMicIndex);
		}

		//开始发言通知
		virtual void OnBeginSpeak(uint8_t abyMicIndex)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onBeginSpeak, abyMicIndex);
		}


		//对聊请求
		virtual void OnVoiceChatRQ(int64_t ai64UserID)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onVoiceChatRQ, ai64UserID);
		}

		//对聊应答
		virtual void OnVoiceChatRS(uint8_t abyResult, int64_t ai64SrcUserID, int64_t ai64DestUserID)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onVoiceChatRS, abyResult, ai64SrcUserID, ai64DestUserID);
		}

		//对聊停止通知
		virtual void OnVoiceChatStop(int64_t ai64UserID)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onVoiceChatStop, ai64UserID);
		}

		//插麦通知
		virtual void OnInsertMicNotify(int64_t ai64ManagerID, int64_t ai64DestUserID, uint8_t abyIndex)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onInsertMicNotify, ai64ManagerID, ai64DestUserID, abyIndex);
		}

		//递麦通知
		virtual void OnGiveMic(int64_t ai64ManagerID, int64_t aiUserID)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onGiveMic, ai64ManagerID, aiUserID);
		}

		//管理员修改了麦时
		virtual void OnMicTimeChanged(int64_t ai64ManagerID, uint8_t abyIndex, uint8_t abyMinute)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onMicTimeChanged, ai64ManagerID, abyIndex, abyMinute);
		}

		//用户状态应答
		virtual void OnUserStateRS(int64_t ai64UserID, int32_t alState)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onUserStateRS, ai64UserID, alState);
		}

		//管理员管麦通知
		virtual void OnManageMicStateNotify(int64_t ai64ManagerID, uint8_t abyIndex, uint8_t abyOpType, bool abState)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onManageMicStateNotify, ai64ManagerID, abyIndex, abyOpType, abState);
		}

		//用户语音状态改变通知
		virtual void OnUserVocieStateChanged(int64_t ai64UserID, uint8_t abyState)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_media_process_obj, onUserVocieStateChanged, ai64UserID, abyState);
		}

		//AVS通知 aiType 0：变更AVS  不为0：变更AVS的同时指定最优项
		virtual void OnAVSChanged(int aiType, uint16_t ausCount, PRKN_STRU_AVS_INFO pAvsList)	{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAVSChanged start");
			jobjectArray args = 0;  
			jsize size = ausCount;
			jclass cls =  env->FindClass("sinashow1android/info/AvsInfo");
			args = env->NewObjectArray(size, cls, 0); 
			jfieldID avs_name = env->GetFieldID(cls,"mpszAvsName","Ljava/lang/String;");  
			jfieldID ip = env->GetFieldID(cls,"mulAvsIp","I");
			jfieldID port = env->GetFieldID(cls,"musVoicePort","S"); 
			for(int i=0; i < size; ++i)  
			{
				PRKN_STRU_AVS_INFO p_avs_info = pAvsList+i;
				jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
				jobject avs_info_obj = env->NewObject(cls,construction_id);
				jstring ss = chartojstring(env, p_avs_info->mpszAvsName);
				env->SetObjectField(avs_info_obj,avs_name,ss);
				env->SetIntField(avs_info_obj,ip,p_avs_info->mulAvsIp);
				env->SetShortField(avs_info_obj,port,p_avs_info->musVoicePort);
				env->SetObjectArrayElement(args, i, avs_info_obj);
				env->DeleteLocalRef(avs_info_obj);
				env->DeleteLocalRef(ss);
			}
			env->CallVoidMethod(g_media_process_obj, onAVSChanged, aiType, size, args);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(args);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAVSChanged end");
		}
	};

	class CValueAddedProcess :public IValueAddedProcess
	{
	private:
		//发送礼物结果  /*abyResult: DEF_CHECK_PROP_AVAILABLE_FAILD ~ DEF_CHECK_PROP_AVAILABLE_POOL*/
		virtual void OnSendGiftResult(uint8_t abyResult, int64_t ai64UserID, int aiGiftID, char* apszGiftName, int aiUseCount)	{
			JNIEnv* env = g_slove_msg_env;
			jstring gift_name = chartojstring(env, apszGiftName);
			env->CallVoidMethod(g_value_added_process_obj, onSendGiftResult, abyResult, ai64UserID, aiGiftID, gift_name, aiUseCount);
			env->DeleteLocalRef(gift_name);
		}

		//礼物广播
		virtual void OnGiftNotify(int64_t ai64UserFrom, int64_t ai64UserTo, int aiGiftID, char* apszGiftName, int aiUseCount
			, int aiPackMark, int aiPackBeginNum, int aiPackUseNum, int aiRecvCount)	{
				JNIEnv* env = g_slove_msg_env;
				jstring gift_name = chartojstring(env, apszGiftName);
				env->CallVoidMethod(g_value_added_process_obj, onGiftNotify, ai64UserFrom, ai64UserTo, aiGiftID, gift_name, aiUseCount, aiPackMark, aiPackBeginNum, aiPackUseNum, aiRecvCount);
				env->DeleteLocalRef(gift_name);
		}

		//大礼物广播
		virtual void OnBigGiftNotify(PRKN_STRU_BIG_GIFT_NOTIFY apBigGiftNotify)	{
			JNIEnv* env = g_slove_msg_env;
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBigGiftNotify start");
			jclass cls =  env->FindClass("sinashow1android/info/BigGiftNotifyInfo");
			jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
			jobject big_gift_info = env->NewObject(cls,construction_id);
			jfieldID from_id = env->GetFieldID(cls,"mi64FromID","J");  
			env->SetLongField(big_gift_info,from_id,apBigGiftNotify->mi64FromID);
			jfieldID from_nick = env->GetFieldID(cls,"mpszFromNick","Ljava/lang/String;");
			jstring ss = chartojstring(env, apBigGiftNotify->mpszFromNick);
			env->SetObjectField(big_gift_info,from_nick,ss);
			jfieldID from_vip_level = env->GetFieldID(cls,"mbyFromVipLevel","B");  
			env->SetByteField(big_gift_info,from_vip_level,apBigGiftNotify->mbyFromVipLevel);
			jfieldID from_peer_level = env->GetFieldID(cls,"mbyFromPeerLevel","B");  
			env->SetByteField(big_gift_info,from_peer_level,apBigGiftNotify->mbyFromPeerLevel);
			jfieldID from_power_level = env->GetFieldID(cls,"mbyFromPowerLevel","B");  
			env->SetByteField(big_gift_info,from_power_level,apBigGiftNotify->mbyFromPowerLevel);
			jfieldID from_week_star = env->GetFieldID(cls,"mbyFromWeekStar","B");
			env->SetByteField(big_gift_info,from_week_star,apBigGiftNotify->mbyFromWeekStar);
			jfieldID from_seller = env->GetFieldID(cls,"mbyFromSeller","B");  
			env->SetByteField(big_gift_info,from_seller,apBigGiftNotify->mbyFromSeller);
			jfieldID to_id = env->GetFieldID(cls,"mi64ToID","J");  
			env->SetLongField(big_gift_info,to_id,apBigGiftNotify->mi64ToID);
			jfieldID to_nick = env->GetFieldID(cls,"mpszToNick","Ljava/lang/String;");  
			jstring ss1 = chartojstring(env, apBigGiftNotify->mpszToNick);
			env->SetObjectField(big_gift_info,to_nick,ss1);
			jfieldID to_vip_level = env->GetFieldID(cls,"mbyToVipLevel","B");  
			env->SetByteField(big_gift_info,to_vip_level,apBigGiftNotify->mbyToVipLevel);
			jfieldID to_peer_level = env->GetFieldID(cls,"mbyToPeerLevel","B");  
			env->SetByteField(big_gift_info,to_peer_level,apBigGiftNotify->mbyToPeerLevel);
			jfieldID to_power_level = env->GetFieldID(cls,"mbyToPowerLevel","B");  
			env->SetByteField(big_gift_info,to_power_level,apBigGiftNotify->mbyToPowerLevel);
			jfieldID to_week_star = env->GetFieldID(cls,"mbyToWeekStar","B");
			env->SetByteField(big_gift_info,to_week_star,apBigGiftNotify->mbyToWeekStar);
			jfieldID to_seller = env->GetFieldID(cls,"mbyFromSeller","B");  
			env->SetByteField(big_gift_info,to_seller,apBigGiftNotify->mbyFromSeller);
			jfieldID gift_id = env->GetFieldID(cls,"miGiftID","I");  
			env->SetIntField(big_gift_info,gift_id,apBigGiftNotify->miGiftID);
			jfieldID count = env->GetFieldID(cls,"miCount","I");  
			env->SetIntField(big_gift_info,count,apBigGiftNotify->miCount);
			jfieldID gift_name = env->GetFieldID(cls,"mpszGiftName","Ljava/lang/String;");  
			jstring ss2 = chartojstring(env, apBigGiftNotify->mpszGiftName);
			env->SetObjectField(big_gift_info,gift_name,ss2);
			jfieldID time_stamp = env->GetFieldID(cls,"mstrTimeStamp","I");  
			env->SetIntField(big_gift_info,time_stamp,apBigGiftNotify->mstrTimeStamp);
			env->CallVoidMethod(g_value_added_process_obj, onBigGiftNotify, big_gift_info);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(big_gift_info);
			env->DeleteLocalRef(ss);
			env->DeleteLocalRef(ss1);
			env->DeleteLocalRef(ss2);
			__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnBigGiftNotify end");
		}

		//虚拟币余额通知
		virtual void OnBalanceNotify(int64_t ai64Balance)	{
			JNIEnv* env = g_slove_msg_env;
			env->CallVoidMethod(g_value_added_process_obj, onBalanceNotify, ai64Balance);
		}


		//发送喇叭结果
		virtual void OnLoudSpeakerResult(uint8_t abyResult, char* apszReason)	{
			JNIEnv* env = g_slove_msg_env;
			jstring reason = chartojstring(env, apszReason);
			env->CallVoidMethod(g_value_added_process_obj, onLoudSpeakerResult, abyResult, reason);
			env->DeleteLocalRef(reason);
		}

		//喇叭通知
		virtual void OnLoudSpeakerNotify(PRKN_STRU_LOUDSPEAKER_NOTIFY apLoudSpeakerNotify)
		{
			JNIEnv* env = g_slove_msg_env;
			jclass cls =  env->FindClass("sinashow1android/info/LoudSpeakerNotifyInfo");
			jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
			jobject loud_speader_notify = env->NewObject(cls,construction_id);
			jfieldID from_id = env->GetFieldID(cls,"mi64FromID","J");  
			env->SetLongField(loud_speader_notify,from_id,apLoudSpeakerNotify->mi64FromID);
			jfieldID from_nick = env->GetFieldID(cls,"mpszFromNick","Ljava/lang/String;");  
			jstring ss1 = chartojstring(env, apLoudSpeakerNotify->mpszFromNick);
			env->SetObjectField(loud_speader_notify,from_nick,ss1);
			jfieldID from_vip_level = env->GetFieldID(cls,"mbyFromVipLevel","B");
			env->SetByteField(loud_speader_notify,from_vip_level,apLoudSpeakerNotify->mbyFromVipLevel);
			jfieldID from_peer_level = env->GetFieldID(cls,"mbyFromPeerLevel","B");
			env->SetByteField(loud_speader_notify,from_peer_level,apLoudSpeakerNotify->mbyFromPeerLevel);
			jfieldID from_power_level = env->GetFieldID(cls,"mbyFromPowerLevel","B");
			env->SetByteField(loud_speader_notify,from_power_level,apLoudSpeakerNotify->mbyFromPowerLevel);
			jfieldID from_week_star = env->GetFieldID(cls,"mbyFromWeekStar","B");
			env->SetByteField(loud_speader_notify,from_week_star,apLoudSpeakerNotify->mbyFromWeekStar);
			jfieldID from_seller = env->GetFieldID(cls,"mbyFromSeller","B");
			env->SetByteField(loud_speader_notify,from_seller,apLoudSpeakerNotify->mbyFromSeller);
			jfieldID type = env->GetFieldID(cls,"mbyType","B");
			env->SetByteField(loud_speader_notify,type,apLoudSpeakerNotify->mbyType);
			jfieldID control = env->GetFieldID(cls,"mpszControl","Ljava/lang/String;");  
			jstring ss2 = chartojstring(env, apLoudSpeakerNotify->mpszControl);
			env->SetObjectField(loud_speader_notify,control,ss2);
			jfieldID content = env->GetFieldID(cls,"mpszContent","Ljava/lang/String;");  
			jstring ss3 = chartojstring(env, apLoudSpeakerNotify->mpszContent);
			env->SetObjectField(loud_speader_notify,content,ss3);
			env->CallVoidMethod(g_value_added_process_obj, onLoudSpeakerNotify, loud_speader_notify);
			env->DeleteLocalRef(cls);
			env->DeleteLocalRef(ss1);
			env->DeleteLocalRef(ss2);
			env->DeleteLocalRef(ss3);
			env->DeleteLocalRef(loud_speader_notify);
		}

		//幸运道具通知	
		//说明 aiPackMark就是方法OnGiftNotify里面的aiPackMark  仅用于输出同步 
		//分包标识          用户ID				用户昵称			礼物ID            最大倍数 
		virtual void OnAwardPropNotify(int32_t aiPackMark, int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiMaxTimes,
			//扩展数据数组长度			扩展数据数组
			int32_t aiExtraDataCount, PRKN_STRU_AWARD_EXTRA_DATA apExtraDataArray){
				JNIEnv* env = g_slove_msg_env;
				__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAwardPropNotify start");
				jstring user_name = chartojstring(env, apszUserName);
				jobjectArray args = 0;  
				
				jsize size = aiExtraDataCount;

				jclass cls =  env->FindClass("sinashow1android/info/awardExtraData");
				args = env->NewObjectArray(size, cls, 0); 

				jfieldID gain_point = env->GetFieldID(cls,"m_i64GainPoint","J"); 
				jfieldID index = env->GetFieldID(cls,"m_nIndex","I");  
				jfieldID times = env->GetFieldID(cls,"m_nTimes","I");  

				for(int i=0; i < size; ++i)  
				{
					PRKN_STRU_AWARD_EXTRA_DATA p_award_extra_data = apExtraDataArray+i;
					jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
					jobject award_extra_data_obj = env->NewObject(cls,construction_id);
					env->SetLongField(award_extra_data_obj,gain_point,p_award_extra_data->m_i64GainPoint);

					env->SetIntField(award_extra_data_obj,index,p_award_extra_data->m_nIndex);
					env->SetIntField(award_extra_data_obj,times,p_award_extra_data->m_nTimes);

					env->SetObjectArrayElement(args, i, award_extra_data_obj);
					env->DeleteLocalRef(award_extra_data_obj);
				}
				env->CallVoidMethod(g_value_added_process_obj, onAwardPropNotify, aiPackMark, ai64UserID, user_name, aiGiftID, aiMaxTimes, size, args);
				env->DeleteLocalRef(cls);
				env->DeleteLocalRef(args);
				__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAwardPropNotify end");		

		}

		//幸运道具统计	
		//说明 aiPackMark就是方法OnGiftNotify里面的aiPackMark  仅用于输出同步		此通知只会在自己中奖时收到
		//此通知中PRKN_STRU_AWARD_EXTRA_DATA中的m_i64GainPoint无效
		//分包标识          用户ID				用户昵称			  礼物ID            最大倍数 
		virtual void OnAwardPropInfo(int32_t aiPackMark, int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiMaxTimes,
			//扩展数据数组长度			扩展数据数组
			int32_t aiExtraDataCount, PRKN_STRU_AWARD_EXTRA_DATA2 apExtraDataArray){
				JNIEnv* env = g_slove_msg_env;
				__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAwardPropInfo start");

				jstring user_name = chartojstring(env, apszUserName);

				jobjectArray args = 0;  
				jsize size = aiExtraDataCount;
				jclass cls =  env->FindClass("sinashow1android/info/extraData");
				args = env->NewObjectArray(size, cls, 0); 
				jfieldID multiple = env->GetFieldID(cls,"miMultiple","I");  
				jfieldID times = env->GetFieldID(cls,"miTimes","I");  
				for(int i=0; i < size; ++i)  
				{
					PRKN_STRU_AWARD_EXTRA_DATA2 p_award_extra_data = apExtraDataArray+i;
					jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
					jobject award_extra_data_obj = env->NewObject(cls,construction_id);

					env->SetIntField(award_extra_data_obj,multiple,p_award_extra_data->miMultiple);
					env->SetIntField(award_extra_data_obj,times,p_award_extra_data->miTimes);

					env->SetObjectArrayElement(args, i, award_extra_data_obj);
					env->DeleteLocalRef(award_extra_data_obj);
				}
				env->CallVoidMethod(g_value_added_process_obj, onAwardPropInfo, aiPackMark, ai64UserID, user_name, aiGiftID, aiMaxTimes, size, args);
				env->DeleteLocalRef(cls);
				env->DeleteLocalRef(args);
				__android_log_write(ANDROID_LOG_DEBUG,"RoomKernelLog"," OnAwardPropInfo end");		


		}

		//烟花通知						发送用户ID				发送用户昵称      礼物ID			使用数量           自己分到的U点数
		virtual void OnFireWorksNotify(int64_t ai64UserID, char* apszUserName, int32_t aiGiftID, int32_t aiUseCount, int64_t ai64GainPoint){
			JNIEnv* env = g_slove_msg_env;
			jstring UserNick = chartojstring(env, apszUserName);
			env->CallVoidMethod(g_value_added_process_obj, onFireWorksNotify, ai64UserID, UserNick, aiGiftID, aiUseCount, ai64GainPoint);
			env->DeleteLocalRef(UserNick);
		}
	};

	class CMpsProcess : public IMpsProcess
	{
	public:
		virtual void OnMpsNotify(uint8_t u8MsgEncoding, const char *pDataBuf)
		{
			__android_log_write(ANDROID_LOG_DEBUG,"CMpsProcess","OnMpsNotify");
			JNIEnv* env = g_slove_msg_env;
			jstring data = chartojstring(env, pDataBuf);
			env->CallVoidMethod(g_mps_process_obj, onMpsNotify, u8MsgEncoding, data);
			env->DeleteLocalRef(data);
		}
	};

	class CSdkProcess : public ISdkProcess
	{
	public:
		//请求接口
		virtual bool QueryInterface(unsigned int uID, void** ppVoid)
		{
			*ppVoid = NULL;

			switch (uID)
			{
			case UID_BASE_PROCESS:
				*ppVoid = static_cast<IBaseProcess*>(&m_BaseProcess);
				break;
			case UID_MEDIA_PROCESS:
				*ppVoid = static_cast<IMediaProcess*>(&m_MediaProcess);
				break;
			case UID_VALUE_ADDED_PROCESS:
				*ppVoid = static_cast<IValueAddedProcess*>(&m_ValueAddedProcess);
				break;
			case UID_MPS_PROCESS:
				*ppVoid = static_cast<IMpsProcess*>(&m_MpsProcess);
				break;
			}

			return (*ppVoid) != NULL;
		}

		//线程同步方法 这是唯一不在上层调用线程回调的方法
		//此通知上层在主线程调用SolveTask
		//以保证其它回调都在调用线程（通常是主线程）里
		virtual void NewTaskEvent()
		{
			__android_log_print(ANDROID_LOG_INFO,"NewTaskEvent","NewTaskEvent");
			JNIEnv* env;
			g_jvm->AttachCurrentThread(&env, NULL);
			__android_log_print(ANDROID_LOG_INFO,"NewTaskEvent1","NewTaskEvent");
			env->CallVoidMethod(g_sdk_process_obj, onNewTaskEvent);
			__android_log_print(ANDROID_LOG_INFO,"NewTaskEvent2","NewTaskEvent");
			g_jvm->DetachCurrentThread();
			__android_log_print(ANDROID_LOG_INFO,"NewTaskEvent3","NewTaskEvent");
		}
	private:
		CBaseProcess m_BaseProcess;
		CMediaProcess m_MediaProcess;
		CValueAddedProcess m_ValueAddedProcess;
		CMpsProcess m_MpsProcess;
	};

	static CSdkProcess g_SdkProcess;

	/*******************************************************************************

	基础业务接口

	********************************************************************************/

void Java_com_example_hellojni_SdkKernel_init(JNIEnv * env, 
jobject obj, jobject skd_process_obj,jobject mps_process_obj)
{
		env->GetJavaVM(&g_jvm);
		//obj
		g_sdk_process_obj = env->NewGlobalRef(skd_process_obj);
		g_mps_process_obj = env->NewGlobalRef(mps_process_obj);

		//class
		jclass l_sdk_process_class = env->GetObjectClass(skd_process_obj);
		jclass l_mps_process_class = env->GetObjectClass(mps_process_obj);

		//room process method
		onNewTaskEvent = env->GetMethodID(l_sdk_process_class, "onNewTaskEvent", "()V");

		//mps process method
		onMpsNotify = env->GetMethodID(l_mps_process_class, "onMpsNotify", "(BLjava/lang/String;)V");

		jclass gStringClass= (env)->FindClass("java/lang/String");
		gmidStringGetBytes= (env)->GetMethodID(gStringClass, "getBytes", "(Ljava/lang/String;)[B");
		gmidStringInit= (env)->GetMethodID(gStringClass, "<init>", "([BLjava/lang/String;)V");
		env->DeleteLocalRef(gStringClass);

		CreateObject(&g_pSdkKernel);
		if(g_pSdkKernel)
		{
			g_pSdkKernel->SetProcess(&g_SdkProcess);
			g_pSdkKernel->QueryInterface(UID_MPS_KERNEL, (void**)&g_pMpsKernel);
		}

		env->DeleteLocalRef(l_sdk_process_class);
		env->DeleteLocalRef(l_mps_process_class);
}


	/*
	* Class:     sinashow1android_jroom_Jjroom
	* Method:    initRoomProcess
	* Signature: (Lsinashow1android/iroom/IBaseProcess;Lsinashow1android/iroom/IMediaProcess;Lsinashow1android/iroom/IValueAddedProcess;)V
	*/
	void  Java_sinashow1android_jroom_JRoomKernel_initRoomProcess
		(JNIEnv * env, jobject obj, jobject skd_process_obj, jobject base_process_obj,
		jobject media_process_obj, jobject value_added_process_obj, jobject mps_process_obj)
	{
		env->GetJavaVM(&g_jvm);
		//obj
		g_base_process_obj = env->NewGlobalRef(base_process_obj);
		g_media_process_obj = env->NewGlobalRef(media_process_obj);
		g_value_added_process_obj = env->NewGlobalRef(value_added_process_obj);
		g_sdk_process_obj = env->NewGlobalRef(skd_process_obj);
		g_mps_process_obj = env->NewGlobalRef(mps_process_obj);

		//class
		jclass l_base_process_class = env->GetObjectClass(base_process_obj);
		jclass l_media_process_class = env->GetObjectClass(media_process_obj);
		jclass l_value_added_process_class = env->GetObjectClass(value_added_process_obj);
		jclass l_sdk_process_class = env->GetObjectClass(skd_process_obj);
		jclass l_mps_process_class = env->GetObjectClass(mps_process_obj);

		//room process method
		onNewTaskEvent = env->GetMethodID(l_sdk_process_class, "onNewTaskEvent", "()V");

		//base process method
		onConnetAborted = env->GetMethodID(l_base_process_class, "onConnetAborted", "()V");
		onLoginSucc = env->GetMethodID(l_base_process_class, "onLoginSucc", "(IIJLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		onLoginFailed = env->GetMethodID(l_base_process_class, "onLoginFailed", "(BLjava/lang/String;)V");
		onVisitorUserInfo = env->GetMethodID(l_base_process_class, "onVisitorUserInfo", "(JLjava/lang/String;S)V");
		//sinashow1android/info/UserInfo
		onUserEnter = env->GetMethodID(l_base_process_class, "onUserEnter", "(Ljava/lang/Object;)V");
		onUserLeave = env->GetMethodID(l_base_process_class, "onUserLeave", "(JBLjava/lang/String;)V");
		onUserList = env->GetMethodID(l_base_process_class, "onUserList", "([Ljava/lang/Object;S)V");
		onFlower = env->GetMethodID(l_base_process_class, "onFlower", "(JJI)V");
		onChatMessage = env->GetMethodID(l_base_process_class, "onChatMessage", "(BJJLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		onBroadCast = env->GetMethodID(l_base_process_class, "onBroadCast", "(JLjava/lang/String;)V");
		onChatVerifyCode = env->GetMethodID(l_base_process_class, "onChatVerifyCode", "(Ljava/lang/String;)V");
		onUserBeOperatedNotify = env->GetMethodID(l_base_process_class, "onUserBeOperatedNotify", "(JJBLjava/lang/String;)V");
		onRoomPropertyChangedNotify = env->GetMethodID(l_base_process_class, "onRoomPropertyChangedNotify", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;ZZ)V");
		onRoomBackGroundBmp = env->GetMethodID(l_base_process_class, "onRoomBackGroundBmp", "(Ljava/lang/String;)V");
		onBlackList = env->GetMethodID(l_base_process_class, "onBlackList", "(I[Ljava/lang/Object;)V");
		//sinashow1android.jroominfo.BlackIPUserInfo
		onBlackIPList = env->GetMethodID(l_base_process_class, "onBlackIPList", "(I[Ljava/lang/Object;)V");
		onRoomStateChangedNotify = env->GetMethodID(l_base_process_class, "onRoomStateChangedNotify", "(JIZ)V");
		onUserHermitStateChanged = env->GetMethodID(l_base_process_class, "onUserHermitStateChanged", "(JZ)V");
		//sinashow1android.jroominfo.MDUserInfo
		onUserInfoChanged = env->GetMethodID(l_base_process_class, "onUserInfoChanged", "(Ljava/lang/Object;)V");
		onUserGeneralInfo = env->GetMethodID(l_base_process_class, "onUserGeneralInfo", "(JI)V");
		onLostRateRs = env->GetMethodID(l_base_process_class, "onLostRateRs", "(JI)V");
		onWeekStarNotify = env->GetMethodID(l_base_process_class, "onWeekStarNotify", "(JIIZZ)V");
		onPeerNotify = env->GetMethodID(l_base_process_class, "onPeerNotify", "(JIZ)V");
		onSellerNotify = env->GetMethodID(l_base_process_class, "onSellerNotify", "(JZ)V");
		onManageUserResult = env->GetMethodID(l_base_process_class, "onManageUserResult", "(JBBLjava/lang/String;)V");

		//media process method
		onMicOrderList = env->GetMethodID(l_media_process_class, "onMicOrderList", "([JI)V");
		onMicList = env->GetMethodID(l_media_process_class, "onMicList", "([Ljava/lang/Object;I)V");
		onSpeakerList = env->GetMethodID(l_media_process_class, "onSpeakerList", "([Ljava/lang/Object;I)V");
		onApplyMicRs = env->GetMethodID(l_media_process_class, "onApplyMicRs", "(B)V");
		onBeginSpeak = env->GetMethodID(l_media_process_class, "onBeginSpeak", "(B)V");
		onVoiceChatRQ = env->GetMethodID(l_media_process_class, "onVoiceChatRQ", "(J)V");
		onVoiceChatRS = env->GetMethodID(l_media_process_class, "onVoiceChatRS", "(BJJ)V");
		onVoiceChatStop = env->GetMethodID(l_media_process_class, "onVoiceChatStop", "(J)V");
		onInsertMicNotify = env->GetMethodID(l_media_process_class, "onInsertMicNotify", "(JJB)V");
		onGiveMic = env->GetMethodID(l_media_process_class, "onGiveMic", "(JJ)V");
		onMicTimeChanged = env->GetMethodID(l_media_process_class, "onMicTimeChanged", "(JBB)V");
		onUserStateRS = env->GetMethodID(l_media_process_class, "onUserStateRS", "(JI)V");
		onManageMicStateNotify = env->GetMethodID(l_media_process_class, "onManageMicStateNotify", "(JBBZ)V");
		onUserVocieStateChanged = env->GetMethodID(l_media_process_class, "onUserVocieStateChanged", "(JB)V");
		onAVSChanged = env->GetMethodID(l_media_process_class, "onAVSChanged", "(II[Ljava/lang/Object;)V");

		//value add process method
		onSendGiftResult = env->GetMethodID(l_value_added_process_class, "onSendGiftResult", "(BJILjava/lang/String;I)V");
		onGiftNotify = env->GetMethodID(l_value_added_process_class, "onGiftNotify", "(JJILjava/lang/String;IIIII)V");
		//sinashow1android.jroominfo.BigGiftNotifyInfo
		onBigGiftNotify = env->GetMethodID(l_value_added_process_class, "onBigGiftNotify", "(Ljava/lang/Object;)V");
		onBalanceNotify = env->GetMethodID(l_value_added_process_class, "onBalanceNotify", "(J)V");
		onLoudSpeakerResult = env->GetMethodID(l_value_added_process_class, "onLoudSpeakerResult", "(BLjava/lang/String;)V");
		onLoudSpeakerNotify = env->GetMethodID(l_value_added_process_class, "onLoudSpeakerNotify", "(Ljava/lang/Object;)V");
		onAwardPropNotify = env->GetMethodID(l_value_added_process_class, "onAwardPropNotify", "(IJLjava/lang/String;III[Ljava/lang/Object;)V");
		onAwardPropInfo = env->GetMethodID(l_value_added_process_class, "onAwardPropInfo", "(IJLjava/lang/String;III[Ljava/lang/Object;)V");
		onFireWorksNotify = env->GetMethodID(l_value_added_process_class, "onFireWorksNotify", "(JLjava/lang/String;IIJ)V");

		//mps process method
		onMpsNotify = env->GetMethodID(l_mps_process_class, "onMpsNotify", "(BLjava/lang/String;)V");

		jclass gStringClass= (env)->FindClass("java/lang/String");
		gmidStringGetBytes= (env)->GetMethodID(gStringClass, "getBytes", "(Ljava/lang/String;)[B");
		gmidStringInit= (env)->GetMethodID(gStringClass, "<init>", "([BLjava/lang/String;)V");
		env->DeleteLocalRef(gStringClass);

		CreateObject(&g_pSdkKernel);
		if(g_pSdkKernel)
		{
			g_pSdkKernel->SetProcess(&g_SdkProcess);
			g_pSdkKernel->QueryInterface(UID_BASE_KERNEL, (void**)&g_pBaseKernel);
			g_pSdkKernel->QueryInterface(UID_MEDIA_KERNEL, (void**)&g_pMediaKernel);
			g_pSdkKernel->QueryInterface(UID_VALUE_ADDED_KERNEL, (void**)&g_pValueAddedKernel);
			g_pSdkKernel->QueryInterface(UID_MPS_KERNEL, (void**)&g_pMpsKernel);
		}

		env->DeleteLocalRef(l_base_process_class);
		env->DeleteLocalRef(l_media_process_class);
		env->DeleteLocalRef(l_value_added_process_class);
		env->DeleteLocalRef(l_mps_process_class);
		env->DeleteLocalRef(l_sdk_process_class);
		
	}

	void  Java_com_example_hellojni_SdkKernel_initUserInfo
	(JNIEnv * env, jobject obj, jlong user_id,jstring user_nick,jstring user_pwd,jshort user_photo_nm,jstring version,jboolean have_video, jshort source)
	{
		__android_log_write(ANDROID_LOG_DEBUG,"OBaseKernel","initUserInfo start0");
		if(g_pSdkKernel)
		{
			char tempUserNick[100] = {0};
			jstringToPchar(env, user_nick, "gb2312", tempUserNick, 100);

			char* pVersion = (char*)env->GetStringUTFChars(version, NULL);
			char* pUserPwd = (char*)env->GetStringUTFChars(user_pwd, NULL);
			g_pSdkKernel->SetUserInfo(user_id, tempUserNick, pUserPwd, user_photo_nm);
			env->ReleaseStringUTFChars(version,pVersion);
			env->ReleaseStringUTFChars(user_pwd,pUserPwd);
			__android_log_write(ANDROID_LOG_DEBUG,"OBaseKernel"," initUserInfo end");

		}
	}

	void  Java_com_example_hellojni_SdkKernel_solveTask(JNIEnv * env, jobject obj)
	{
		g_slove_msg_env = env;
		if(g_pSdkKernel)
		{
			g_pSdkKernel->SolveTask();
		}
	}

	/********************************************************************

	基本业务接口

	*********************************************************************/
	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    loginRoom
	* Signature: (ILjava/lang/String;SLjava/lang/String;)V
	*/
	void Java_sinashow1android_jroom_JBaseKernel_loginRoom(JNIEnv* env, jobject obj, jint room_id, jstring server_ip, jshort server_port, jstring room_pwd, jstring machine_code )
	{
		if(g_pBaseKernel)
		{
			char* pServerIp = (char*)env->GetStringUTFChars(server_ip, NULL);
			char* pRoomPwd = (char*)env->GetStringUTFChars(room_pwd, NULL);
			char* pMCode = (char*)env->GetStringUTFChars(machine_code, NULL);
			g_pBaseKernel->LoginRoom(room_id, pServerIp, server_port, pRoomPwd, pMCode);
			env->ReleaseStringUTFChars(server_ip,pServerIp);
			env->ReleaseStringUTFChars(room_pwd,pRoomPwd);
			env->ReleaseStringUTFChars(machine_code,pMCode);
		}

		/*	jclass cls =  env->FindClass("sinashow1android/info/BlackUserInfo");

		jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
		jobject black_list = env->NewObject(cls,construction_id);

		jfieldID ival = env->GetFieldID(cls,"mlLimitedTime","I");  
		env->SetIntField(black_list,ival,10);

		g_env->CallVoidMethod(g_base_process_obj, onBlackList, 1, black_list);
		*/

		/*jobjectArray args = 0;  
		jsize        size = 2;
		jclass cls =  env->FindClass("sinashow1android/info/BlackUserInfo");
		args = env->NewObjectArray(size, cls, 0); 
		jfieldID ival = env->GetFieldID(cls,"mlLimitedTime","I"); 

		for(int i=0; i < size; i++ )  
		{  
		jmethodID construction_id = env->GetMethodID(cls, "<init>", "()V");  
		jobject black_info_obj = env->NewObject(cls,construction_id);

		env->SetIntField(black_info_obj,ival,10+i);  

		env->SetObjectArrayElement(args, i, black_info_obj);  
		}  
		g_env->CallVoidMethod(g_base_process_obj, onBlackList, size, args);
		*/

	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    logOut
	* Signature: (I)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_logOut
		(JNIEnv * env, jobject obj, jint room_id)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->LogOut(room_id);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    sendFlower
	* Signature: (JB)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_sendFlower
		(JNIEnv * env, jobject obj, jlong dst_id, jbyte flower_index)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->SendFlower(dst_id, flower_index);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    sendChat
	* Signature: (BJLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_sendChat
		(JNIEnv * env, jobject obj, jbyte chat_type, jlong user_id, jstring mood, jstring contrl, jstring content)
	{
		if(g_pBaseKernel)
		{
			char tempContent[350] = {0};
			jstringToPchar(env, content, "gb2312", tempContent, 349);

			//char* pMood = (char*)env->GetStringUTFChars(mood, NULL);
			//char* pContrl = (char*)env->GetStringUTFChars(contrl, NULL);
			char tempMood[100] = {0};
			jstringToPchar(env, mood, "gb2312", tempMood, 99);

			char tempControl[300] = {0};
			jstringToPchar(env, contrl, "gb2312", tempControl, 299);
			//char* pContent = (char*)env->GetStringUTFChars(tempcode, NULL);

			g_pBaseKernel->SendChat(chat_type, user_id, tempMood, tempControl, tempContent);
			//env->ReleaseStringUTFChars(mood,pMood);
			//env->ReleaseStringUTFChars(contrl,pContrl);
			//env->ReleaseStringUTFChars(content,pContent);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    changeHermitState
	* Signature: (Z)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_changeHermitState
		(JNIEnv * env, jobject obj, jboolean hermit)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->ChangeHermitState(hermit);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    manageUser
	* Signature: (JBILjava/lang/String;)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_manageUser
		(JNIEnv * env, jobject obj, jlong user_id, jbyte type, jint other_param, jstring text)
	{
		if(g_pBaseKernel)
		{
			char* pText = (char*)env->GetStringUTFChars(text, NULL);
			g_pBaseKernel->ManageUser(user_id, type, other_param, pText);
			env->ReleaseStringUTFChars(text,pText);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    getBlackList
	* Signature: ()V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_getBlackList
		(JNIEnv * env, jobject obj)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->GetBlackList();
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    getBlackIPList
	* Signature: ()V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_getBlackIPList
		(JNIEnv * env, jobject obj)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->GetBlackIPList();
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    modifyRoomStateRQ
	* Signature: (SZ)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_modifyRoomStateRQ
		(JNIEnv * env, jobject obj, jshort property, jboolean value)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->ModifyRoomStateRQ(property, value);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    sendBroadCast
	* Signature: (Ljava/lang/String;)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_sendBroadCast
		(JNIEnv * env, jobject obj, jstring text)
	{
		if(g_pBaseKernel)
		{
			char temp[300] = {0};
			jstringToPchar(env, text, "gb2312", temp, 299);
			//char* pText = (char*)env->GetStringUTFChars(text, NULL);
			g_pBaseKernel->SendBroadCast(temp);
			//env->ReleaseStringUTFChars(text,pText);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    modifyRoomProperty
	* Signature: (ZLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_modifyRoomProperty
		(JNIEnv * env, jobject obj, jboolean is_lock, jstring pwd, jstring topic, jstring salutatory)
	{
		if(g_pBaseKernel)
		{
			char* pPwd = (char*)env->GetStringUTFChars(pwd, NULL);
			char* pTopic = (char*)env->GetStringUTFChars(topic, NULL);
			char* pSalutatory = (char*)env->GetStringUTFChars(salutatory, NULL);
			g_pBaseKernel->ModifyRoomProperty(is_lock, pPwd, pTopic, pSalutatory);
			env->ReleaseStringUTFChars(pwd,pPwd);
			env->ReleaseStringUTFChars(topic,pTopic);
			env->ReleaseStringUTFChars(salutatory,pSalutatory);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    sendGeneralInfo
	* Signature: (JS)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_sendGeneralInfo
		(JNIEnv * env, jobject obj, jlong user_id, jshort type)
	{
		if(g_pBaseKernel)
		{
			g_pBaseKernel->SendGeneralInfo(user_id, type);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JBaseKernel
	* Method:    modifyUserInfo
	* Signature: (Lsinashow1android/jroom/MDUserInfoItem;B)V
	*/
	void  Java_sinashow1android_jroom_JBaseKernel_modifyUserInfo
		(JNIEnv * env, jobject obj, jobject user_info_list, jbyte count)
	{
		if(g_pBaseKernel)
		{
			//g_pBaseKernel->ModifyUserInfo(****, count);
		}
	}


	/***************************************************************

	增值业务接口

	****************************************************************/


	/*
	* Class:     sinashow1android_jroom_IValueAddedKernel
	* Method:    sendGift
	* Signature: (JILjava/lang/String;I)V
	*/
	void  Java_sinashow1android_jroom_JValueAddedKernel_sendGift
		(JNIEnv * env, jobject obj, jlong user_id, jint gift_id, jstring gift_name, jint user_count)
	{
		if(g_pBaseKernel)
		{
		//	char* pGiftName = (char*)env->GetStringUTFChars(gift_name, NULL);
			char temp[100] = {0};
			jstringToPchar(env, gift_name, "gb2312", temp, 99);

			g_pValueAddedKernel->SendGift(user_id, gift_id, temp, user_count);
		//	env->ReleaseStringUTFChars(gift_name,pGiftName);
		}
	}

	/*
	* Class:     sinashow1android_jroom_IValueAddedKernel
	* Method:    sendLoudSpeaker
	* Signature: (BLjava/lang/String;Ljava/lang/String;)V
	*/
	void  Java_sinashow1android_jroom_JValueAddedKernel_sendLoudSpeaker
		(JNIEnv * env, jobject obj, jbyte type, jstring content, jstring control)
	{
		if(g_pBaseKernel)
		{
			//char* pContent = (char*)env->GetStringUTFChars(content, NULL);
			//char* pControl = (char*)env->GetStringUTFChars(control, NULL);
			char tempContent[350] = {0};
			jstringToPchar(env, content, "gb2312", tempContent, 349);

			char temp[350] = {0};
			jstringToPchar(env, control, "gb2312", temp, 349);

			g_pValueAddedKernel->SendLoudSpeaker(type, tempContent, temp);
			//env->ReleaseStringUTFChars(content,pContent);
			//env->ReleaseStringUTFChars(control,pControl);
		}
	}

	/***************************************************************

	音视频业务接口

	****************************************************************/
	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    applyMic
	* Signature: ()V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_applyMic
		(JNIEnv * env, jobject obj)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ApplyMic();
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    manageMic
	* Signature: (JBB)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_manageMic
		(JNIEnv * env, jobject obj, jlong user_id, jbyte type, jbyte index)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ManageMic(user_id, type, index);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    insertMic
	* Signature: (JB)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_insertMic
		(JNIEnv * env, jobject obj, jlong user_id, jbyte index)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->InsertMic(user_id, index);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    stopSpeak
	* Signature: ()V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_stopSpeak
		(JNIEnv * env, jobject obj)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->StopSpeak();
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    changeMicTime
	* Signature: (BB)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_changeMicTime
		(JNIEnv * env, jobject obj, jbyte index, jbyte time)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ChangeMicTime(index, time);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    manageMicState
	* Signature: (BBZ)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_manageMicState
		(JNIEnv * env, jobject obj, jbyte type, jbyte index, jboolean value)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ManageMicState(type, index, value);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    changeRecvState
	* Signature: (BBZ)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_changeRecvState
		(JNIEnv * env, jobject obj, jbyte type, jbyte index, jboolean state)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ChangeRecvState(type, index, state);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    userStateRQ
	* Signature: (J)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_userStateRQ
		(JNIEnv * env, jobject obj, jlong dst_id)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->UserStateRQ(dst_id);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    userChangeState
	* Signature: (SB)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_userChangeState
		(JNIEnv * env, jobject obj, jshort type, jbyte value)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->UserChangeState(type, value);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    sendSpeakerInfo
	* Signature: ([Ljava/lang/Object;)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_sendSpeakerInfo
		(JNIEnv * env, jobject obj, jobjectArray speak_info)
	{
		if(g_pMediaKernel)
		{
			//g_pMediaKernel->SendSpeakerInfo(***);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    voiceChatRQ
	* Signature: (J)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_voiceChatRQ
		(JNIEnv * env, jobject obj, jlong user_id)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->VoiceChatRQ(user_id);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    voiceChatRS
	* Signature: (J)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_voiceChatRS
		(JNIEnv * env, jobject obj, jlong user_id)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->VoiceChatRS(user_id);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    stopVoiceChat
	* Signature: (J)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_stopVoiceChat
		(JNIEnv * env, jobject obj, jlong user_id)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->StopVoiceChat(user_id);
		}
	}

	/*
	* Class:     sinashow1android_jroom_JMediaKernel
	* Method:    changeAvsNodify
	* Signature: (IS)V
	*/
	void  Java_sinashow1android_jroom_JMediaKernel_changeAvsNodify
		(JNIEnv * env, jobject obj, jint ip, jshort port)
	{
		if(g_pMediaKernel)
		{
			g_pMediaKernel->ChangeAvsNodify(ip, port);
		}
	}

	/***************************************************************

	MPS接口

	****************************************************************/
	/*
	* Class:     sinashow1android_jroom_JMpsKernel
	* Method:    applyMic
	* Signature: ()V
	*/
	void  Java_com_example_hellojni_MpsKernel_connectMps
		(JNIEnv * env, jobject obj, jstring addr, jshort port)
	{

		if(g_pMpsKernel)
		{
			char* paddr = (char*)env->GetStringUTFChars(addr, NULL);
			__android_log_print(ANDROID_LOG_INFO,"connectMps","port=%d ip=%s",port,paddr);
			g_pMpsKernel->ConnectMps(paddr, port);
			env->ReleaseStringUTFChars(addr,paddr);
		}
	}
    
    void  Java_sinashow1android_jroom_JMpsKernel_CloseMpsConnection
    (JNIEnv * env, jobject obj)
	{
		g_pMpsKernel->CloseMpsConnection();
	}

	void  Java_sinashow1android_jroom_JMpsKernel_SetServerID		
		(JNIEnv * env, jobject obj,jshort sid)
	{
		g_pMpsKernel->SetServerID( sid );
	}


#ifdef __cplusplus
}
#endif
#endif
