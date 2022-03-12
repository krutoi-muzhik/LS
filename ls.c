#include "ls.h"

void LS (const char *name, int R, int a, int l, int i) {
	int fd, nread;
	char buf[BUF_SIZE];
	struct linux_dirent *d;
	struct linux_dirent64 *d64;
	int bpos = 0;
	char d_type;
	struct passwd *pws;

	char *pathname = (char *) calloc (1024, sizeof (char));
	strcpy (pathname, name);

	int str = strcmp (name, ".");

	if ((fd = open (name, O_RDONLY | O_DIRECTORY)) == -1)
		handle_error ("open");
	if (R)
		printf ("%s/:\n", name);

	do {
		bpos = 0;
		if ((nread = getdents64 (fd, buf, BUF_SIZE)) == -1)
			handle_error ("getdents64");

		while (bpos < nread) {
			d64 = (struct linux_dirent64 *) (buf + bpos);
			bpos += d64->d_reclen;

			if (!a && (d64->d_name[0] == '.'))
				continue;

			if (i) {
				if (l)
					printf ("%17ld  ", d64->d_ino);
				else
					printf ("%ld  ", d64->d_ino);
			}

			if (str)
				pathname = PathUnite (name, d64->d_name);

			if (l)
				PrintLong (d64, pathname);
			else 
				printf ("%s  ", d64->d_name);
		}
		printf ("\n");

		if (R) {
			bpos = 0;
			while (bpos < nread) {
				d64 = (struct linux_dirent64 *) (buf + bpos);
				bpos += d64->d_reclen;

				if (d64->d_name[0] == '.') {
					continue;
				}

				if (IsDir (d64)) {
					printf ("\n");
					pathname = PathUnite (name, d64->d_name);
					LS (pathname, R, a, l, i);
				}
			}
		}
	} while (!nread);

	if (close (fd) == -1)
		handle_error ("close");
	return;
}

void PrintLong (struct linux_dirent64 *d64, const char *pathname) {
	struct stat statbuf;
	if (stat (pathname, &statbuf) == -1) {
		printf ("\n\n%s\n\n", pathname);
		handle_error ("stat");
	}

	mode_t mode = statbuf.st_mode;
	for (int i = 1; i < 512; i *= 2) {
		if (mode & i) printf ("r");
		else printf ("-");
		i *= 2;
		if (mode & i) 
			printf ("w");
		else 
			printf ("-");
		i *= 2;
		if (mode & i) printf ("x");
		else printf ("-");
	}

	printf ("  ");
	printf ("%8ld  ", statbuf.st_size);
	switch (d64->d_type) {
		case DT_BLK:
			printf ("block device");
			break;
		case DT_CHR:
			printf ("character device");
			break;
		case DT_DIR:
			printf ("directory");
			break;
		case DT_FIFO:
			printf ("fifo     ");
			break;
		case DT_LNK:
			printf ("softlink ");
			break;
		case DT_REG:
			printf ("  file   ");
			break;
		case DT_SOCK:
			printf ("UNIX domain socket");
			break;
		case DT_UNKNOWN:
			printf ("unknown type");
			break;
		default:
			printf ("????????????");
	}
	printf ("  ");

	struct passwd *pws;
	if ((pws = getpwuid (statbuf.st_gid)) == NULL)
		handle_error ("getpwuid");
	printf ("%s (%d)  ", pws->pw_name, pws->pw_uid);

	char *time = ctime (&statbuf.st_mtime);
	time[strlen(time) - 1] = ' ';
	printf ("%s ", time);
	printf ("%s\n", d64->d_name);
	
	return;
}

char *PathUnite (const char *s1, const char *s2) {
	size_t len1 = strlen (s1);
	size_t len2 = strlen (s2);

	char *result = calloc (len1 + len2 + 1, sizeof (char));
	memcpy (result, s1, len1);
	result[len1] = '/';
	memcpy (result + len1 + 1, s2, len2);
	//printf ("\n\n\n%s\n\n\n", result);
	//result[len1 + len2 + 1] = ' ';

	return result;
}

size_t IsDir (struct linux_dirent64 *d64) {
	return (d64->d_type == DT_DIR);
}
