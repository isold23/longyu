// MyCryptLib.cpp: implementation of the MyCryptLib class.
//
//////////////////////////////////////////////////////////////////////
#include "MyCryptLib.h"

// For timeGetTime();timeBeginPeriod() timeEndPeriod()
// #include  <Mmsystem.h>
// #pragma comment( lib, "winmm" )


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyCryptLib::MyCryptLib()
{
	m_mtIndex=0;
	m_bSeeded=false;
	memset(&m_mtbuffer,0,sizeof(m_mtbuffer));
}

MyCryptLib::~MyCryptLib()
{

}


// Used to Speed up prime nr generator. 
const uint32_t MyCryptLib::SMALL_PRIMES[] =  {
	3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 
	47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 
	103, 107, 109, 113,127, 131, 137, 139, 149, 151, 
	157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
	211, 223, 227, 229,233, 239, 241, 251, 257, 263, 
	269, 271, 277, 281,283, 293, 307, 311, 313, 317, 
	331, 337, 347, 349,353, 359, 367, 373, 379, 383, 
	389, 397, 401, 409,419, 421, 431, 433, 439, 443, 
	449, 457, 461, 463,467, 479, 487, 491, 499, 503, 
	509, 521, 523, 541,547, 557, 563, 569, 571, 577, 
	587, 593, 599, 601,607, 613, 617, 619, 631, 641, 
	643, 647, 653, 659,661, 673, 677, 683, 691, 701, 
	709, 719, 727, 733,739, 743, 751, 757, 761, 769, 
	773, 787, 797, 809,811, 821, 823, 827, 829, 839, 
	853, 857, 859, 863,877, 881, 883, 887, 907, 911, 
	919, 929, 937, 941,947, 953, 967, 971, 977, 983, 
	991, 997,
};

const uint32_t MyCryptLib::_NUMBEROFPRIMES_=sizeof(MyCryptLib::SMALL_PRIMES)/sizeof(uint32_t);


// SHA konstants. 
#ifdef SYSTEM_LITTLE_ENDIAN
const uint32_t MyCryptLib::_SHA_MASK_[4]={0x00000000, 0x000000ff, 0x0000ffff, 0x00ffffff};
const uint32_t MyCryptLib::_SHA_BITS_[4]={0x00000080, 0x00008000, 0x00800000, 0x80000000};
#else
const uint32_t MyCryptLib::_SHA_MASK_[4]={0x00000000, 0xff000000, 0xffff0000, 0xffffff00};
const uint32_t MyCryptLib::_SHA_BITS_[4]={0x80000000, 0x00800000, 0x00008000, 0x00000080};
#endif

/*
*	Add(uint32_t C[], uint32_t A[], uint32_t B[], uint32_t nSize)
-----------------------------------------------------
*  Addition for very big numbers A,B,C
*  Assumes that A, B and C, have the same size. 
*  nSize = number of bytes. 
*  Adds A & B and put the result in C. 
*  Reference  Knuth, Donald. 1968. The Art of Computer Programming
*  Returns 0 if success 1 if overflow. 
*/

uint32_t MyCryptLib::BNAdd(uint32_t C[], const uint32_t A[], const uint32_t B[], const uint32_t nSize)
{	
	uint32_t k=0; // carry 
	for (uint32_t i = 0; i < nSize; i++)
	{
		C[i] = A[i] + k;
		if(C[i]>=k)// detect overflow and set k
			k=0;
		else
			k=1;

		C[i] += B[i];
		if (C[i] < B[i]) // Detect overflow again. 
			k++;	
	}
	return k;
}


// Returns ceil(x) as a non-negative integer or 0 if x < 0 
uint32_t MyCryptLib::BNUiceil(double x)
{
	uint32_t c;
	if (x < 0) return 0;
	c = (uint32_t)x;
	if ((x - c) > 0.0)
		c++;
	return c;
}



/*
*	SHA1 Implementation algoritm from, the algorith is taken from 
*	Federal Information
*	Processing Standards Publication 180-1, 1995 April 17
*  http://www.itl.nist.gov/fipspubs/fip180-1.htm
*  
*/


/*
* Sha1Hash(unsigned char *_pOutDigest, const unsigned char *_pData,uint32_t nSize)
*
*
* Computes SH1 hash given data (_pData) of size nSize.  	
*  
* _pOutDigest is an buffer of size SHA1_DIGEST_SIZE (20) which will be filled with 
* the digestvalue. 
*
*
*/

void MyCryptLib::SHA1Hash(unsigned char *_pOutDigest, const unsigned char *_pData,uint32_t nSize)
{

	// Be safe
	if ( !_pOutDigest || !_pData )
		return;

	SHA1_STATETYPE csha1;
	memset(&csha1,0,sizeof(csha1));
	SHA1_Start(&csha1);
	SHA1_Hash(_pData,nSize,&csha1);
	SHA1_Finish(_pOutDigest,&csha1);
}


void MyCryptLib::SHA1_Transform(SHA1_STATETYPE* _pcsha1)
{

	uint32_t   w[80], i, a, b, c, d, e, t;

	for (i = 0; i < SHA1_BLOCK_SIZE / 4; ++i)
		w[i] = SHA_BLOCK32(_pcsha1->wbuf[i]);

	for (i = SHA1_BLOCK_SIZE / 4; i < 80; ++i)
		w[i] = rotate32(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

	a = _pcsha1->hash[0];
	b = _pcsha1->hash[1];
	c = _pcsha1->hash[2];
	d = _pcsha1->hash[3];
	e = _pcsha1->hash[4];

	for(i = 0; i < 20; ++i)
	{
		sha_round(F0to19, 0x5a827999);    
	}

	for(i = 20; i < 40; ++i)
	{
		sha_round(F20to39, 0x6ed9eba1);
	}

	for(i = 40; i < 60; ++i)
	{
		sha_round(F40to59, 0x8f1bbcdc);
	}

	for(i = 60; i < 80; ++i)
	{
		sha_round(F60to79, 0xca62c1d6);
	}

	_pcsha1->hash[0] += a; 
	_pcsha1->hash[1] += b; 
	_pcsha1->hash[2] += c; 
	_pcsha1->hash[3] += d; 
	_pcsha1->hash[4] += e;

}
void MyCryptLib::SHA1_Start(SHA1_STATETYPE *_pcsha1)
{

	_pcsha1->hash[0] = 0x67452301;
	_pcsha1->hash[1] = 0xefcdab89;
	_pcsha1->hash[2] = 0x98badcfe;
	_pcsha1->hash[3] = 0x10325476;
	_pcsha1->hash[4] = 0xc3d2e1f0;
	_pcsha1->count[0] = 0;
	_pcsha1->count[1] = 0;
}

void MyCryptLib::SHA1_Finish(unsigned char* _pShaValue, SHA1_STATETYPE* _pcsha1)
{
	uint32_t    i = (uint32_t)(_pcsha1->count[0] & (SHA1_BLOCK_SIZE - 1));
	_pcsha1->wbuf[i >> 2] = (_pcsha1->wbuf[i >> 2] & _SHA_MASK_[i & 3]) | _SHA_BITS_[i & 3];

	if(i > SHA1_BLOCK_SIZE - 9)
	{
		if(i < 60) _pcsha1->wbuf[15] = 0;
		SHA1_Transform(_pcsha1);
		i = 0;
	}
	else   
		i = (i >> 2) + 1;

	while(i < 14) 
		_pcsha1->wbuf[i++] = 0;


	_pcsha1->wbuf[14] = SHA_BLOCK32((_pcsha1->count[1] << 3) | (_pcsha1->count[0] >> 29));
	_pcsha1->wbuf[15] = SHA_BLOCK32(_pcsha1->count[0] << 3);

	SHA1_Transform(_pcsha1);


	for(i = 0; i < SHA1_DIGEST_SIZE; ++i)
		_pShaValue[i] = (unsigned char)(_pcsha1->hash[i >> 2] >> 8 * (~i & 3));
}


void MyCryptLib::SHA1_Hash(const unsigned char *_pData, unsigned int _iSize, SHA1_STATETYPE* _pcsha1)
{
	uint32_t ipos = (uint32_t)(_pcsha1->count[0] & (SHA1_BLOCK_SIZE - 1));
	uint32_t ispace = SHA1_BLOCK_SIZE - ipos;
	unsigned char *pData=(unsigned char *)_pData;
	if((_pcsha1->count[0] += _iSize) < _iSize)
		++(_pcsha1->count[1]);
	while(_iSize >= ispace)     
	{
		memcpy(((unsigned char*)_pcsha1->wbuf) + ipos, pData, ispace);
		ipos = 0; 
		_iSize -= ispace; 
		pData += ispace; 
		ispace = SHA1_BLOCK_SIZE; 
		SHA1_Transform(_pcsha1);
	}	
	memcpy(((unsigned char*)_pcsha1->wbuf) + ipos, pData, _iSize);
}



/*
*	BNAdddw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize)
-----------------------------------------------------
*  Addition for very big numbers w,u
*  w=u+v. 
*  nSize = number of bytes. 
*  Reference  Knuth, Donald. 1968. The Art of Computer Programming
*  Returns 0 if success 1 if overflow. 
*/
inline uint32_t MyCryptLib::BNAdddw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize)
{
	uint32_t k=0;
	w[0] = u[0] + v;
	k=(w[0] >= v) ? 0:1;	
	for (uint32_t j = 1; j < nSize; j++)
	{
		w[j] = u[j] + k;
		k=(w[j] >= k) ? 0:1;
	}
	return k;	
}

/*
*	BNSubtract(uint32_t C[], uint32_t A[], uint32_t B[], uint32_t nSize)
-----------------------------------------------------
*  Subtraction  for very big numbers A,B,C
*  Assumes that A, B and C, have the same size. 
*  nSize = number of bytes. 
*  Calculates C = A - B where A >= B
*  Reference  Knuth, Donald. 1968. The Art of Computer Programming
*  Returns 0 if success 1 if overflow. 
*/

