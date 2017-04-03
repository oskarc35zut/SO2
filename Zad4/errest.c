#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>

extern char** environ;
int main( int argc, char **argv) 
{	
	char* input = argv[1];

	printf( "%s\n",input);

	int length = 0;
	while(input[length] != '\0') {length++;}

	if((length%2) != 0) {length--;}



	if(length != 0)
		{
		char input_one[(length/2)];
		for(int i = 0; i < (length/2); i++) input_one[i] = input[i];

		char input_two[(length/2)];
		for(int i = 0; i < (length/2); i++) input_two[i] = input[i+((length/2))];
		
		pid_t pID1 = fork();
		if(pID1 == 0)
		{
		execlp("./errest", "errest", input_one , NULL);
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
		else
		{
			printf( "%s\n", input);
			exit(0);
		}

	

	return 0;
	}