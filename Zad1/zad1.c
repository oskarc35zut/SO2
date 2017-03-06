#include <stdio.h>
#include <utmp.h>
#include <utmpx.h>


main()
{

struct utmpx *
getutxent(void)
{
retutn (struct utmpx *) __getutent();
}

printf("Hello, world!\n");
return 0;
}