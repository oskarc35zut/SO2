#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dlfcn.h>
struct passwd *pw;
void (*UserPID)(char*);
void (*UserGroup)(char*);
int main(int argc,char *argv[])
{
    struct utmp *login[100];
    char *username;
    int atr;
    void *handle = dlopen( "./2_SO2.lib.so.0.1", RTLD_LAZY);
    if (!handle)
          dlerror();
    else
    {
      printf("---------------------------------------------\n");
      UserPID = dlsym( handle, "UserPID");
      UserGroup = dlsym( handle, "UserGroup");
      while ((atr = getopt (argc,argv, "ab")) != -1)
            switch (atr) {
              case 'a':
              while((login[0]=getutent())!= NULL )
              {
                username=login[0]->ut_user;
                UserPID(username);
              }
              printf("---------------------------------------------\n");
              dlclose(handle);
              return 0;
              break;
              case 'b':
              while((login[0]=getutent())!= NULL )
              {
                username=login[0]->ut_user;
                pw = getpwnam(login[0]->ut_user);
                if(pw != NULL)
                {
                UserGroup(username);
                }
              }
              printf("---------------------------------------------\n");
              dlclose(handle);
              return 0;
              break;
            }
            while((login[0]=getutent())!= NULL )
            {
                if((login[0]->ut_type == 7))
                {
                  printf("%s\n",login[0]->ut_user);
                }
            }
      printf("---------------------------------------------\n");
      endutent();
      dlclose(handle);
    }
    return 0;
}
