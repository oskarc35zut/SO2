#include <stdio.h>
extern char** environ;
int main( int argc, char **argv) //(…, char *argv[])
{
char **var;
for( var = environ; *var != NULL; ++var)
printf( "%s\n", *var);
for( int i=0; i<argc; i++)
printf( "%s\n", argv[ i]);
return 0;
}