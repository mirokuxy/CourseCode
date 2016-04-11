#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAXL 20

int init(char argv[][MAXL]){ 
	int i=0,j=0;
	char ch;
	int flag = 0;
	while(1){ 
		scanf("%c",&ch);
		if(ch!=' ' && ch!='\n' && ch!='\t'){ 
			argv[i][j] = ch;
			j++;	
			if(!flag) flag = 1;
		}
		else{ 
			if(flag){ 
				argv[i][j] = '\0';
				i++;
				j=0;
				flag = 0;
			}
		}
		if(ch=='\n') break;
	}

	return i;
}

void call(char *argv[]){ 
	pid_t pid;
	int status;

	pid = fork();
	if(pid<0){ 
		printf("system call fork() failed\n");
		exit(1);
	}
	else if(pid==0){ 
		if(execvp(argv[0],argv) <0) { 
			printf("system call execvp() failed\n");
			exit(1);
		}
	}
	else{ 
		waitpid(pid,&status,0);
	}
}

char argv[10][MAXL];
char *argvp[10];

int main()
{ 
	int count = init(argv);
	
	/*
	int i;
	for(i=0;i<count;i++)
		printf("%s||\n",argv[i]);
	printf("%d\n",count);
	*/
	int i;
	for(i=0;i<count;i++)
		argvp[i]=(char*)argv[i];
	argvp[i] = '\0';

	for(i=0;argvp[i];i++)
		printf("%s|\n",argvp[i]);
	printf("%d\n",count);
	
	return 0;
}
