/*! @file hj_mempool.h
* *****************************************************************************
* @n</PRE>
* @n模块名       ：内存池操作相关库函数申明
* @n文件名       ：hj_mempool.h
* @n相关文件     ：hj_mempool.cpp
* @n文件实现功能 ：内存池操作相关库函数申明
* @n作者         ：huangjun - 新浪技术（中国）
* @n版本         ：1.0.1
* @n-----------------------------------------------------------------------------
* @n备注：
* @n-----------------------------------------------------------------------------
* @n修改记录：
* @n日期        版本        修改人      修改内容
* @n20080731    1.0.1       Huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#ifndef __HJ_MEMPOOL_H__
#define __HJ_MEMPOOL_H__

class CHJMemPool
{
public:
    explicit CHJMemPool(void);
    virtual ~CHJMemPool() {Destroy();}

    int Init(size_t BlockSize, size_t BlockCount);
    void Destroy(void);

    void* Alloc(void);
    void Free(void *pItem);

    size_t GetBlockSize(void) const;

private:
    typedef unsigned char byte;
    typedef struct block
    {
        struct block *pNext;
    } block;

    byte  *m_pBaseAddr;
    size_t m_BlockSize;
    size_t m_BlockCount;

    block *m_pFreeBlockList;
};

#endif
