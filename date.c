#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include"utils.h"
#include<string.h>
void date(char *params[20])
{
    //extra params
    //extra files
    int argc = count_params(params);
    int _u_flag = 0;
    int _r_flag = 0;
    const char *path;
    int file_count = 0;
    for (size_t i = 1; i < 20 && params[i] != NULL; i++)
    {
        if (strcmp(params[i],"&t")==0)
        {
            continue;
        }
        
        if (params[i][0] == '-')
        {
            if (params[i][1] == 'u')
            {
                _u_flag = 1;
            }
            else if (params[i][1] == 'r')
            {
                _r_flag = 1;
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

        path = params[i];
        file_count++;
    }
    if (file_count > 0 & _r_flag == 0)
    {
        printf("syntax not supported\n");
        return;
    }
    if (_r_flag)
    {
        if (file_count > 0)
        {
            struct stat attr;
            stat(path, &attr);
            if (_u_flag)
            {
                struct tm * time;
                time = gmtime((time_t *)&(attr.st_ctim));
                fputs(asctime(time),stdout);
            }else
            {
            fputs(ctime((time_t *)&attr.st_mtim), stdout);
                
            }
            
            
            return;
        }
        else
        {
            printf("No file provided\n");
            return;
        }
    }

    time_t t;
    struct tm * timeS;
    t = time(NULL);
    if (_u_flag)
    {
        timeS =gmtime(&t);
    }else{    
    timeS =localtime(&t);
    }
    fputs(asctime(timeS),stdout);

}