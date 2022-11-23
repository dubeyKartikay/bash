#include<stdio.h>
#include"utils.h"
#include<string.h>
void echo(char* params[20]){
    //incorrect flags handled
    //input after --help command handled
    int newline = 1;
    int escape = 1;
    int string_started = 0;
    int params_count = count_params(params);
    for (size_t i = 1; i < 20 && params[i]!=NULL; i++)
    {
      if (params[i][0] == '-' && string_started == 0)
      {

        if (params[i][1]=='n')
        {
            newline = 0;
        }else if (params[i][1]=='E')
        {
             escape = 1;
        }else if (strcmp(params[i],"--help")==0)
        {
             if (params_count>2)
            {
                printf("too many arguments to echo in this context\n");
                return;
            }
            printf("echo function prints out the input it was given to the console\n");
            printf("supported flags\n -n -> don't add a newline to the output\n -E -> disable interpretation of backslash escapes (default) \n");
           
            return;
            
        }
        
        else{
            printf("unrecognised flag -%c\n",params[i][1]);
            return;
        }
        continue;
      }
      string_started = 1;
      fputs(params[i],stdout);
      printf(" ");
    }
    if (newline)
    {
        printf("\n");
    }
    
    
    
}