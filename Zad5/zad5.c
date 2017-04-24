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

void PidS(char programName[1000]);

extern char** environ;
int main( int argc, char **argv)
{
	char wejs[1000];



	if (argc == 2) {
		strcpy(wejs, argv[1]);
		printf(" |%s| \n", wejs);
		PidS(wejs);
	}



printf("\n\n");
	return 0;
	}

void PidS(char programName[1000]) {
	printf("programName = |%s|\n", programName);

		DIR* str_dir;
		struct dirent* wejscie;
		char str_bufor[1000];
		char bufor;
		char str_name[1000];
		char str_postName[1000];
		char tmp[1000];
		int comm;
		int name;

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

			if (!strcmp(pnamebuff, programName)) {
				printf("%s ", wejscie->d_name);
			}



			close(comm);

		}while (1);
}
