/*
FlyNet
Copyright (C) 2005  author:lu_zi

这一函数库是自由软体，您可以遵照自由软体基金会出版的 GNU GENERAL PUBLIC LICENSE
条款来修改和重新发布这一程式，或者用许可证的第二版，或者 (根据您的选择)
用任何更新的版本。

发布这一函数库的目的是希望它有用，但没有任何担保。甚至没有适合特定目的而隐含的
担保。更详细的情况请参阅 GNU Lesser General Public License。

有任何问题请发邮件至:lu_zi@msn.com
*/
#include "stdafx.h"
#include <iostream>

#include "AutoBuffer.h"

CBigMemoryAllocator<CAutoBuffer::s_blockSize> CAutoBuffer::s_allocator;

void CAutoBuffer::Append(const unsigned char* pBuffer,int length)
{
 // mutex::scoped_lock lock(m_mutex);
  assert(pBuffer && length>0);
  
  int len=CAutoBuffer::s_blockSize-(m_length+m_beginPos)%CAutoBuffer::s_blockSize;
  m_length+=length;
  unsigned char* p=NULL;
  while(length) {
    if(len==CAutoBuffer::s_blockSize) {
      //前一个缓冲区没有剩余字节，新建一个缓冲区
      p=CAutoBuffer::s_allocator.GetBuffer();
      m_buffer.push_back(p);
    }
    else {
      //得到最后一个缓冲区
      p=*m_buffer.rbegin();
      p+=CAutoBuffer::s_blockSize-len;
    }
    memcpy(p,pBuffer,len=(len>=length)?length:len);
    pBuffer+=len;
    length-=len;
      len=CAutoBuffer::s_blockSize;
  }
}
  
unsigned char* CAutoBuffer::AllocateFullBuffer(int& length)
{
  unsigned char* pBuffer=NULL;
  if(m_length>length) {
    pBuffer=new unsigned char[length];
    BeginTop();
    GetTop(pBuffer,length);
    EndTop();
    return pBuffer;
  }
  else if(m_length<length) {
    length=m_length;
  }

 // mutex::scoped_lock lock(m_mutex);
  pBuffer=new unsigned char[length];
  GetTopBuffer(pBuffer,length,m_beginPos,m_buffer.begin());
  ClearBuffer();
  return pBuffer;
}
  
void CAutoBuffer::Clear()
{
 // mutex::scoped_lock lock(m_mutex);
  ClearBuffer();
}
  
unsigned char* CAutoBuffer::LockCurrentPieceForWrite(int& length)
{
 // m_lock.lock();
  
  length=CAutoBuffer::s_blockSize-(m_length+m_beginPos)%CAutoBuffer::s_blockSize;
  unsigned char* p=NULL;
  if(length==CAutoBuffer::s_blockSize) {
    //前一个缓冲区没有剩余字节，新建一个缓冲区
    p=CAutoBuffer::s_allocator.GetBuffer();
    m_buffer.push_back(p);
  }
  else {
    //得到最后一个缓冲区
    p=*m_buffer.rbegin();
    p+=CAutoBuffer::s_blockSize-length;
  }
  return p;
}

void CAutoBuffer::UnlockCurrentPieceForWrite(int writedLength)
{
  //如果写入的字节数据为0，就要判断我们是否加入了一个空的分片，如果加入了，为了保持链表在
  //得到尾分片时的高速定位，就要将其删除，还好这个情况不应该有很多
  if(writedLength<=0) {
    int length=CAutoBuffer::s_blockSize-(m_length+m_beginPos)%CAutoBuffer::s_blockSize;
    if(length==CAutoBuffer::s_blockSize) {
      unsigned char* p=*(m_buffer.rbegin());
      m_buffer.pop_back();
      CAutoBuffer::s_allocator.ReturnBuffer(p);
    }
  }
  else {
    m_length+=writedLength;
  }
 // m_lock.unlock();
}

bool CAutoBuffer::BeginTop()
{
  //m_lock.lock();
  if(!m_buffer.size())
    return false;
  
  if(!m_pTop)
    m_pTop=new CAutoBuffer::Top;
  
  m_pTop->m_beginPiece=m_buffer.begin();
  m_pTop->m_pieceOffset=m_pTop->m_pieceOffsetOld=m_beginPos;
  m_pTop->m_length=0;
  return true;
}

