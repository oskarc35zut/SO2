#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

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
		
		pid_t pID = fork();
		
		if(pID == 0)
		{
		execlp("./errest", "errest", input_one , NULL);
		execlp("./errest", "errest", input_two , NULL);
		}
		if(pID > 0)
		{
		//kill(pID, SIGINT);
		wait(0);
		}

		//printf( "%s\n",input_one);	
		//printf( "%s\n",input_two);
		
		
		}
		else
		{
			printf( "%s\n", input);
			exit(0);
		}

	

	return 0;
	}