/*! @hj_cfg.h
*******************************************************************************
</PRE>
模块名       ：读配置文件相关库函数申明
文件名       ：hj_cfg.h
相关文件     ：hj_cfg.cpp
文件实现功能 ：读配置文件相关库函数申明
作者         ：huangjun - 神州星国际(http://www.shenzhoustar.com)
版本         ：1.0.1
-------------------------------------------------------------------------------
备注：
-------------------------------------------------------------------------------
修改记录：
日期        版本        修改人      修改内容
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/

#ifndef __HJ_CFG_H__
#define __HJ_CFG_H__

#define CFG_STRING  (int)1
#define CFG_INT     (int)2
#define CFG_LONG    (int)3
#define CFG_DOUBLE  (int)4

void HJ_Cfg_GetConfig(const char *pszConfigFilePath, ...);

#endif
