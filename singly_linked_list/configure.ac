AC_INIT([List], [0.1], [https://github.com/rbuj/basic-data-structures/issues])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
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
              AC_HELP_STRING([--enable-sanitize], [turn on profiler]))
if test x"$enable_profile" = xyes
then
    CFLAGS="$CFLAGS -pg -g"
fi

AC_ARG_ENABLE(sanitize,
              AC_HELP_STRING([--enable-sanitize], [turn on address sanitizer]))
if test x"$enable_sanitizee" = xyes
then
  CFLAGS="$CFLAGS -O0 -fsanitize=address"
  LDFLAGS="$LDFLAGS -O0 -fsanitize=address"
fi

AC_PROG_LIBTOOL
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])
AC_OUTPUT