uint32_t MyCryptLib::BNSubtract(uint32_t C[], const uint32_t A[], const uint32_t B[],const uint32_t nSize)
{
	uint32_t  k=0;
	for (uint32_t i = 0; i < nSize; i++)
	{
		C[i] = A[i] - k;
		if (C[i] > _MAXIMUMNR_ - k) // detect underflow (borrow) 
			k = 1;
		else
			k = 0;
		C[i] -= B[i];
		if (C[i] > _MAXIMUMNR_  - B[i])
			k++;
	}	
	return k;
}

/*
*	BNSubtract(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize)
-----------------------------------------------------
*  Subtraction  for very big numbers u to an normal uint32_t. 
*  Assumes that w,u, have the same size. 
*  nSize = number of bytes. 
*  Calculates w=u-v
*  Reference  Knuth, Donald. 1968. The Art of Computer Programming
*  Returns 0 if success 1 if overflow. 
*/



uint32_t MyCryptLib::BNSubtractdw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize)
{
	uint32_t k=0;
	w[0] = u[0] - v;
	if (w[0] > _MAXIMUMNR_- v)
		k = 1;
	else
		k = 0;
	for (uint32_t j = 1; j < nSize; j++)
	{
		w[j] = u[j] - k;
		if (w[j] > _MAXIMUMNR_ - k)
			k = 1;
		else
			k = 0;
	}	
	return k;	
}


// CString MyCryptLib::BNPrint(const uint32_t *p, uint32_t nSize)
// {
// 	CString stmp=L"";
// 	CString sRet=L"";
// 	// Trim leading zeroes 
// 	while (nSize--)
// 	{
// 		if (p[nSize] != 0)
// 			break;
// 	}
// 	nSize++;
// 
// 	// Catch empty len to show 0 
// 	if ( nSize==0 ) 
// 		nSize=1;
// 
// 	while ( nSize-- )
// 	{
// 
// 		stmp.Format(L"%08lx ", p[nSize]);
// 		sRet+=stmp;
// 	}
// 
// 	return sRet;
// }


// CString MyCryptLib::BNPrintC(const uint32_t *p, uint32_t nSize)
// {
// 	CString stmp=L"";
// 	CString sRet;
// 	sRet.Format(L"[%i] = {\r\n",nSize);
// 	int iNrPrinted=0;
// 	for ( uint32_t i=0; i<nSize; i++ )
// 	{
// 
// 		stmp.Format(L"0x%08lx, ", p[i]);
// 		iNrPrinted++;
// 		sRet+=stmp;
// 		if(iNrPrinted%6==0)
// 			sRet+=L"\r\n";
// 	}
// 	sRet+=L"};";
// 	return sRet;	
// }

/*
*	Returns an CString version of the number
*
*/
// CString MyCryptLib::BNToString(const uint32_t *a, uint32_t nSize,uint32_t nBase)
// {
// 
// 	// Is the number is Zero 
// 	if ( BNIsZero(a, nSize) )
// 		return L"0";
// 
// 	CString sRet=L""; // return String 
// 
// 	const char DEC_DIGITS[] = "0123456789";
// 	const char HEX_DIGITS[] = "0123456789abcdef";
// 	const char *cdigits;
// 	double dFactor=0.0;
// 
// 	// Setup the data according to nBase
// 	switch (nBase)
// 	{
// 	case 10:
// 		cdigits = DEC_DIGITS;
// 		dFactor = 2.40824;	/* log(256)/log(10)=2.40824 */
// 		break;
// 	case 16:
// 		cdigits = HEX_DIGITS;
// 		dFactor = 2.0;	/* log(256)/log(16)=2.0 */
// 		break;
// 	default:
// 		return L"Base must be 10 or 16";
// 	}
// 	// Convert to 8 bits octtlets (is easier to handle)
// 	uint32_t nbytes = nSize * sizeof(uint32_t);
// 	uint8_t* pOct=NULL;
// 	pOct=new uint8_t[nbytes];
// 	// be safe
// 	if ( pOct==NULL )
// 		return L"Not enough memory: pOct=new uint8_t[nbytes] Failed..";
// 	memset(pOct,0,nbytes);
// 	uint32_t NumberOfOctNeeded= BNToOctets(a,nSize,pOct,nbytes);
// 
// 	// Create temporary place
// 	uint32_t NewOctLength=BNUiceil(NumberOfOctNeeded*dFactor);
// 	uint8_t* pNewOct=new uint8_t[NewOctLength];
// 	// Be safe 
// 	if ( pNewOct==NULL )
// 	{
// 		delete[] pOct;
// 		return L"Not enough memory: pNewOct=new uint8_t[NewOctLength] Failed..";
// 	}
// 	memset(pNewOct,0,NewOctLength);
// 	// Transform 
// 	uint32_t t=0;
// 	uint32_t i=0;
// 	for (i  = 0; i < nbytes; i++)
// 	{
// 		t = pOct[i];
// 		for (uint32_t j = NewOctLength; j > 0; j--)
// 		{
// 			t += (unsigned long)(pNewOct[j-1] * 256);
// 			pNewOct[j-1] = (unsigned char)(t % nBase);
// 			t /= nBase;
// 		}
// 	}
// 
// 	// Find index of leading significant digit 
// 	uint32_t isig=0;
// 	for ( isig = 0; isig < NewOctLength; isig++ )
// 		if (pNewOct[isig])
// 			break;
// 	// number of charachters needed.. 	
// 	uint32_t nchars = NewOctLength - isig;
// 
// 	for(i=0;i<nchars;i++)
// 		sRet+=cdigits[pNewOct[isig+i]];
// 
// 
// 	delete[] pOct;
// 	delete[] pNewOct;
// 	return sRet;
// }



/*
*	Returns True if a == b else false
*/
int MyCryptLib::BNIsEqual(const uint32_t a[], const uint32_t b[], uint32_t nSize)
{
	if ( nSize <= 0 ) 
		return 0;

	while ( nSize-- )
	{
		if ( a[nSize] != b[nSize] )
			return 0;	
	}	
	return 1;
}

/*
*	Makes A=0
*/
void MyCryptLib::BNSetZero(uint32_t A[], uint32_t nSize)
{
	while ( nSize-- )
		A[nSize] = 0;
}


/*
*	Return True if a==0
*/
int MyCryptLib::BNIsZero(const uint32_t a[], uint32_t nSize)
{
	if (nSize == 0) 
		return 0;

	for (uint32_t i = 0; i < nSize; i++)	
	{
		if (a[i] != 0)
			return 0;	
	}

	return 1;
}

/*
*	Makes a=b
*/

void MyCryptLib::BNSetEqual(uint32_t a[], const uint32_t b[], uint32_t nSize)
{
	for (uint32_t i = 0; i < nSize; i++)
	{
		a[i] = b[i];
	}	
}

/*
* Makes a=d
* Where d is an normal uint32_t. 
*/
void MyCryptLib::BNSetEqualdw(uint32_t a[], const uint32_t d, uint32_t nSize)
{
	if(nSize<=0)
		return;
	BNSetZero(a,nSize);
	a[0]=d;
}


int MyCryptLib::BNCompare(const uint32_t a[], const uint32_t b[], uint32_t nSize)
{
	if ( nSize <= 0 ) 
		return 0;
	while (nSize--)
	{
		if (a[nSize] > b[nSize])
			return 1;	// Grater than 
		if (a[nSize] < b[nSize])
			return -1;	// Less Than 
	}
	return 0;// equal 
}

/* Returns sign of (a - b) where b is an uint32_t */
inline int MyCryptLib::BNComparedw(const uint32_t a[], uint32_t b, uint32_t nSize)
{

	// Be Safe 
	if (nSize == 0) return (b ? -1 : 0);

	for (uint32_t i = 1; i < nSize; i++)
	{
		if (a[i] != 0)
			return 1;	// Greater than 
	}

	if ( a[0] < b) 
		return -1;	// Less than 
	else if ( a[0] > b )
		return 1;		// Greater 

	return 0; //equal  	
}


/*  BNShiftLeft(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize)
*	Computes a = b << x 
*  returns carry 
*/
inline uint32_t MyCryptLib::BNShiftLeft(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize)
{
	uint32_t mask, carry, nextcarry;
	uint32_t i=0;

	if ( x >= sizeof(uint32_t)*8 )
		return 0;

	mask = _HIBITMASK_;
	for (i = 1; i < x; i++)
	{
		mask = (mask >> 1) | mask;
	}
	if (x == 0) mask = 0x0;

	uint32_t y = (sizeof(uint32_t)*8) - x;
	carry = 0;
	for (i = 0; i < nSize; i++)
	{
		nextcarry = (b[i] & mask) >> y;
		a[i] = b[i] << x | carry;
		carry = nextcarry;
	}

	return carry;
}


/* BNShiftRight(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize)
* Computes a = b >> x 
* returns carry 
*
*/
inline uint32_t MyCryptLib::BNShiftRight(uint32_t a[], const uint32_t *b, uint32_t x, uint32_t nSize)
{

	uint32_t mask, carry, nextcarry;
	uint32_t i=0;
	// be safe. 
	if ( x >= (sizeof(uint32_t)*8) )
		return 0;

	// Create mask
	mask = 0x1;
	for (i = 1; i < x; i++)
	{
		mask = (mask << 1) | mask;
	}
	if (x == 0) mask = 0x0;

	uint32_t y = (sizeof(uint32_t)*8) - x;
	carry = 0;
	i = nSize;
	while (i--)
	{
		nextcarry = (b[i] & mask) << y;
		a[i] = b[i] >> x | carry;
		carry = nextcarry;
	}

	return carry;	
}




/* BNDivdw(uint32_t q[], const uint32_t a[], uint32_t b, uint32_t nSize)
*   Calculates quotient q = a div b
*   Returns remainder r = a mod b
*   a,q are big numbers of nSize
*	 r, a are normal uint32_tS.
*
*/
inline uint32_t MyCryptLib::BNDividedw(uint32_t q[], const uint32_t u[], uint32_t v, uint32_t nSize)
{
	uint32_t j;
	uint32_t t[2], r;
	uint32_t shift;
	uint32_t bitmask, overflow, *uu;

	if (nSize == 0) return 0;
	if (v == 0)	return 0;

	bitmask = _HIBITMASK_;
	for (shift = 0; shift < (sizeof(uint32_t)*8); shift++)
	{
		if (v & bitmask)
			break;
		bitmask >>= 1;
	}	
	v <<= shift;
	overflow = BNShiftLeft(q, u, shift, nSize);
	uu = q;
	r = overflow;	
	j = nSize;
	while (j--)
	{
		t[0] = uu[j];
		t[1] = r;
		overflow = BNDivideHelper(&q[j], &r, t, v);
	}
	r >>= shift;	
	return r;
}







