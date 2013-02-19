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
/**
 * @file AutoBuffer.h
 * @brief 自动缓冲管理工具
 * @author lu_zi
 * @versino 1.0
 * @date 2004.11.26
 */
#ifndef __AUTO_BUFFER__
#define __AUTO_BUFFER__

//#include "FlyNetPublic.h"

#include <list>
#include <cassert>
using namespace std;

//#include <boost/thread.hpp>
//
//using namespace boost;

#include "BigMemoryAllocator.h"

/**
* @brief 自动缓冲管理，用于对可增加的缓冲进行自动管理，程序先会按要求自动分配定长
  大小的缓冲区用于复制数据，当所有数据复制完成后，再进行一次整体copy，将数据放到
  一个大小和有效数据一致的缓冲区中，以这种方式来减少缓冲区copy的次数
* @author lu_zi
* @versino 1.0
* @date 2004.11.26
* @version 1.1
* @date 2004.12.10
* 增加可在文件头部输出的操作，以适应一些流操作的应用，使自动缓冲更象一个输入输出流
* @version 1.2
* @data 2004.12.20
* 增加对多线程的支持
* @version 1.3
* @data 2005.4.20
* 对内存进行管理
*/
class CAutoBuffer
{
 public:
  /**@块大小*/
  static const int s_blockSize=2048;
  /**@内存分配器*/
  static CBigMemoryAllocator<CAutoBuffer::s_blockSize> s_allocator;
 protected:
  unsigned int m_length;
  list<unsigned char*> m_buffer;
 public:
  CAutoBuffer():m_length(0),m_pTop(NULL),m_beginPos(0){}
  ~CAutoBuffer(){Clear();}
 public:
  /**@brief 增加数据*/
  void Append(const unsigned char* pBuffer,int length);
  /**@brief 得到完整缓冲区内容*/
  unsigned char* AllocateFullBuffer(int& length);
  /**@brief 得到缓冲区长度*/
  unsigned int GetLength()const {return m_length;}
  /**@关闭*/
  void Clear();
 public:
  /**@brief 出于对直接写入缓冲区的效率考虑，用户可以得到当前缓冲片的可写入位置及可写入
     数据的长度用于直接写入，写入后通过UnlockCurrentPiece来设定相关参数*/
  unsigned char* LockCurrentPieceForWrite(int& length);
  /**@brief 用于解锁当前写入缓冲分片*/
  void UnlockCurrentPieceForWrite(int writedLength);
  /**@brief 出于对直接读取缓冲区的效率考虑，用户可以得到当前缓冲片的读取位置及可读取
     数据的长度用于直接读取，读取后通过UnlockCurrentPiece来设定相关参数*/
  const unsigned char* LockCurrentPieceForRead(int& length);
  /**@brief 用于解锁当前读取缓冲分片*/
  void UnlockCurrentPieceForRead(int readedLength);
 protected:
  struct Top
  {
    /**@brief 当前的缓冲偏移*/
    unsigned int m_pieceOffset;
    /**@brief 上一次的缓冲偏移*/
    unsigned int m_pieceOffsetOld;
    /**@brief 当前块的位置*/
    list<unsigned char*>::iterator m_beginPiece;
    /**@brief 输出的总长度*/
    int m_length;
  };
  Top* m_pTop;
  /**@brief 缓冲区在第一个片内的起始位置，也是缓冲区的起始位置*/
  int m_beginPos;
  /**@brief 线程模式*/
  //boost::mutex m_mutex;
  //mutex::scoped_lock m_lock;
 public:
  /**@brief 开始从头部取数据*/
  bool BeginTop();
  /**@brief 得到头部数据*/
  unsigned int GetTop(unsigned char* p,int length);
  /**@brief 结束取数据，缓冲区被刷新*/
  void EndTop();
  /**@brief 结束取数据，缓冲区被回滚*/
  void RestoreTop();
 protected:
  /**
   * @brief 复制从头部开始的指定长度的缓冲
   * @param pBuffer 缓冲区
   * @param length 缓冲区长度
   * @param beginPos 开始位置
   * @param iterBegin 开始的片位置
   * @param endPos 复制后结束的位置
   * @param iterEnd 复制后结束的片位置
   * @return 实际复制的长度
   */
  int GetTopBuffer(unsigned char* pBuffer,unsigned int length,unsigned int beginPos,list<unsigned char*>::iterator iterBegin,unsigned int* endPos=NULL,list<unsigned char*>::iterator* iterEnd=NULL);
  void ClearBuffer();
  
};



#endif//__AUTO_BUFFER__
