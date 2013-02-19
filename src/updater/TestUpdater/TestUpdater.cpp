#include <iostream>

using namespace std;

#include "http.h"
#include <vld.h>

void callbackfun(void* p)
{
	char *info = (char*)p;
	cout<<info<<endl;
}

int main(int argv, char ** argc)
{
	if (argv < 2)
	{
		cout<<"user age : url path"<<endl<<"----url: Internet file path"<<endl<<"----path: local file path"<<endl;
	}

	CHttpBase http((WINNET_STATE_FUN)callbackfun);
	//http.Add(argc[1], argc[2]);
	http.Add("http://im.xiaonei.com/update/XiaoNeiUpdate.exe?2342", "D:/update.exe");

	Sleep(1000*60*3);

	system("pause");
	return 0;
}