#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#if defined(__linux__) || defined(__APPLE__)
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#define __stdcall 
#endif

#ifdef _WIN32

#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")
#include <sys/timeb.h>
#include <time.h>
#define  timeb _timeb

#endif

#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <cassert>
#include <list>
#include <map>
#include <exception>

using namespace std;

#include "define.h"
#include "pack/StandardSerialize.h"
#include "CriticalSection.h"
#include "Common.h"

#endif //_INCLUDE_H_






