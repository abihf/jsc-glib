dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(jsc-glib, 0.9.0, http://github.com/abihf/jsc-glib)
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11  -Wno-portability])
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
GTK_DOC_CHECK(1.9)

AC_OUTPUT([
Makefile
jsc-glib/jsc-glib-1.0.pc
jsc-glib/Makefile
po/Makefile.in
tests/Makefile
tests/units/Makefile])