/*
*	BNMultiply(uint32_t C[], uint32_t A[], uint32_t B[], uint32_t nSize)
-----------------------------------------------------
*  Multiplication for very big numbers A,B,C
*  Assumes that A, B  have the same size, and C have the size of 2*nSize; 
*  nSize = number of bytes. 
*  Calculates C = A - B where A >= B
*  Reference  Knuth, Donald. 1968. The Art of Computer Programming
*  Returns 0 if success 1 if overflow. 
* v=B 
* u=A
*/

uint32_t MyCryptLib::BNMultiply(uint32_t C[], const uint32_t A[], const uint32_t B[], const uint32_t nSize)
{
	uint32_t  k, tmp[2];
	uint32_t m, n;
	m = n = nSize;
	for ( uint32_t i = 0; i < 2 * m; i++)
		C[i] = 0;

	for ( uint32_t j = 0; j < n; j++)
	{
		if (B[j] == 0) // Zero multiplication ?
		{
			C[j + m] = 0;
		}
		else
		{
			k = 0;
			for (uint32_t i = 0; i < m; i++)
			{
				// Perform t = A[i] * B[i]+C[i+j] + k
				// use Help function for code cleaness. 
				BNMultiplyHelper(tmp, A[i], B[j]);
				tmp[0] += k;
				if (tmp[0] < k) // Overflow? 
					tmp[1]++;
				tmp[0] += C[i+j];
				if (tmp[0] < C[i+j])
					tmp[1]++;
				k = tmp[1];
				C[i+j] = tmp[0];

			}	
			C[j+m] = k;
		}
	}	
	return 0;
}

/*
*	w=u*v where u is an multipresition nr and v is an normal number. 
*/

uint32_t MyCryptLib::BNMultiplydw(uint32_t w[], const uint32_t u[], uint32_t v, uint32_t nSize)
{
	uint32_t k, t[2];
	uint32_t j;
	if (v == 0) 
	{
		for (j = 0; j < nSize; j++)
			w[j] = 0;
		return 0;
	}
	k = 0;
	for (j = 0; j < nSize; j++)
	{
		BNMultiplyHelper(t, u[j], v);
		w[j] = t[0] + k;
		if (w[j] < k) // Overflow ? 
			t[1]++;
		k = t[1];
	}
	return k;	
}

/*
* Compute w = w - qv
* where w = (WnW[n-1]...W[0])
*  return modified Wn.
*/
inline uint32_t MyCryptLib::BNMultSub(uint32_t wn, uint32_t w[], const uint32_t v[], uint32_t q, uint32_t n)
{
	uint32_t k, t[2];
	uint32_t i;

	if ( q == 0 )	// Nothing to do 
		return wn;

	k = 0;

	for (i = 0; i < n; i++)
	{
		BNMultiplyHelper(t, q, v[i]);
		w[i] -= k;
		if (w[i] > _MAXIMUMNR_ - k)
			k = 1;
		else
			k = 0;
		w[i] -= t[0];
		if (w[i] > _MAXIMUMNR_ - t[0])
			k++;
		k += t[1];
	}

	// Cope with Wn not stored in array w[0..n-1] 
	wn -= k;

	return wn;	
}


/*
*	 Function Helper for numeric Multiplication 
*   Reference: Arbitrary Precision Computation
*	 http://numbers.computation.free.fr/Constants/constants.html
*   Splits the x,y to half and performin the multplication of each half. 
*/
inline int MyCryptLib::BNMultiplyHelper(uint32_t p[2], const uint32_t x, const uint32_t y)
{
#ifdef _USEOPTIMIZEASM_
	__asm
	{
		mov eax, x
			xor edx, edx
			mul y
			; Product in edx:eax
			mov ebx, p
			mov uint32_t ptr [ebx], eax
			mov uint32_t ptr [ebx+4], edx
	}
#else 
	uint32_t x0, y0, x1, y1;
	uint32_t t, u, carry;
	x0 = LOHALF(x);
	x1 = HIHALF(x);
	y0 = LOHALF(y);
	y1 = HIHALF(y);
	p[0] = x0 * y0;
	t = x0 * y1;
	u = x1 * y0;
	t += u;
	if (t < u)
		carry = 1;
	else
		carry = 0;
	carry = TOHIGH(carry) + HIHALF(t);
	t = TOHIGH(t);
	p[0] += t;
	if (p[0] < t)
		carry++;
	p[1] = x1 * y1;
	p[1] += carry;

#endif
	return 0;
}
/*	
*  Function Helper 
* Compute uu = uu - q(v1v0) 
* 
*/
inline void MyCryptLib::BNMultSubHelper(uint32_t uu[], uint32_t qhat, uint32_t v1, uint32_t v0)
{
	uint32_t p0, p1, t;
	p0 = qhat * v0;
	p1 = qhat * v1;
	t = p0 + TOHIGH(LOHALF(p1));
	uu[0] -= t;
	if (uu[0] > _MAXIMUMNR_ - t)
		uu[1]--;	// Borrow
	uu[1] -= HIHALF(p1);

}
/*	Help function for BNDivide (For code cleaness) 
* Returns true if Qhat is too big
* i.e. if (Qhat * Vn-2) > (b.Rhat + Uj+n-2)
* 
*/

inline int MyCryptLib::BNQhatTooBigHelper(uint32_t qhat, uint32_t rhat, uint32_t vn2, uint32_t ujn2)
{
	uint32_t t[2];
	BNMultiplyHelper(t, qhat, vn2);
	if ( t[1] < rhat )
		return 0;
	else if ( t[1] > rhat )
		return 1;
	else if ( t[0] > ujn2 )
		return 1;
	return 0;	
}


/*
*	Function Helper for numeric Multiplication 
*  Computes quotient q = u / v, remainder r = u mod v
*  u an uint32_t[2].
*  v,q,r are normal uint32_ts. 
*  Assumes that v1>=b/2 where b is the size of half uint32_t
*
*/

inline uint32_t MyCryptLib::BNDivideHelper(uint32_t *q, uint32_t *r, const uint32_t u[], uint32_t v)
{
	uint32_t q2;
	uint32_t qhat, rhat, t, v0, v1, u0, u1, u2, u3;
	uint32_t uu[2];
	uint32_t B= _MAXHALFNR_+1;

	if (!(v & _HIBITMASK_))
	{	
		*q = *r = 0;
		return _MAXIMUMNR_;
	}

	v0 = LOHALF(v);
	v1 = HIHALF(v);
	u0 = LOHALF(u[0]);
	u1 = HIHALF(u[0]);
	u2 = LOHALF(u[1]);
	u3 = HIHALF(u[1]);
	qhat = (u3 < v1 ? 0 : 1);
	if (qhat > 0)
	{
		rhat = u3 - v1;
		t = TOHIGH(rhat) | u2;
		if (v0 > t)
			qhat--;
	}
	uu[0] = u[1];
	uu[1] = 0;		
	if (qhat > 0)
	{

		BNMultSubHelper(uu, qhat, v1, v0);
		if (HIHALF(uu[1]) != 0)
		{
			uu[0] += v;
			uu[1] = 0;
			qhat--;
		}
	}
	q2 = qhat;
	t = uu[0];
	qhat = t / v1;
	rhat = t - qhat * v1;
	t = TOHIGH(rhat) | u1;
	if ( (qhat == B) || (qhat * v0 > t) )
	{
		qhat--;
		rhat += v1;
		t = TOHIGH(rhat) | u1;
		if ((rhat < B) && (qhat * v0 > t))
			qhat--;
	}
	uu[1] = HIHALF(uu[0]);	
	uu[0] = TOHIGH(LOHALF(uu[0])) | u1;	
	BNMultSubHelper(uu, qhat, v1, v0);
	if ( HIHALF(uu[1]) != 0 )
	{	
		qhat--;
		uu[0] += v;
		uu[1] = 0;
	}
	*q = TOHIGH(qhat);
	t = uu[0];
	qhat = t / v1;
	rhat = t - qhat * v1;
	t = TOHIGH(rhat) | u0;
	if ( (qhat == B) || (qhat * v0 > t) )
	{
		qhat--;
		rhat += v1;
		t = TOHIGH(rhat) | u0;
		if ((rhat < B) && (qhat * v0 > t))
			qhat--;
	}
	uu[1] = HIHALF(uu[0]);
	uu[0] = TOHIGH(LOHALF(uu[0])) | u0;	
	BNMultSubHelper(uu, qhat, v1, v0);
	if (HIHALF(uu[1]) != 0)
	{	
		qhat--;
		uu[0] += v;
		uu[1] = 0;
	}
	*q |= LOHALF(qhat);
	*r = uu[0];
	return q2;
}


