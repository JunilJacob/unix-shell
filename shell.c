#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void split(char *args[10],int *argc,char *command){
	char current_arg[100];
	int i=0;
	while(*command){	
		while(*command == ' ')
			command++;
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
int i,ipc[2];;
main(){
	
	char command[1024];
	char *args[10];
	int argc,pid,fd=-1,fdin=-1,fdout=-1,currentinput=0,currentoutput=1;	
	while(i<10)
		args[i++]=NULL;
	pipe(ipc);
	while(1){
		i=0;argc=0;
		write(1,"myshell$",8);
		scanf("%s",command);
		split(args,&argc,command);
		i=0;	
		while(i<argc){
			if(argc==1 )
				if(fork()==0 ){
					execlp(args[i],args[i],(char *)0);
			}
			else{
			}
			
			
			while (pid = waitpid(-1, NULL, 0)) {
 				if (errno == ECHILD) {
   				   break;
   				}
			}
			i++;
		}
	
	}
}
