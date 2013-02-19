# /*! @makefile
# *******************************************************************************
# </PRE>
# ģ����       : Web PushServer��Makefile�ļ�
# �ļ���       : makefile
# ����ļ�     : ���е����.h�Լ�.cpp�ļ�
# �ļ�ʵ�ֹ��� : ������صķ���ϵͳ�Լ�Ӧ�ó���
# ����         : huangjun - ���˼���(�й�)
# �汾         : 1.0.1
# -------------------------------------------------------------------------------
# ��ע: 
# -------------------------------------------------------------------------------
# �޸ļ�¼: 
# ����        �汾        �޸���      �޸�����
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