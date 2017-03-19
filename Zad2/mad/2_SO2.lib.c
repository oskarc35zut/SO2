#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "2_SO2.h"
struct passwd *pw;
struct group *gr;
int ngroups,counter=0;
gid_t *groups;
void UserPID(char* username)
{
  struct utmp *login[100];
  while((login[0]=getutent())!= NULL )
  {
  if((login[0]->ut_user == username))
  {
    if((login[0]->ut_type == 7))
    {
      printf("%d  %s\n",login[0]->ut_pid,login[0]->ut_user);
    }
  }
}
}
void UserGroup(char* username)
{
  struct utmp *login[100];
    while((login[0]=getutent())!= NULL )
    {
    if((login[0]->ut_user == username))
    {
    if((login[0]->ut_type == 7))
    {
    ngroups=1;
    groups = malloc(ngroups * sizeof (gid_t));
    pw = getpwnam(login[counter]->ut_user);
    if(pw != NULL)
    {
    while(getgrouplist(login[counter]->ut_user, pw->pw_gid, groups, &ngroups) == -1)
    {
    ngroups=ngroups++;
    free(groups);
    groups = malloc(ngroups * sizeof (gid_t));
    }
    printf("%s [",login[counter]->ut_user);
    for(int i=0; i<ngroups; i++)
    {
    gr = getgrgid(groups[i]);
    if (gr != NULL)
        printf(" %s ",gr->gr_name);
    }
    counter++;
    printf("]\n");
    free(groups);
    pw=NULL;
    }
    }
  }
}
}
