/*! @hj_misc.cpp
*******************************************************************************
</PRE>
模块名       ：与进程处理相关库函数定义
文件名       ：hj_misc.cpp
相关文件     ：hj_misc.h
文件实现功能 ：与进程处理相关库函数定义
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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>

#include "hj_misc.h"

/* This ignores the SIGPIPE signal.  This is usually a good idea, since
   the default behaviour is to terminate the application.  SIGPIPE is
   sent when you try to write to an unconnected socket.  You should
   check your return codes to make sure you catch this error! */
void HJ_ignore_pipe(void)
{
  struct sigaction sig;

  sig.sa_handler = SIG_IGN;
  sig.sa_flags = 0;
  sigemptyset(&sig.sa_mask);
  sigaction(SIGPIPE, &sig, NULL);
}

/****************************************************************************
* 功能：把当前进程加入后台运行
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
void HJ_InitDaemon(void)
{
    pid_t pid;

    if ((pid = fork()) != 0)
    {
        exit(0);
    }

    setsid();

    signal(SIGINT,  SIG_IGN);
    signal(SIGHUP,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    HJ_ignore_pipe();

    if ((pid = fork()) != 0)
    {
        exit(0);
    }

    chdir("/");
    umask(0);
}

/****************************************************************************
* 功能：把当前进程的pid写入到指定文件
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
void HJ_CreatePIDFile(char *sPIDFile)
{
    if (sPIDFile == NULL)
    {
        // DEBUG_PRINT(LM_ERROR, "存在传入的指针参数为空！\n");
        return ;
    }

    FILE *pstFile = fopen(sPIDFile, "w");
    if (pstFile == NULL)
    {
        printf("%s: 打开文件(%s)失败！\n", __FUNCTION__, sPIDFile);
    }
    else
    {
        fprintf(pstFile, "%d", getpid());
        fclose(pstFile);
    }
}

/****************************************************************************
* 功能：扩展系统的一些限制参数
* 作者：huangjun
* 日期：2006-12-08
***************************************************************************/
int HJ_SetRLimit(void)
{
    //////////////////////////////////////////////////////////////////////////
    rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim);

    printf("The before of setting open file number: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);

    rlim.rlim_max = rlim.rlim_cur = (unsigned short)-1;
    if(setrlimit(RLIMIT_NOFILE, &rlim))
    {
        printf("Call setrlimit for RLIMIT_NOFILE failed!\n");
    }
    getrlimit(RLIMIT_NOFILE, &rlim);
    printf("The after of setting open file number: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);


    getrlimit(RLIMIT_CORE, &rlim);
    printf("The before of setting core dump: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);

    rlim.rlim_max = rlim.rlim_cur = (rlim_t)(-1);  // 25 is a magic number.
    if(setrlimit(RLIMIT_CORE, &rlim))
    {
        printf("Call setrlimit for RLIMIT_CORE failed!\n");
    }

    getrlimit(RLIMIT_CORE, &rlim) ;
    printf("The after of setting core dump: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);

    getrlimit(RLIMIT_STACK, &rlim);
    printf("The before of setting stack autoincrement: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);

    rlim.rlim_max = rlim.rlim_cur = (rlim_t)(-1);  // 25 is a magic number.
    if(setrlimit(RLIMIT_STACK, &rlim))
    {
        printf("Call setrlimit for RLIMIT_STACK failed!\n");
    }
    getrlimit(RLIMIT_STACK, &rlim);
    printf("The after of setting stack autoincrement: max(%lu) - cur(%lu)\n"
        , rlim.rlim_max, rlim.rlim_cur);
    //////////////////////////////////////////////////////////////////////////

    return 0;
}
