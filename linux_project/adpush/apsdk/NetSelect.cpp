#include "NetSelect.h"
CNetSelect::CNetSelect(){
	memset(m_pSocket, 0, sizeof(m_pSocket));
	m_currentFdNum = 0;
	m_maxFd = 0;
}

CNetSelect::~CNetSelect(){
}

bool CNetSelect::Init(unsigned int aiMaxSocketSize /*= DEF_FD_SIZE*/){
	return true;
}

bool CNetSelect::Destroy(){
	return true;
}

int CNetSelect::CheckEvent(int time_out/*=0*/){
	if(m_currentFdNum <= 0){
		return 0;
	}

	if(0 == time_out){
		FD_ZERO(&m_stReadSet);
		FD_ZERO(&m_stWriteSet);
		FD_ZERO(&m_stExceptSet);
		for(int i = 0; i < DEF_FD_SIZE; ++i){
			if(m_pSocket[i] == NULL) continue;
			Setfd(m_pSocket[i]->miSocket);
		}
		struct timeval stTimeout;
		stTimeout.tv_sec = 3; 
		stTimeout.tv_usec = 0;
		int nRet = select(int(m_maxFd + 1), &m_stReadSet, &m_stWriteSet, &m_stExceptSet, &stTimeout);
		return nRet;
	}
	return 0;
}
int CNetSelect::ProcessEvent(int aiEventSize){
	int return_code = 0;
	bool lbRecvFlag = false;
	if(aiEventSize <= 0){
		return 0;
	}else{
		if(m_currentFdNum <= 0){
			return 0;
		}
		for(int i = 0; i < DEF_FD_SIZE; ++i){
			if(m_pSocket[i] == NULL) continue;
			if (FD_ISSET(m_pSocket[i]->miSocket, &m_stExceptSet)){
				ptr_error_notify(m_pUserParam, m_pSocket[i]->miSocket);
				//m_pSocket[i] = NULL;
				return -1;
			}

			if (FD_ISSET(m_pSocket[i]->miSocket, &m_stReadSet)){
				if(!m_pSocket[i]->RecvData()){
					ptr_error_notify(m_pUserParam, m_pSocket[i]->miSocket);
					//m_pSocket[i] = NULL;
					return -1;
				}else{
					lbRecvFlag =  true;
				}

				while(lbRecvFlag){
					char buffer[3000];
					memset(buffer, 0, 3000);
					int length = 3000;
					bool lbRet = m_pSocket[i]->RecvData(buffer, length);
					if(lbRet){
						ptr_data_notify(m_pUserParam, m_pSocket[i]->miSocket, buffer, length);
					}else{
						break;
					}
				}
			}

			if (FD_ISSET(m_pSocket[i]->miSocket, &m_stWriteSet)){
				if(COMMON_TCP_CONNECTING == m_pSocket[i]->moNetStat){
					m_pSocket[i]->moNetStat = COMMON_TCP_CONNECTED;
					ptr_connect_notify(m_pUserParam, m_pSocket[i]->miSocket);
					return_code = 1;
				}

				m_pSocket[i]->mbCanSend = true;
				//ModifyReadEvent(false);
				int nRet = m_pSocket[i]->SendData();
				if(-1 == nRet){
					ptr_error_notify(m_pUserParam, m_pSocket[i]->miSocket);
					//m_pSocket[i] = NULL;
					return -1;
				}else if(1 == nRet){
					//	ModifyReadEvent(true);
				}
			}
		}
	}
	return return_code;
}

bool CNetSelect::SendData(int fd, const char* buffer, const int length){
	for (int i = 0; i < DEF_FD_SIZE; ++i){
		if(m_pSocket[i] == NULL) continue;
		if(m_pSocket[i]->miSocket == fd){
			m_pSocket[i]->SendData(buffer, length);
			int nRet = m_pSocket[i]->SendData();
			if(-1 == nRet){
				m_pSocket[i]->Close();
				return false;
			}else if(1 == nRet){
				//	ModifyReadEvent(true);
				return true;
			}
		}
	}
	return true;
}

bool CNetSelect::Addfd(CNetSocket* apNetSocket){
	if(apNetSocket == NULL)
	{
		return false;
	}

	for(int i = 0; i <= m_currentFdNum; ++i)
	{
		if(m_pSocket[i] == NULL){
			m_pSocket[i] = apNetSocket;
			break;
		}
	}

	m_currentFdNum++;
	m_maxFd = m_maxFd > apNetSocket->miSocket ? m_maxFd : apNetSocket->miSocket;
	return true;
}
bool CNetSelect::Delfd(CNetSocket* apNetSocket){
	if(apNetSocket == NULL){
		return false;
	}
	FD_CLR(apNetSocket->miSocket, &m_stReadSet);
	FD_CLR(apNetSocket->miSocket, &m_stWriteSet);
	FD_CLR(apNetSocket->miSocket, &m_stExceptSet);
	for(int i = 0; i < DEF_FD_SIZE; ++i)
	{
		if(m_pSocket[i] == NULL) 
			continue;

		if(m_pSocket[i]->miSocket == apNetSocket->miSocket)
		{
			m_pSocket[i] = NULL;
			m_currentFdNum--;
			break;
		}
	}

	return true;
}

bool CNetSelect::Setfd(int fd){
	FD_SET(fd, &m_stReadSet);
	FD_SET(fd, &m_stWriteSet);
	FD_SET(fd, &m_stExceptSet);
	return true;
}

void CNetSelect::SetCallBackFun(ptrOnNotify pError, ptrOnNotify pConnect, ptrOnRecvDataNotify pRecvData, void* param)
{
	ptr_error_notify = pError;
	ptr_connect_notify = pConnect;
	ptr_data_notify = pRecvData;
	m_pUserParam = param;
}

// void CNetSelect::ModifyReadEvent(bool flag)
// {
// 	if(NULL == m_pSocket)return;
// 
// 	if(flag)
// 	{
// 		FD_SET(m_pSocket->miSocket, &m_stWriteSet);
// 	}
// 	else
// 	{
// 		FD_CLR(m_pSocket->miSocket, &m_stWriteSet);
// 	}
// }