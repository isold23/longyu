# /*! @makefile
# *******************************************************************************
# </PRE>
# 模块名       ：libhj库构建makefile
# 文件名       ：makefile
# 相关文件     ：所有相关的头文件和库文件
# 文件实现功能 ：构造libhj库
# 作者         ：huangjun - 神州星国际(http://www.shenzhoustar.com)
# 版本         ：1.0.1
# -------------------------------------------------------------------------------
# 备注：
# -------------------------------------------------------------------------------
# 修改记录：
# 日期        版本        修改人      修改内容
# 20080731    1.0.1       Huangjun    Created
# </PRE>
# ******************************************************************************/

INSTALL_INC_DIR = ../include
INSTALL_LIB_DIR = ../lib

INC_MYSQL = -I/usr/include/mysql
#LIB_MYSQL = -L/usr/lib/mysql -lmysqlclient

INC_ALL = $(INC_MYSQL)
#LIB_ALL = $(LIB_MYSQL)

SRCINCS := $(wildcard *.h)
DSTINCS := $(patsubst %, $(INSTALL_INC_DIR)/%, $(SRCINCS))

LCLSRCS := $(wildcard *.c *.cpp)
LCLOBJS := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(LCLSRCS)))

SRCLIB := libhj.a
DSSFL := $(patsubst %, $(INSTALL_LIB_DIR)/%, $(SRCLIB))

CXX = g++
GCC = gcc

CFLAGS = -g -O -Wall -DNDEBUG

.SUFFIXES: .o .c .cpp

all: $(SRCLIB)

.c.o :
	$(GCC) $(CFLAGS) -o $@ $(INC_ALL) -c $<

.cpp.o :
	$(CXX) $(CFLAGS) -o $@ $(INC_ALL) -c $<

$(SRCLIB) : $(LCLOBJS)
	@ar -rs $@ $^
	@echo Build successful!

rebuild : clean all

install : all
	@cp $(SRCINCS) $(INSTALL_INC_DIR)/
	@cp $(SRCLIB)  $(INSTALL_LIB_DIR)/
	@echo Install successful!

uninstall :
	@rm -f $(DSTINCS) $(DSSFL)
	@echo Uninstall complete!
	
clean :
	@rm -f $(SRCLIB) $(LCLOBJS) $~
