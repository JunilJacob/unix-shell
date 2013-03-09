void redirect_I(char *command,char* input){
	int fd = open(input,O_RDONLY);
	close(0);
	dup(fd);
	execlp(command,command,(char *)0);

}
void redirect_O(char *command,char* output){
	int fd ;
	fd= open(output,O_WRONLY|O_CREAT|O_TRUNC, 0644);
	close(1);
	dup(fd);
	execlp(command,command,(char *)0);

}
void pipe_IO(char* command1,char* command2){
	int ipc[2];
	int pid;
	pipe(ipc);
	if((pid = fork()) == 0){
		close(ipc[0]);
		close(1);
		dup(ipc[1]);
		execlp(command1,command1,(char *)0);
	}
	else{
		close(ipc[1]);	
		close(0);
		dup(ipc[0]);
		execlp(command2,command2,(char *)0);
	}
}
