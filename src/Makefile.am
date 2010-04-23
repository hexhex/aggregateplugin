plugin_LTLIBRARIES = libdlvhexaggregateplugin.la

libdlvhexaggregateplugin_la_SOURCES = AggPluginInterface.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexaggregateplugin_la_LDFLAGS = -avoid-version -module

