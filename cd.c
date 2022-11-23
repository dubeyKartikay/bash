#include<stdio.h>
#include"utils.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <unistd.h>
#include "utils.h"
char last_dir[256] = {'\0'};
void cd(char* params[20],char * pwd){
     //handled incorrect flags
     //hangle too many arguments
     //handles errors thown by chdir
    char curdir[256];
    char path[256];

    getcwd(curdir, sizeof (curdir));
    
    int params_count = count_params(params);
    int string_started = 0;
    int l = 0;
    int p = 0;

    for (size_t i = 1; i < 20 && params[i]!=NULL; i++)
    {
      if (params[i][0] == '-' && string_started == 0)
      {

        if (params[i][1]=='L')
        {
            l= 1;
        }else if (params[i][1]=='P')
        {
             p =1;
        }
        else{
            printf("unrecognised flag -%c\n",params[i][1]);
            return;
        }
        continue;
      }
      if (i != params_count-1)
      {
        printf("too many arguments to cd\n");
        return;
      }
      break;
      
    }
    char * arg = params[params_count-1];
    if (!strcmp(arg,"-")){
        if (*last_dir == '\0')
        {
            printf("No previous directory\n");
            return;
        }
        arg = last_dir;
    }else{
         if (*arg == '~') {
            if (arg[1] == '/' || arg[1] == '\0') {
                snprintf(path, sizeof path, "%s%s", getenv("HOME"), arg + 1);
                arg = path;
            }
    }

    if (chdir(arg)) {
        fputs(strerror(errno),stdout);
        return;
    }
    strcpy(last_dir, curdir);


        }
}