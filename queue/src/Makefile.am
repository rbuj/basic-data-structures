CC = gcc
AM_CFLAGS = -ggdb3 -O0 -fsanitize=address
AM_LDFLAGS = -O0 -fsanitize=address

lib_LTLIBRARIES = libqueue.la
libqueue_la_SOURCES = queue.c queue.h

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = libqueue.la
