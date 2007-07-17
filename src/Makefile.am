AUTOMAKE_OPTIONS = foreign

plugin_LTLIBRARIES = libdlvhexaggregateplugin.la

libdlvhexaggregateplugin_la_SOURCES = AggPluginInterface.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(DLVHEX_CFLAGS)

libdlvhexaggregateplugin_la_LDFLAGS = -avoid-version -module

