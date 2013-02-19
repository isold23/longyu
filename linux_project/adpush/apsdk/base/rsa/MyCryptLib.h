// MyCryptLib.h: interface for the MyCryptLib class.
// 
// Written by Amin Gholiha, 2005, The source code apply under 
// ADAPTIVE PUBLIC LICENSE (Please read License-APLl.txt)
// 
//  ADDITIONAL  LIMITATION OF LIABILITY
// -----------------------------------------------------
// IN NO EVENT WILL AMIN GHOLIHA  BE LIABLE TO YOU FOR ANY 
// DAMAGES, CLAIMS OR COSTS WHATSOEVER OR ANY CONSEQUENTIAL, 
// INDIRECT, INCIDENTAL DAMAGES, OR ANY LOST PROFITS OR LOST SAVINGS, 
// EVEN IF AN  REPRESENTATIVE HAS BEEN ADVISED OF 
// THE POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS OR 
// FOR ANY CLAIM BY ANY THIRD PARTY.  
// THE FOREGOING LIMITATIONS AND EXCLUSIONS APPLY TO 
// THE EXTENT PERMITTED BY APPLICABLE LAW IN YOUR JURISDICTION. 
// 
// 
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_)
#define AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_
#include "ComDef.h"

//////////////////////////////////////////////
/// Definitions. 
//////////////////////////////////////////////

#define _MYCRYPTLIB_DEMOS_ // Undef to leave out the unnessary Demo*(..) functions. 

#define   WIN32_LEAN_AND_MEAN

// Is the system little or Big endian. 
#if (('1234' >> 24) == '1')
#define  SYSTEM_LITTLE_ENDIAN 1234
#elif (('4321' >> 24) == '1')
#define SYSTEM_BIG_ENDIAN      4321
#endif


#define LOHALF(x) ((uint32_t)((x) & _MAXHALFNR_))
#define HIHALF(x) ((uint32_t)((x) >> sizeof(uint32_t)*4 & _MAXHALFNR_))
#define TOHIGH(x) ((uint32_t)((x) << sizeof(uint32_t)*4))
//#define rotate32(x,n) (((x) << n) | ((x) >> (32 - n)))
//#define rotate32(x,n) _lrotl((x), (n))
#define rotate32(a,n) (((a)>>(n))+((a)<<(32-(n))))




#if (SYSTEM_BIG_ENDIAN)

#define SHA_BLOCK32(x) (x)
// The HiBITMASK used for computation, FIX FOR LATER: should change to fit your system e.g 64 bit CPUs. 
#define _HIBITMASK_ 0x00000008
// The maximum nr supported by the system, used to detect owerflows. 
#define _MAXIMUMNR_ 0xffffffff
// The maximum nr you can get using half the number of bits. 
#define _MAXHALFNR_ 0x000Lffff 
#else
#define SHA_BLOCK32(x) ((rotate32((x), 8) & 0x00ff00ff) | (rotate32((x), 24) & 0xff00ff00))
// The HiBITMASK used for computation, FIX FOR LATER: should change to fit your system e.g 64 bit CPUs. 
#define _HIBITMASK_ 0x80000000

// The maximum nr supported by the system, used to detect owerflows. 
#define _MAXIMUMNR_ 0xffffffff
// The maximum nr you can get using half the number of bits. 
#define _MAXHALFNR_ 0xffff 
#endif


#define SHA1_BLOCK_SIZE  64
#define SHA1_DIGEST_SIZE 20

// for code cleanness. 

#define F0to19(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define F20to39(x,y,z)		((x) ^ (y) ^ (z))
#define F40to59(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define F60to79(x,y,z)		 F20to39(x,y,z)


#define sha_round(func,k)  t = a; a = rotate32(a,5) + func(b,c,d) + e + k + w[i];\
	e = d;d = c; c = rotate32(b, 30); b = t;

typedef struct
{   
	uint32_t wbuf[16];
	uint32_t hash[5];
	uint32_t count[2];
} SHA1_STATETYPE;

#ifdef _MYCRYPTLIB_DEMOS_
//#include "HistoryEdit.h"
#include <math.h>
#endif

