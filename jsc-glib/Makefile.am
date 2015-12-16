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
	jsc-enumtypes.c \
	jsc-error.c \
	converter.c
libjsc_glib_1_0_la_LDFLAGS = -version-info 1:0:0
libjsc_glib_1_0_la_LIBADD = $(JSC_GLIB_LIBS)


jscincludedir = $(includedir)/jsc-glib-1.0/jsc-glib
jscinclude_HEADERS = \
	jsc-glib.h \
	jsc-context.h \
	jsc-object.h \
	jsc-value.h \
	jsc-enumtypes.h \
	jsc-error.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = jsc-glib-1.0.pc


# glib-mkenums
enum_headers = $(filter-out jsc-enumtypes.h,$(jscinclude_HEADERS))

jsc-enumtypes.c: $(enum_headers) jsc-enumtypes.c.template
	glib-mkenums --identifier-prefix JSC \
	    --template $(filter %.template,$^) \
	    $(filter-out %.template,$^) > $(srcdir)/jsc-enumtypes.c
	    
jsc-enumtypes.h: $(enum_headers) jsc-enumtypes.h.template
	glib-mkenums --identifier-prefix JSC \
	    --template $(filter %.template,$^) \
	    $(filter-out %.template,$^) > $(srcdir)/jsc-enumtypes.h

BUILT_SOURCES = \
	jsc-enumtypes.c \
	jsc-enumtypes.h

CLEANFILES = $(pkgconfig_DATA) $(BUILT_SOURCES)

# intospection
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION
INTROSPECTION_GIRS = JSC-1.0.gir

introspection_source = \
	$(libjsc_glib_1_0_la_SOURCES) \
	$(jscinclude_HEADERS)

JSC-1.0.gir: libjsc-glib-1.0.la Makefile

JSC_1_0_gir_VERSION = 1.0
JSC_1_0_gir_LIBS = libjsc-glib-1.0.la
JSC_1_0_gir_FILES = $(introspection_source)
JSC_1_0_gir_CFLAGS = -I$(top_srcdir) -I$(top_builddir) $(JSC_GLIB_CFLAGS)
JSC_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0
JSC_1_0_gir_SCANNERFLAGS = --warn-all --identifier-prefix=JSC --symbol-prefix=jsc --pkg-export jsc-glib-1.0 --c-include "jsc-glib/jsc-glib.h"

girdir = $(datadir)/gir-1.0
dist_gir_DATA = JSC-1.0.gir

typelibsdir = $(libdir)/girepository-1.0/
typelibs_DATA = JSC-1.0.typelib

CLEANFILES += $(dist_gir_DATA) $(typelibs_DATA) jsc-glib-1.0.gi
endif # HAVE_INTROSPECTION


EXTRA_DIST = \
	private.h \
	jsc-glib-1.0.pc.in \
	jsc-enumtypes.c.template \
	jsc-enumtypes.h.template

-include $(top_srcdir)/git.mk
