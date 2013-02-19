#pragma once

class CDynBuffer
{
public:
	CDynBuffer(void) 
		:m_ptr(0),
		m_nSize(0),
		m_nBufferSize(0) {
	} 

	~CDynBuffer(void) {
		Release();
	}

	unsigned char* Ptr(void) {
		return m_ptr;
	}
	const unsigned char* Ptr(void) const {
		return m_ptr;
	}
	bool IsEmpty(void) const {
		return m_nSize == 0;
	}
	unsigned int Size(void) const {
		return m_nSize;
	}

	void Set(unsigned char *buf,unsigned int nSize) {
		if (m_nBufferSize < nSize) {
			Release();
			m_ptr = new unsigned char[nSize];
			m_nBufferSize = nSize;
		}
		m_nSize = nSize;
		if (buf != 0)
			memcpy(m_ptr,buf,nSize);
	}

	void Release(void) {
		if (m_nBufferSize != 0)
			delete[] m_ptr;
		m_ptr = 0;
		m_nSize = 0;
		m_nBufferSize = 0;
	} 
private:
	unsigned int m_nSize;
	unsigned char *m_ptr;
	unsigned int m_nBufferSize;
};


class CStaticBuffer 
{
public:
	CStaticBuffer(void) 
		: m_ptr(NULL),
		  m_nSize(0) {

	}

	CStaticBuffer(unsigned char *buf,unsigned int nSize) 
		:m_ptr(buf),
	     m_nSize(nSize) {
	} 

	~CStaticBuffer(void) {
	}

	unsigned char* Ptr(void) {
		return m_ptr;
	}
	const unsigned char* Ptr(void) const {
		return m_ptr;
	}

	bool IsEmpty(void) const {
		return m_nSize == 0;
	}
	unsigned int Size(void) const {
		return m_nSize;
	}

	void Set(int nSize) {
		m_nSize = nSize;
	}

	void Set(unsigned char *buf,unsigned int nSize) {
		ASSERT(buf != NULL);
		m_ptr = buf; m_nSize = nSize;
	}
 
private:
	unsigned int m_nSize;
	unsigned char *m_ptr;
};