class MyCryptLib  
{
public:
	// Demostration of RSA.. 
	//void DemoRSA(uint32_t nSize);
	// Collecting Entropy using existing HW. 
	bool MTCollectEntropy(uint8_t *pRandomPool, uint32_t nSize);
	// Verifies Signature Computed by DigitalSignSHA1rDSA using the trusted public keys n and e. 
	bool DigitalVerifySHA1rDSA(unsigned char* pmsgbuff, uint32_t nSizeMsg,uint32_t n[],uint32_t e,uint32_t S[],uint32_t nSize);
	// Creates an Digital signature (S) of pmsgbuff using private key d, public key n.
	int DigitalSignSHA1rDSA(unsigned char* pmsgbuff, uint32_t nSizeMsg,uint32_t d[],uint32_t n[],uint32_t S[],uint32_t nSize);
	// Computes The Sha1Hash for an given data with length nSize
	void SHA1Hash(unsigned char *_pOutDigest, const unsigned char *_pData,uint32_t nSize);
	void SHA1_Start(SHA1_STATETYPE* _pcsha1);
	void SHA1_Finish(unsigned char* _pShaValue, SHA1_STATETYPE* _pcsha1);
	void SHA1_Hash(const unsigned char *_pData, unsigned int _iSize, SHA1_STATETYPE* _pcsha1);
	// RSA Decrypt using CRT method. 
	int RSADecryptCRT(uint32_t m[],uint32_t c[],uint32_t p[], uint32_t q[], uint32_t dP[], uint32_t dQ[], uint32_t qInv[], uint32_t nSize);
	// RSA Encrypt function 
	inline int RSAEncrypt(uint32_t c[], uint32_t m[], uint32_t n[], uint32_t e[], uint32_t nSize);
	// RSA Encrypt function 
	inline int RSAEncrypt(uint32_t c[],uint32_t m[],uint32_t n[],uint32_t nSize,uint32_t e);
	// Generates an RSA Key 	
	int RSAGenerateKey(uint32_t n[], uint32_t d[], uint32_t p[], uint32_t q[], uint32_t dP[], uint32_t dQ[], uint32_t qInv[], uint32_t nSize,uint32_t nPSize,uint32_t nQSize,uint32_t e=65537, uint8_t* pSeedData=NULL,uint32_t nSeedData=0);
	// Genereates an RSA SAFE Prime nr. 
	int BNMakeRSAPrime(uint32_t p[],uint32_t ee, uint32_t nSize,uint32_t nMaximumRetry=30);
	MyCryptLib();
	virtual ~MyCryptLib();
	// Create an well defined Random nr. 
	uint32_t BNMakeRandomNr(uint32_t a[], uint32_t nSize);
	// Return an CStirng containing the number. 
	//CString BNPrint(const uint32_t *p, uint32_t nSize);
	// print out the number in C format. 
	//CString BNPrintC(const uint32_t *p, uint32_t nSize);
	// Generate an prime nr. 
	int BNMakePrime(uint32_t p[],uint32_t nSize, uint8_t* pEntropyPool=NULL, uint32_t nSizeEntropyPool=0);
	// Is the number provided an prime nr? 
	int BNIsPrime(uint32_t W[],uint32_t nSize,uint32_t nrRounds);
	// Generate an random nr between the given border. 
	inline uint32_t RandBetween(uint32_t dwLower,uint32_t dwUpper);
	// Mersenne Twister random generator, returns an random nr. 
	inline uint32_t MTRandom();
	// Mersenne Twinster init..
	inline bool MTInit(uint8_t *pRandomPool=NULL, uint32_t nSize=0);
	// The Rabin Miller algorihm 
	int BNRabinMiller(const uint32_t w[], uint32_t ndigits, uint32_t t);
	// GCD(x,y) Greatest Common dividor. 
	int BNGcd(uint32_t g[], const uint32_t x[], const uint32_t y[], uint32_t nSize);
	// inv = u^(-1) mod v
	int BNModInv(uint32_t inv[], const uint32_t u[], const uint32_t v[], uint32_t nSize);
	// w=x*x more optimized and Mult. 
	inline int BNSquare(uint32_t w[], const uint32_t x[], uint32_t nSize);
	// Computes y = x^e mod m 
	int BNModExp(uint32_t yout[], const uint32_t x[], const uint32_t e[], const uint32_t m[], uint32_t nSize);
	// a = (x * y) mod m 
	uint32_t BNModMult(uint32_t a[], const uint32_t x[], const uint32_t y[], const uint32_t m[], uint32_t nSize);
	// r = u mod v
	uint32_t BNMod(uint32_t r[], const uint32_t u[], uint32_t nUSize, uint32_t v[], uint32_t nVSize);
	// Get an Big nr from Hex string
	uint32_t BNFromHex(uint32_t a[], uint32_t nSize, const char *s,uint32_t nStringLength);
	// Get an Big nr from Decimal String 
	uint32_t BNFromDecimal(uint32_t a[], uint32_t nSize, const char *s, uint32_t nStringLength);
	// Returns ceil(x) as a non-negative integer or 0 if x < 0, We don't whant to include Math lib for only this function. 
	uint32_t BNUiceil(double x);
	// Big nr => octets 
	uint32_t BNToOctets(const uint32_t a[], uint32_t nSize, unsigned char *c, uint32_t nbytes);
	// array of octets => Bing number 
	uint32_t BNFromOctets(uint32_t a[], uint32_t nSize, const unsigned char *c, uint32_t nOctBytes);
	// convert an Big Numer to an CString 
	//CString BNToString( const uint32_t *a, uint32_t nSize,uint32_t nBase=10);
	// returns r = a mod d, where d is an normal uint32_t. 
	inline uint32_t BNModdw(uint32_t a[],uint32_t d, uint32_t nSize);
	//  for future Optimization 
	inline void BNFree(uint32_t **p);
	inline uint32_t * BNAlloc(uint32_t nSize);
	// Returns number of significant bits in d 
	uint32_t BNBitLength(const uint32_t *d,uint32_t nSize);
	// w=u-v, where v is an normal uint32_t. 
	uint32_t BNSubtractdw(uint32_t w[], const uint32_t u[], uint32_t v,  uint32_t  nSize);
	// returns a-b
	inline int BNComparedw(const uint32_t a[], uint32_t b, uint32_t nSize);
	// returns a-b
	int BNCompare(const uint32_t a[], const uint32_t b[], uint32_t nSize);
	//  a = b >> x 
	inline uint32_t BNShiftRight(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize);
	//a = b << x 
	inline uint32_t BNShiftLeft(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize);
	// Divide an big nr with an ordenary uint32_t.
	inline uint32_t BNDividedw(uint32_t q[], const uint32_t u[], uint32_t  v, uint32_t nSize);
	// Sets a=d
	void BNSetEqualdw(uint32_t a[], const uint32_t d, uint32_t nSize);
	// Set a=b 
	inline void BNSetEqual(uint32_t a[], const uint32_t b[], uint32_t nSize);
	// returns a==0
	int BNIsZero(const uint32_t a[], uint32_t nSize);
	// Returns True if A == B. 
	int BNIsEqual(const uint32_t a[], const uint32_t b[], uint32_t nSize);
	// Returns the real size of A
	inline uint32_t BNSizeof(const uint32_t A[], uint32_t nSize);
	// Makesure that the data in A is zero
	void BNSetZero(uint32_t A[],uint32_t nSize);
	// Divides 
	int BNDivide(uint32_t q[], uint32_t r[], const uint32_t u[], uint32_t usize,uint32_t v[],uint32_t vsize);
	// Subtract Big numbers, returns C=B-A, (B>A)
	uint32_t BNSubtract(uint32_t C[], const uint32_t A[], const uint32_t B[], const uint32_t nSize);
	// Adds Big numbers, returns C=A+B
	uint32_t BNAdd(uint32_t C[], const uint32_t A[],const  uint32_t B[], const uint32_t nSize);
	// Adds an normal uint32_t to an big uint32_t. 
	uint32_t BNAdddw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize);
	// Multiplies Big numbers C=A*B. 
	inline	uint32_t BNMultiply(uint32_t C[], const uint32_t A[], const uint32_t B[], const uint32_t nSize);
	inline uint32_t BNMultiplydw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize);
