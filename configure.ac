
AC_INIT(lcmaps-plugins-namespace,0.5.0,bbockelm@cse.unl.edu)
AC_PREREQ(2.57)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([no-define foreign])

AC_USE_SYSTEM_EXTENSIONS

AC_PROG_LIBTOOL([disable-static])
AC_PROG_CC

AC_ARG_WITH([moduledir],
  [AS_HELP_STRING([--with-moduledir=path],
    [Specify the install location of the plug-ins])],
[
        AC_SUBST([MODULEDIR], [$withval])
],
[
        AC_SUBST([MODULEDIR], ['${libdir}/lcmaps'])
])

if test "x${prefix}" == "xNONE" ; then
    prefix_resolved=${ac_default_prefix}
    prefix=${ac_default_prefix}
else
    eval "prefix_resolved=\"${prefix}\""
fi
if test "x${libexecdir}" == "xNONE" ; then
    libexecdir_resolved=${prefix_resolved}/libexec
else
    eval "libexecdir_resolved=\"${libexecdir}\""
    eval "libexecdir_resolved=\"${libexecdir_resolved}\""
fi
AC_SUBST(prefix_resolved)
AC_SUBST(libexecdir_resolved)

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile src/lcmaps_namespace.c])
AC_OUTPUT