/*
*	BNDivide(uint32_t q[], uint32_t r[], const uint32_t u[], uint32_t usize, uint32_t v[], uint32_t vsize)
-----------------------------------------------------
*  Division for very big numbers 
*
* Computes quotient q = u / v and remainder r = u mod v
* where q, r, u are multiple precision digits
* all of udigits and the divisor v is vdigits.
*/
int MyCryptLib::BNDivide(uint32_t q[], uint32_t r[], const uint32_t u[], uint32_t usize, uint32_t v[], uint32_t vsize)
{
	uint32_t shift;
	int n, m, j;
	uint32_t bitmask, overflow;
	uint32_t qhat, rhat, t[2];
	uint32_t *uu, *ww;
	int qhatOK, cmp;
	BNSetZero(q, usize);
	BNSetZero(r, usize);

	//  Work out exact sizes of u and v 
	n = (int)BNSizeof(v, vsize);
	m = (int)BNSizeof(u, usize);
	m -= n;

	// special cases 
	if ( n == 0 )
		return -1;	// divide by zero

	if ( n == 1 )
	{	// Short div is better 
		r[0] = BNDividedw(q, u, v[0], usize);
		return 0;
	}

	if ( m < 0 )
	{   // set r=u
		BNSetEqual(r, u, usize);
		return 0;
	}

	if ( m == 0 )
	{
		cmp = BNCompare(u, v, (uint32_t)n);
		if (cmp < 0)
		{
			BNSetEqual(r, u, usize);
			return 0;
		}
		else if (cmp == 0)
		{
			BNSetEqualdw(q, 1, usize);
			return 0;
		}
	}

	bitmask =  _HIBITMASK_;
	for ( shift = 0; shift < 32; shift++ )
	{
		if (v[n-1] & bitmask)
			break;
		bitmask >>= 1;
	}

	overflow = BNShiftLeft(v, v, shift, n);
	overflow = BNShiftLeft(r, u, shift, n + m);
	t[0] = overflow;	
	uu = r;	
	for ( j = m; j >= 0; j-- )
	{
		qhatOK = 0;
		t[1] = t[0];
		t[0] = uu[j+n-1];
		overflow = BNDivideHelper(&qhat, &rhat, t, v[n-1]);
		if ( overflow )
		{	
			rhat = uu[j+n-1];
			rhat += v[n-1];
			qhat = _MAXIMUMNR_;
			if (rhat < v[n-1])	
				qhatOK = 1;
		}
		if (qhat && !qhatOK && BNQhatTooBigHelper(qhat, rhat, v[n-2], uu[j+n-2]))
		{	
			rhat += v[n-1];
			qhat--;
			if (!(rhat < v[n-1]))
				if (BNQhatTooBigHelper(qhat, rhat, v[n-2], uu[j+n-2]))
					qhat--;
		}
		ww = &uu[j];
		overflow = BNMultSub(t[1], ww, v, qhat, (uint32_t)n);
		q[j] = qhat;
		if (overflow)
		{	
			q[j]--;
			overflow = BNAdd(ww, ww, v, (uint32_t)n);
		}
		t[0] = uu[j+n-1];	
	}	
	for (j = n; j < m+n; j++)
		uu[j] = 0;
	BNShiftRight(r, r, shift, n);
	BNShiftRight(v, v, shift, n);
	return 0;
}

inline uint32_t MyCryptLib::BNModdw(uint32_t a[], uint32_t d, uint32_t nSize)
{
	uint32_t *q=NULL;
	uint32_t r = 0;
	// allocate temporary ultiprecision integer of nSize*2. 
	q = BNAlloc(nSize * 2);
	if(q!=NULL)
	{
		r = BNDividedw(q, a, d, nSize);
		BNFree(&q);
	}
	return r;
}

/*	
* BNMod(uint32_t r[], const uint32_t u[], uint32_t nUSize, uint32_t v[], uint32_t nVSize)
* Computes r = u mod v
* where r, v are multiprecision integers of length vdigits
* and u is a multiprecision integer of length udigits.
* r may overlap v.
*/

uint32_t MyCryptLib::BNMod(uint32_t r[], const uint32_t u[], uint32_t nUSize, uint32_t v[], uint32_t nVSize)
{
	uint32_t *qq, *rr;
	uint32_t nn = max(nUSize, nVSize);
	qq = BNAlloc(nUSize);
	rr = BNAlloc(nn);

	// rr[nn] = u mod v 
	BNDivide(qq, rr, u, nUSize, v, nVSize);
	// r=rr
	BNSetEqual(r, rr, nVSize);
	BNFree(&rr);
	BNFree(&qq);
	return 0;
}


/*	Computes a = (x * y) mod m */
uint32_t MyCryptLib::BNModMult(uint32_t a[], const uint32_t x[], const uint32_t y[], const uint32_t m[], uint32_t nSize)
{
	uint32_t *p;
	uint32_t *tm;
	p = BNAlloc(nSize * 2);
	tm = BNAlloc(nSize);
	BNSetEqual(tm, m, nSize);
	BNMultiply(p, x, y, nSize);
	BNMod(a, p, nSize * 2, tm, nSize);
	BNFree(&p);
	BNFree(&tm);
	return 0;	
}




/* BNSizeof(const uint32_t A[], uint32_t nSize)
*
* Returns size of significant digits in A.
*/

uint32_t MyCryptLib::BNSizeof(const uint32_t A[], uint32_t nSize)
{
	while ( nSize-- )
	{
		if ( A[nSize] != 0 )
			return (++nSize);
	}
	return 0;
}


// Returns number of significant bits in d 
uint32_t MyCryptLib::BNBitLength(const uint32_t *d, uint32_t nSize)
{
	uint32_t n, i, bits;
	uint32_t mask;

	// be Safe 
	if ( !d || nSize == 0 )
		return 0;

	// Get The size of it 
	n = BNSizeof(d, nSize);
	if (0 == n) return 0;

	uint32_t dwLastWord= d[n-1];
	uint32_t dwDummY=0;
	mask =_HIBITMASK_;
	for (i = 0; mask > 0;i++)
	{
		if (dwLastWord & mask)
			break;
		mask >>= 1;
	}

	bits = n * (sizeof(uint32_t)*8) - i;

	return bits;
}

/*
*	Alloc and free is made inside the class for future optimization 
*  e.g reusing allocated memory etc.. 
*/

inline uint32_t * MyCryptLib::BNAlloc(uint32_t nSize)
{
	uint32_t* p=NULL;
	if(nSize<=0)
		return NULL;

	p=(uint32_t*)calloc(nSize, sizeof(uint32_t));
	return p; 
}

inline void MyCryptLib::BNFree(uint32_t **p)
{
	if (*p!=NULL)
	{
		free(*p);
		*p = NULL;
	}
}


/* 
* Creates an Big (multiprecision) Number from an nOctBytes octects array
* Returns actual number of digits set. 
* 
* This funcion is normaly used to import data from other sources (for test porpose) 
* 
*/
uint32_t MyCryptLib::BNFromOctets(uint32_t a[], uint32_t nSize, const unsigned char *c, uint32_t nOctBytes)
{
	uint32_t i;
	int j, k;
	uint32_t t;
	uint32_t t2;
	BNSetZero(a, nSize);

	/* Read in octets, least significant first */
	/* i counts into big_d, j along c, and k is # bits to shift */
	for (i = 0, j = nOctBytes - 1; (i < nSize)&&(j >= 0); i++)
	{
		t = 0;
		for (k = 0; (j >= 0) && (k < (sizeof(uint32_t)*8)); j--, k += 8)
		{
			t2=((uint32_t)c[j]);
			t |= t2 << k;
		}
		a[i] = t;
	}

	return i;
}

/*
* Convert an big Number a into an array of octets, in big-endian order,
* padding to nbytes or truncating if necessary.
* Return number of octets required excluding leading zero bytes.
*/

uint32_t MyCryptLib::BNToOctets(const uint32_t a[], uint32_t nSize, unsigned char *c, uint32_t nbytes)
{
	int j, k, len;
	uint32_t t;
	uint32_t i, noctets, nbits;

	nbits = BNBitLength(a, nSize);
	noctets = (nbits + 7) / 8;

	len = (int)nbytes;

	for (i = 0, j = len - 1; i < nSize && j >= 0; i++)
	{
		t = a[i];
		for (k = 0; j >= 0 && k < (sizeof(uint32_t)*8); j--, k += 8)
			c[j] = (unsigned char)(t >> k);
	}

	for ( ; j >= 0; j--)
		c[j] = 0;

	return noctets;	
}



uint32_t MyCryptLib::BNFromDecimal(uint32_t a[], uint32_t nSize, const char *s,uint32_t nStringLength)
{


	BNSetZero(a, nSize);
	//  Create some temp storage for int values.
	uint32_t newlen = BNUiceil(nStringLength * 0.41524);	// log(10)/log(256)=0.41524 
	uint8_t* ptmp=NULL;
	ptmp=new uint8_t[newlen];

	memset(ptmp,0,newlen);
	if (ptmp==NULL) 
		return 0; //FAILED 

	// Go through zero-terminated string
	uint32_t t=0;
	for (uint32_t i = 0; s[i]; i++)
	{
		t = s[i] - '0';
		if (t > 9 || t < 0) continue;
		for (uint32_t j = newlen; j > 0; j--)
		{
			t += (uint32_t)(ptmp[j-1] * 10);
			ptmp[j-1] = (unsigned char)(t & 0xFF);
			t >>= 8;
		}
	}

	// now Convert bytes to big digits 
	uint32_t AcctualNumberofbytes = BNFromOctets(a, nSize, ptmp, newlen);

	// Clean up 
	delete[] ptmp;

	return AcctualNumberofbytes;
}

uint32_t MyCryptLib::BNFromHex(uint32_t a[], uint32_t nSize, const char *s, uint32_t nStringLength)
{

	size_t newlen;
	uint8_t  *newdigits;
	size_t n;
	uint32_t t;
	size_t i, j;

	BNSetZero(a, nSize);

	// temporary 
	n = strlen(s);
	newlen = BNUiceil(n * 0.5);	// log(16)/log(256)=0.5 
	newdigits = new uint8_t[newlen];

	if (newdigits==NULL)
		return 0; 

	memset(newdigits,0,newlen);
	// Work through zero-terminated string 
	for ( i = 0; s[i]; i++ )
	{
		t = s[i];
		if ((t >= '0') && (t <= '9')) t = (t - '0');
		else if ((t >= 'a') && (t <= 'f')) t = (t - 'a' + 10);
		else if ((t >= 'A') && (t <= 'F')) t = (t - 'A' + 10);
		else continue;
		for (j = newlen; j > 0; j--)
		{
			t += (uint32_t)newdigits[j-1] << 4;
			newdigits[j-1] = (unsigned char)(t & 0xFF);
			t >>= 8;
		}
	}

	// Convert bytes to big digits 
	n = BNFromOctets(a, nSize, newdigits, (uint32_t)newlen);

	// Clean up 
	delete[] newdigits;

	return (uint32_t)n;


}


