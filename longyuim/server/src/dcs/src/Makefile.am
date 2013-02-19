# header files
h_sources = PackDef/dcs_dns.h \
DCSInclude.h \
DCSConfig.h \
DCSDealData.h \
DCSWorker.h

# cpp files
cpp_sources = PackDef/dcs_dns.cpp \
DCSConfig.cpp \
DCSDealData.cpp \
DCSWorker.cpp \
DispatchCenterServer.cpp

bin_PROGRAMS = dcs
INCLUDES = -I$(top_srcdir)/Common -I./PackDef -I./
bindir = $(prefix)/dcs/bin
dcs_LDADD = $(top_srcdir)/Common/libCommon.la
dcs_SOURCES = $(h_sources) $(cpp_sources)