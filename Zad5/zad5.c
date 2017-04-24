#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


void PidS(char programName[1000], char argvZERO[1000]);



extern char** environ;
int main( int argc, char **argv)
{
	const char *target = "./zad5.c";
	const char *linkpath = "./killall";

	symlink(target, linkpath);

	//printf("|%s|\n", argv[0]);

	if (argc == 2) {
		char wejs[1000];
		char argvZERO[1000];
		strcpy(argvZERO, argv[0]);
		strcpy(wejs, argv[1]);
		PidS(wejs, argvZERO);
	}

printf("\n\n");
	return 0;
	}

void PidS(char programName[1000], char argvZERO[1000]) {

		DIR* str_dir;
		struct dirent* wejscie;
		char str_bufor[1000];
		char bufor;
		char str_name[1000];
		char str_postName[1000];
		char compare[1000];
		char tmp[1000];
		int comm;
		int name;
		int int_pID;

		char buff;
		char pnamebuff[1024];
		int l;

		str_dir = opendir("/proc/");

		do{
			wejscie = readdir(str_dir);
			if (wejscie == NULL) break;
			if (wejscie->d_type != DT_DIR) continue;
			if(!strcmp(wejscie->d_name, ".")) continue;
			if(!strcmp(wejscie->d_name, "..")) continue;



			strcpy(str_bufor, "/proc/");
			strcat(str_bufor, wejscie->d_name);
			strcat(str_bufor, "/comm");
			strcat(str_bufor, "\0");

			comm = open(str_bufor, O_RDONLY);


	    if(comm < 0)
	      continue;
	    else{
	      for(int l=0; l<1023; l++){
	        read(comm, &buff, 1);
	        if(buff == '\n'){
	        pnamebuff[l] = '\0';
						break;
	        }
	        pnamebuff[l] = buff;
	      }
	    }

			int_pID = atoi(wejscie->d_name);

			if (!strcmp(pnamebuff, programName))
			{
				strcpy(compare, "./zad5");
				if (!strcmp(argvZERO, compare))
				{
					printf("%d ", int_pID);
				}
				else
				{
					strcpy(compare, "./killall");
					if (!strcmp(argvZERO, compare))
					{
						//printf("| kill# %d |", int_pID);
						kill(int_pID, SIGINT);
					}
					else
					{
						printf("\n# Blad pid #");
					}
				}

			}



			close(comm);

		}while (1);
}
