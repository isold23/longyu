#ifndef Kernel_h__
#define Kernel_h__

#include "RoomKernel.h"
#include "MpsKernel.h"
#include "NetSocket.h"
#include "NetSelect.h"
#include "base/CriticalSection.h"
#include "base/ThreadGroup.h"
#include "base/task/task_queue.h"

class CKernel: public IKernelService, public ISdkKernel
{
public:
	CKernel();

	~CKernel();
public:
	//添加任务
	virtual void AddTask(Task* pTask);

	//发送CRS数据
	virtual void SendRoomData(char* data, uint16_t wLen);

	//连接房间
	virtual void ConnectRoom(const char* aspszServerAddr, uint16_t awServerPort);

	//关闭房间
	virtual void CloseRoom();

	//发送MPS数据
	virtual void SendMpsData(char* data, uint16_t wLen);

	//连接MPS
	virtual void ConnectMps(const char* aspszServerAddr, uint16_t awServerPort);

	//关闭MPS链接
	virtual void CloseMpsConnection();
public:
	//获取错误码
	virtual unsigned int GetLastError();

	//请求接口
	virtual bool QueryInterface(uint32_t uID, void** ppVoid);

	//设置IProcess接口
	virtual void SetProcess(ISdkProcess* pSdkProcess);

	/*********************************************************
	* 同步方法 
	* SDK在内部有新任务要通知上层时，会把所有回调动作缓存起来 
	* 同时调用NewTaskEvent通知上层，转到主线程调用此方法
	*   当调用线程调用此方法时，SDK一次性执行所有缓存的动作
	*   达到让所有回调执行在调用线程的目的
	**********************************************************/
	virtual void SolveTask();

	//设置用户信息
	virtual void SetUserInfo(int64_t ai64UserID, const char* apszNick, const char* apszPsw, uint16_t usPhotoNm);

	//设置网络信息
	virtual void SetNetInfo(int32_t netType,const char* proxyIP, int32_t proxyPort,const char* proxyUser,const char* proxyPwd);

public:
	void OnErrorNotify(uint32_t fd);

	void OnConnectNotify(uint32_t fd);

	void OnRecvDataNotify(uint32_t fd, char *buffer, uint32_t length);

	unsigned int NetWork(STRU_THREAD_CONTEXT *aoContext);
private:
	CRoomKernel m_RoomKernel;
	CMpsKernel  m_MpsKernel;


	ISdkProcess* m_pSdkProcess;

	CNetSocket m_mpsFd;
	CNetSocket mpTcpSession;
	CNetPackCRS m_objCrsNetPack;
	CNetPackMPS m_objMpssNetPack;

	CNetSelect mNetSelect;
	CEvent mNetThreadEvent;
	CEvent mNetThreadExitEvent;
	bool mbNetThreadExit;
	TaskQueue m_TaskQueue;

	CThreadGroup thread_group;
	bool m_bNetThreadWait;

	int64_t mi64LastKeepLiveTime;
};
#endif // Kernel_h__