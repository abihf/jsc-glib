## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(JSC_GLIB_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libjsc-glib-1.0.la

libjsc_glib_1_0_la_SOURCES = \
	jsc-context.c \
	jsc-object.c \
	jsc-value.c \
	private.h \
	jsc-enumtypes.c \
	jsc-error.c

libjsc_glib_1_0_la_LDFLAGS = -version-info 1:0:0

libjsc_glib_1_0_la_LIBADD = $(JSC_GLIB_LIBS)


jscincludedir = $(includedir)/jsc-glib-1.0
jscinclude_HEADERS = \
	jsc-glib.h \
	jsc-context.h \
	jsc-object.h \
	jsc-value.h \
	jsc-enumtypes.h \
	jsc-error.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = jsc-glib-1.0.pc


enum_headers = $(filter-out jsc-enumtypes.h,$(jscinclude_HEADERS))

jsc-enumtypes.c: $(enum_headers) jsc-enumtypes.c.template
	glib-mkenums --identifier-prefix JSC \
	    --template jsc-enumtypes.c.template \
	    $(enum_headers) > $(srcdir)/jsc-enumtypes.c
	    

jsc-enumtypes.h: $(enum_headers) jsc-enumtypes.h.template
	glib-mkenums --identifier-prefix JSC \
	    --template jsc-enumtypes.h.template \
	    $(enum_headers) > $(srcdir)/jsc-enumtypes.h

BUILT_SOURCES = \
	jsc-enumtypes.c \
	jsc-enumtypes.h

DISTCLEANFILES = \
	jsc-enumtypes.c \
	jsc-enumtypes.h

EXTRA_DIST = \
	jsc-glib-1.0.pc.in \
	jsc-enumtypes.c.template \
	jsc-enumtypes.h.template

-include $(top_srcdir)/git.mk