unsigned int CAutoBuffer::GetTop(unsigned char* p,int length)
{
  assert(m_pTop);
  assert(p && length>0);
  int len=GetTopBuffer(p,length,m_pTop->m_pieceOffset,m_pTop->m_beginPiece,&m_pTop->m_pieceOffset,&m_pTop->m_beginPiece);
  m_pTop->m_length+=len;
  m_length-=len;
  return len;
}

int CAutoBuffer::GetTopBuffer(unsigned char* pBuffer,unsigned int length,unsigned int beginPos,list<unsigned char*>::iterator iterBegin,unsigned int* endPos,list<unsigned char*>::iterator* iterEnd)
{
  unsigned int pos=0;//当前复制的位置，也是已经复制的长度
  //每个块内的有效长度,第一个块的有效长度可能会小于块的长度
  int validSize=CAutoBuffer::s_blockSize-beginPos;
  list<unsigned char*>::iterator iter=iterBegin;
  int len=0;
  for(;iter!=m_buffer.end();iter++) {
    len=length-pos;
    len=(len>validSize)?validSize:len;
    const unsigned char* pBufferOld=*iter;
    memcpy(pBuffer+pos,pBufferOld+CAutoBuffer::s_blockSize-validSize,len);
    pos+=len;
    if(length<=pos)
  break;
    validSize=CAutoBuffer::s_blockSize;
  }
  if(endPos) {
    if(beginPos!=0 && validSize==CAutoBuffer::s_blockSize)
      {//进行了第二次循环，则原来的beginPos无效，
	*endPos=len;
      }
    else {//未进行第二次或原来的起始位置就是0，则使用beginPos作为起始位置
      *endPos=len+beginPos;
    }
  }
  if(iterEnd) *iterEnd=iter;
  return pos;
}

void CAutoBuffer::EndTop()
{
  assert(m_pTop);
  
  if(m_length<=0) {
    ClearBuffer();
  }
  else {
    m_beginPos=m_pTop->m_pieceOffset;
    list<unsigned char*>::iterator iter=m_buffer.begin();
    while(iter!=m_pTop->m_beginPiece) {
      unsigned char* p=(*iter);
      CAutoBuffer::s_allocator.ReturnBuffer(p);
      m_buffer.pop_front();
      iter=m_buffer.begin();
    }
  }
 // m_lock.unlock();
}

void CAutoBuffer::RestoreTop()
{
  m_length+=m_pTop->m_length;
  //m_lock.unlock();
}

void CAutoBuffer::ClearBuffer()
{
  for(list<unsigned char*>::iterator iter=m_buffer.begin();iter!=m_buffer.end();iter++)  {
    CAutoBuffer::s_allocator.ReturnBuffer(*iter);
  }
  m_buffer.clear();
  if(m_pTop) {
    delete m_pTop;
    m_pTop=NULL;
  }
  m_length=0;
  m_beginPos=0;
}

const unsigned char* CAutoBuffer::LockCurrentPieceForRead(int& length)
{
 // m_lock.lock();
  if(!m_length) {
    length=0;
    return NULL;
  }
  length=((m_beginPos+m_length)>CAutoBuffer::s_blockSize)?(CAutoBuffer::s_blockSize-m_beginPos):m_length;
  const unsigned char* p=*(m_buffer.begin());
  return p+m_beginPos;
}

void CAutoBuffer::UnlockCurrentPieceForRead(int readedLength)
{
  if(m_length && readedLength>0) {
    int readed=readedLength;
    while(readedLength>0){
      int length=((m_beginPos+m_length)>CAutoBuffer::s_blockSize)?(CAutoBuffer::s_blockSize-m_beginPos):m_length;
      if(readedLength>=length)  {
	unsigned char* p=*m_buffer.begin();
	CAutoBuffer::s_allocator.ReturnBuffer(p);
	m_buffer.pop_front();
	m_beginPos=0;
	readedLength-=length;
	m_length-=length;
      }
      else  {
	m_beginPos+=readedLength;
	m_length-=readedLength;
	break;
      }
    }

    if(m_length<=0){
      ClearBuffer();
    }
  }
  
 // m_lock.unlock();
}
