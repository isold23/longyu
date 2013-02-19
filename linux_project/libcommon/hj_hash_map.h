/*! @file hj_hash_map.h
* *****************************************************************************
* @n</PRE>
* @n模块名       ：hash表操作相关库函数申明
* @n文件名       ：hj_hash_map.h
* @n相关文件     ：hj_hash_map.cpp
* @n文件实现功能 ：hash表操作相关库函数申明
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
#ifndef __HJ_HASH_MAP_H__
#define __HJ_HASH_MAP_H__

class CHJ_HashMap
{
public:
    CHJ_HashMap();
    virtual ~CHJ_HashMap() {Destroy();}
    int Init(size_t MaxKey);
    void Destroy(void);

    void* Insert(size_t Key, void *pItem);
    void* Replace(size_t Key, void *pItem);
    void* Remove(size_t Key, void *pItem);
    void* Search(size_t Key, void *pItem);

    void SetHashTable(int *pHashTable, const int &nMaxHashDepth);
    typedef int (*COMPARE)(void *, void *);
    void SetCompare(COMPARE compare);

private:
    int GetNeededDepth(size_t MaxKey);
    void UpdateRowLength();

    static int m_Hash_Default_Prime_Table[];
    static int m_Hash_Default_Prime_Table_Depth;
    static int m_DefaultCompare(void *pItemDest, void *pItemSrc);

    void **m_ppHashMap;
    int *m_pHashTable;       // prime table
    int  m_nMaxHashDepth;    // Hash表本身的最大Depth
    int  m_nHashDepth;       // 实际所用Hash表的Depth
    int  m_nHashRowLength;
    int (*m_fCompare)(void *pItemDest, void *pItemSrc);
};

#endif
