#include "ls.h"

int main (int argc, char* argv[]) {
	int opt = 0;
	int R = 0, a = 0, l = 0, i = 0;	

	while ((opt = getopt (argc, argv, "Rali")) != -1) {
		switch (opt) {
			case 'R':
				R = 1;
				break;
			case 'a':
				a = 1;
				break;
			case 'l':
				l = 1;
				break;
			case 'i':
				i = 1;
				break;
			default:
				printf ("Usage of unknown flag \nOnly -R -a -l -i flags are supported\n");
				exit (EXIT_FAILURE);
		}
	}
	
	LS (argc > optind ? argv[optind] : ".", R, a, l, i);
	exit (EXIT_SUCCESS);
}
