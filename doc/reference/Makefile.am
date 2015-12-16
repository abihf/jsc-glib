DOC_MODULE = jsc-glib
DOC_MAIN_SGML_FILE = $(DOC_MODULE)-docs.xml
DOC_SOURCE_DIR = $(top_srcdir)/jsc-glib $(top_builddir)/jsc-glib

SCANGOBJ_OPTIONS =
SCAN_OPTIONS = --deprecated-guards="JSC_DISABLE_DEPRECATED" --rebuild-types
MKDB_OPTIONS = --output-format=xml --name-space=jsc
MKTMPL_OPTIONS =
FIXXREF_OPTIONS = \
	--extra-dir=$(GLIB_PREFIX)/share/gtk-doc/html/glib \
	--extra-dir=$(GLIB_PREFIX)/share/gtk-doc/html/gobject 

HFILE_GLOB = $(top_srcdir)/jsc-glib/*.h $(top_builddir)/jsc-glib/*.h
CFILE_GLOB = $(top_srcdir)/jsc-glib/*.c

IGNORE_HFILES = \
	private.h

EXTRA_HFILES =

HTML_IMAGES =

content_files = \
	version.xml

expand_content_files =

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) $(JSC_GLIB_CFLAGS)
GTKDOC_LIBS = $(top_builddir)/jsc-glib/libjsc-glib-1.0.la $(JSC_GLIB_LIBS)

include $(top_srcdir)/gtk-doc.make

EXTRA_DIST += version.xml.in


TESTS_ENVIRONMENT = \
	DOC_MODULE=$(DOC_MODULE) \
	DOC_MAIN_SGML_FILE=$(DOC_MAIN_SGML_FILE) \
	SRCDIR=$(abs_srcdir) \
	BUILDDIR=$(abs_builddir)


-include $(top_srcdir)/git.mk
