//Oskar Cieślikiewicz 36010 211A 06.03.17r. ZUT Systemy Operacyjne II

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


main( int argc, char **argv)
{
printf("  #########################################################################\n");
printf(" ##                                                                       ##\n");
printf("##   Oskar Cieslikiewicz 36010 211A 06.03.17r. ZUT Systemy Operacyjne II   ##\n");
printf(" ##                                                                       ##\n");
printf("  #########################################################################\n\n");

//./zad1 x -a -c 10 a b

	int aflag = 0, bflag = 0, ret, index;
	char *cvalue = NULL;
	opterr = 0; //no default "invalid option" info


	while ((ret = getopt (argc, argv, "abc:")) != -1)
		{
		switch (ret) 
			{
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			return 1;
			default: abort ();
			}
		}


	printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);
	printf ("non-option arguments: ");

	for (index = optind; index < argc; index++)
	{
		printf (" %s ", argv[index]);
		printf ("\n");
	}
	for (index = 1; index < argc; index++) printf ("argv[%d]:%s ", index, argv[index]);

return 0;
}