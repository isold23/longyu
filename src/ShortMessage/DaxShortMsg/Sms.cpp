// Sms.cpp : implementation file
//

#include "stdafx.h"
#include "Sms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSms

CSms::CSms()
{
}

CSms::~CSms()
{
}


BEGIN_MESSAGE_MAP(CSms, CWnd)
	//{{AFX_MSG_MAP(CSms)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSms message handlers
//返回值 ：1－成功，0－失败；
//打开串口
int CSms::Open_Com(int port, int baud_rate){

	if(com.Open(port,baud_rate)==true){


		return 1;
	}
	else
		return 0;
}

void CSms::Set_Wnd(HWND hWnd){
	com.SetWnd(hWnd);
}

//关闭串口
void CSms::Close_Com(){
	com.Close();
}

LRESULT CSms::On_Receive(WPARAM wp, LPARAM lp)
{
	int len;
	char str[100];
	len = com.Read(str, 100);
	
	AfxMessageBox(" com Read!in dll");
	if(len > 0)
	{
		char com_str[10];
		strcpy(com_str, "COM");
		ltoa((long)wp, com_str + 3, 10); //	WPARAM 保存端口号
		strResult+=str;
		AfxMessageBox(" com Read!in dll");


	}
	
	return 0;
}

//发送AT指令
int CSms::Send_ATCmd(char* ATCmd,char* result){
	int i,len=0;
	char str[300];
	CString beginstring;
	char beginstr[2];
	char endokstr[4]={' ',' ',' ',' '};
	char enderrorstr[7]={' ',' ',' ',' ',' ',' ',' '};
	int count=0;

	if(!com.IsOpen()) return 0;

	beginstring=ATCmd;

	strcpy(beginstr,beginstring.Left(2));

	if((strncmp(beginstr,"at", 2) == 0) || (strncmp(beginstr,"AT", 2) == 0)) {
	
		strResult="";

		i=com.Write(ATCmd);

		while(true){

			len = com.Read(str, 300);

			strResult+=str;

			if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
			if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;

		}

		strcpy(result,strResult);

		return 1;
	}else{
		return 0;
	}

}

//获取SIM卡短信容量
int CSms::Get_SmCapacity(char* smCapacity){
	int i,len=0;
	char str[300];
	
	if(!com.IsOpen()) return 0;
	
	i=com.Write("AT+CPMS?\r");
	
	strResult="";
	
	while(true){
		len = com.Read(str, 300);
		
		strResult+=str;
		
		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;
	}
	
	strcpy(smCapacity,(strResult.Right(24)).Mid(0,11));
	
	return 1;
}

//获取短信中心号码
int CSms::Get_Smsc(char* smsc){
	int i,len=0;
	char str[300];

	if(!com.IsOpen()) return 0;

	i=com.Write("AT+CSCA?\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;
	}

	strcpy(smsc,(strResult.Right(24)).Mid(0,11));

	return 1;
}

//设置短信中心号码
int CSms::Set_Smsc(char* smsc){
	int i,len=0;
	char str[300];
	char cmd[20];

	strcpy(cmd,"AT+CSCA=");
	strcat(cmd,smsc);
	strcat(cmd,"\r");

	if(!com.IsOpen()) return 0;

	i=com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) return 1;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

}

//发送短信
int CSms::Send_Msg(char* PhoneID,char* SmsContent){
	SM_PARAM SmParam;
	int len,i;
	char str[300];
	char smsc[11];
	CString strSmsc;
	CString strNumber;
	CString strContent;
	int nPduLength;		// PDU串长度
	unsigned char nSmscLength;	// SMSC串长度
//	int nLength;		// 串口收到的数据长度
	char cmd[16];		// 命令串
	char pdu[512];		// PDU串
//	char ans[128];		// 应答串

	if(!com.IsOpen()) return 0;

	com.Write("AT+CMGF=0\r");
	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}


	i=Get_Smsc(smsc);

	if(i==0) return 0;

	strSmsc=smsc;

	strNumber=PhoneID;
	strContent=SmsContent;

		// 去掉号码前的"+"
		if(strSmsc[0] == '+')  strSmsc = strSmsc.Mid(1);
		if(strNumber[0] == '+')  strNumber = strNumber.Mid(1);

		// 在号码前加"86"
		if(strSmsc.Left(2) != "86")  strSmsc = "86" + strSmsc;
		if(strNumber.Left(2) != "86")  strNumber = "86" + strNumber;

		// 填充短消息结构
		strcpy(SmParam.SCA, strSmsc);
		strcpy(SmParam.TPA, strNumber);
		strcpy(SmParam.TP_UD, strContent);
		SmParam.TP_PID = 0;
		SmParam.TP_DCS = GSM_UCS2;

	nPduLength = gsmEncodePdu(&SmParam, pdu);	// 根据PDU参数，编码PDU串
	strcat(pdu, "\x01a");		// 以Ctrl-Z结束

	//AfxMessageBox(pdu);

	gsmString2Bytes(pdu, &nSmscLength, 2);	// 取PDU串中的SMSC信息长度
	nSmscLength++;		// 加上长度字节本身

	// 命令中的长度，不包括SMSC信息长度，以数据字节计
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// 生成命令

	//AfxMessageBox(cmd);

	i=com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

			strResult+=str;

		if(strncmp(strResult.Right(2),"> ", 2) == 0) {

			com.Write(pdu);
			break;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}

	while(true){
		len = com.Read(str, 300);

			strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	} 

}

