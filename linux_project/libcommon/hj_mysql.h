/*! @file hj_mysql.h
* *****************************************************************************
* @n</PRE>
* @n模块名       ：mysql数据库操作相关库函数申明
* @n文件名       ：hj_mysql.h
* @n相关文件     ：hj_mysql.cpp
* @n文件实现功能 ：mysql数据库操作相关库函数申明
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
#ifndef __HJ_MYSQL_H__
#define __HJ_MYSQL_H__

#include <mysql/mysql.h>
#include <mysql/errmsg.h>

typedef struct
{
    // 数据库主机名
    char sHost[64];
    // 数据库监听的端口号
    unsigned int uPort;
    // 数据库连接用户名
    char sUser[64];
    // 数据库连接密码
    char sPasswd[64];
    // 数据库名
    char sDB[64];
} HJ_MYSQL_CONN;

typedef struct
{
    HJ_MYSQL_CONN stMysqlConn; // 数据库连接信息

    MYSQL stMysql;              // Mysql连接
    int  iConnected;            // 当前数据库是否已经连接，0-没有，1-已连接

    char szQuery[10240];        // 当前操作的SQL语句
    int  iQueryType;            // 当前操作SQL语句是否需要返回值，0-不要，1-需要，也即是select查询

    MYSQL_RES *pstRes;          // 当前操作SQL后的返回集
    MYSQL_ROW ppRow;            // 当前操作SQL后，通过取一行后的返回行

    // int nResNotNull;         // 当前操作SQL后的RecordSet是否为空，0-为空，1-非空
    int nResNum;                // 当前操作SQL后的RecordSet的记录数目
} HJ_MYSQL_LINK;

/*!
* 功能：初始化Mysql连接
* @n作者：huangjun
* @n日期：2008-07-31
*/
void HJ_Init_Mysql(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：连接Mysql
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_ConnectDB(HJ_MYSQL_LINK *pstMysqlLink, const char *pEncode);

/*!
* 功能：关闭Mysql连接
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_CloseDB(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：执行Mysql操作语句
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_ExecSQL(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：从Mysql返回集中取出一行
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_FetchRow(HJ_MYSQL_LINK* pstMysqlLink);

/*!
* 功能：查看最近一次的Mysql操作影响行数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_AffectedRow(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：释放最近一次Mysql操作返回集
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_FreeResult(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：查看最近一次Mysql操作返回集的字段数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_NumFields(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* 功能：查看最近一次Mysql操作返回集的行数
* @n作者：huangjun
* @n日期：2008-07-31
*/
int HJ_Mysql_NumRows(HJ_MYSQL_LINK *pstMysqlLink);

#endif