/*	Computes y = x^e mod m */
/*	Binary left-to-right method */
int MyCryptLib::BNModExp(uint32_t yout[], const uint32_t x[], const uint32_t e[], const uint32_t m[], uint32_t nSize)
{
	// Be safe
	if ( nSize <= 0 ) 
		return -1;

	uint32_t mask;
	uint32_t n;
	uint32_t *t1, *t2, *t3, *tm, *y; //temporary variables 

	// Create some temporary variables
	const uint32_t nn = nSize * 2;

	t1 = BNAlloc(nn);
	if(t1==NULL)
	{
		return -1;
	}
	t2 = BNAlloc(nn);
	if(t2==NULL)
	{
		BNFree(&t1);
		return -1;
	}
	t3 = BNAlloc(nn);
	if(t3==NULL)
	{
		BNFree(&t1);
		BNFree(&t2);
		return -1;
	}
	tm = BNAlloc(nSize);
	if(tm==NULL)
	{
		BNFree(&t1);
		BNFree(&t2);
		BNFree(&t3);
		return -1;
	}
	y = BNAlloc(nSize);
	if(y==NULL)
	{
		BNFree(&t1);
		BNFree(&t2);
		BNFree(&t3);
		BNFree(&tm);
		return -1;
	}

	BNSetEqual(tm, m, nSize);

	//  Find second-most significant bit in e 
	n = BNSizeof(e, nSize);
	for (mask = _HIBITMASK_; mask > 0; mask >>= 1)
	{
		if (e[n-1] & mask)
			break;
	}

	// next bitmask 
	if ( mask==1 )
	{
		mask=_HIBITMASK_;
		n--;
	}else
		mask >>=1; 

	BNSetEqual(y, x, nSize);

	while ( n )
	{

		BNModSquareTmp(y, y, tm, nSize, t1, t2, t3);	
		if (mask & e[n-1])
			BNMultTmp(y, y, x, tm, nSize, t1, t2, t3);

		// Move to next bit
		// next bitmask 
		if ( mask==1 )
		{
			mask=_HIBITMASK_;
			n--;
		}else
			mask >>=1; 
	}

	BNSetEqual(yout, y, nSize);

	BNFree(&t1);
	BNFree(&t2);
	BNFree(&t3);
	BNFree(&tm);
	BNFree(&y);
	return 0;
}
// helper function for code cleannesss. 
inline int MyCryptLib::BNMultTmp(uint32_t a[], const uint32_t x[], const uint32_t y[], uint32_t m[], uint32_t nSize, uint32_t temp[], uint32_t tqq[], uint32_t trr[])
{
	BNMultiply(temp, x, y, nSize);
	BNModuloTmp(a, temp, nSize * 2, m, nSize, tqq, trr);
	return 0; 
}

inline int MyCryptLib::BNModuloTmp(uint32_t r[], const uint32_t u[], uint32_t nUSize, uint32_t v[], uint32_t nVSize, uint32_t tqq[], uint32_t trr[])
{
	BNDivide(tqq, trr, u, nUSize, v, nVSize);
	BNSetEqual(r, trr, nVSize);	
	return 0;
}

inline int MyCryptLib::BNModSquareTmp(uint32_t a[], const uint32_t x[], uint32_t m[], uint32_t nSize, uint32_t temp[], uint32_t tqq[], uint32_t trr[])
{
	//x*x
	BNSquare(temp, x, nSize);

	// Then modulo m
	BNModuloTmp(a, temp, nSize * 2, m, nSize, tqq, trr);
	return 0;
}


/*	
* Computes sw = x * x
* where:
* 	x is a Big multiprecision Number
*	w is a Big multiprecision Number of 2*nSize
*	nSize is the size of the number in bytes. 
*/

inline int MyCryptLib::BNSquare(uint32_t w[], const uint32_t x[], uint32_t nSize)
{
	uint32_t k, p[2], u[2], cbit, carry;
	uint32_t i, j, t, i2, cpos;
	t = nSize;

	i2 = t << 1;

	for (i = 0; i < i2; i++)
		w[i] = 0;

	carry = 0;
	cpos = i2-1;

	for (i = 0; i < t; i++)
	{

		i2 = i << 1; 
		BNMultiplyHelper(p, x[i], x[i]);
		p[0] += w[i2];

		if (p[0] < w[i2])
			p[1]++;
		k = 0;	
		if ( i2 == cpos && carry )
		{
			p[1] += carry;
			if (p[1] < carry)
				k++;
			carry = 0;
		}

		u[0] = p[1];
		u[1] = k;
		w[i2] = p[0];

		k = 0;
		for ( j = i+1; j < t; j++ )
		{
			BNMultiplyHelper(p, x[j], x[i]);
			cbit = (p[0] & _HIBITMASK_) != 0;
			k =  (p[1] & _HIBITMASK_) != 0;
			p[0] <<= 1;
			p[1] <<= 1;
			p[1] |= cbit;

			p[0] += u[0];
			if (p[0] < u[0])
			{
				p[1]++;
				if (p[1] == 0)
					k++;
			}
			p[1] += u[1];
			if (p[1] < u[1])
				k++;

			p[0] += w[i+j];
			if (p[0] < w[i+j])
			{
				p[1]++;
				if (p[1] == 0)
					k++;
			}
			if ((i+j) == cpos && carry)
			{
				p[1] += carry;
				if (p[1] < carry)
					k++;
				carry = 0;
			}
			u[0] = p[1];
			u[1] = k;
			w[i+j] = p[0];
		}

		carry = u[1];
		w[i+t] = u[0];
		cpos = i+t;
	}	
	return 0;
}

//	Computes inv = u^(-1) mod v 
//  This function is not 100% correct, I have to check it later. 
int MyCryptLib::BNModInv(uint32_t inv[], const uint32_t u[], const uint32_t v[], uint32_t nSize)
{
	uint32_t *u1, *u3, *v1, *v3, *t1, *t3, *q, *w;
	u1=u3=v1=v3=t1=t3=q=w=NULL;
	int bIterations;
	int result;

	// Allocate temp storage
	u1 = BNAlloc(nSize);
	if ( u1==NULL )
	{
		return -1;
	}
	u3 = BNAlloc(nSize);
	if ( u3==NULL )
	{
		BNFree(&u1);
		return -1;
	}
	v1 = BNAlloc(nSize);
	if ( v1==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		return -1;
	}
	v3 = BNAlloc(nSize);
	if ( v3==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		BNFree(&v1);
		return -1;
	}


	t1 = BNAlloc(nSize);

	if ( t1==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		BNFree(&v1);
		BNFree(&v3);
		return -1;
	}

	t3 = BNAlloc(nSize);
	if ( t3==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		BNFree(&v1);
		BNFree(&v3);
		BNFree(&t1);
		return -1;
	}

	q  = BNAlloc(nSize);
	if ( q==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		BNFree(&v1);
		BNFree(&v3);
		BNFree(&t1);
		BNFree(&t3);
		return -1;
	}
	w  = BNAlloc(2 * nSize);
	if ( w==NULL )
	{
		BNFree(&u1);
		BNFree(&u3);
		BNFree(&v1);
		BNFree(&v3);
		BNFree(&t1);
		BNFree(&t3);
		BNFree(&q);
		return -1;
	}

	// Init 
	BNSetEqualdw(u1, 1, nSize);		 // u1 = 1 

	BNSetEqual(u3, u, nSize);		 // u3 = u 
	BNSetZero(v1, nSize);			 // v1 = 0 
	BNSetEqual(v3, v, nSize);		 // v3 = v 

	bIterations = 1;	
	while ( !BNIsZero(v3, nSize) )		
	{					
		BNDivide(q, t3, u3, nSize, v3, nSize);

		BNMultiply(w, q, v1, nSize);	

		// what if the real sizeof(w+u1)> nSize ???
		//ASSERT(BNSizeof(w,nSize*2)>nSize);

		BNAdd(t1, u1, w, nSize);		

		// Swap 
		BNSetEqual(u1, v1, nSize);
		BNSetEqual(v1, t1, nSize);
		BNSetEqual(u3, v3, nSize);
		BNSetEqual(v3, t3, nSize);
		bIterations = -bIterations;
	}

	if (bIterations < 0)
		BNSubtract(inv, v, u1, nSize);	
	else
		BNSetEqual(inv, u1, nSize);	


	if (BNComparedw(u3, 1, nSize) != 0)
	{
		result = 1;
		BNSetZero(inv, nSize);
	}
	else
		result = 0;

	// Free the memory 
	BNSetZero(u1, nSize);
	BNSetZero(v1, nSize);
	BNSetZero(t1, nSize);
	BNSetZero(u3, nSize);
	BNSetZero(v3, nSize);
	BNSetZero(t3, nSize);
	BNSetZero(q, nSize);
	BNSetZero(w, 2*nSize);
	BNFree(&u1);
	BNFree(&v1);
	BNFree(&t1);
	BNFree(&u3);
	BNFree(&v3);
	BNFree(&t3);
	BNFree(&q);
	BNFree(&w);
	return 0;

}

int MyCryptLib::BNGcd(uint32_t g[], const uint32_t x[], const uint32_t y[], uint32_t nSize)
{
	uint32_t *yy, *xx;	
	yy = BNAlloc(nSize);

	if( yy==NULL )
		return -1;

	xx = BNAlloc(nSize);

	if( xx==NULL )
	{
		BNFree(&yy);
		return -1;
	}

	BNSetZero(yy, nSize);
	BNSetZero(xx, nSize);
	BNSetEqual(xx, x, nSize);
	BNSetEqual(yy, y, nSize);
	BNSetEqual(g, yy, nSize);		

	while ( !BNIsZero(xx, nSize) )	
	{
		BNSetEqual(g, xx, nSize);
		BNMod(xx, yy, nSize, xx, nSize);	
		BNSetEqual(yy, g, nSize);	
	}
	BNSetZero(xx, nSize);
	BNSetZero(yy, nSize);
	BNFree(&xx);
	BNFree(&yy);

	return 0;	// gcd = g 
}