//删除短信
int CSms::Delete_Msg(int index){

	int len;
	char str[300];
	char cmd[16];		// 命令串

	if(!com.IsOpen()) return 0;

	sprintf(cmd, "AT+CMGD=%d\r", index);	// 生成命令

	// 输出命令串
	com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

//按序号读短信
int CSms::Read_Msg(int index,char* PhoneID,char* SmsContent,char* Date){
	int len;
	char str[300];
	char cmd[16];		// 命令串
	char sptr[512];
	char* ptr;
	SM_PARAM pMsg;

	if(!com.IsOpen()) return 0;

	strResult="";

	sprintf(cmd, "AT+CMGR=%d\r", index);	// 生成命令

	// 输出命令串
	com.Write(cmd);

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {

			strcpy(sptr,strResult);

			ptr=sptr;


			// 读取一条短消息, 以"+CMGR:"开头
			if((ptr = strstr(ptr, "+CMGR:")) != NULL){

				ptr = strstr(ptr, "\r\n");	// 找下一行
				if (ptr != NULL){
					ptr += 2;		// 跳过"\r\n", 定位到PDU
			
					gsmDecodePdu(ptr, &pMsg);	// PDU串解码
				}
				strcpy(PhoneID,pMsg.TPA);
				strcpy(SmsContent,pMsg.TP_UD);
				strcpy(Date,pMsg.TP_SCTS);
			}

			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}

}

//按类型读所有短信
//type 0 － 所有未读短信
//     1 － 所有已读短信
//     2 － 所有未发送短信
//     3 － 所有已发送短信
//     4 － 所有短信
int CSms::Read_AllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index){
	int len;
	char str[300];
	char cmd[16];		// 命令串
	char sptr[8192];
	char* ptr;
	SM_PARAM pMsg;
	int nMsg=0;

	if(!com.IsOpen()) return 0;

	strResult="";

	sprintf(cmd, "AT+CMGL=%d\r", type);	// 生成命令

	// 输出命令串
	com.Write(cmd);

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		//AfxMessageBox(strResult);

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {

			strcpy(sptr,strResult);

			ptr=sptr;


			// 循环读取每一条短消息, 以"+CMGL:"开头
			while((ptr = strstr(ptr, "+CMGL:")) != NULL)
			{
	
				ptr += 7;		// 跳过"+CMGL:", 定位到序号

				//取序号		
				CString strindex=ptr;
				char cindex[2];
				int j=0;

				//AfxMessageBox(strindex);

				while(strindex.Mid(j,1)!=","){
					j++;
				}
				strcpy(cindex,strindex.Mid(0,j));

		
				ptr = strstr(ptr, "\r\n");	// 找下一行
				if (ptr != NULL)
				{
					ptr += 2;		// 跳过"\r\n", 定位到PDU
				
					gsmDecodePdu(ptr, &pMsg);	// PDU串解码

					strcpy(PhoneID+nMsg*20,pMsg.TPA);
					strcpy(SmsContent+nMsg*512,pMsg.TP_UD);
					strcpy(Date+nMsg*20,pMsg.TP_SCTS);
					strcpy(Index+nMsg*3,cindex);

					nMsg++;		// 短消息计数加1
				}		

			}

			return nMsg;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

//初始化
int CSms::SMS_Init(){
	int i,len=0;
	char str[100];

	if(!com.IsOpen()) return 0;

	i=com.Write("AT\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	i=com.Write("AT+CMEE=0\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	i=com.Write("AT+CMGF=0\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	return 1;

}

//设置短信发送模式
int CSms::Set_SendModle(int modle)
{
	int len;
	char str[300];
	char cmd[16];		// 命令串

	if(!com.IsOpen()) return 0;

	sprintf(cmd, "AT+CMGF=%d\r", modle);	// 生成命令

	AfxMessageBox(cmd);

	com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		AfxMessageBox(strResult);

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//private method
// 可打印字符串转换为字节数据
// 如："C8329BFD0E01" --> {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标数据指针
// 返回: 目标数据长度
int CSms::gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	for (int i = 0; i < nSrcLength; i += 2)
	{
		// 输出高4位
		if ((*pSrc >= '0') && (*pSrc <= '9'))
		{
			*pDst = (*pSrc - '0') << 4;
		}
		else
		{
			*pDst = (*pSrc - 'A' + 10) << 4;
		}

		pSrc++;

		// 输出低4位
		if ((*pSrc>='0') && (*pSrc<='9'))
		{
			*pDst |= *pSrc - '0';
		}
		else
		{
			*pDst |= *pSrc - 'A' + 10;
		}

		pSrc++;
		pDst++;
	}

	// 返回目标数据长度
	return (nSrcLength / 2);
}

// 字节数据转换为可打印字符串
// 如：{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01" 
// 输入: pSrc - 源数据指针
//       nSrcLength - 源数据长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf的字符查找表

	for (int i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// 输出高4位
		*pDst++ = tab[*pSrc & 0x0f];	// 输出低4位
		pSrc++;
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return (nSrcLength * 2);
}

// 7bit编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
int CSms::gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nSrc;		// 源字符串的计数值
	int nDst;		// 目标编码串的计数值
	int nChar;		// 当前正在处理的组内字符字节的序号，范围是0-7
	unsigned char nLeft;	// 上一字节残余的数据

	// 计数值初始化
	nSrc = 0;
	nDst = 0;

	// 将源串每8个字节分为一组，压缩成7个字节
	// 循环该处理过程，直至源串被处理完
	// 如果分组不到8字节，也能正确处理
	while (nSrc < nSrcLength)
	{
		// 取源字符串的计数值的最低3位
		nChar = nSrc & 7;

		// 处理源串的每个字节
		if(nChar == 0)
		{
			// 组内第一个字节，只是保存起来，待处理下一个字节时使用
			nLeft = *pSrc;
		}
		else
		{
			// 组内其它字节，将其右边部分与残余数据相加，得到一个目标编码字节
			*pDst = (*pSrc << (8-nChar)) | nLeft;

			// 将该字节剩下的左边部分，作为残余数据保存起来
			nLeft = *pSrc >> nChar;

			// 修改目标串的指针和计数值
			pDst++;
			nDst++;
		}

		// 修改源串的指针和计数值
		pSrc++;
		nSrc++;
	}

	// 返回目标串长度
	return nDst;
}

// 7bit解码
// 输入: pSrc - 源编码串指针
//       nSrcLength - 源编码串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nSrc;		// 源字符串的计数值
	int nDst;		// 目标解码串的计数值
	int nByte;		// 当前正在处理的组内字节的序号，范围是0-6
	unsigned char nLeft;	// 上一字节残余的数据

	// 计数值初始化
	nSrc = 0;
	nDst = 0;
	
	// 组内字节序号和残余数据初始化
	nByte = 0;
	nLeft = 0;

	// 将源数据每7个字节分为一组，解压缩成8个字节
	// 循环该处理过程，直至源数据被处理完
	// 如果分组不到7字节，也能正确处理
	while(nSrc<nSrcLength)
	{
		// 将源字节右边部分与残余数据相加，去掉最高位，得到一个目标解码字节
		*pDst = ((*pSrc << nByte) | nLeft) & 0x7f;

		// 将该字节剩下的左边部分，作为残余数据保存起来
		nLeft = *pSrc >> (7-nByte);

		// 修改目标串的指针和计数值
		pDst++;
		nDst++;

		// 修改字节计数值
		nByte++;

		// 到了一组的最后一个字节
		if(nByte == 7)
		{
			// 额外得到一个目标解码字节
			*pDst = nLeft;

			// 修改目标串的指针和计数值
			pDst++;
			nDst++;

			// 组内字节序号和残余数据初始化
			nByte = 0;
			nLeft = 0;
		}

		// 修改源串的指针和计数值
		pSrc++;
		nSrc++;
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标串长度
	return nDst;
}

// 8bit编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
int CSms::gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	// 简单复制
	memcpy(pDst, pSrc, nSrcLength);

	return nSrcLength;
}

// 8bit解码
// 输入: pSrc - 源编码串指针
//       nSrcLength -  源编码串长度
// 输出: pDst -  目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	// 简单复制
	memcpy(pDst, pSrc, nSrcLength);

	// 输出字符串加个结束符
	*pDst = '\0';

	return nSrcLength;
}

// UCS2编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
int CSms::gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE宽字符数目
	WCHAR wchar[128];	// UNICODE串缓冲区

	// 字符串-->UNICODE串
	nDstLength = MultiByteToWideChar(CP_ACP, 0, pSrc, nSrcLength, wchar, 128);

	// 高低字节对调，输出
	for(int i=0; i<nDstLength; i++)
	{
		*pDst++ = wchar[i] >> 8;		// 先输出高位字节
		*pDst++ = wchar[i] & 0xff;		// 后输出低位字节
	}

	// 返回目标编码串长度
	return nDstLength * 2;
}

