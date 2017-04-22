#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/wait.h>


extern char** environ;
int main( int argc, char **argv)
{
	//Sprawdzenie czy parametry zostaly podane
	if (argc == 1) {
		printf("Blad: Podaj ciag znakow\n");
		return 2;
	}

	//Historia//////////////////////////////////
	char *ar2 = NULL;
	char bufor[1000];

	switch(argc)
	{
	    case 2:
				strcat(bufor, argv[1]);
				strcat(bufor," ");
	        break;
			case 3:
				strcat(bufor, argv[2]);
				strcat(bufor," ");
				strcat(bufor, argv[1]);
				strcat(bufor," ");
			  	break;
	    default :
					if (argc < 2) {
						printf("Blad: Program bez parametow\n");
					} else {
						printf("Blad: Zbye wiele parametow\n");
						return 2;
					}
	        break;
	}

	//Obliczanie dlugosci//////////////////////////////
	char* input = argv[1];
	int length = 0;
	length = strlen(input);
	if((length%2) != 0 && (length) != 1) {length--;}
	//end Obliczanie dlugosci///////////////////////////////

	if(length > 1)
		{

		//Dzielenie wejscia na dwie zmienne
		char input_one[(length/2)];
		for(int i = 0; i < (length/2); i++) input_one[i] = input[i];

		char input_two[(length/2)];
		for(int i = 0; i < (length/2); i++) input_two[i] = input[i+((length/2))];
		//end Dzielenie wejscia na dwie zmienne////////////////////////////

		//Pierwsze dziecko//////////
		pid_t pID1 = fork();
		//Rodzimy dzieci
		if(pID1 == 0)
			{

			const char* in = input_one;

			execlp("./errest", "errest", input_one , bufor, NULL);
			}


			//czekamy na smiersc dziecka
			if(pID1 > 0)
			{
			wait(0);
			}
			//end czekamy na smiersc dziecka ///////////////////////
			//end Pierwsze dziecko//////////////////////////////////


			//Drugie dziecko/////////////////
			pid_t pID2 = fork();

			if(pID2 == 0)
			{

			execlp("./errest", "errest", input_two , bufor, NULL);

			}

			//czekamy na smiersc dziecka
			if(pID2 > 0) {
				wait(0);
			}
			//end czekamy na smiersc dziecka
			//end Drugie dziecko////////////////////////////////////

		}
//end Rodzimy dzieci/////////////////////


	printf( "%s \n",bufor);
	return 0;
	}