/*	Returns true if w is a probable prime using the
*  Rabin-Miller Probabilistic Primality Test.
*  Carries out t iterations specified by user.
*
* DSS Standard recommends using t >= 50
* Ferguson & Schneier recommend t = 64 for prob error < 2^-128
* In practice, most random composites are caught in the first
* round or two and so specifying a large t will only affect
* the final check.
*
*/


int MyCryptLib::BNRabinMiller(const uint32_t w[], uint32_t nSize, uint32_t t)
{

	uint32_t *m, *a, *b, *z, *w1, *j;
	uint32_t maxrand;
	int failed;
	int32_t bisprime;
	uint32_t i;

	// Catch w <= 1 
	if (BNComparedw(w, 1, nSize) <= 0) 
		return 0;

	// Allocate temp storage..

	m = BNAlloc(nSize);
	if ( m== NULL ) 
	{
		return 0;
	}
	a = BNAlloc(nSize);
	if ( a==NULL )  
	{
		BNFree(&m);
		return 0;
	}
	b = BNAlloc(nSize);
	if ( b==NULL ) 
	{
		BNFree(&m);
		BNFree(&a);
		return 0;
	}
	z = BNAlloc(nSize);
	if ( z==NULL ) 
	{
		BNFree(&m);
		BNFree(&a);
		BNFree(&b);
		return 0;
	}
	w1 = BNAlloc(nSize);
	if ( w1==NULL ) 
	{
		BNFree(&m);
		BNFree(&a);
		BNFree(&b);
		BNFree(&z);
		return 0;
	}
	j = BNAlloc(nSize);
	if ( j==NULL ) 
	{
		BNFree(&m);
		BNFree(&a);
		BNFree(&b);
		BNFree(&z);
		BNFree(&w1);
		return 0;
	}

	// Rabin-Miller from FIPS-186-2 Appendix 2. 
	// Step 1. Set i = 1 [but do # tests requested by user].
	// Step 2. Find a and m where w = 1 + (2^a)m
	//	m is odd and 2^a is largest power of 2 dividing w - 1 

	BNSubtractdw(w1, w, 1, nSize);	
	BNSetEqual(m, w1, nSize);		

	for (BNSetZero(a, nSize); (!(m[0]&0x1));  BNAdddw(a, a, 1, nSize))
	{
		BNShiftRight(m, m, 1, nSize);
	}

	if ( BNSizeof(w, nSize) == 1 )
		maxrand = w[0] - 1;
	else
		maxrand = _MAXIMUMNR_;

	bisprime = 1;
	for (i = 0; i < t; i++)
	{
		failed = 1;
		//  Step 3. Generate random integer b, 1 < b < w 
		BNSetZero(b, nSize);
		do
		{
			b[0] = RandBetween(2, maxrand);
		} while (BNCompare(b, w, nSize) >= 0);


		// Step 4. Set j = 0 and z = b^m mod w 
		BNSetZero(j, nSize);
		BNModExp(z, b, m, w, nSize);
		do
		{
			// Step 5. If j = 0 and z = 1, or if z = w - 1 */
			if ((BNIsZero(j, nSize) && BNComparedw(z, 1, nSize) == 0) || (BNCompare(z, w1, nSize) == 0))
			{	// Passes on this loop  - go to Step 9 
				failed = 0;
				break;
			}

			// Step 6. If j > 0 and z = 1 */
			if ( !BNIsZero(j, nSize) && (BNComparedw(z, 1, nSize) == 0) )
			{	// Fails - go to Step 8 
				failed = 1;
				break;
			}

			//  Step 7. j = j + 1. If j < a set z = z^2 mod w 
			BNAdddw(j, j, 1, nSize);
			if ( BNCompare(j, a, nSize) < 0 )
				BNModMult(z, z, z, w, nSize);

			// if j < a go to Step 5 
		} while (BNCompare(j, a, nSize) < 0);

		if ( failed )
		{	// Step 8. Not a prime. 
			bisprime = 0;
			break;
		}
	}	

	BNSetZero(m, nSize);
	BNSetZero(a, nSize);
	BNSetZero(b, nSize);
	BNSetZero(z, nSize);
	BNSetZero(w1, nSize);
	BNSetZero(j, nSize);
	BNFree(&m);
	BNFree(&a);
	BNFree(&b);
	BNFree(&z);
	BNFree(&w1);
	BNFree(&j);	
	return bisprime;
}



/* The Mersenne Twister Random generator init
* The function inits the Random generator with pRandomPool and nSize 
* If the pRandomPool is not provided it uses the old dangerus srand() and rand() to
* init. 
*/
inline bool MyCryptLib::MTInit(uint8_t *pRandomPool, uint32_t nSize)
{
	// If no Random pool is given use the Function MTCollectEntropy to 
	// get entopry from the HW (see the MTCollectEntropy) function. The acctual 
	// entropy we get is less than ~128 bits. It's a good idea to have a tenth 
	// to a fifth as much entropy as the length of the key othervise it 
	// is very dangerous. But hey FBI & CIA is no after oss right ? :=)
	if ( pRandomPool==NULL || nSize<624*4 ) 
	{
		if ( nSize>0&&pRandomPool )
		{
			memcpy(&m_mtbuffer,pRandomPool,nSize);	  
		}

		// If entropy is not given collect from HW. 
		if ( nSize<624*4 )
		{
			uint8_t *pmtbuffer=(uint8_t*)&m_mtbuffer;
			MTCollectEntropy(pmtbuffer+nSize,624*4-nSize);	
		}		

		m_bSeeded=true;
	}
	m_mtIndex=624; // Start with performin the shuffel so the randomness is spread around. 
	return m_bSeeded;
}

/*
* MTCollectEntropy(uint8_t *pRandomPool, uint32_t nSize)
*
* This function collects entropy (true randomness) from the Hardware
* Using different source namely: 
*  
* - System time 
* - Current process ID
* - Current thread ID 
* - Get clock ticks since system booted
* - The nr pages and memory allockated. 
*
* The entropies above are destilled to with SHA1 hash function to fill the 
* pRadomPool of size nSize. 
* 
* Observe! Warning!  
* - This function gives approximatly ~128 bit entropy destilled into
*   pRandomPool with nSize. 
* - The last 20 bytes may hold more entropie than the other in pRandomPool, Additional
*   destilling is needed.
*/
bool MyCryptLib::MTCollectEntropy(uint8_t *pRandomPool, uint32_t nSize)
{
// 	SYSTEMTIME st;
// 	FILETIME ft;
// 	MEMORYSTATUS ms;
	SHA1_STATETYPE csha1;
	uint32_t nCollected = 0; 
	uint8_t EntropyBucket[SHA1_DIGEST_SIZE];
	uint8_t *pEntropyBucket=(uint8_t*)EntropyBucket;
	uint32_t dwRes=0;
	uint32_t dwTick=0;
	//ms.dwLength = sizeof(MEMORYSTATUS);
	memset(&csha1,0,sizeof(csha1));
	SHA1_Start(&csha1);

	while ( nSize-nCollected>0 )
	{	
		// Hash the previus entropy Bucket..
		SHA1_Hash(pEntropyBucket,SHA1_DIGEST_SIZE,&csha1);

		// Destill The process ID
// 		dwRes=GetCurrentProcessId();
// 		SHA1_Hash((uint8_t*)&dwRes,sizeof(uint32_t),&csha1);
// 
// 		// Destill The thread ID	
// 		dwRes=GetCurrentThreadId();
// 		SHA1_Hash((uint8_t*)&dwRes,sizeof(uint32_t),&csha1);
// 
// 		// Destill The system time. 
// 		GetSystemTime(&st);
// 		SystemTimeToFileTime(&st, &ft);
// 		SHA1_Hash((uint8_t*)&ft,sizeof(FILETIME),&csha1);
// 
// 		// Destill The processors tickcount. 
// 		dwTick = GetTickCount();
// 		SHA1_Hash((uint8_t*)&dwTick,sizeof(uint32_t),&csha1);
// 
// 		// Destill The memory allocated
// 		GlobalMemoryStatus(&ms);
// 		SHA1_Hash((uint8_t*)&ms, sizeof(MEMORYSTATUS),&csha1);
// 
// 		// Put it inside the Bucket. 
 		SHA1_Finish(EntropyBucket,&csha1);

		// Copy the Entropy to the pool
		if ( nSize-nCollected<SHA1_DIGEST_SIZE )
		{
			memcpy(pRandomPool+nCollected,pEntropyBucket,nSize-nCollected);
			nCollected+=nSize-nCollected;
		}
		else
		{
			memcpy(pRandomPool+nCollected,pEntropyBucket,SHA1_DIGEST_SIZE);
			nCollected+=SHA1_DIGEST_SIZE;
		}
	}
	return true; 
}



