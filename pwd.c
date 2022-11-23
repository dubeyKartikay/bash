#include<unistd.h>
#include<stdio.h>
#include "utils.h"
void pwdir(char* params[20],char * pwd){
    //handles too many arguments
    //handles inaccesible cwd
      char curdir[256];
      int l=0,p=0;
      int param_count = count_params(params);
      if (param_count >3)
      {
        printf("too many arguments to pwd\n");
        return;
      }
      
      for (size_t i = 1; i < 20 && params[i]!=NULL; i++)
    {
      if (params[i][0] == '-')
      {

        if (params[i][1]=='L')
        {
            l= 1;
        }else if (params[i][1]=='P')
        {
             p =1;
        }
        else{
            printf("unrecognised flag -%c\n", params[i][1]);
            return;
        }
        continue;
      }
      
    }

    if(getcwd(curdir, sizeof (curdir))){
        printf("inaccessible directory");
        return; 
    }
    fputs(curdir,stdout);
    printf("\n");
    
}