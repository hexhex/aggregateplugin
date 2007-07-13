AUTOMAKE_OPTIONS = foreign

#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexplugin_la_SOURCES = plugin.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(DLVHEX_CFLAGS)

#
# replace 'plugin' on the left side as above and
# add other needed libs to linker flags if necessary
#
libdlvhexplugin_la_LDFLAGS = -avoid-version -module

