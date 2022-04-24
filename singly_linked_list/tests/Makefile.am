TESTS = check_list check_queue check_stack
check_PROGRAMS = check_list check_queue check_stack

check_list_SOURCES = check_list.c $(top_builddir)/src/list.h
check_list_CFLAGS = @CHECK_CFLAGS@
check_list_LDADD = $(top_builddir)/src/liblist.la @CHECK_LIBS@

check_queue_SOURCES = check_queue.c $(top_builddir)/src/queue.h
check_queue_CFLAGS = @CHECK_CFLAGS@
check_queue_LDADD = $(top_builddir)/src/libqueue.la @CHECK_LIBS@

check_stack_SOURCES = check_stack.c $(top_builddir)/src/stack.h
check_stack_CFLAGS = @CHECK_CFLAGS@
check_stack_LDADD = $(top_builddir)/src/libstack.la @CHECK_LIBS@
