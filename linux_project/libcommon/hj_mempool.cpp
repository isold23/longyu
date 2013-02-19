/*! @file hj_mempool.cpp
* *****************************************************************************
* @n</PRE>
* @n模块名       ：内存池操作相关库函数定义
* @n文件名       ：hj_mempool.cpp
* @n相关文件     ：hj_mempool.h
* @n文件实现功能 ：内存池操作相关库函数定义
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
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <new>

#include "hj_mempool.h"

using namespace std;

CHJMemPool::CHJMemPool(void)
    : m_pBaseAddr(NULL), m_BlockSize(0), m_BlockCount(0), m_pFreeBlockList(NULL)
{
}

int CHJMemPool::Init(size_t BlockSize, size_t BlockCount)
{
    if (BlockSize < sizeof(block))
    {
        return -1;
    }

    // 已经初始化
    if (m_pBaseAddr)
    {
        return 1;
    }

    size_t total_size = BlockSize * BlockCount;
    m_pBaseAddr = (byte*)(new (nothrow) char[total_size]);
    if (!m_pBaseAddr)
    {
        return -2;
    }
    m_BlockSize  = BlockSize;
    m_BlockCount = BlockCount;

    bzero(m_pBaseAddr, total_size);

    block *first_block = (block*)m_pBaseAddr, *current_block = first_block, *next_block;
    for (size_t i = 1; i < BlockCount; i++)
    {
        next_block = (block*)((byte*)current_block + m_BlockSize);
        current_block->pNext = next_block;
        current_block = next_block;
    }
    current_block->pNext = NULL;

    m_pFreeBlockList = first_block;

    return 0;
}

void CHJMemPool::Destroy(void)
{
    if (m_pBaseAddr)
    {
        delete m_pBaseAddr;
        m_pBaseAddr = NULL;
        m_pFreeBlockList = NULL;
        m_BlockCount = 0;
        m_BlockSize = 0;
    }
    return;
}

void* CHJMemPool::Alloc(void)
{
    if (!m_pFreeBlockList)
    {
        return NULL;
    }

    block *pFreeList = m_pFreeBlockList;
    m_pFreeBlockList = m_pFreeBlockList->pNext;

    return (void*)pFreeList;
}

void CHJMemPool::Free(void *pItem)
{
    assert(pItem);

    ((block*)pItem)->pNext = m_pFreeBlockList;
    m_pFreeBlockList = (block*)pItem;

    return;
}

size_t CHJMemPool::GetBlockSize(void) const
{
    return m_BlockSize;
}