/*
*	The Mersenne Twister is a new random number generator, 
*	discovered in 1996 by Matsumora and Nishimura. 
*  MT is a twisted GFSR(624,397), similar in spirit to R250 and R521 but faster. 
*  It takes up more space than R250 or R521, but less than the two combined. 
*	MT has an amazing period of 2^19937-1. Overall, and passes all the statistical tests. 
*  Assumes it is already initciaded. 	
*
* More info () ----------------------------------------
* The Mersenne Twister, a new variant of the twisted GFSR (L"TGFSR") by Matsumoto and Nishimura, 
* sets new standards for the period, quality and speed of random number generators. The incredible 
* period is 219937 - 1, a number with about 6000 decimal digits; the 32-bit random numbers exhibit 
* best possible equidistribution properties in dimensions up to 623; and it's fast, very fast. 
* A paper on the Mersenne Twister has been submitted to ACM TOMACS. 
* 
* The Mersenne Twister generator passes all current statistical tests.
*/
inline uint32_t MyCryptLib::MTRandom()
{
	if( !m_bSeeded )
		MTInit();

	if ( m_mtIndex >= 624 )
	{
		m_mtIndex = 0;
		int i = 0;
		int s;
		for (; i < 624 - 397; i++) {
			s = (m_mtbuffer[i] & 0x80000000) | (m_mtbuffer[i+1] & 0x7FFFFFFF);
			m_mtbuffer[i] = m_mtbuffer[i + 397] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
		}
		for (; i < 623; i++) {
			s = (m_mtbuffer[i] & 0x80000000) | (m_mtbuffer[i+1] & 0x7FFFFFFF);
			m_mtbuffer[i] = m_mtbuffer[i - (624 - 397)] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
		}

		s = (m_mtbuffer[623] & 0x80000000) | (m_mtbuffer[0] & 0x7FFFFFFF);
		m_mtbuffer[623] = m_mtbuffer[396] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
	}
	uint32_t tmp=m_mtbuffer[m_mtIndex++];
	tmp  ^= (tmp >> 11);
	tmp ^= (tmp << 7) & (uint32_t)0x9D2C5680;
	tmp ^= (tmp << 15) & (uint32_t)0xEFC60000;
	return tmp ^ (tmp >> 18);
}
/*
*	Generates an Random nr between dwLower and dwUpper. 
*/
inline uint32_t MyCryptLib::RandBetween(uint32_t dwLower, uint32_t dwUpper)
{

	uint32_t d, range;
	unsigned char *bp;
	int i, nbits;
	uint32_t mask;

	if ( dwUpper <= dwLower ) 
	{
		return dwLower;
	}
	range = dwUpper - dwLower;

	do
	{
		bp = (unsigned char *)&d;
		for (i = 0; i < sizeof(uint32_t); i++)
		{
			bp[i] = uint8_t(MTRandom() & 0xFF);
		}


		mask = _HIBITMASK_;
		for (nbits = sizeof(uint32_t)*8; nbits > 0; nbits--, mask >>= 1)
		{
			if (range & mask)
				break;
		}
		if (nbits < sizeof(uint32_t)*8)
		{
			mask <<= 1;
			mask--;
		}
		else
			mask = _MAXIMUMNR_;

		d &= mask;

	} while (d > range); 

	return (dwLower + d);
}




/*
*	Returns true if w > 2 is a probable prime
*  tryes some small nr primes and then uses 
*	the rabin Miller alghorim to detect the prime nr
*
*  nrRounds denotes the number of rounds to use when determine that 
*  the number is an primenumber or not. 
*/
int MyCryptLib::BNIsPrime(uint32_t W[], uint32_t nSize, uint32_t nrRounds)
{

	// if the number is even then return FALSE;
	if ((!(W[0] & 0x1)))
		return 0;


	// if the number is bigger than the biggest prime nr..
	if (BNComparedw(W, SMALL_PRIMES[_NUMBEROFPRIMES_-1], nSize) > 0)
	{
		for (uint32_t i = 0; i < _NUMBEROFPRIMES_; i++)
		{
			if (BNModdw(W, SMALL_PRIMES[i], nSize) == 0) // if the number contain one of the small primes. 
				return 0;
		}
	}
	else //W < Biggest prime in the list so we are going to check it our self. 
	{	
		for (uint32_t i = 0; i < _NUMBEROFPRIMES_; i++)
		{
			if (BNComparedw(W, SMALL_PRIMES[i], nSize) == 0)
				return 1; // Is an small prime	
		}
		return 0; // Not an prime. 
	}
	// Use Rabin Miller now. 
	return BNRabinMiller(W, nSize, nrRounds);
}

/*
* Creates an prime nr.	
* Return number of signifikant bits if success, -1 if the functions did not sucess. 
* -------------------------------------------------------------------------------------------
* The prime nr is not completly  cryptographically secure because it relies on the   
* Mersenne Twister random generator, and Rabin Miller prime detection algorithm.  
* But if it is propetly seeded it is quite safe (se below).
* ------------------------ 
* The Mersenne Twister, a new variant of the twisted GFSR (L"TGFSR") by Matsumoto and Nishimura, 
* sets new standards for the period, quality and speed of random number generators. The incredible 
* period is 2^(219937 - 1), a number with about 6000 decimal digits; the 32-bit random numbers exhibit 
* best possible equidistribution properties in dimensions up to 623; and it's fast, very fast. 
* A paper on the Mersenne Twister has been submitted to ACM TOMACS. 
* 
* The Mersenne Twister generator passes all current statistical tests.
*/
int MyCryptLib::BNMakePrime(uint32_t p[], uint32_t nSize, uint8_t* pEntropyPool, uint32_t nSizeEntropyPool)
{
	// if entropy is provided use it!
	if ( pEntropyPool )
	{
		MTInit(pEntropyPool,nSizeEntropyPool);
	}

	for ( uint32_t i = 0; i < nSize; i++ )
		p[i] = MTRandom();	

	// Make sure the highest and low bits are set, so we have an nice big odd nr. 
	p[nSize - 1] |= _HIBITMASK_;
	p[0] |= 0x1;

	// Check if prime 
	//  Why 10 rounds ? well
	// DSS Standard recommends using t >= 50
	// Ferguson & Schneier recommend t = 64 for prob error < 2^-128
	// But in practice the moste primes is found in round one or two so 10 is an nice
	// home made nr of rounds. 
	while (!BNIsPrime(p, nSize, 10) )
	{
		// Keep adding 2 until we find a prime 
		BNAdddw(p, p, 2, nSize);

		// Check for overflow 
		if (!(p[nSize - 1] & _HIBITMASK_))
			return -1;	// Failed to find a prime 
	}
	// return nr of significant bits.
	return BNBitLength(p,nSize);
}






/*
* BNMakeRSAPrime(uint32_t p[], uint32_t ee[], uint32_t nSize)
*	
* Return number of signifikant bits if success, -1 if the functions did not sucess. 
* -------------------------------------------------------------------------------------------
* The prime nr is not completly  cryptographically secure because it relies on the   
* Mersenne Twister random generator, and Rabin Miller prime detection algorithm.  
* But if it is propetly seeded it is quite safe (se below).
* ------------------------ 
* The Mersenne Twister, a new variant of the twisted GFSR (L"TGFSR") by Matsumoto and Nishimura, 
* sets new standards for the period, quality and speed of random number generators. The incredible 
* period is 219937 - 1, a number with about 6000 decimal digits; the 32-bit random numbers exhibit 
* best possible equidistribution properties in dimensions up to 623; and it's fast, very fast. 
* A paper on the Mersenne Twister has been submitted to ACM TOMACS. 
* 
* The Mersenne Twister generator passes all current statistical tests.
*
* Important assumptions!:
*  - ee is an Fermat prime nr greater than 2.  
*
*/
int MyCryptLib::BNMakeRSAPrime(uint32_t p[], uint32_t ee, uint32_t nSize,uint32_t nMaximumRetry)
{
	uint32_t nRet=-1; 
	for ( uint32_t i=0; i<nMaximumRetry; i++ )
	{
		nRet=BNMakePrime(p,nSize);
		if(nRet>0&&BNModdw(p, ee,nSize)!=1)
			break;
	}
	return nRet;
}



/*
* Creates an random nr. 	
* 
* OBS!! not cryptographically secure!! why? 
* Well we do some homemade modification to the number. 
* 1) We fill it up to n (n also random) with random numbers  
* 2) We fill the rest with zeros. 
* 3) We mask the number n with an mask. 
*
* why? Because of practical resons, we do not whant numbers near owerflow and underflow.!
*/
uint32_t MyCryptLib::BNMakeRandomNr(uint32_t a[], uint32_t nSize)
{
	uint32_t  i, n, bits;
	uint32_t mask;

	n = (uint32_t)RandBetween(1, nSize);
	for ( i = 0; i < n; i++) 
		a[i] = MTRandom();
	for ( i = n; i < nSize; i++)
		a[i] = 0;
	// Mask it 50% chance 
	bits = (uint32_t)RandBetween(0, 16*sizeof(uint32_t));

	if ( bits != 0 && bits < 8*sizeof(uint32_t) )
	{	
		mask = _HIBITMASK_;
		for (i = 1; i < bits; i++)
		{
			mask |= (mask >> 1);
		}
		mask = ~mask;
		a[n-1] &= mask;
	}
	return n;	
}





