dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(jsc-glib, 0.1.1, http://github.com/abihf/jsc-glib/issues, jsc-glib, http://github.com/abihf/jsc-glib)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([jsc-glib/jsc-glib.h])
AC_CONFIG_MACRO_DIR(m4)

AM_INIT_AUTOMAKE([1.11 no-define foreign -Wno-portability dist-xz no-dist-gzip tar-ustar subdir-objects])
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])

AC_PROG_CC
AM_PROG_CC_C_O

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************

GETTEXT_PACKAGE=jsc-glib
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

LT_PREREQ([2.2.6])
LT_INIT([dlopen])

PKG_CHECK_MODULES(JSC_GLIB, [javascriptcoregtk-4.0 glib-2.0 ])

dnl =============================gtk-doc=======================================
# check for gtk-doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])
dnl === Test suite ============================================================

GLIB_TESTS

dnl === GLIB PREFIX ============================================================

GLIB_PREFIX="`$PKG_CONFIG --variable=prefix glib-2.0`"
AC_SUBST(GLIB_PREFIX)


AC_OUTPUT([
Makefile
jsc-glib/jsc-glib-1.0.pc
jsc-glib/Makefile
po/Makefile.in
tests/Makefile
tests/units/Makefile
doc/Makefile
doc/reference/Makefile
doc/reference/version.xml

])
