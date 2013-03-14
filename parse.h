#define MAX_ARGS 10
#define MAX_LEN 200
#define MAX_COMMANDS 3
void split(char *args[],int *argc,char *command);
void gen_argv(char* command,char *argv[]);
void run_command(char * command);
void redirect_I(char *command,char* input);
void redirect_O(char *command,char* output);
void pipe_IO(char* command1,char* command2);
