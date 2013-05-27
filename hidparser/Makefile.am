
AM_CPPFLAGS = -I$(top_srcdir)/hidapi/

hdrdir = $(includedir)/hidapi
hdr_HEADERS = $(top_srcdir)/hidapi/hidparse.h

EXTRA_DIST =



noinst_PROGRAMS = hidparse

hidparse_SOURCES = testparse.c hidparse.c
hidparse_LDADD = $(top_builddir)/$(backend)/libhidapi.la
