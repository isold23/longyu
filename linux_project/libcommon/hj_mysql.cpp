/*! @file hj_mysql.cpp
* *****************************************************************************
* @n</PRE>
* @n模块名       ：mysql数据库操作相关库函数定义
* @n文件名       ：hj_mysql.cpp
* @n相关文件     ：hj_mysql.h
* @n文件实现功能 ：mysql数据库操作相关库函数定义
* @n作者         ：huangjun - 神州星国际(http://www.shenzhoustar.com)
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
#include <stdio.h>
#include <strings.h>

#include "hj_mysql.h"

/*!
* 功能：初始化Mysql连接
* @n作者：huangjun
* @n日期：2008-07-31
*/
void HJ_Init_Mysql(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    bzero(pstMysqlLink, sizeof(HJ_MYSQL_LINK));

    // 初始化Mysql连接
    mysql_init(&(pstMysqlLink->stMysql));
}

/*!
* 功能：连接Mysql
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_ConnectDB(HJ_MYSQL_LINK *pstMysqlLink, const char *pEncode)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected)
    {
        HJ_Mysql_CloseDB(pstMysqlLink);
        pstMysqlLink->iConnected = 0;
    }

    if (!mysql_real_connect(&(pstMysqlLink->stMysql)
        , pstMysqlLink->stMysqlConn.sHost
        , pstMysqlLink->stMysqlConn.sUser
        , pstMysqlLink->stMysqlConn.sPasswd
        , pstMysqlLink->stMysqlConn.sDB
        , pstMysqlLink->stMysqlConn.uPort
        , NULL, 0))
    {
        return -1;
    }

    if (pEncode)
    {
        char szSetEncode[32];
        snprintf(szSetEncode, sizeof(szSetEncode), "SET NAMES %s"
            , pEncode);
        if (mysql_query(&(pstMysqlLink->stMysql), szSetEncode))
        {
            mysql_close(&(pstMysqlLink->stMysql));
            return -3;
        }
    }

    pstMysqlLink->iConnected = 1;

    return 0;
}

/*!
* 功能：关闭Mysql连接
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_CloseDB(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected)
    {
        HJ_Mysql_FreeResult(pstMysqlLink);
        mysql_close(&(pstMysqlLink->stMysql));
        pstMysqlLink->iConnected = 0;
    }

    return 0;
}

/*!
* 功能：执行Mysql操作语句
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_ExecSQL(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->iConnected)
    {
        return -1;
    }

    if (pstMysqlLink->iQueryType == 1)
    {
        if (strncasecmp("select", pstMysqlLink->szQuery, 6))
        {
            return -2;
        }

        HJ_Mysql_FreeResult(pstMysqlLink);
    }

    if (mysql_query(&(pstMysqlLink->stMysql), pstMysqlLink->szQuery))
    {
        if (mysql_errno(&(pstMysqlLink->stMysql)) == CR_SERVER_GONE_ERROR)
        {
            HJ_Mysql_CloseDB(pstMysqlLink);
            return -3;
        }

        return -4;
    }

    if (pstMysqlLink->iQueryType == 1)
    {
        pstMysqlLink->pstRes = mysql_store_result(&(pstMysqlLink->stMysql));
        if (!pstMysqlLink->pstRes)
        {
            pstMysqlLink->nResNum = 0;
            return -5;
        }
        else
        {
            pstMysqlLink->nResNum = mysql_num_rows(pstMysqlLink->pstRes);
        }
    }

    return 0;
}

/*!
* 功能：从Mysql返回集中取出一行
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_FetchRow(HJ_MYSQL_LINK* pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes || (pstMysqlLink->nResNum == 0))
    {
        return -1;
    }

    pstMysqlLink->ppRow = mysql_fetch_row(pstMysqlLink->pstRes);

    return pstMysqlLink->ppRow? 0 : -2;
}

/*!
* 功能：查看最近一次的Mysql操作影响行数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_AffectedRow(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected == 0)
    {
        return -1;
    }

    return mysql_affected_rows(&pstMysqlLink->stMysql);
}

/*!
* 功能：释放最近一次Mysql操作返回集
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_FreeResult(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->pstRes)
    {
        mysql_free_result(pstMysqlLink->pstRes);
        pstMysqlLink->pstRes = NULL;
    }

    return 0;
}

/*!
* 功能：查看最近一次Mysql操作返回集的字段数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_NumFields(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes)
    {
        return -1;
    }

    return mysql_num_fields(pstMysqlLink->pstRes);
}

/*!
* 功能：查看最近一次Mysql操作返回集的行数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_NumRows(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes)
    {
        return -1;
    }

    return mysql_num_rows(pstMysqlLink->pstRes);
}
