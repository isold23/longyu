#ifndef _MD5_H_
#define _MD5_H_

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <strstream>
using namespace std;


	class MD5_CTX {
	public:
		MD5_CTX();
		~MD5_CTX();

		void MD5Update ( unsigned char *input, unsigned int inputLen);
		void MD5Final (unsigned char digest[16]);

	private:
		unsigned int state[4];		/* state (ABCD) */
		unsigned int count[2];		/* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];       /* input buffer */
		unsigned char PADDING[64];		/* What? */

	private:
		void MD5Init ();
		void MD5Transform (unsigned int state[4], unsigned char block[64]);
		void MD5_memcpy (unsigned char* output, unsigned char* input,unsigned int len);
		void Encode (unsigned char *output, unsigned int *input,unsigned int len);
		void Decode (unsigned int *output, unsigned char *input, unsigned int len);
		void MD5_memset (unsigned char* output,int value,unsigned int len);
	};

#endif //_MD5_H_






