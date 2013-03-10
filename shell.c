#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#define MAX_LEN 100
#define MAX_COMMANDS 3

int i;//,*i_p=&i;

main(){
	
	char input[MAX_LEN];
	char *command[MAX_COMMANDS];
	int pid,argc;	
	while(i<MAX_COMMANDS){
		command[i++]=NULL;
	}
	while(1){
		i=0;argc=0;
		write(1,"myshell$",8);
		gets(input);
		if(strcmp(input,"exit")==0)
			break;
		split(command,&argc,input);//generating tokens
		if (argc == 1) {
			if((pid = fork()) == 0){
				run_command(command[0]);
			}
		}		 
		else if(strcmp(command[1],">")==0) {
			if((pid = fork()) == 0) {
				redirect_O(command[0],command[2]);
			}
		} 
		else if(strcmp(command[1],"<")==0) {
			if((pid = fork()) == 0){
				redirect_I(command[0],command[2]);
			}
		} 
		else if(strcmp(command[1],"|")==0) {
			if((pid = fork()) == 0)
				pipe_IO(command[0],command[2]);
		}
		waitpid(pid,NULL,0);
		
	}
}
