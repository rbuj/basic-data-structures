CC = gcc
AM_CFLAGS = -ggdb3 -O0 -fsanitize=address
AM_LDFLAGS = -O0 -fsanitize=address

lib_LTLIBRARIES = liblist.la
liblist_la_SOURCES = list.c list.h

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = liblist.la
