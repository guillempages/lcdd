INCLUDES = -I$(top_srcdir)/include

noinst_LIBRARIES = libaux.a 
lib_LTLIBRARIES = liblcd.la
sbin_PROGRAMS = lcdd
bin_PROGRAMS = lcdwrite

check_PROGRAMS = lcdTest

TESTS=$(check_PROGRAMS)

libaux_a_SOURCES = auxfunctions.c

liblcd_la_SOURCES = lcdCommon.c lcdCommonCXX.cpp
liblcd_la_LDFLAGS = -version-info 0:0:0

lcdd_SOURCES = lcdd.cpp
lcdd_LDADD = libaux.a

lcdwrite_SOURCES = lcdwrite.cpp
lcdwrite_LDADD = liblcd.la

lcdTest_SOURCES = lcdTest.cpp
lcdTest_LDADD = liblcd.la
