libcommon_a_SOURCES = md5.cpp \
Common.cpp \
LMEnDecrypt.cpp \
TimeStamp.cpp \
ThreadGroup.cpp \
CriticalSection.cpp \
debugtrace.cpp \
StandardSerialize.cpp \
NetPack.cpp \
NetSocket.cpp \
NetEpoll.cpp \
UdpSocket.cpp \
Configure.cpp \
DynamicLib.cpp \
TcpStream.cpp \
libnet.cpp \
HostIpCache.cpp \
HttpClient.cpp \
FileStatManager.cpp

libcommon_a_HEADERS = define.h \
md5.h \
list.h \
Common.h \
LMEnDecrypt.h \
SafeList.h \
TimeStamp.h \
ThreadGroup.h \
Pool.h \
sigslot.h \
CriticalSection.h \
debugtrace.h \
StandardSerialize.h \
BasePack.h \
include.h \
NetAddress.h \
NetPack.h \
NetSocket.h \
NetEpoll.h \
UdpSocket.h \
Configure.h \
DynamicLib.h \
TcpStream.h \
libnet.h \
HostIpCache.h \
HttpClient.h \
FileStatManager.h \
base64.h \
BaseEncrypt.h 

AUTOMAKE_OPTIONS=foreign
AM_CXXFLAGS = -fPIC
libdir=$(top_srcdir)/common/lib
libcommon_adir=$(top_srcdir)/common/include
lib_LIBRARIES = libcommon.a
common_a_LDADD = -lssl
