AC_INIT([Stack], [0.1], [https://github.com/rbuj/basic-data-structures/issues])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR

AC_PROG_CC
if test x"$GCC" = xyes
then
    CFLAGS="$CFLAGS -W -Wall -Wimplicit \
-Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings \
-Waggregate-return -Wstrict-prototypes -Wmissing-prototypes \
-Wnested-externs -Wconversion -Wpointer-arith -Wmissing-declarations"
    AC_MSG_NOTICE([Adding gcc options: $CFLAGS])
fi

AC_ARG_ENABLE(profile,
              AC_HELP_STRING([--enable-profile], [turn on profiler]),,
              enable_profile=no)
if test x"$enable_profile" = xyes
then
    CFLAGS="$CFLAGS -pg -g"
fi

AC_ARG_ENABLE(sanitize,
              AC_HELP_STRING([--enable-sanitize], [turn on address sanitizer]),,
              enable_sanitize=no)
if test x"$enable_sanitizee" = xyes
then
  CFLAGS="$CFLAGS -O0 -fsanitize=address"
  LDFLAGS="$LDFLAGS -O0 -fsanitize=address"
fi

AC_PROG_LIBTOOL
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AC_CONFIG_HEADERS([config.h])

AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)

AC_OUTPUT([
  Makefile
  src/Makefile
  tests/Makefile
])

echo "
configure summary:

  $PACKAGE_STRING
  `echo $PACKAGE_STRING | sed "s/./=/g"`

  compuler ............ $CC
  cflags .............. $CFLAGS
  link flags .......... $LDFLAGS

  profile support ..... $enable_profile
  sanitize support .... $enable_profile
"
