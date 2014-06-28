CLEANFILES = *~
DISTCLEANFILES =
MAINTAINERCLEANFILES = Makefile.in

include $(top_srcdir)/.buildvars

pkglib_LTLIBRARIES = SimpleTrace.la

SimpleTrace_la_LDFLAGS = -module -avoid-version

SimpleTrace_la_SOURCES = \
		SimpleTrace.h \
		SimpleTrace.cpp
