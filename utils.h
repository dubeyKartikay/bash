#ifndef UTILS
#define UTILS 1
void type_promt();
void get_command(char *);
char * classify(char *);
int is_threaded(char * params[20]);
void read_command(char *,char **);
int count_params(char * params[20]);
struct threadingArgs
{
    char * command;
    char ** parameters;   
    char* pwd;
};
#endif
