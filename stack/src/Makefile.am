CC = gcc
AM_CFLAGS = -ggdb3 -O0 -fsanitize=address
AM_LDFLAGS = -O0 -fsanitize=address

lib_LTLIBRARIES = libstack.la
libstack_la_SOURCES = stack.c stack.h

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = libstack.la
