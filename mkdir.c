#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include<errno.h>
int is_numeric(char * str){
    if (strspn(str,"0123456789") == strlen(str))
    {
        return 1;
    }
    return 0;
    
}
void mkDir(char *params[20], char *pwd)
{
    //flags
    //mkdir errors
    int mode = 755;
    int _m_flag = 0;
    int _v_flag = 0;
    int argc = count_params(params);
    char *paths[20];
    int file_count = 0;
    for (size_t i = 1; i < 20 && params[i] != NULL; i++)
    {
        if (strcmp(params[i], "&t") == 0)
        {
            continue;
        }

        if (params[i][0] == '-')
        {
            if (params[i][1] == 'v')
            {
                _v_flag = 1;
            }
            else if (params[i][1] == 'm')
            {
                _m_flag = 1;
                if (i+1 <argc && is_numeric(params[i+1]))
                {
                    mode = atoi(params[i+1]);
                }else{
                    printf("mode: %s is not a vaild mode\n",params[i+1]);
                    
                }
                if (params[i+1]!=NULL)
                {
                    i++;
                }
                
                
            }
            else
            {
                printf("unrecognised flag -%c\n", params[i][1]);
                return;
            }
            continue;
        }
        if (params[i][0] == '\0')
        {
            continue;
        }

        paths[file_count] = params[i];
        file_count++;
    }
    if (file_count==0)
    {
        printf("No directories to create\n");
        return;
    }

    for (int i = 0; i < file_count; i++)
    {
        if (mkdir(paths[i],mode)<0)
        {
            printf("mkdir: %s : %s\n",paths[i],strerror(errno));
        }else{
            if (_v_flag)
            {
                printf("created directoy %s\n",paths[i]);
            }
            
        }
        
    }
    

}
