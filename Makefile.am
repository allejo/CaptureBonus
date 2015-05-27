lib_LTLIBRARIES = CaptureBonus.la

CaptureBonus_la_SOURCES = CaptureBonus.cpp
CaptureBonus_la_CXXFLAGS= -I$(top_srcdir)/include -I$(top_srcdir)/plugins/plugin_utils
CaptureBonus_la_LDFLAGS = -module -avoid-version -shared
CaptureBonus_la_LIBADD = $(top_builddir)/plugins/plugin_utils/libplugin_utils.la

AM_CPPFLAGS = $(CONF_CPPFLAGS)
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

EXTRA_DIST = \
	README.txt \
	CaptureBonus.def \
	CaptureBonus.sln \
	CaptureBonus.vcxproj

MAINTAINERCLEANFILES =	\
	Makefile.in