/*
* Generates keys used for RSA Encryption/Decryption Algorithm 	
*
* n is the public key modulus..
* e is the public exponent encryption exponent.
* d is the secret exponent or decryption exponent.
* The  private key as a quintuple  (p, q, dP, dQ, and qInv), is used 
* for the Chinese Remainder Theorem (CRT) decryption. 
* The CRT method of decryption is four times faster overall 
* than calculating m = c^d mod n.
* p and q are prime factors of n.
* dP and dQ are known as the CRT exponents.
* qInv is the CRT coefficient. 
* 
* nPSize is the size of the prime nr P 
* nQSize is the size of the prime nr Q
*
* The key length is nPSize+nQSize
*
* nSize is the size of the input variables. 
* 
* Observe! nSize must be big enough (eg nSize>=max(nPSize,nQSize)*2) 
*
* In practice, common choices for e are 3, 17 and 65537 (2^16+1). These are Fermat primes and are chosen 
* because they make the modular exponentiation operation faster. 
* 
* Assumed that e is an primenumber greater than 2. 
*
* pSeedData is an pointer to an Random number pool of size nSeedData.
* This pool is used with the Mersenne Twister random nr generator to 
* if pSeedData is NULL then the Random number pool is seeded with 
* current time  since 1981 and time in ms since the computer started and the
* old srand() rand function. 
* if e is NULL then the the default nr 65537.
*/
int MyCryptLib::RSAGenerateKey(uint32_t n[], uint32_t d[], uint32_t p[], uint32_t q[], uint32_t dP[], uint32_t dQ[], uint32_t qInv[], uint32_t nSize, uint32_t nPSize,uint32_t nQSize,uint32_t e, uint8_t* pSeedData,uint32_t nSeedData)
{

	// Make sure that nSize is big enough 	
	if( nSize<max(nPSize,nQSize)*2 )
		return -30;

	// The operation size of primes. (they are bigger than this nr) 
	uint32_t nPrimeSize=max(nPSize,nQSize);
	// The operation size of public key N. 
	uint32_t nNSize=0; 
	// The operation size of private key D. 
	uint32_t nDSize=0;


	// Create some temporary data. 
	uint32_t *pG=BNAlloc(nSize);
	if ( pG==NULL )
	{
		return -1;
	}

	uint32_t *pP1=BNAlloc(nSize);
	if ( pP1==NULL )
	{
		BNFree(&pG);
		return -2;
	}

	uint32_t *pQ1=BNAlloc(nSize);
	if ( pQ1==NULL )
	{
		BNFree(&pG);
		BNFree(&pP1);
		return -3;
	}

	uint32_t *pPhi=BNAlloc(nSize);
	if ( pPhi==NULL )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		return -4;
	}

	uint32_t *pE=BNAlloc(nSize);
	if ( pE==NULL )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		return -5;
	}	


	if ( pSeedData!=NULL && nSeedData>=0 ) 
		MTInit(pSeedData,nSeedData/2);
	else 
		MTInit();

	int nRet=BNMakeRSAPrime(p,e,nPSize);
	if ( nRet<=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -6;
	}

	if ( pSeedData!=NULL && nSeedData>=0)  
		MTInit(pSeedData+nSeedData/2,nSeedData/2);
	else 
		MTInit();

	nRet=BNMakeRSAPrime(q,e,nQSize);
	if ( nRet<=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -7;
	}

	// Check if the prime nr is ok 
	if ( BNIsEqual(p,q,nPrimeSize) )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -8;
	}


	BNSetEqualdw(pE,e,nSize);

	// If q > p swap p and q so p > q 
	if ( BNCompare(p, q,nPrimeSize) < 1 )
	{	
		BNSetEqual(pG, p,nPrimeSize);
		BNSetEqual(p, q,nPrimeSize);
		BNSetEqual(q, pG,nPrimeSize);
	}


	if ( BNSubtractdw(pP1,p,1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -8;
	}


	if ( BNSubtractdw(pQ1,q,1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -8;
	}

	// Make sure that GCD(p-1,e)!=1 and GCD(q-1,e)!=1 

	BNGcd(pG, pP1, pE,nPrimeSize);

	if ( BNComparedw(pG,1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -9;
	}



	BNGcd(pG, pQ1, pE,nPrimeSize);

	if ( BNComparedw(pG,1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -9;
	}


	// n = pq 
	BNMultiply(n, p, q,nPrimeSize);

	nNSize=BNSizeof(n,nSize);

	if ( BNIsZero(n,nNSize)) 
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -11;
	}
	//
	// d = e^-1 mod (p-1)(q-1) 
	// 

	// pPhi = (p-1)(q-1) 
	BNMultiply(pPhi, pP1, pQ1,nPrimeSize);
	// pPhi have the operation size of nPrimeSize*2<=nSize

	if ( BNIsZero(pPhi,nSize))  
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -11;
	}

	nRet = BNModInv(d, pE, pPhi,nSize);

	nDSize=BNSizeof(d,nSize);


	if ( BNIsZero(d,nDSize) || nRet!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -11;
	}

	// Check ed = 1 mod phi 
	BNSetZero(pG,nSize);
	//BNModMult(pG, pE, d, pPhi,nSize);
	BNModMult(pG, pE, d, pPhi,max(nDSize,nPrimeSize*2));


	if ( BNComparedw(pG,1,nSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -11;
	}

	if ( BNModInv(dP, pE, pP1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -12;
	}

	if ( BNModInv(dQ, pE, pQ1,nPrimeSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -13;
	}

	if ( BNModInv(qInv, q, p,nSize)!=0 )
	{
		BNFree(&pG);
		BNFree(&pP1);
		BNFree(&pQ1);
		BNFree(&pPhi);
		BNFree(&pE);
		return -14;
	}

	BNFree(&pG);
	BNFree(&pP1);
	BNFree(&pQ1);
	BNFree(&pPhi);
	BNFree(&pE);
	return nNSize;	
}

/*
* Encrypts the message m with the public key n and public exp e. 	
* 
* Assumed that c,m,n have the same size. 
*
*/
int MyCryptLib::RSAEncrypt(uint32_t c[], uint32_t m[], uint32_t n[], uint32_t nSize, uint32_t e)
{
	// be Safe 
	if ( !c||!m||!n||nSize<=0 )
		return 0;

	int iRet=0;

	// Create some temporary data. 
	uint32_t *pE=BNAlloc(nSize);
	if ( pE==NULL )
	{
		return -1;
	}
	BNSetEqualdw(pE,e,nSize);
	iRet=RSAEncrypt(c,m,n,pE,nSize);

	if( pE )
		BNFree(&pE);
	return iRet;
}

/*
* Encrypts the message m with the public key n and public exp e. 	
* 
* Assumed that c,m,n have the same size. 
*
*/
int MyCryptLib::RSAEncrypt(uint32_t c[], uint32_t m[], uint32_t n[], uint32_t e[], uint32_t nSize)
{
	// be Safe 
	if ( !c || !m || !n || !e || nSize<=0 )
		return -1;
	return  BNModExp(c, m, e, n,nSize);
}

/*
* Decrypt using the CRT RSA Method. 	
*
* Chinese Remainder Theorem
*
* The  private key as a quintuple  (p, q, dP, dQ, and qInv), is used 
* for the Chinese Remainder Theorem (CRT) decryption. 
* The CRT method of decryption is four times faster overall 
* than calculating m = c^d mod n.
* p and q are prime factors of n.
* dP and dQ are known as the CRT exponents.
* qInv is the CRT coefficient. 
* 
* nSize is the size of the public key n in bits. 
* The size of the Primenumbers is ~nSize/2. 
*
* In practice, common choices for e are 3, 17 and 65537 (2^16+1). These are Fermat primes and are chosen 
* because they make the modular exponentiation operation faster. 
*  
*/
int MyCryptLib::RSADecryptCRT(uint32_t m[],uint32_t c[],uint32_t p[], uint32_t q[], uint32_t dP[], uint32_t dQ[], uint32_t qInv[], uint32_t nSize)
{
	uint32_t dwOverFlow=0;
	// Create some temporary data. 
	uint32_t *pm2=BNAlloc(nSize);
	if ( pm2==NULL )
	{
		return -1;
	}
	uint32_t *ph=BNAlloc(nSize);

	if ( ph==NULL )
	{
		BNFree(&pm2);
		return -2;
	}

	uint32_t *phq=BNAlloc(nSize);

	if ( phq==NULL )
	{
		BNFree(&pm2);
		BNFree(&ph);
		return -3;
	}

	// Clear the temporary variables.
	BNSetZero(pm2,nSize);
	BNSetZero(ph,nSize);
	BNSetZero(phq,nSize);


	// Let m_1 = c^dP mod p.
	dwOverFlow+=(uint32_t)BNModExp(m, c, dP, p,nSize);
	// Let m_2 = c^dQ mod q.
	dwOverFlow+=(uint32_t)BNModExp(pm2, c, dQ, q,nSize);

	// if  m < pm2 the make m=m+p
	if ( BNCompare(m, pm2,nSize) < 0 )
	{
		dwOverFlow+=BNAdd(m, m, p,nSize);
	}
	dwOverFlow+=BNSubtract(m, m, pm2,nSize);	
	dwOverFlow+=BNModMult(ph, qInv, m, p,nSize/2);
	dwOverFlow+=BNMultiply(phq, ph, q,nSize/2);
	dwOverFlow+=BNAdd(m, pm2, phq,nSize);

	BNFree(&pm2);
	BNFree(&ph);
	BNFree(&phq);
	return (int)dwOverFlow;
}

/*
* 	DigitalSignSHA1rDSA(...) 
*  Computes the SHA1 hash value of pmsgbuff and sign 
*  the result using. 
*
*  Digital Signatures Using Reversible Public Key (ANSI X9.31 -1998)
*    
*  pmsgBuff  - the msg that is going to be signed. 
*  nSizeMsg  - the size of pmsgBuff
*  d		  - the private RSA key. 
*  e		  - the public key. 
*  n		  - the trusted public key. (that the client already have) 
*  S		  - the signature. 
*  nSize	  - the size of n,d. 
* 
*/

int MyCryptLib::DigitalSignSHA1rDSA(unsigned char* pmsgbuff, uint32_t nSizeMsg,uint32_t d[],uint32_t n[],uint32_t S[],uint32_t nSize)
{
	// Create some temporary data. 
	int iRet=0;
	uint32_t *pHashvalue=BNAlloc(5); // 5*4 = 20 uint8_t for SHA1 in enough
	if ( pHashvalue==NULL )
	{
		return -2;
	}

	BNSetZero(pHashvalue,5);
	BNSetZero(S,nSize);

	// Compute the hash... 
	SHA1Hash((unsigned char*)pHashvalue,pmsgbuff,nSizeMsg);

	//  Compute hash^d mod n
	iRet=BNModExp(S,pHashvalue,d,n,nSize);	

	BNFree(&pHashvalue);
	return iRet; 
}





bool MyCryptLib::DigitalVerifySHA1rDSA(unsigned char* pmsgbuff, uint32_t nSizeMsg,uint32_t n[],uint32_t e,uint32_t S[],uint32_t nSize)
{

	bool bRet=true;
	// Create some temporary data. 
	uint32_t *ptmp=BNAlloc(nSize);
	if ( ptmp==NULL )
	{
		return false;
	}

	uint32_t *pHashvalue=BNAlloc(5); 
	if ( pHashvalue==NULL )
	{
		BNFree(&ptmp);
		return false;
	}

	uint32_t *ptmp2=BNAlloc(nSize); // 5*4 = 20 uint8_t for SHA1 in enough
	if ( ptmp2==NULL ) 
	{

		BNFree(&ptmp);
		BNFree(&pHashvalue);
		return false;
	}

	BNSetZero(pHashvalue,5);
	BNSetZero(ptmp,nSize);
	BNSetEqualdw(ptmp2,e,nSize);


	// Compute the hash... 
	SHA1Hash((unsigned char*)pHashvalue,pmsgbuff,nSizeMsg);

	// y=(S)^e mod n ptmp2=e=3. 
	BNModExp(ptmp,S,ptmp2,n,nSize);	

	//FIXME: change this.. 
	bRet=BNIsEqual(ptmp,pHashvalue,5);

	BNFree(&ptmp);
	BNFree(&ptmp2);
	BNFree(&pHashvalue);
	return bRet;
}



