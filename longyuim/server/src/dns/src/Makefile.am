# header files
h_sources = PackDef/dns_crs.h \
PackDef/dcs_dns.h \
DNSInclude.h \
DNSConfig.h \
DNSDealData.h \
DNSChildWorker.h \
DNSWorker.h

# cpp files
cpp_sources = PackDef/dns_crs.cpp \
PackDef/dcs_dns.cpp \
DNSConfig.cpp \
DNSDealData.cpp \
DNSChildWorker.cpp \
DNSWorker.cpp \
DispatchNodeServer.cpp

bin_PROGRAMS = dns
INCLUDES = -I$(top_srcdir)/Common -I./PackDef -I./
bindir = $(prefix)/dns/bin
dns_LDADD = $(top_srcdir)/Common/libCommon.la
dns_SOURCES = $(h_sources) $(cpp_sources)