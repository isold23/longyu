#ifndef RoomKernrl_h__
#define RoomKernrl_h__


#include "BaseKernel.h"
#include "MediaKernel.h"
#include "ValueAddedKernel.h"
#include "base/rsa/RSAMainFun.h"
#include "base/ThreadGroup.h"

//RSA请求
struct STRU_RSA_INFO 
{
	uint32_t * mpContent;			//公钥
	int32_t		nLen;				//公钥长度
	int32_t		nSize;				//原始长度
	int32_t		nType;				//加密步骤
	int64_t 	mi64UserID;		//用户ID

	STRU_RSA_INFO()
	{
		mpContent	= NULL;
		nLen		= 0;
		nType		= 0;
		mi64UserID	= 0;			
	}
};

class CRoomKernel: public IRoomKernelService, public IRoomKernel
{
public:
	CRoomKernel();

	~CRoomKernel();
public: //IKernelService
	void SetProcess(ISdkProcess* pSdkProcess);

	//连接房间
	virtual void ConnectRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort);

	//关闭房间
	virtual void CloseRoom(int32_t alRoomId);

	//RSA加密
	virtual void RSAEncrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen);

	//RSA解密
	virtual void RSADecrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen);
public: 
	//请求接口
	bool QueryInterface(uint32_t uID, void** ppVoid);
public:
	void SolveMsg(char * apPackData, uint16_t awPackDataLen); 

	void OnOpenTCPSession(const int32_t &alHallID);

	void OnCloseTCPSession(const int32_t &alHallID);

	void OnErrTCPSession(const uint8_t &abyErrType,const int32_t &alHallID);

	uint32_t threadCreateKey();

	void KeepLive();
private:
 	void SetPublicKey(uint32_t * pKey,int32_t nLen, int32_t nSize);
 
 	void SendRSAKeyRQ();
private:
	void DealPack(const int32_t &alHallID,char * pData, uint16_t wDataLen);

	void DealVisitorIDRs(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS* pStru);

	void DealLoginRs(STRU_UC_CL_CRS_LOGIN_HALL_RS_2009* pstruLoginRs);

	void DealUserEnter(STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009* pstruUserEnter);

	void DealUserList(STRU_UC_CL_CRS_USER_INFO_ID_2009* pstruUserList);

	void DealMicList(STRU_UC_CL_CRS_MIC_INFO_LIST_ID* pStru);

	void DealSpeakUserList(STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID* pStru);

	void DealBlackList(STRU_UC_CL_CRS_TIME_BLACK_LIST* pStru);

	void DealBlackIPList(STRU_UC_CL_CRS_BLACKIP_LIST_RS* pStru);

	void DealModifyUserInfoID(STRU_UC_CL_CRS_CHG_USER_INFO_ID* pStru);

	void DealAvsChanged(STRU_UC_CRS_CL_USER_AVS_INFO_ID* pStru);

	void DealVipUserNotify(STRU_UC_CL_VIP_ENTER_NOTIFY_EX* pstru);

	void DealBigGiftNotify(STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY* pstru);

	void DealLoudSpeakerNotify(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY* pstru);

	void DealAwardPropNotify(STRU_UC_CL_CRS_AWARD_NOTIFY* pstru);

	void DealAwardPropInfo(STRU_UC_CL_CRS_AWARD_INFO* pstru);

 	void DealApplyRsaKeyRS(STRU_RSA_INFO_RS* pStru);
 
 	void DealRASDecrypt(STRU_ENDECRYPT_FUN* pStru);
private:
	CRSAMainFun* m_pRsaFun;
	//客户端公钥
	STRU_RSA_INFO m_PublicKey;

	CThreadGroup thread_group;
private:
	CBaseKernel m_BaseKernel;
	CMediaKernel m_MediaKernel;
	CValueAddedKernel m_ValueAddedKernel;

	IBaseProcess* m_pBaseProcess;
	IMediaProcess* m_pMediaProcess;
	IValueAddedProcess* m_pValueAddedProcess;
};
#endif // RoomKernrl_h__