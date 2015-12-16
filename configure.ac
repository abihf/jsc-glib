dnl ***************************************************************************
dnl JSCGLib 
dnl ***************************************************************************
AC_INIT(jsc-glib, 
	0.1.1,
	http://github.com/abihf/jsc-glib/issues,
	jsc-glib,
	http://github.com/abihf/jsc-glib)


dnl ***************************************************************************
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([jsc-glib/jsc-glib.h])
AC_CONFIG_MACRO_DIR(m4)


dnl ***************************************************************************
dnl Automake
dnl ***************************************************************************
AM_INIT_AUTOMAKE([1.11 no-define foreign -Wno-portability dist-xz no-dist-gzip
	tar-ustar subdir-objects])
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])


dnl ***************************************************************************
dnl Libtool
dnl ***************************************************************************
LT_PREREQ([2.2.6])
LT_INIT([dlopen])

dnl ***************************************************************************
dnl check for required applications
dnl ***************************************************************************
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P


dnl ***************************************************************************
dnl Headers & libraries
dnl ***************************************************************************
PKG_CHECK_MODULES(JSC_GLIB, [glib-2.0 gobject-2.0 javascriptcoregtk-4.0])


dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
GETTEXT_PACKAGE=jsc-glib
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])


dnl ***************************************************************************
dnl Introspection
dnl ***************************************************************************
GOBJECT_INTROSPECTION_CHECK([0.9.5])

dnl ***************************************************************************
dnl Documentation
dnl ***************************************************************************
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])

GLIB_PREFIX="`$PKG_CONFIG --variable=prefix glib-2.0`"
AC_SUBST(GLIB_PREFIX)


dnl ***************************************************************************
dnl Test Suite
dnl ***************************************************************************
AC_ARG_ENABLE(test,
	AC_HELP_STRING([--enable-test], [enable test. [default=yes]]),
	[want_test=$enableval],
	[want_test="yes"])
AM_CONDITIONAL([ENABLE_TEST], test "x$want_test" = "xyes")
AC_SUBST(ENABLE_TEST)
#GLIB_TESTS


dnl ***************************************************************************
dnl DONE
dnl ***************************************************************************
AC_CONFIG_FILES([
	Makefile
	jsc-glib/Makefile
	jsc-glib/jsc-glib-1.0.pc
	po/Makefile.in
	doc/Makefile
	doc/reference/Makefile
	doc/reference/version.xml
	tests/Makefile
	tests/units/Makefile
])
AC_OUTPUT
