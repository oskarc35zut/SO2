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


	

	void get_userPID(char* username)
	{
	
	utmpname("/var/run/utmp");
	struct utmp *get_usr;
	struct group *get_list;
	struct psswd *get_pwid;
	gid_t *groups;
	char* usr_name;
	const char* name = username;
	//printf("<<<  %s  >>>\n", name);

				while((get_usr = getutent()) != NULL)
				{	
					//printf("====  %s  =====\n", name);
					usr_name = get_usr->ut_user;

					if(usr_name == name && (get_usr->ut_type) == 7)
					{
					printf("%d %s\n",get_usr->ut_pid,get_usr->ut_user);
					}
				}
	}



	void get_userGroup(char *username)
	{

	utmpname("/var/run/utmp");
	struct utmp *get_usr;
	struct group *get_list;
	struct psswd *get_pwid;
	gid_t *groups;
	char* usr_name;

		while((get_usr = getutent()) != NULL)
				{	
					usr_name = get_usr->ut_user;
					if(usr_name != username && (get_usr->ut_type) == 7)
					{

 	int j, ngroups;
           gid_t *groups;
           struct passwd *pw;
           struct group *gr;



					while((get_usr = getutent()) != NULL)
				{
					if((get_usr->ut_type) == 7)
					{
					ngroups = 100;
					pw = getpwnam((get_usr->ut_user));
					printf("%s [",get_usr->ut_user);
					break;
					}
				}
           

           groups = malloc(ngroups * sizeof (gid_t));
           if (groups == NULL) {
               perror("malloc");
              
           }


           
           if (pw == NULL) {
               perror("getpwnam");
               
           }


           if (getgrouplist(get_usr->ut_user, pw->pw_gid, groups, &ngroups) == -1) {
               fprintf(stderr, "getgrouplist() returned -1; ngroups = %d\n",
                       ngroups);
           }

           for (j = 0; j < ngroups; j++) {
               gr = getgrgid(groups[j]);
               if (gr != NULL)
                   printf(" %s ", gr->gr_name);
           }

          
					}
				}

				
				printf("]\n");
	}