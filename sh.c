#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include"utils.h"
#include"commands.h"
void handle_internally(char * params[20],char * pwd);
void* handle_externally(void * args);
int main(){
    char command[256], *parameters[20],*cmd;
    struct threadingArgs* args = (struct threadingArgs*)malloc(sizeof(struct threadingArgs));
    char * pwd = "/home/kartikay/OS/ASN1/";
    chdir(pwd);
    char * binPath = "/home/kartikay/OS/ASN1/";
    while(1){
        type_promt();
        get_command(command);
        cmd = classify(command);
        if (cmd == NULL)
        {
            continue;
        }
        
        read_command(command,parameters);
        if (!(strcmp(cmd,"echo")&&strcmp(cmd,"cd")&&strcmp(cmd,"pwd"))){
            handle_internally(parameters,pwd);
        }else{
            if (is_threaded(parameters))
            {
                pthread_t thread;
                args->command = cmd;
                args->parameters = parameters;
                args->pwd = pwd;
                pthread_create(&thread,NULL,handle_externally,args);
                pthread_join(thread,NULL);
            }else{
                if (fork() != 0)
                {
                    wait(NULL);
                }else{
                    char * path = (char *)malloc(256*sizeof(char));
                    parameters[0] = pwd;
                    strcpy(path,binPath);
                    strcat(path,cmd);
                    execv(path,parameters);
                    free(path);
                }
                
            }
            
        }
    }
}

void handle_internally(char * params[20],char * pwd){
    const char * cmd = params[0];
    if (strcmp(cmd,"cd")==0)
    {
        cd(params,pwd);
    }else if (strcmp(cmd,"echo") == 0 )
    {
        echo(params);
    }else
    {
        pwdir(params,pwd);
    }   
}
void* handle_externally(void * args){
    struct threadingArgs * argsT = (struct threadingArgs *)args;
    if (strcmp(argsT->command,"ls")==0 )
    {
            ls(argsT->parameters,argsT->pwd);
    }else if (strcmp(argsT->command,"rm")==0)
    {
        rm(argsT->parameters,argsT->pwd);
    }else if (strcmp(argsT->command,"mkdir")==0)
    {
        mkDir(argsT->parameters,argsT->pwd);
    }else if (strcmp(argsT->command,"date")==0)
    {
        date(argsT->parameters);
    }else if (strcmp(argsT->command,"cat")==0)
    {
        cat(argsT->parameters,argsT->pwd);
    }else
    {
        printf("Unsupported command Entered\n");
    }
}