// UCS2解码
// 输入: pSrc - 源编码串指针
//       nSrcLength -  源编码串长度
// 输出: pDst -  目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE宽字符数目
	WCHAR wchar[128];	// UNICODE串缓冲区

	// 高低字节对调，拼成UNICODE
	for(int i=0; i<nSrcLength/2; i++)
	{
		wchar[i] = *pSrc++ << 8;	// 先高位字节
		wchar[i] |= *pSrc++;		// 后低位字节
	}

	// UNICODE串-->字符串
	nDstLength = WideCharToMultiByte(CP_ACP, 0, wchar, nSrcLength/2, pDst, 160, NULL, NULL);

	// 输出字符串加个结束符
	pDst[nDstLength] = '\0';

	// 返回目标字符串长度
	return nDstLength;
}

// 正常顺序的字符串转换为两两颠倒的字符串，若长度为奇数，补'F'凑成偶数
// 如："8613851872468" --> "683158812764F8"
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// 目标字符串长度
	char ch;			// 用于保存一个字符

	// 复制串长度
	nDstLength = nSrcLength;

	// 两两颠倒
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// 保存先出现的字符
		*pDst++ = *pSrc++;	// 复制后出现的字符
		*pDst++ = ch;		// 复制先出现的字符
	}

	// 源串长度是奇数吗？
	if(nSrcLength & 1)
	{
		*(pDst-2) = 'F';	// 补'F'
		nDstLength++;		// 目标串长度加1
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return nDstLength;
}

