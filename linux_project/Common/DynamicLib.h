
/****************************************************************************************************************************
版本声明：	北京新浪信息技术有限责任公司
文件名：	DynamicLib.h
创建人：	张亚伟
创建日期：	2006-12-07
说明：		封装跨平台动态库调用使用的函数，供外界调用动态库使用
版本号：	1.00.000
*****************************************************************************************************************************/

#ifndef DEF_SINA_DYNAMIC_LINK_LIBRARY_H
#define DEF_SINA_DYNAMIC_LINK_LIBRARY_H

#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h> 
#endif 

#include "include.h"

class CDynamicLib{
public:
	//构造函数
	CDynamicLib(void);

	//析构函数
	~CDynamicLib(void);

public:
	//根据文件名称，装入制定动态库，注意传入文件名时不包括扩展名
	bool LoadDynamicLib(const char* apFileName);

	//取得制定函数的地址
	void* GetDynamicLibFun(const char* apFunName); 

	//关闭打开的动态链接库
	void CloseDynamicLib();

private:

#ifdef WIN32
	HMODULE mhDynamic;	//动态链接库打开后的句柄
#else
	void* mhDynamic;	//动态链接库打开后的句柄
#endif
};

#endif /*DEF_SINA_DYNAMIC_LINK_LIBRARY_H*/


