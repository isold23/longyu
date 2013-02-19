#include <iostream>

using namespace std;

#include "http.h"
#include <vld.h>

static bool all_done = false;

void callbackfun(void* p)
{
	char *info = (char*)p;
	cout<<info<<endl;

    // TODO: all_done = true;
}

int main(int argv, char ** argc)
{
	CHttpBase http((WINNET_STATE_FUN)callbackfun);
	
    const char * url_arr = {
        "http://news.163.com/", // big file
        "http://google.com",    // redirect ???
        "http://im.xiaonei.com/update/XiaoNeiUpdate.exe",
        "http://www.google.com/notexist",   // error 
        "http://errorhost.com/file",        // host
        0
    };

    const char *p = url_arr;
    for (int i=0; i<sizeof(url_arr)/sizeof(*url_arr); ++i)
    {
        // ostringstream filename;
        // filename << "fn" << i;
        // http.Add(url_arr[i], filename.str());
    }

    while (!all_done)
        sleeep(100);
    
	system("pause");
	return 0;
}