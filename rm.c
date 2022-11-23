#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "utils.h"
int isdir(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
void rm(char *params[20], char *pwd)
{
    // extra options
    // invaild input , trying to remove a directory
    int argc = count_params(params);
    char *paths[20];


    int *files = (int *)calloc(sizeof(int), 20);
    for (size_t i = 0; i < 20; i++)
        files[i] = -1;
    int _v_flag = 0;
    int _d_flag = 0;
    int file_count = 0;
    for (size_t i = 1; i < 20 && params[i] != NULL; i++)
    {
        if (strcmp(params[i],"&t")==0)
        {
            continue;
        }
        
        if (params[i][0] == '-')
        {
            if (params[i][1] == 'v')
            {
                _v_flag = 1;
            }
            else if (params[i][1] == 'd')
            {
                _d_flag = 1;
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
    if (file_count == 0)
    {
        printf("No file to remove\n");
        return;
    }
    for (int i = 0; i < file_count; i++)
    {
        if (_d_flag)
        {
            if (remove(paths[i]) < 0)
            {
                printf("%s : ", paths[i]);
                fputs(strerror(errno), stdout);
                printf("\n");
            }
            else
            {
                if (_v_flag)
                {
                    if (isdir(paths[i]))
                    {

                        printf("removed directory '%s'\n", paths[i]);
                    }
                    else
                    {
                        printf("removed '%s'\n", paths[i]);
                    }
                }
            }
        }
        else
        {
            if (isdir(paths[i]))
            {
                printf("'%s' is a directory\n", paths[i]);
            }
            else
            {
                if (remove(paths[i]) < 0)
                {
                    printf("%s : ", paths[i]);
                    fputs(strerror(errno), stdout);
                    printf("\n");
                }
                else
                {
                    if (_v_flag)
                    {
                        printf("removed '%s'\n", paths[i]);
                    }
                }
            }
        }
    }

    free(files);
}