#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"commands.h"
#include"utils.h"
int first = 1;
void type_promt(){
    if(first){
    first = 0;    
    printf("\e[1;1H\e[2J");
    
    }
    printf(">");
}
void get_command(char * command){
    size_t size = 256;
    fgets(command,size,stdin);
    
}
char * classify(char * command){
    if (strlen(command)<=1)
    {
       printf("Invalid command\n");
       return NULL;
    }
    
    char* cmd = (char*)malloc(20*sizeof(char));
    for (size_t i = 0; i < 20; i++)
    {
        cmd[i] = '\0';
    }
    
    
    for (int i = 0; (i < 20)&&(i<strlen(command)); i++)
    {
        if (command[i]== ' '|| command[i] == '\0' || command[i]== '\n')
        {
            break;
        }
        cmd[i] = command[i];
        
    }  
    const char* acceptable_cmd[] = {"cd","echo","pwd","ls","cat","date","rm","mkdir"};
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(cmd,acceptable_cmd[i]) == 0)
        {
            return cmd;
        }
        
    }

    printf("Invalid command\n");
    return NULL;
    
}
void clear_string(char*str){
    for (size_t i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
    
}
void read_command(char * command,char * parameters[20]){
    char* cmd = (char*)malloc(256*sizeof(char));
    //free cmd;
    for (size_t i = 0; i < 20; i++)
    {
        parameters[i] = (char*)malloc(256*sizeof(char));
        clear_string(parameters[i]);
    }
    clear_string(cmd);
    int param_index = 0;
    for (int i = 0; (i < 256)&&(i<strlen(command)); i++)
    {
        if (command[i]== ' '|| command[i] == '\0' || command[i]== '\n')
        {
           strcpy(parameters[param_index],cmd);
           param_index++;
           clear_string(cmd);
            continue;
        }
        strncat(cmd,command+i,1);
        
    }
    parameters[param_index]=NULL;
    free(cmd);
    
    
    
    
}
int is_threaded(char * params[20]){
    int i =0;
    while (params[i]!=NULL&&i<20)
    {
        if (strcmp(params[i],"&t")==0)
        {
            return 1;
        }
        i++;
        
    }
    return 0;
    
}

int count_params(char * params[20]){
    int count = 0;
    while (params[count]!=NULL&&count<20)
    {   
        count++;
    }
    return count;
    
}