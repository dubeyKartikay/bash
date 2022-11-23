#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <fcntl.h>
#include<errno.h>
#include"utils.h"
void cat(char* params[20],char * pwd){
    //wrongs flags
    //invalid paths
    int argc = count_params(params);
    char * paths[20];    
    int files[20];
    for (size_t i = 0; i < 20; i++) files[i]=-1; 
    int _n_flag=0;
    int _E_flage =0;
    int file_count = 0;
    for (size_t i = 1; i < 20 && params[i]!=NULL; i++)
    {
        if (strcmp(params[i],"&t")==0)
        {
            continue;
        }
        
      if (params[i][0] == '-')
      {
        if (params[i][1]=='n')
        {
            _n_flag = 1;
        }else if (params[i][1]=='E')
        {
            _E_flage = 1;
        }
        else{
            if (params[i][1] == '\0')
            {
                paths[file_count] = params[i];
                file_count++;
            }else{
                printf("unrecognised flag -%c\n", params[i][1]);
                return;
            }
        }
        continue;
      }
      if (params[i][0]=='\0')
      {
        continue;
      }
      
      paths[file_count] = params[i];
      file_count++;
    }
    // printf("%d",file_count);
    // printf("%s",params[file_count-1]);
    if (file_count == 0)
    {
        paths[0] = "-";
        file_count++;
    }
    for (int i = 0; i < file_count; i++)
    {
        if (strcmp(paths[i],"-")==0)
        {
            files[i] = STDIN_FILENO;
            continue;
        }
        
        files[i] = open(paths[i],O_RDONLY);
        if (files[i]==-1)
        {
            fputs(paths[i],stdout);
            printf(" : ");
            fputs(strerror(errno),stdout);
            printf("\n");
        }
        
    }
    int linecount = 1;
    for (int i = 0; i < file_count; i++)
    {
        if (_n_flag)
        {
           printf("%d  ",linecount);
        }
        
        char ch;
        while (read(files[i], &ch, 1) > 0)
        {
            if (ch=='\n' && _E_flage)
            {
                printf("$");
            }
            
            
            printf("%c", ch);
            if (ch=='\n' && _n_flag)
            {
        
                
                linecount++;
                printf("%d  ",linecount);
            }
        }
        printf("\n");
    }
    
    
    
}