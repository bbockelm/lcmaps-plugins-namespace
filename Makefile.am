

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = \
	-Werror \
	-Wall \
	-Wp,-D_FORTIFY_SOURCE=2 \
	$(LCMAPS_CFLAGS)

EXTRA_DIST = bootstrap lcmaps-plugins-namespace.spec

plugindir = $(MODULEDIR)
plugin_LTLIBRARIES = \
	liblcmaps_namespace.la

liblcmaps_namespace_la_SOURCES = \
	src/lcmaps_namespace.c

liblcmaps_namespace_la_LDFLAGS = -avoid-version

progdatadir = $(datadir)/lcmaps-plugins-namespace
progdata_PROGRAMS = lcmaps-namespace-init

lcmaps_namespace_init_SOURCES = \
	src/pid_ns_init.c

install-data-hook:
	( \
	cd $(DESTDIR)$(plugindir); \
	for mod in mount_under_scratch ; do \
	    rm -f lcmaps_$$mod.mod; \
	    ln -s liblcmaps_$$mod.so.0.0.0 lcmaps_$$mod.mod; \
	done \
	)