// 两两颠倒的字符串转换为正常顺序的字符串
// 如："683158812764F8" --> "8613851872468"
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
int CSms::gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// 目标字符串长度
	char ch;			// 用于保存一个字符

	// 复制串长度
	nDstLength = nSrcLength;

	// 两两颠倒
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// 保存先出现的字符
		*pDst++ = *pSrc++;	// 复制后出现的字符
		*pDst++ = ch;		// 复制先出现的字符
	}

	// 最后的字符是'F'吗？
	if(*(pDst-1) == 'F')
	{
		pDst--;
		nDstLength--;		// 目标字符串长度减1
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return nDstLength;
}

// PDU编码，用于编制、发送短消息
// 输入: pSrc - 源PDU参数指针
// 输出: pDst - 目标PDU串指针
// 返回: 目标PDU串长度
int CSms::gsmEncodePdu(const CSms::SM_PARAM* pSrc, char* pDst)
{
	int nLength;			// 内部用的串长度
	int nDstLength;			// 目标PDU串长度
	unsigned char buf[256];	// 内部用的缓冲区

	// SMSC地址信息段
	nLength = strlen(pSrc->SCA);	// SMSC地址字符串的长度	
	buf[0] = (char)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;	// SMSC地址信息长度
	buf[1] = 0x91;		// 固定: 用国际格式号码
	nDstLength = gsmBytes2String(buf, pDst, 2);		// 转换2个字节到目标PDU串
	nDstLength += gsmInvertNumbers(pSrc->SCA, &pDst[nDstLength], nLength);	// 转换SMSC号码到目标PDU串

	// TPDU段基本参数、目标地址等
	nLength = strlen(pSrc->TPA);	// TP-DA地址字符串的长度
	buf[0] = 0x11;					// 是发送短信(TP-MTI=01)，TP-VP用相对格式(TP-VPF=10)
	buf[1] = 0;						// TP-MR=0
	buf[2] = (char)nLength;			// 目标地址数字个数(TP-DA地址字符串真实长度)
	buf[3] = 0x91;					// 固定: 用国际格式号码
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], 4);		// 转换4个字节到目标PDU串
	nDstLength += gsmInvertNumbers(pSrc->TPA, &pDst[nDstLength], nLength);	// 转换TP-DA到目标PDU串

	// TPDU段协议标识、编码方式、用户信息等
	nLength = strlen(pSrc->TP_UD);	// 用户信息字符串的长度
	buf[0] = pSrc->TP_PID;			// 协议标识(TP-PID)
	buf[1] = pSrc->TP_DCS;			// 用户信息编码方式(TP-DCS)
	buf[2] = 0;						// 有效期(TP-VP)为5分钟
	if(pSrc->TP_DCS == GSM_7BIT)	
	{
		// 7-bit编码方式
		buf[3] = nLength;			// 编码前长度
		nLength = gsmEncode7bit(pSrc->TP_UD, &buf[4], nLength+1) + 4;	// 转换TP-DA到目标PDU串
	}
	else if(pSrc->TP_DCS == GSM_UCS2)
	{
		// UCS2编码方式
		buf[3] = gsmEncodeUcs2(pSrc->TP_UD, &buf[4], nLength);	// 转换TP-DA到目标PDU串
		nLength = buf[3] + 4;		// nLength等于该段数据长度
	}
	else
	{
		// 8-bit编码方式
		buf[3] = gsmEncode8bit(pSrc->TP_UD, &buf[4], nLength);	// 转换TP-DA到目标PDU串
		nLength = buf[3] + 4;		// nLength等于该段数据长度
	}
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], nLength);		// 转换该段数据到目标PDU串

	// 返回目标字符串长度
	return nDstLength;
}

