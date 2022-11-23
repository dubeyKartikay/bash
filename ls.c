#include <dirent.h>
#include <stdio.h>
#include<errno.h>
#include<string.h>
void ls(char *params[20], char *pwd)
{
   //incorrect flags
   //worng directory 
    int _i_flag = 0;
    int _a_flag = 0;
    int _1_flag = 0;
    const char * path;
    int file_count = 0;
    for (size_t i = 1; i < 20 && params[i] != NULL; i++)
    {
        if (strcmp(params[i],"&t")==0)
        {
            continue;
        }
        
        if (params[i][0] == '-')
        {
            if (params[i][1] == 'i')
            {
                _i_flag = 1;
            }
            else if (params[i][1] == 'a')
            {
                _a_flag = 1;
            }
             else if (params[i][1] == '1')
            {
                _1_flag = 1;
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
    if (file_count > 1)
    {
        printf("Syntax not supported");
        return;
    }
    if (file_count == 0)
    {
        path ="./";
    }
    struct dirent *dir;
    DIR *d = opendir(path);
    if (d == NULL)
    {
        fputs(strerror(errno),stdin);
        return;
    }
    while ((dir = readdir(d)) != NULL)
    {
        if (!_a_flag && dir->d_name[0] == '.')
        {
            continue;
        }
        
       if (_i_flag)
       {
            printf("%ld ",dir->d_ino);
            fputs(dir->d_name,stdout);
            printf(" ");
       }else{
            fputs(dir->d_name,stdout);
            printf(" ");

       }
       if (_1_flag)
       {
        printf("\n");
       }
       

       
    }
    if (!_1_flag)
    {
    printf("\n");
    }
    
    
    
    
}