#ifndef _TCP_STREAM_H_
#define _TCP_STREAM_H_

class CTcpStream
{
public:
	CTcpStream(int liTimeout = 1000);
	~CTcpStream(void);
	bool Connect(const char* apszDestIp,unsigned short ausPort,int liTimeout = 0);
	bool SendData(const char* apData,unsigned short ausDataLen);
	int RecvData(char* apBuff,unsigned short ausBuffSize,int liTimeout = 1000);
	void Disconnect();
	int GetSocket(){return miSocket;}	
private:
	int	miSocket;
};

#endif //_TCP_STREAM_H_

