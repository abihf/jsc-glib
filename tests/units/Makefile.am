## Process this file with automake to produce Makefile.in

TESTS = test

noinst_PROGRAMS =  \
	test

test_SOURCES =  \
	main.c \
	shared.h \
	context.c

test_LDADD = $(JSC_GLIB_LIBS) ../../jsc-glib/libjsc-glib-1.0.la

AM_CPPFLAGS = $(JSC_GLIB_CFLAGS) -I$(top_srcdir)

-include $(top_srcdir)/git.mk
