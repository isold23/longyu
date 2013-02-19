
/****************************************************************************************************************************
版本声明：	北京新浪信息技术有限责任公司
文件名：	DynamicLib.h
创建人：	张亚伟
创建日期：	2006-12-07
说明：		封装跨平台动态库调用使用的函数，供外界调用动态库使用
版本号：	1.00.000
*****************************************************************************************************************************/

#include "DynamicLib.h"

//构造函数
CDynamicLib::CDynamicLib(void){
	mhDynamic = NULL;
}

//析构函数
CDynamicLib::~CDynamicLib(void){
	CloseDynamicLib();
}

//根据文件名称，装入制定动态库
bool CDynamicLib::LoadDynamicLib(const char* apFileName){
	char lszName[512];
	memset(lszName, 0, 512);

#ifdef WIN32
	sprintf(lszName, "%s%s", apFileName, ".dll");
	mhDynamic = LoadLibrary(lszName);
#else
	sprintf(lszName, "%s%s", apFileName, ".so");
	mhDynamic = dlopen(lszName, RTLD_NOW);

	if (NULL == mhDynamic){
		printf("CDynamicLib::LoadDynamicLib error:%s!", dlerror());
	}
#endif

	return (NULL != mhDynamic);
}

//取得制定函数的地址
void* CDynamicLib::GetDynamicLibFun(const char* apFunName){
	if (NULL == mhDynamic){
		return NULL;
	}

#ifdef WIN32
	return GetProcAddress(mhDynamic, apFunName);
#else
	return dlsym(mhDynamic, apFunName);
#endif
}

//关闭打开的动态链接库
void CDynamicLib::CloseDynamicLib(){
	if (NULL == mhDynamic){
		return;
	}

#ifdef WIN32
	FreeLibrary(mhDynamic);
#else
	dlclose(mhDynamic);
#endif
	mhDynamic = NULL;
}


