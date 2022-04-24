lib_LTLIBRARIES = liblist.la libqueue.la libstack.la

liblist_la_SOURCES = list.c list.h

libqueue_la_SOURCES = queue.c queue.h
libqueue_la_LIBADD = liblist.la

libstack_la_SOURCES = stack.c stack.h
libstack_la_LIBADD = liblist.la

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = liblist.la
