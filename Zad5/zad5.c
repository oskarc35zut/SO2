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

extern char** environ;
int main( int argc, char **argv)
{

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
		//if (comm == -1) continue;

		/*FILE *fp = fopen(str_bufor, "r");
		if(fp){
			fscanf(fp, "%s", pnamebuff);
			printf("%s\n", pnamebuff);
		}*/



    if(comm < 0)
      continue;
    else{
      //printf("%s\n", Buffer);
      for(int l=0; l<1023; l++){
        read(comm, &buff, 1);
        if(buff == '\n'){
        pnamebuff[l] = '\0';
					break;
        }
        pnamebuff[l] = buff;
      }
    }
		printf("%s\n", pnamebuff);



		//strcpy(tmp, pnamebuff);

/*
		//name = read (comm, str_name, sizeof(str_name));
		//printf("%s\n", str_bufor);
		l = read(comm, buff,1024);
		//perror("read");
		//printf("length: %d\n", l);
		strncpy(pnamebuff, buff, l);

		strncpy(str_postName, buff, l);
strcat(pnamebuff, "\0");


		for (int i = 0; i < 100; i++) {
			if (!strcmp(&str_postName[i], "\n")) {
				strcpy(&str_postName[i], "\0");
				break;
			}
			//printf("%c", str_postName[i]);
			strcat(tmp, &str_postName[i]);
		}*/
		close(comm);




		//printf("%s | %s \n", str_name, str_bufor);
		//printf("%s | %s \n",tmp, str_bufor);


	}while (1);
printf("\n\n");








	return 0;
	}
