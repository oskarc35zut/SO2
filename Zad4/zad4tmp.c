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
#include <signal.h>

int flaga = 0;

void bolesnyUpadek(int signal, siginfo_t* siginfo, void* p)
{
	flaga++;
}



extern char** environ;
int main( int argc, char **argv)
{
	//printf("| argc= %d pID= %d", argc, getpid);
	switch (argc) {
		case 4:
			//printf("| argv[3]= %s ", argv[3]);
		case 3:
			//printf("| argv[2]= %s ", argv[2]);
		case 2:
			//printf("| argv[1]= %s | ", argv[1]);
			break;
	}




	//Zmiana obslugi sygnalu smierci////
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;

	sa.sa_sigaction = bolesnyUpadek;
	sigaction(SIGINT, &sa, NULL);


	//Sprawdzenie czy parametry zostaly podane
	if (argc == 1) {
		printf("Blad: Podaj ciag znakow\n");
		return 2;
	}


	//Historia//////////////////////////////////
	char *ar2 = NULL;
	char bufor[1000];

	int pID_root = 99999;

	switch(argc)
	{
	    case 2:
				strcat(bufor, argv[1]);
				strcat(bufor," ");
				//pID_root = getpid();
	        break;
			case 4:
				strcat(bufor, argv[2]);
				strcat(bufor," ");
				strcat(bufor, argv[1]);
				strcat(bufor," ");
				//pID_root = argv[3];
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

			execlp(argv[0], argv[0], input_one , bufor, pID_root, NULL);
			}


			//czekamy na smiersc dziecka
			if(pID1 > 0)
			{
				while (1) {
					if (flaga != 0) {
						kill(pID1, SIGINT);
						break;
					}
				}
			wait(0);
			}
			//end czekamy na smiersc dziecka ///////////////////////
			//end Pierwsze dziecko//////////////////////////////////


			//Drugie dziecko/////////////////
			pid_t pID2 = fork();

			if(pID2 == 0)
			{

			execlp(argv[0], argv[0], input_two , bufor, pID_root, NULL);

			}

			//czekamy na smiersc dziecka
			if(pID2 > 0) {
				while (1) {
					if (flaga != 0) {
						kill(pID2, SIGINT);
						break;
					}
				}

				wait(0);
			}
			//end czekamy na smiersc dziecka
			//end Drugie dziecko////////////////////////////////////

		}
//end Rodzimy dzieci/////////////////////


	printf( "%s || %d \n",bufor, pID_root);
	return 0;
	}
