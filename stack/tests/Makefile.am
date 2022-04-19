AM_CFLAGS = -ggdb3 -O0 -fsanitize=address
AM_LDFLAGS = -O0 -fsanitize=address

TESTS = check_stack
check_PROGRAMS = check_stack
check_stack_SOURCES = check_stack.c $(top_builddir)/src/stack.h
check_stack_CFLAGS = @CHECK_CFLAGS@
check_stack_LDADD = $(top_builddir)/src/libstack.la @CHECK_LIBS@
