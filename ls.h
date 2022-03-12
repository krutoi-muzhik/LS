#pragma once

#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdint.h>
#include <linux/types.h>
#include <time.h>
#include <pwd.h>
#include <getopt.h>
#include <string.h>


#define handle_error(cmd) \
	do { perror (cmd); exit (EXIT_FAILURE); } while (0)

struct linux_dirent {
	long d_ino;
	off_t d_off;
	unsigned short d_reclen;
	char d_name[];
};

struct linux_dirent64 {
	ino64_t d_ino;
	off64_t d_off;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[];
};

#define BUF_SIZE 1024

size_t IsDir (struct linux_dirent64 *d64);
char *PathUnite (const char *s1, const char *s2);
void LS (const char *name, int R, int a, int l, int i);
void PrintInode (struct linux_dirent64 *d64);
void PrintLong (struct linux_dirent64 *d64, const char *pathname);
