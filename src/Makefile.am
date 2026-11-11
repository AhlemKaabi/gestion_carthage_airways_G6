## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = carthage_airways_g6

carthage_airways_g6_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	outils.c outils.h auth.c auth.h ecrans.h commun.h couleurs.h

carthage_airways_g6_LDADD = @PACKAGE_LIBS@

