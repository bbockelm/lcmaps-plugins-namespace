
AC_INIT(lcmaps-plugins-namspace,0.1.0,bbockelm@cse.unl.edu)
AC_PREREQ(2.57)
AM_INIT_AUTOMAKE([0.1 no-define foreign])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_LIBTOOL
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
if test "x${datadir}" == "xNONE" ; then
    datadir_resolved=${prefix_resolved}/libexec
else
    eval "datadir_resolved=\"${datadir}\""
    eval "datadir_resolved=\"${datadir_resolved}\""
fi
AC_SUBST(datadir_resolved)

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile src/lcmaps_namespace.c])
AC_OUTPUT

