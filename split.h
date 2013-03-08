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
