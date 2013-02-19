# /*! @makefile
# *******************************************************************************
# </PRE>
# 模块名       : Web PushServer的Makefile文件
# 文件名       : makefile
# 相关文件     : 所有的相关.h以及.cpp文件
# 文件实现功能 : 构建相关的服务系统以及应用程序
# 作者         : huangjun - 新浪技术(中国)
# 版本         : 1.0.1
# -------------------------------------------------------------------------------
# 备注: 
# -------------------------------------------------------------------------------
# 修改记录: 
# 日期        版本        修改人      修改内容
# 20081202    1.0.0       huangjun    Created
# </PRE>
# ******************************************************************************/

INSTALL_BIN_DIR = ../bin/

INC_COMM = -I/usr/local/hj_lib/include
LIB_COMM = -L/usr/local/hj_lib/lib -lhj -lpthread

INC_ALL = $(INC_COMM)
LIB_ALL = $(LIB_COMM)

OUTPUT = mps_srv mps_msg_trans

CFLAGS = -g -Wall -O2 #-DNDEBUG

CXX = g++
GCC = gcc

.SUFFIXES: .o .c .cpp

.c.o :
	$(GCC) $(CFLAGS) -o $@ $(INC_ALL) -c $<

.cpp.o :
	$(CXX) $(CFLAGS) -o $@ $(INC_ALL) -c $<

.o :
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB_ALL)

all : $(OUTPUT)
strip : all
	strip $(OUTPUT)

install : all
	mv mps_srv $(INSTALL_BIN_DIR)
	mv mps_msg_trans $(INSTALL_BIN_DIR)
	rm * -f
	
rebuild : clean all
clean :
	rm -f $(OUTPUT) *.o *~
once :
	touch *.cpp *.c *.h makefile
	make install
	rm -Rf *

mps_srv : mps_srv.o mps_usrinfo_acs.o
mps_msg_trans : mps_msg_trans.o