// PDU解码，用于接收、阅读短消息
// 输入: pSrc - 源PDU串指针
// 输出: pDst - 目标PDU参数指针
// 返回: 用户信息串长度
int CSms::gsmDecodePdu(const char* pSrc, CSms::SM_PARAM* pDst)
{
	int nDstLength;			// 目标PDU串长度
	unsigned char tmp;		// 内部用的临时字节变量
	unsigned char buf[256];	// 内部用的缓冲区

	// SMSC地址信息段
	gsmString2Bytes(pSrc, &tmp, 2);	// 取长度
	tmp = (tmp - 1) * 2;	// SMSC号码串长度
	pSrc += 4;			// 指针后移，忽略了SMSC地址格式
	gsmSerializeNumbers(pSrc, pDst->SCA, tmp);	// 转换SMSC号码到目标PDU串
	pSrc += tmp;		// 指针后移

	// TPDU段基本参数
	gsmString2Bytes(pSrc, &tmp, 2);	// 取基本参数
	pSrc += 2;		// 指针后移

	// 取回复号码
	gsmString2Bytes(pSrc, &tmp, 2);	// 取长度
	if(tmp & 1) tmp += 1;	// 调整奇偶性
	pSrc += 4;			// 指针后移，忽略了回复地址(TP-RA)格式
	gsmSerializeNumbers(pSrc, pDst->TPA, tmp);	// 取TP-RA号码
	pSrc += tmp;		// 指针后移

	// TPDU段协议标识、编码方式、用户信息等
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_PID, 2);	// 取协议标识(TP-PID)
	pSrc += 2;		// 指针后移
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_DCS, 2);	// 取编码方式(TP-DCS)
	pSrc += 2;		// 指针后移
	gsmSerializeNumbers(pSrc, pDst->TP_SCTS, 14);		// 服务时间戳字符串(TP_SCTS) 
	pSrc += 14;		// 指针后移
	gsmString2Bytes(pSrc, &tmp, 2);	// 用户信息长度(TP-UDL)
	pSrc += 2;		// 指针后移
	if(pDst->TP_DCS == GSM_7BIT)	
	{
		// 7-bit解码
		nDstLength = gsmString2Bytes(pSrc, buf, tmp & 7 ? (int)tmp * 7 / 4 + 2 : (int)tmp * 7 / 4);	// 格式转换
		gsmDecode7bit(buf, pDst->TP_UD, nDstLength);	// 转换到TP-DU
		nDstLength = tmp;
	}
	else if(pDst->TP_DCS == GSM_UCS2)
	{
		// UCS2解码
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// 格式转换
		nDstLength = gsmDecodeUcs2(buf, pDst->TP_UD, nDstLength);	// 转换到TP-DU
	}
	else
	{
		// 8-bit解码
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// 格式转换
		nDstLength = gsmDecode8bit(buf, pDst->TP_UD, nDstLength);	// 转换到TP-DU
	}

	// 返回目标字符串长度
	return nDstLength;
}


