//SO2 IS1 211A LAB01
//Oskar Cieślikiewicz
//ocieslikiewicz@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>



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
		
	
	//printf("get = %s", *get);

	while ((ret = getopt (argc, argv, "abc:")) != -1)
		{
		switch (ret) 
			{
			case 'a':
				param = 1;
				
				while((get_usr = getutent()) != NULL)
				{
					if((get_usr->ut_type) == 7)
					{
					printf("%d %s\n",get_usr->ut_pid,get_usr->ut_user);
					}
				}
				break;
			case 'b':
				param = 1;
				
				while((get_usr = getutent()) != NULL)
				{
					if((get_usr->ut_type) == 7)
					{

					//get_pwid = getpwid(7);
					//printf("%s [\n",get_usr->ut_user);
					
					//int getgrouplist(const char *user, gid_t group, gid_t *groups, int *ngroups);

 	int j, ngroups;
           gid_t *groups;
           struct passwd *pw;
           struct group *gr;

	/*
           if (argc != 3) {
               fprintf(stderr, "Usage: %s <user> <ngroups>\n", argv[0]);
           }
	*/

					while((get_usr = getutent()) != NULL)
				{
					if((get_usr->ut_type) == 7)
					{
					//printf("%d %s\n",get_usr->ut_pid,get_usr->ut_user);
					ngroups = 100;//atoi((get_usr->ut_pid));
					pw = getpwnam((get_usr->ut_user));
					printf("%s [",get_usr->ut_user);
					break;
					}
				}
           

           groups = malloc(ngroups * sizeof (gid_t));
           if (groups == NULL) {
               perror("malloc");
              
           }

           /* Fetch passwd structure (contains first group ID for user) */

           
           if (pw == NULL) {
               perror("getpwnam");
               
           }

           /* Retrieve group list */
//printf("NK\n");
           if (getgrouplist(get_usr->ut_user, pw->pw_gid, groups, &ngroups) == -1) {
               fprintf(stderr, "getgrouplist() returned -1; ngroups = %d\n",
                       ngroups);
           }

           /* Display list of retrieved groups, along with group names */

           //fprintf(stderr, "ngroups = %d\n", ngroups);
           for (j = 0; j < ngroups; j++) {
               //printf("%d", groups[j]);
               gr = getgrgid(groups[j]);
               if (gr != NULL)
                   printf(" %s ", gr->gr_name);
              // printf("\n");
           }

          
					}
				}

				
				printf("]\n");
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