#define MAX_ARGS 10
void split(char *args[],int *argc,char *command){
	char current_arg[100];
	int i=0;
	while(*command == ' ')
			command++;
	while(*command){	
		if(*command == '|' ||*command == '<'||*command == '>'){
			current_arg[i]='\0';			
			args[*argc]=(char *)malloc(strlen(current_arg)+1);
			strcpy(args[*argc],current_arg);
			*argc=*argc+1;			
			args[*argc]=(char *)malloc(2);
			if(*command == '|'){
					
					strcpy(args[*argc],"|");
			}
			else if(*command == '<'){
					strcpy(args[*argc],"<");
			}
			else if(*command == '>'){
					strcpy(args[*argc],">");
			}
			*argc=*argc+1;			
			i=0;
			command++;
			while(*command == ' ')
				command++;
		}
		else{
			
			current_arg[i++]=*command;
			command++;
			if(*command == '\0'){
				current_arg[i]='\0';
				args[*argc]=(char *)malloc(strlen(current_arg)+1);
				strcpy(args[*argc],current_arg);
				*argc=*argc+1;
				args++;
				return;
			}
		
		}
	}
}
void gen_argv(char* command,char *argv[]){
	int i=0,j=0;
	char current_arg[20];
	while(i<MAX_ARGS){
		//if(argv[i]!=NULL)
			//free(argv[i]);
		argv[i++]=NULL;
	}
	i=0;
	while(*command){
		while(*command==' ')
			command++;
		while(*command!=' ' && *command!='\0' ){
			current_arg[i]=*command;
			command++;
			i++;
		}
		
		current_arg[i]='\0';
		if(strlen(current_arg)>0){
		argv[j]=(char *)malloc(strlen(current_arg)+1);
		strcpy(argv[j++],current_arg);
		i=0;}
	}
	
}
void run_command(char * command){
	char *argv[MAX_ARGS];
	gen_argv(command,argv);
	execvp(argv[0],argv);
}

void redirect_I(char *command,char* input){
	int fd = open(input,O_RDONLY);
	close(0);
	dup(fd);
	run_command(command);
}
void redirect_O(char *command,char* output){
	int fd = open(output,O_WRONLY|O_CREAT|O_TRUNC, 0644);
	close(1);
	dup(fd);
	run_command(command);


}
void pipe_IO(char* command1,char* command2){
	int ipc[2];
	pipe(ipc);
	if(fork() == 0){
		close(ipc[0]);
		close(1);
		dup(ipc[1]);
		run_command(command1);
	}
	else{
		close(ipc[1]);	
		close(0);
		dup(ipc[0]);
		run_command(command2);	}
}


