#ifndef _CODE_COMMON_H_
#define _CODE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

#include "defines.h"

#include <Windows.h>
#include <tchar.h>

#define _CRT_SECURE_NO_DEPRECATE 1

namespace code_common
{
	////////////////////////////////////////////////////////////////////////////////////
	enum _LOG_LEVEL 
	{
		_LOG_LEVEL_ERROR = 0,
		_LOG_LEVEL_DEBUG,
		_LOG_LEVEL_RELEASE,
		_LOG_LEVEL_CONFIG,
		_LOG_LEVEL_FILE,
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CErrorBase
	{
	public:
		CErrorBase(void);
		CErrorBase(uint32 error);
		~CErrorBase(void);

		const uint32 GetErrorCode(void) const { return m_nErrorCode; }
		const std::string GetErrorDescription(void) const { return m_strDescription; }

		void SetErrorCode(uint32 error) { m_nErrorCode = error; }
		void SetDescription(const std::string &description) { m_strDescription = description; }

	private:
		std::string m_strReason;
		std::string m_strDescription;
		uint32 m_nErrorCode;
		uint32 m_nType;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CTimeBase
	{
	public:
		static string GetCurrentTime()
		{
			std::string strTime = "";
			struct tm *ptm;
			time_t tme;
			tme = time(NULL);
 			ptm = localtime(&tme);
			char szTime[256];
			memset(szTime, 0, 256);
			sprintf(szTime, "%d-%02d-%02d %02d:%02d:%02d", (ptm->tm_year + 1900),
				ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
			strTime = szTime;
			return strTime;
		}

		static uint32 GetTime()
		{
			return static_cast<uint32>(time(NULL));
		}

		static uint32 GetElapsedTime()
		{
			return (GetTime() - s_time);
		}
	public:
		static uint32 s_time;
	};
	////////////////////////////////////////////////////////////////////////////////////
	//in: d:/direction/test.h out: test.h
	static const char* DescribeFile(const char* file) 
	{
		const char* end1 = ::strrchr(file, '/');
		const char* end2 = ::strrchr(file, '\\');
		if (!end1 && !end2)
			return file;
		else
			return (end1 > end2) ? end1 + 1 : end2 + 1;
	}

	inline static void Log(size_t nLogLevel, char *pszFmt, va_list argp)
	{
		assert(pszFmt != NULL);
		assert(strlen(pszFmt) < 1000);

		switch(nLogLevel)
		{
		case _LOG_LEVEL_DEBUG:
			{
				char szLogLine[1000];
				memset(szLogLine, 0, 1000);
				vsnprintf(szLogLine, 1000, pszFmt, argp);

				char szFullLogLine[1024];
				memset(szFullLogLine, 0, 1024);
				int iLen = _snprintf((&(szFullLogLine[0])), 1024, 
					("%s %s\r\n"), CTimeBase::GetCurrentTime().c_str(), szLogLine);
				OutputDebugString(_T(szFullLogLine));
				//TRACE(_T(szFullLogLine));
				//cout<<szFullLogLine;
				break;     
			}                           
		case _LOG_LEVEL_RELEASE:
			{
				break;
			}
		default:
			{
				break;
			}
		};
	}

	inline static void PrintLog(size_t nLogLevel, char *pszFmt, ...)
	{
		assert(pszFmt != NULL);

		va_list argp;
		va_start(argp, pszFmt);
		Log(nLogLevel, pszFmt, argp);
		va_end(argp);
	}


	////////////////////////////////////////////////////////////////////////////////////

	/* MD5 Class. */
	class MD5_CTX {
	public:
		MD5_CTX();
		~MD5_CTX();

		void MD5Update ( unsigned char *input, unsigned int inputLen);
		void MD5Final (unsigned char digest[16]);

	private:
		unsigned long int state[4];		/* state (ABCD) */
		unsigned long int count[2];		/* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];       /* input buffer */
		unsigned char PADDING[64];		/* What? */

	private:
		void MD5Init ();
		void MD5Transform (unsigned long int state[4], unsigned char block[64]);
		void MD5_memcpy (unsigned char* output, unsigned char* input,unsigned int len);
		void Encode (unsigned char *output, unsigned long int *input,unsigned int len);
		void Decode (unsigned long int *output, unsigned char *input, unsigned int len);
		void MD5_memset (unsigned char* output,int value,unsigned int len);
	};
	////////////////////////////////////////////////////////////////////////////////////
	static int MakeMD5WithBuffer(unsigned char *Input, unsigned int InputLen, unsigned char *Output)
	{
		MD5_CTX md5;
		md5.MD5Update (Input, InputLen);
		md5.MD5Final (Output);
		return 0;
	}

	static uint32 MakeMD5WithFile(const char* pcszFileName, char* Output)
	{
		FILE *file = NULL;
		uint32 len = 0;
		unsigned char buffer[1024];
		memset(buffer, 0, 1024);

		if ((file = fopen(pcszFileName, "rb")) == NULL)
		{
			PrintLog(_LOG_LEVEL_DEBUG, "%s can't be opened\n", pcszFileName);
		}
		else 
		{
			MD5_CTX md5;
			while (len = (uint32)fread(buffer, 1, 1024, file))
				md5.MD5Update(buffer, len);
			md5.MD5Final((puint8)Output);
			fclose (file);
		}
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////
	/**
	* 加密,解密
	*/
	class CEncdec
	{
	public:
		CEncdec(){};
		~CEncdec(){};
	public:
		void Encrypt(unsigned char *in, int inlen, unsigned long *key, unsigned char *out, unsigned long *outlen);
		int Decrypt(unsigned char *in, int inlen, unsigned long *key, unsigned char *out, unsigned long *outlen);
	private:
		void encrypt_qword(const unsigned long *, const unsigned long *, unsigned long *);
		void decrypt_qword(const unsigned long *, const unsigned long *, unsigned long *);
	};
	////////////////////////////////////////////////////////////////////////////////////

	/**
	  * 分析路径
	  * m_strPathName:  路径全名称("d://test/test.txt")
	  * GetPath():      返回路径("d://test/")
	  * GetFileName():  返回文件名称("test.txt")
	  * GetExtension(): 返回扩展名("txt")
	  * GetFolderName():返回文件夹名称("test")
	*/
	const char* const FOLDER_DELIMS = "/\\";
//#if WIN32
	const char DEFAULT_FOLDER_DELIM = '\\';
//#else  // !WIN32
//	const char DEFAULT_FOLDER_DELIM = '/';
//#endif  // !WIN32

	class CPathName
	{
	public:
		CPathName(const char* pathname);
		CPathName(const string &pathname);
		~CPathName(void);

		const std::string GetPath(void) const;
		const std::string GetFileName(void) const;
		const std::string GetExtension(void) const;
		const std::string GetFolderName(void) const;

	public:
		const string m_strPathName;
	};
	////////////////////////////////////////////////////////////////////////////////////
	class CConfig
	{
	public:
		CConfig(void);
		~CConfig(void);
		bool Write(const std::string &FamilyId, const std::string &SubId, const std::string &strValue);
		bool Read(const std::string &FamilyId, const std::string &SubId, std::string &strValue) const;
	private:
		const std::string m_strConfigName;
		const std::string m_strKey;
	};
	////////////////////////////////////////////////////////////////////////////////////
	/**
	  *compress/decompress file or buffer
	*/
	class CCpsDps
	{
	public:
		CCpsDps();
		~CCpsDps();

		uint32 compress(const char* Input, const uint32 Inlen, char *Output);
		uint32 decompress(const char* Input, const uint32 Inlen, char *Output);

		uint32 compress(const char *InFile, const char *OutFile);
		uint32 decompress(const char *InFile, const char *OutFile);
	private:

	};
	////////////////////////////////////////////////////////////////////////////////////
	class CFileBase
	{
	public:
		CFileBase(void);
		CFileBase(const char *name);
		CFileBase(std::string &name);
		~CFileBase(void);

		int Read(char *buffer, int length);
		int Write(const char *buffer, const int length);

		int GetFileSize(const char *pFileName);
		int GetFileSize(std::string &strFileName);
		int GetFileSize(void);

		bool IsExist(std::string &strFileName);
		bool IsExist(const char *pFileName);

		bool Delete(std::string &strFileName);
		bool Delete(const char *pFileName);

		bool Open(std::string &strFileName);
		bool Open(const char *pFileName);

		bool Close(void);

	private:
		std::fstream m_File;
	};
	////////////////////////////////////////////////////////////////////////////////////
	/**
	  * BASE64编码，解码
	*/
#define BASE64_t2       0x30 //00110000
#define BASE64_m2       0x0c //00001100
#define BASE64_b2       0x03 //00000011
#define BASE64_t4       0x3c //00111100
#define BASE64_b4       0x0f //00001111
#define BASE64_h2       0xc0 //11000000
#define BASE64_b6       0x3f //00111111

	static const char cBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

	static const char DeBase64Tab[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62,        // '+'
		0, 0, 0,
		63,        // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61,        // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,        // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,        // 'a'-'z'
	};

	class CBase64
	{
	public:
		CBase64(void){}
		~CBase64(void){}
		static int Encode(char *DataOut, const char *DataIn, int size);
		static int Decode(char *DataOut, const char *DataIn, int size);
	private:

	};

	inline int CBase64::Encode (char *DataOut, const char *DataIn, int size)
	{
		int lOutputBufferLength;
		long n;
		long iGroupsOf3;
		long iLeftover;
		char *pBuffer;
		unsigned char a;
		unsigned char b;
		unsigned char c;
		unsigned char r;

		// how many groups and leftovers
		iGroupsOf3 = size / 3;
		iLeftover = 3 - (size % 3);

		// every 3 characters become 4
		lOutputBufferLength = iGroupsOf3;
		if (iLeftover)
			lOutputBufferLength++;
		lOutputBufferLength *= 4;

		// create new buffer (with terminator byte)
		pBuffer = DataOut;

		// encode
		for (n = 0; n < (iGroupsOf3 * 3); n += 3)
		{
			a = DataIn[n + 0];        // aaaaaabb
			b = DataIn[n + 1];        // bbbbcccc
			c = DataIn[n + 2];        // ccdddddd

			// first character
			r = a;                    // aaaaaabb
			r = r >> 2;               // 00aaaaaa
			*pBuffer++ = cBase64Alphabet[r];

			// second character
			r = a;                    // aaaaaabb
			r = r & BASE64_b2;        // 000000bb
			r = r << 4;               // 00bb0000
			r = r + (b >> 4);         // 00bb0000 + 0000bbbb = 00bbbbbb
			*pBuffer++ = cBase64Alphabet[r];

			// third character
			r = b;                    // bbbbcccc
			r = b << 2;               // bbcccc00
			r = r & BASE64_t4;        // 00cccc00
			r = r + (c >> 6);         // 00cccc00 + 000000cc = 00cccccc
			*pBuffer++ = cBase64Alphabet[r];

			// fourth character
			r = c;                    // ccdddddd
			r = r & BASE64_b6;        // 00dddddd

			*pBuffer++ = cBase64Alphabet[r];
		}

		// handle non multiple of 3 data and insert padding
		if (iLeftover)
		{
			n = (iGroupsOf3 * 3);
			switch (iLeftover)
			{
			case 2:
				a = DataIn[n + 0];    // aaaaaabb
				b = 0;                //by lqh add ,......

				// first character
				r = a;                // aaaaaabb
				r = r >> 2;           // 00aaaaaa
				*pBuffer++ = cBase64Alphabet[r];
				// second character
				r = a;                // aaaaaabb
				r = r & BASE64_b2;    // 000000bb
				r = r << 4;           // 00bb0000
				r = r + (b >> 4);     // 00bbcccc
				*pBuffer++ = cBase64Alphabet[r];
				// insert padding x 2
				*pBuffer++ = cBase64Alphabet[64];
				*pBuffer++ = cBase64Alphabet[64];
				break;
			case 1:
				a = DataIn[n + 0];    // aaaaaabb
				b = DataIn[n + 1];    // bbbbcccc
				// first character
				r = a;                // aaaaaabb
				r = r >> 2;           // 00aaaaaa
				*pBuffer++ = cBase64Alphabet[r];
				// second character
				r = a;                // aaaaaabb
				r = r & BASE64_b2;    // 000000bb
				r = r << 4;           // 00bb0000
				r = r + (b >> 4);     // 00bbcccc
				*pBuffer++ = cBase64Alphabet[r];
				// third character
				r = b;                // bbbbcccc
				r = b << 2;           // bbcccc00
				r = r & BASE64_t4;    // 00cccc00
				*pBuffer++ = cBase64Alphabet[r];
				// insert padding
				*pBuffer++ = cBase64Alphabet[64];
				break;
			}
		}

		//test code
		int nTemp = (int)(pBuffer - DataOut);
		return nTemp;
	}

	inline int CBase64::Decode (char* pDst, const char* pSrc, int nSrcLen)
	{
		int nDstLen;                  // .......
		int nValue;                   // ........
		int i;

		i = 0;
		nDstLen = 0;

		// .4....................3...
		while (i < nSrcLen)
		{
			if (*pSrc != '\r' && *pSrc != '\n')
			{
				nValue = DeBase64Tab[*pSrc++] << 18;
				nValue += DeBase64Tab[*pSrc++] << 12;
				*pDst++ = (nValue & 0x00ff0000) >> 16;
				nDstLen++;

				if (*pSrc != '=')
				{
					nValue += DeBase64Tab[*pSrc++] << 6;
					*pDst++ = (nValue & 0x0000ff00) >> 8;
					nDstLen++;

					if (*pSrc != '=')
					{
						nValue += DeBase64Tab[*pSrc++];
						*pDst++ = nValue & 0x000000ff;
						nDstLen++;
					}
				}

				i += 4;
			}
			else                      // .......
			{
				pSrc++;
				i++;
			}
		}

		// .......
		*pDst = '\0';

		return nDstLen;
	}
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
}//end namespace code_common
#endif //_CODE_COMMON_H_