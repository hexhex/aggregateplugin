plugin_LTLIBRARIES = libdlvhexplugin-aggregate.la

libdlvhexplugin_aggregate_la_SOURCES = 	AggPlugin.cpp \
										AggAtom.cpp \
										MinAtom.cpp \
										MaxAtom.cpp \
										CountAtom.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_aggregate_la_LDFLAGS = -avoid-version -module

