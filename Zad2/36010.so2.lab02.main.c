//SO2 IS1 211A LAB02
//Oskar Cieślikiewicz
//ocieslikiewicz@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <dlfcn.h>

void usrPID(char* username);

main( int argc, char **argv)
{
printf("  #########################################################################\n");
printf(" ##                                                                       ##\n");
printf("##   Oskar Cieslikiewicz 36010 211A 06.03.17r. ZUT Systemy Operacyjne II   ##\n");
printf(" ##                                                                       ##\n");
printf("  #########################################################################\n\n");

//./zad1 x -a -c 10 a b

	int ret, index;
	char *cvalue = NULL;
	opterr = 0; //no default "invalid option" info

	
	
	utmpname("/var/run/utmp");

	struct utmp *get_usr;
	struct group *get_list;
	struct psswd *get_pwid;
	gid_t *groups;
	int param = 0;
	
	void *lib = dlopen( "./libzad2.so", RTLD_LAZY);
	
	//printf("get = %s", *get);
	
	while ((ret = getopt (argc, argv, "abc:")) != -1)
		{
		switch (ret) 
			{
			case 'a':
				
				if(lib)
				{
				
				param = 1;
				
				void (*usrPID)(char*);
				usrPID = dlsym(lib, "get_userPID");
				while((get_usr = getutent()) != NULL)
				{
					//printf("====  %d  =====\n", get_usr->ut_type);
					if((get_usr->ut_type) == 7)
					{
					//printf("====  %s  =====\n", get_usr->ut_user);
					usrPID(get_usr->ut_user);
					}
				}
				}
				break;
			case 'b':
				if(lib)
				{
				
				param = 1;

				void (*usrGroup)(char*);
				usrGroup = dlsym(lib, "get_userGroup");
				
				usrGroup("");
				
				}				
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
			default:

				abort ();
				break;
			}
		}

	
	if(param == 0)
	{
		while((get_usr = getutent()) != NULL)
		{
		if((get_usr->ut_type) == 7)
		{
		printf("%s\n",get_usr->ut_user);
		}
		}
	}

	/*
	printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);
	printf ("non-option arguments: ");

	for (index = optind; index < argc; index++)
	{
		printf ("\n %s ", argv[index]);
		
	}
	
	//printf ("");
	for (index = 1; index < argc; index++) printf ("argv[%d]:%s ", index, argv[index]); //wyślwietlenie tablicy wejscia
	//printf ("");
	*/
return 0;
}