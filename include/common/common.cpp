#include "stdafx.h"
#include "common.h"

using namespace wlw;
////////////////////////////////////////////////////////////////////////////////////
CErrorBase::CErrorBase(void)
{

}
CErrorBase::CErrorBase(uint32 error) : m_nErrorCode(error)
{

}

CErrorBase::~CErrorBase()
{

}
////////////////////////////////////////////////////////////////////////////////////
uint32 CTimeBase::s_time = CTimeBase::GetTime();
/************************************************************************/
/*                                                                      */
/************************************************************************/

/* Constants for MD5Transform routine.
*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* F, G, H and I are basic MD5 functions.
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (unsigned long int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (unsigned long int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (unsigned long int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (unsigned long int)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}


/* MD5 initialization. Begins an MD5 operation, writing a new context.
*/

MD5_CTX::MD5_CTX()
{
	MD5Init ();
}

MD5_CTX::~MD5_CTX()
{
}

void MD5_CTX::MD5Init ()
{
	this->count[0] = this->count[1] = 0;
	/* Load magic initialization constants.*/
	this->state[0] = 0x67452301;
	this->state[1] = 0xefcdab89;
	this->state[2] = 0x98badcfe;
	this->state[3] = 0x10325476;
	/* Add by Liguangyi */
	MD5_memset(PADDING, 0, sizeof(PADDING));
	*PADDING=0x80;
	//PADDING = {
	//	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	};
}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
void MD5_CTX::MD5Update (unsigned char *input,unsigned int inputLen)
{
	unsigned int i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (unsigned int)((this->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((this->count[0] += ((unsigned long int)inputLen << 3))
		< ((unsigned long int)inputLen << 3))
		this->count[1]++;
	this->count[1] += ((unsigned long int)inputLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible.
	*/
	if (inputLen >= partLen) {
		MD5_memcpy((unsigned char*)&this->buffer[index], 
			(unsigned char*)input, partLen);
		MD5Transform (this->state, this->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (this->state, &input[i]);

		index = 0;
	}
	else
		i = 0;

	/* Buffer remaining input */
	MD5_memcpy ((unsigned char*)&this->buffer[index], (unsigned char*)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
the message digest and zeroizing the context.
*/
void MD5_CTX::MD5Final (unsigned char digest[16])
{
	unsigned char bits[8];
	unsigned int index, padLen;

	/* Save number of bits */
	Encode (bits, this->count, 8);

	/* Pad out to 56 mod 64.
	*/
	index = (unsigned int)((this->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update ( PADDING, padLen);

	/* Append length (before padding) */
	MD5Update (bits, 8);
	/* Store state in digest */
	Encode (digest, this->state, 16);

	/* Zeroize sensitive information.
	*/
	MD5_memset ((unsigned char*)this, 0, sizeof (*this));
	this->MD5Init();
}

/* MD5 basic transformation. Transforms state based on block.
*/
void MD5_CTX::MD5Transform (unsigned long int state[4], unsigned char block[64])
{
	unsigned long int a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode (x, block, 64);

	/* Round 1 */
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	/* Zeroize sensitive information.
	*/
	MD5_memset ((unsigned char*)x, 0, sizeof (x));
}

/* Encodes input (unsigned long int) into output (unsigned char). Assumes len is
a multiple of 4.
*/
void MD5_CTX::Encode (unsigned char *output, unsigned long int *input,unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
	}
}

/* Decodes input (unsigned char) into output (unsigned long int). Assumes len is
a multiple of 4.
*/
void MD5_CTX::Decode (unsigned long int *output, unsigned char *input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((unsigned long int)input[j]) | (((unsigned long int)input[j+1]) << 8) |
		(((unsigned long int)input[j+2]) << 16) | (((unsigned long int)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.
*/

void MD5_CTX::MD5_memcpy (unsigned char* output, unsigned char* input,unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
*/
void MD5_CTX::MD5_memset (unsigned char* output,int value,unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		((char *)output)[i] = (char)value;
}
////////////////////////////////////////////////////////////////////////////////////


void CEncdec::encrypt_qword(const unsigned long *v,const unsigned long *const k, unsigned long * w)
{
	register unsigned long y=v[0],z=v[1],sum=0,delta=0x9E3779B9,n=32;

	while(n-->0)
	{
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
	}
	w[0]=y; w[1]=z;
}

void CEncdec::decrypt_qword(const unsigned long *const v,const unsigned long *const k, unsigned long * w)
{
	register unsigned long y=v[0],z=v[1],sum=0xC6EF3720,
		delta=0x9E3779B9,n=32;
	/* sum = delta<<5, in general sum = delta * n */
	while(n-->0)
	{
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
	}
	w[0]=y; w[1]=z;
}
/**********************************************************************
* use key to encrypt in buffer
* key must be 16+ bytes long!
* 
* input:
*    in: buffer to be encrypted
*    inlen: length of input buffer
*    key: unsigned long key[4]
*    out: buffer to store encrypted memory
*    outlen: length of encrypted buffer
*  
*  no output
**********************************************************************/
void CEncdec::Encrypt(unsigned char *in, int inlen, unsigned long *key, unsigned char *out, unsigned long *outlen)
{
	register int m, i, j, count, p = 1;
	unsigned char q[12], *q1, *q2, *inp;
	unsigned char mkey[8];

	m = (inlen+10)%8;
	if (m)  m = 8-m;
	q[0] = (rand()&0xf8) | m;
	i = j = 1;
	while(m>0) {
		q[i++] = rand()&0xff;
		m --;
	}
	count = *outlen = 0;
	q2 = q1 = out;
	memset(mkey, 0, sizeof(mkey));
	while( p <= 2 ) {
		if (i < 8) {
			q[i++] = rand()&0xff;
			p ++;
		}
		if (i == 8) {
			for (i = 0; i < 8; i ++)
				q[i] ^= mkey[i];
			encrypt_qword((unsigned long *)q, key, (unsigned long *)out);
			for (i = 0; i < 8; i ++)
				q1[i] ^= mkey[i];
			q2 = q1;
			q1 += 8;
			count += 8;
			memcpy(mkey, q, 8);
			j = i = 0;
		}
	}
	inp = in;
	while (inlen > 0) {
		if (i < 8) {
			q[i] = inp[0];
			inp ++;
			i ++;
			inlen --;
		}
		if (i == 8) {
			for (i = 0; i < 8; i ++)  {
				if (j) q[i] ^= mkey[i];
				else q[i] ^= q2[i];
			}
			j = 0;
			encrypt_qword((unsigned long *)q, key, (unsigned long *)q1);
			for (i = 0; i < 8; i ++)
				q1[i] ^= mkey[i];
			count += 8;
			memcpy(mkey, q, 8);
			q2 = q1;
			q1 += 8;
			i = 0;
		}
	}
	p = 1;
	while (p < 8) {
		if (i < 8) {
			memset(q+i, 0, 4);
			p++;
			i++;
		}
		if (i == 8) {
			for (i = 0; i < 8; i ++)
				q[i] ^= q2[i];
			encrypt_qword((unsigned long *)q, key, (unsigned long *)q1);
			for (i = 0; i < 8; i ++)
				q1[i] ^= mkey[i];
			memcpy(mkey, q, 8);
			count += 8;
			q2 = q1;
			q1 += 8;
			i = 0;
		}
	}
	*outlen = count;
}
/********************************************************************** 
* decrypt a encrypted string
* key must be 16+ bytes long
* input:
*    in: buffer to be decrypted
*    inlen: length of input encrypted buffer
*    key: unsigned long key[4]
*    out: buffer to store decrypted memory
*    outlen: length of decrypted buffer
*
* output:
*    0 - decrypt failed.
*    1 - decrypt successed.
**********************************************************************/
int CEncdec::Decrypt(unsigned char *in, int inlen, unsigned long *key, unsigned char *out, unsigned long *outlen)
{
	unsigned char q[8], mkey[8], *q1, *q2, *outp;
	register int count, i, j, p;
	if (inlen%8 || inlen<16) return 0;
	/* get basic information of the packet */
	decrypt_qword((unsigned long *)in, key, (unsigned long *)q);
	j = q[0]&0x7;
	count = inlen - j - 10;
	if (*outlen < (unsigned long)count || (unsigned long)count < 0) return 0;
	*outlen = count;
	memset(mkey, 0, 8);
	q2 = mkey;
	i = 8; p = 1;
	q1 = in+8;
	j ++;
	while (p <= 2) {
		if (j < 8) {
			j ++;
			p ++;
		} else if (j == 8) {
			q2 = in;
			for (j = 0; j < 8; j ++ ) {
				if (i + j >= inlen) return 0;
				q[j] ^= q1[j];
			}
			decrypt_qword((unsigned long *)q, key, (unsigned long *) q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
	outp = out;
	while(count !=0) {
		if (j < 8) {
			outp[0] = q2[j] ^ q[j];
			outp ++;
			count --;
			j ++;
		} else if (j == 8) {
			q2 = q1-8;
			for (j = 0; j < 8; j ++ ) {
				if (i + j >= inlen) return 0;
				q[j] ^= q1[j];
			}
			decrypt_qword((unsigned long *)q, key, (unsigned long *) q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
	for (p = 1; p < 8; p ++) {
		if (j < 8) {
			if (q2[j]^q[j])
				return 0;
			j ++;
		} else if (j == 8 ) {
			q2 = q1;
			for (j = 0; j < 8; j ++ ) {
				if (i + j >= inlen) return 0;
				q[j] ^= q1[j];
			}
			decrypt_qword((unsigned long *)q, key, (unsigned long *) q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
	return 1;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CPathName::CPathName(const char *pathname)
:m_strPathName(pathname)
{

}

CPathName::CPathName(const string &pathname)
:m_strPathName(pathname)
{

}

CPathName::~CPathName(void)
{

}

const std::string CPathName::GetPath(void) const
{
	std::string pathname = "";
	return pathname;
}

const std::string CPathName::GetFileName() const
{
	//
	std::string filename = "";

	return filename;
}

const std::string CPathName::GetExtension() const
{
	std::string extension = "";
	return extension;
}

const std::string CPathName::GetFolderName() const
{
	std::string foldername = "";
	return foldername;
}

////////////////////////////////////////////////////////////////////////////////////
CCpsDps::CCpsDps()
{

}
CCpsDps::~CCpsDps()
{

}

uint32 CCpsDps::compress(const char* Input, const uint32 Inlen, char *Output)
{
	return 0;
}
uint32 CCpsDps::decompress(const char* Input, const uint32 Inlen, char *Output)
{
	return 0;
}

uint32 CCpsDps::compress(const char *InFile, const char *OutFile)
{
	return 0;
}
uint32 CCpsDps::decompress(const char *InFile, const char *OutFile)
{
	return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CFileBase::CFileBase(void)
{
}

CFileBase::~CFileBase(void)
{
}

CFileBase::CFileBase(const char *name)
{
	Open(name);
}
CFileBase::CFileBase(std::string &name)
{
	Open(name);
}
bool CFileBase::Open(std::string &strFileName)
{
	m_File.open(strFileName.c_str(), ios::in | ios::out | ios::binary | ios::app);
	if (m_File.bad())
	{
		return false;
	}
	else
	{
		return true;
	}

}
bool CFileBase::Open(const char *pFileName)
{
	m_File.open(pFileName, ios::in | ios::out | ios::binary | ios::app);
	if (m_File.bad())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int CFileBase::Read(char *buffer, int length)
{
	if (m_File.good())
	{
		m_File.read(buffer, length);
		if (m_File.bad())
		{
			return false;
		}
	}
	return true;
}
int CFileBase::Write(const char *buffer, const int length)
{
	if (m_File.good())
	{
		m_File.write(buffer, length);
		if (m_File.bad())
		{
			return false;
		}
	}
	return true;
}

bool CFileBase::Delete(std::string &strFileName)	
{
	int nReturn = remove(strFileName.c_str());
	if (nReturn == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CFileBase::Delete(const char *pFileName)
{
	int nReturn = remove(pFileName);
	if (nReturn == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CFileBase::Close(void)
{
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}

int CFileBase::GetFileSize(void)
{
	int size = 0;
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
	}
	return size;
}

int CFileBase::GetFileSize(const char *pFileName)
{
	int size = 0;
	m_File.open(pFileName, ios::in | ios::binary);
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
		m_File.close();
	}
	return size;
}

int CFileBase::GetFileSize(std::string &strFileName)
{
	int size = 0;
	m_File.open(strFileName.c_str(), ios::in | ios::binary);
	if (m_File.good())
	{
		filebuf *p;
		p = m_File.rdbuf();
		size = p->pubseekoff(0, ios::end, ios::in);
		m_File.close();
	}
	return size;
}

bool CFileBase::IsExist(std::string &strFileName)
{
	m_File.open(strFileName.c_str(), ios::in | ios::binary);
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}
bool CFileBase::IsExist(const char *pFileName)
{
	m_File.open(pFileName, ios::in | ios::binary);
	if (m_File.good())
	{
		m_File.close();
		return true;
	}
	return false;
}

bool CFileBase::Copy(pcint8 srcFileName, pcint8 dstFileName)
{
	ifstream in(srcFileName, ios::in | ios::binary | ios::app);
	ofstream out(dstFileName, ios::out | ios::binary | ios::app);

	std::string strLine = "";
	while(getline(in, strLine))
	{
		out<<strLine;
	}
	in.close();
	out.close();
	return true;
}

bool CFileBase::CutPaste(pcint8 srcFileName, pcint8 dstFileName)
{
	Copy(srcFileName, dstFileName);
	Delete(srcFileName);
	return true;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CConfig::CConfig(void)
:m_strConfigName("config.config"), m_strKey("@88@#nk#45%34%#345%@!$#8@#!")
{

}

CConfig::~CConfig()
{

}

bool CConfig::Write(const std::string &FamilyId, const std::string &SubId, const std::string &strValue)
{
	return true;
}

bool CConfig::Read(const std::string &FamilyId, const std::string &SubId, std::string &strValue) const 
{
	return true;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/