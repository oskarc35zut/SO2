#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/wait.h>


extern char** environ;
int main( int argc, char **argv) 
{	
	char* input = argv[1];

	

	int length = 0;
	
	length = strlen(input);



	if((length%2) != 0 && (length) != 1) {length--;}
	
	char *ar2 = NULL;
	//char *bufor = NULL;	
	char bufor[1000];
	strcat(bufor," ");

			if(argc == 3)
			{

				strcat(bufor, argv[1]);
				strcat(bufor," ");
				//strcat(bufor, argv[1]);
				strcat(bufor, argv[2]);
				strcat(bufor," ");
			}
			if(argc == 2)
			{
				strcat(bufor, argv[1]);
			}
	

	if(length > 1)
		{
		char input_one[(length/2)];
		for(int i = 0; i < (length/2); i++) input_one[i] = input[i];

		char input_two[(length/2)];
		for(int i = 0; i < (length/2); i++) input_two[i] = input[i+((length/2))];
		
		pid_t pID1 = fork();

		if(pID1 == 0)
			{



			const char* in = input_one;
			strcat(bufor, argv[1]);
			


			execlp("./errest", "errest", input_one , bufor, NULL);
			}
			if(pID1 > 0)
			{
			
			
			wait(0);
			}

			pid_t pID2 = fork();

			if(pID2 == 0)
			{
			
			execlp("./errest", "errest", input_two , NULL);
			}
			if(pID2 > 0)
			{

			wait(0);
			}
		

		
		
		}


	
	printf( "%s \n",bufor);
	return 0;
	}