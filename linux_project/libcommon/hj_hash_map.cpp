/*! @file hj_hash_map.cpp
* *****************************************************************************
* @n</PRE>
* @n模块名       ：hash表操作相关库函数定义
* @n文件名       ：hj_hash_map.cpp
* @n相关文件     ：hj_hash_map.h
* @n文件实现功能 ：hash表操作相关库函数定义
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
#include <new>
#include <stdio.h>
#include <cstring>
#include <strings.h>

#include "hj_hash_map.h"

using namespace std;

/*!
* static members 
*/
int CHJ_HashMap::m_Hash_Default_Prime_Table[] =
{
    599999, 599993, 599983, 599959, 599941,
    599939, 599933, 599927, 599899, 599891,
    599869, 599857, 599843, 599831, 599803,
    599783, 599779, 599759, 599741, 599719,
    599713, 599701, 599699, 599693, 599681,
    599663, 599657, 599629, 599623, 599611,
    599603, 599597, 599591, 599561, 599551,
    599537, 599519, 599513, 599491, 599479,
    599477, 599429, 599419, 599413, 599407,
    599399, 599387, 599383, 599371, 599359
};  // 用求余数法得到hash值时，最好采用素数取余

int CHJ_HashMap::m_Hash_Default_Prime_Table_Depth
    = sizeof(CHJ_HashMap::m_Hash_Default_Prime_Table)
    / sizeof(CHJ_HashMap::m_Hash_Default_Prime_Table[0]);

int CHJ_HashMap::m_DefaultCompare(void *pItemDest, void *pItemSrc)
{
    assert(pItemDest && pItemSrc);

    return (char*)pItemDest - (char*)pItemSrc;
}

void CHJ_HashMap::UpdateRowLength()
{
    int nRowLength = 0;
    for (int i = 0; i < m_nHashDepth; ++i)
    {
        if (nRowLength < m_pHashTable[i])
        {
            nRowLength = m_pHashTable[i];
        }
    }
    m_nHashRowLength = nRowLength;
}

CHJ_HashMap::CHJ_HashMap()
    : m_ppHashMap(NULL)
    , m_pHashTable(m_Hash_Default_Prime_Table)
    , m_nMaxHashDepth(m_Hash_Default_Prime_Table_Depth)
    , m_nHashDepth(m_Hash_Default_Prime_Table_Depth)
    , m_nHashRowLength(0)
    , m_fCompare(m_DefaultCompare)
{
}

void CHJ_HashMap::SetHashTable(int *pHashTable, const int &nMaxHashDepth)
{
    assert(pHashTable);

    m_pHashTable = pHashTable;
    m_nMaxHashDepth = nMaxHashDepth;
}

void CHJ_HashMap::SetCompare(COMPARE compare)
{
    m_fCompare = compare? compare : m_DefaultCompare;
}

int CHJ_HashMap::GetNeededDepth(size_t MaxKey)
{
    int nMinLineWidth = m_pHashTable[0]; // 注意Hash表不得为空
    for (int i = 0; i < m_nMaxHashDepth; i++)
    {
        if (nMinLineWidth > m_pHashTable[i])
        {
            nMinLineWidth = m_pHashTable[i];
        }
    }

    assert(nMinLineWidth); // 防止出现下面的除零异常

    int nDepth = (MaxKey * 5 / 4 + nMinLineWidth) / nMinLineWidth;
    if (nDepth < 5)
    {
        nDepth = 5;
    }

    return nDepth;
}

int CHJ_HashMap::Init(size_t MaxKey)
{
    // 如果已经初始化
    if (m_ppHashMap)
    {
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    // 更新nHashDepth
    m_nHashDepth = GetNeededDepth(MaxKey);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // 更新m_nHashRowLength
    int nRowLength = 0;
    for (int i = 0; i < m_nHashDepth; ++i)
    {
        if (nRowLength < m_pHashTable[i])
        {
            nRowLength = m_pHashTable[i];
        }
    }
    m_nHashRowLength = nRowLength;
    //////////////////////////////////////////////////////////////////////////

    // 初始化内存
    int nTotalSize = m_nHashRowLength * m_nHashDepth * sizeof(void*);
    m_ppHashMap = (void**)(new (nothrow) char[nTotalSize]);
    if (!m_ppHashMap)
    {
        return -1;
    }
    bzero(m_ppHashMap, nTotalSize);

    return 0;
}

void CHJ_HashMap::Destroy(void)
{
    if (m_ppHashMap)
    {
        delete [] m_ppHashMap;
        m_ppHashMap = NULL;
    }
}

void* CHJ_HashMap::Insert(size_t Key, void *pItem)
{
    assert(pItem);

    int nLastPos = -1, nPos = -1, nLineStart = 0;
    bool bFound = false;

    for (int i = 0; i < m_nHashDepth; ++i)
    {
        nPos = Key % m_pHashTable[i] + nLineStart;

        if (m_ppHashMap[nPos] == NULL)
        {
            if (nLastPos == -1)
            {
                nLastPos = nPos;
            }
        }
        else if (m_fCompare(m_ppHashMap[nPos], pItem) == 0)
        {
            nLastPos = nPos;
            bFound = true;
            break;
        }

        nLineStart += m_nHashRowLength;
    }

    if (nLastPos == -1)
    {
        return NULL; // 哈希表溢出
    }
    else if (!bFound)
    {
        m_ppHashMap[nLastPos] = pItem;
    }

    return m_ppHashMap[nLastPos];
}

void* CHJ_HashMap::Replace(size_t Key, void *pItem)
{
    assert(pItem);

    int nLastPos = -1, nPos = -1, nLineStart = 0;

    for (int i = 0; i < m_nHashDepth; ++i)
    {
        nPos = Key % m_pHashTable[i] + nLineStart;

        if (m_ppHashMap[nPos] == NULL)
        {
            if (nLastPos == -1)
            {
                nLastPos = nPos;
            }
        }
        else if (m_fCompare(m_ppHashMap[nPos], pItem) == 0)
        {
            nLastPos = nPos;
            break;
        }

        nLineStart += m_nHashRowLength;
    }

    if (nLastPos == -1)
    {
        return NULL; // 哈希表溢出
    }
    else
    {
        void *pTemp = NULL;
        if (m_ppHashMap[nLastPos])
        {
            pTemp = m_ppHashMap[nLastPos];
        }
        else
        {
            pTemp = pItem;
        }
        m_ppHashMap[nLastPos] = pItem;

        return pTemp;
    }
}

void* CHJ_HashMap::Remove(size_t Key, void *pItem)
{
    assert(pItem);

    int nPos = -1, nLineStart = 0;
    for (int i = 0; i < m_nHashDepth; ++i)
    {
        nPos = Key % m_pHashTable[i] + nLineStart;

        if ((m_ppHashMap[nPos] != NULL)
            && (m_fCompare(m_ppHashMap[nPos], pItem) == 0))
        {
            void *pTemp = m_ppHashMap[nPos];
            m_ppHashMap[nPos] = NULL;
            return pTemp;
        }

        nLineStart += m_nHashRowLength;
    }

    return NULL;
}

void* CHJ_HashMap::Search(size_t Key, void *pItem)
{
    assert(pItem);

    int nPos = -1, nLineStart = 0;
    for (int i = 0; i < m_nHashDepth; ++i)
    {
        nPos = Key % m_pHashTable[i] + nLineStart;

        if ((m_ppHashMap[nPos] != NULL)
            && (m_fCompare(m_ppHashMap[nPos], pItem) == 0))
        {
            return m_ppHashMap[nPos];
        }

        nLineStart += m_nHashRowLength;
    }

    return NULL;
}
