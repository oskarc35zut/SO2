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


int flaga = 0;
int pIDroot;

void bolesnyUpadek(int signal, siginfo_t* siginfo, void* p)
{
	flaga++;
}

void vCtrlZ(int signal, siginfo_t* siginfo, void* p)
{
	int _used = 1;

	FILE *fp;
	if ((fp=fopen("flagaZ.txt", "w"))==NULL)
	{
		printf("Nie moge otworzyc pliku do zapisu!\n");
	}
	fprintf (fp, "%d", _used);
	fclose(fp);
}

void getNap() {
	printf("%d Zasypia\n", getpid());
	while (1)
	{
		if (flaga != 0)
		{
			break;
		}
	}



}

extern char** environ;
int main( int argc, char **argv)
{
	//Sprawdzenie czy parametry zostaly podane
	if (argc == 1) {
		printf("Blad: Podaj ciag znakow\n");
		return 2;
	}

//Sygnaly/////////////////////////////////////////
	if (argc == 2) {

		pIDroot = getpid();

		FILE *fp;
		if ((fp=fopen("test.txt", "w"))==NULL)
		{
			printf("Nie moge otworzyc pliku do zapisu!\n");
			return 0;
		}
		fprintf (fp, "%d", pIDroot);
		fclose(fp);

		int used = 0;

		if ((fp=fopen("flagaZ.txt", "w"))==NULL)
		{
			printf("Nie moge otworzyc pliku do zapisu!\n");
			return 0;
		}
		fprintf (fp, "%d", used);
		fclose(fp);

	}

	FILE *fp;

	if ((fp=fopen("test.txt", "r"))==NULL)
	{
		printf("Nie moge otworzyc pliku do zapisu!\n");
		return 0;
	}
	char ppp[1000];
	fscanf(fp, "%s", ppp);
	pIDroot = atoi(ppp);

	//Zmiana obslugi sygnalu smierci////
	struct sigaction exterminuj;

	exterminuj.sa_flags = SA_SIGINFO;

	exterminuj.sa_sigaction = bolesnyUpadek;
	sigaction(SIGINT, &exterminuj, NULL);


	//Zmiana obslugi sygnalu ctrl+z////
	struct sigaction CtrlZ;
	sigprocmask(SIG_BLOCK, )

	CtrlZ.sa_flags = SA_SIGINFO;
	struct sigprocmask CtrlBlock;

	CtrlZ.sa_sigaction = vCtrlZ;
	sigaction(SIGTSTP, &CtrlZ, NULL);

//end Sygnaly//////////////////////////////////////




	//Historia//////////////////////////////////
	char *ar2 = NULL;
	char bufor[1000];
	//int pID_root = 99;

	switch(argc)
	{
	    case 2:
				strcat(bufor, argv[1]);
				strcat(bufor," ");
	        break;
			case 4:
			case 3:
				strcat(bufor, argv[2]);
				strcat(bufor," ");
				strcat(bufor, argv[1]);
				strcat(bufor," ");
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
			if(pID1 == 0)
			{
				setpgid(pID1,pID1);
				execlp(argv[0], argv[0], input_one , bufor, NULL);
			}
			//end Pierwsze dziecko//////////////////////////////////

			//Drugie dziecko/////////////////
			pid_t pID2 = fork();
			if(pID2 == 0){
			setpgid(pID2,pID2);
			execlp(argv[0], argv[0], input_two , bufor, NULL);
			}
			//end Drugie dziecko////////////////////////////////////

			getNap();

			//czekamy na smiersc dzieci i propagujemy
			if(pID1 > 0){
				kill(pID1, SIGINT);
				wait(0);
			}
			if(pID2 > 0){
				kill(pID2, SIGINT);
				wait(0);
			}



			kill(pIDroot, SIGINT);

		}
		else
		{
			getNap();
		}
//end Rodzimy dzieci/////////////////////



if (argc == 2) {
	int tmp = 0;
	for (long int i = 0; i < length*900000; i++) {
		tmp++;
		tmp--;
	}
}


printf( "\b\b%s ",bufor);

if (0) {


switch (argc) {
	case 4:
		printf("| argv[3]= %s ", argv[3]);
	case 3:
		printf("| argv[2]= %s ", argv[2]);
	case 2:
		printf("| argv[1]= %s | ", argv[1]);
		break;
}
printf("| argc= %d pIDroot= %d length= %d\n", argc, pIDroot, length);
}else
{
	printf("\n");
}
if (argc == 2) {
	printf("\n\n\n");
}
	return 0;
	}