// 发送短消息，仅发送命令，不读取应答
// 输入: pSrc - 源PDU参数指针
int CSms::gsmSendMessage(CSms::SM_PARAM* pSrc)
{
	int nPduLength;		// PDU串长度
	unsigned char nSmscLength;	// SMSC串长度
	int nLength;		// 串口收到的数据长度
	char cmd[16];		// 命令串
	char pdu[512];		// PDU串
	char ans[128];		// 应答串

	nPduLength = gsmEncodePdu(pSrc, pdu);	// 根据PDU参数，编码PDU串
	strcat(pdu, "\x01a");		// 以Ctrl-Z结束

	AfxMessageBox(pdu);

	gsmString2Bytes(pdu, &nSmscLength, 2);	// 取PDU串中的SMSC信息长度
	nSmscLength++;		// 加上长度字节本身

	// 命令中的长度，不包括SMSC信息长度，以数据字节计
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// 生成命令

	AfxMessageBox(cmd);



	com.Write(cmd, strlen(cmd));	// 先输出命令串

	nLength = com.Read(ans, 128);	// 读应答数据

	// 根据能否找到"\r\n> "决定成功与否
	if(nLength == 4 && strncmp(ans, "\r\n> ", 4) == 0)
	{
//		return com.Write(pdu, strlen(pdu));		// 得到肯定回答，继续输出PDU串
	}

	return 0;
}

// 读取短消息，仅发送命令，不读取应答
// 用+CMGL代替+CMGR，可一次性读出全部短消息
int CSms::gsmReadMessageList()
{
	return com.Write("AT+CMGL\r", 8);
}

// 删除短消息，仅发送命令，不读取应答
// 输入: index - 短消息序号，1-255
int CSms::gsmDeleteMessage(int index)
{
	char cmd[16];		// 命令串

	sprintf(cmd, "AT+CMGD=%d\r", index);	// 生成命令

	// 输出命令串
	return com.Write(cmd, strlen(cmd));
}

// 读取GSM MODEM的应答，可能是一部分
// 输出: pBuff - 接收应答缓冲区
// 返回: GSM MODEM的应答状态, GSM_WAIT/GSM_OK/GSM_ERR
// 备注: 可能需要多次调用才能完成读取一次应答，首次调用时应将pBuff初始化
int CSms::gsmGetResponse(CSms::SM_BUFF* pBuff)
{
	int nLength;		// 串口收到的数据长度
	int nState;

	// 从串口读数据，追加到缓冲区尾部
	nLength = com.Read(&pBuff->data[pBuff->len], 128);	
	pBuff->len += nLength;

	// 确定GSM MODEM的应答状态
	nState = GSM_WAIT;
	if ((nLength > 0) && (pBuff->len >= 4))
	{
		if (strncmp(&pBuff->data[pBuff->len - 4], "OK\r\n", 4) == 0)  nState = GSM_OK;
		else if (strstr(pBuff->data, "+CMS ERROR") != NULL) nState = GSM_ERR;
	}

	return nState;
}

// 从列表中解析出全部短消息
// 输入: pBuff - 短消息列表缓冲区
// 输出: pMsg - 短消息缓冲区
// 返回: 短消息条数
int CSms::gsmParseMessageList(CSms::SM_PARAM* pMsg, CSms::SM_BUFF* pBuff)
{
	int nMsg;			// 短消息计数值
	char* ptr;			// 内部用的数据指针

	nMsg = 0;
	ptr = pBuff->data;

	// 循环读取每一条短消息, 以"+CMGL:"开头
	while((ptr = strstr(ptr, "+CMGL:")) != NULL)
	{
		ptr += 6;		// 跳过"+CMGL:", 定位到序号
		sscanf(ptr, "%d", &pMsg->index);	// 读取序号
//		TRACE("  index=%d\n",pMsg->index);

		ptr = strstr(ptr, "\r\n");	// 找下一行
		if (ptr != NULL)
		{
			ptr += 2;		// 跳过"\r\n", 定位到PDU
			
			gsmDecodePdu(ptr, pMsg);	// PDU串解码

			pMsg++;		// 准备读下一条短消息
			nMsg++;		// 短消息计数加1
		}
	}

	return nMsg;
}