private:
	// SHA1 Functions 
	inline void SHA1_Transform(SHA1_STATETYPE* _pcsha1);


	// SHA1 MASK
	static const uint32_t _SHA_MASK_[4];
	static const uint32_t _SHA_BITS_[4];

	// Prime nrs
	static const uint32_t SMALL_PRIMES[];
	static const uint32_t _NUMBEROFPRIMES_;

	// The Mersenne Twister radnom bufffer and index. 
	uint32_t m_mtIndex;
	uint32_t m_mtbuffer[624];
	bool m_bSeeded;
	// Helpers for code cleaness. 
	inline int BNQhatTooBigHelper(uint32_t qhat, uint32_t  rhat,uint32_t vn2, uint32_t ujn2);
	inline uint32_t BNMultSub(uint32_t wn, uint32_t w[], const uint32_t v[], uint32_t q, uint32_t n);
	inline void BNMultSubHelper(uint32_t uu[2], uint32_t qhat, uint32_t v1, uint32_t v0);
	inline int BNMultiplyHelper(uint32_t p[2], const uint32_t x, const uint32_t y);
	inline uint32_t BNDivideHelper(uint32_t *q, uint32_t *r, const uint32_t u[2], uint32_t v);
	inline int BNModSquareTmp(uint32_t a[], const uint32_t x[], uint32_t m[], uint32_t nSize, uint32_t temp[], uint32_t tqq[], uint32_t trr[]);
	inline int BNModuloTmp(uint32_t r[], const uint32_t u[], uint32_t nUSize, uint32_t v[], uint32_t nVSize, uint32_t tqq[], uint32_t trr[]);
	inline int BNMultTmp(uint32_t a[], const uint32_t x[], const uint32_t y[], uint32_t m[], uint32_t nSize,  uint32_t temp[], uint32_t tqq[], uint32_t trr[]);
};

#endif // !defined(AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_)
