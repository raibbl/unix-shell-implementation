#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> 

//Function for all the built in Commands
char* builtinfunction[10] = {"-p","exit","pid","ppid","cd","pwd","set","get","jobs","cmd"};
//variable for making sure of the background process. 
int background =0;




/*handle built in functions,returns 1 to indicate it ran and is a built in function*/
int function(char* function,char **argvv){
	
	if(strcmp(function,builtinfunction[1])==0){
		//exit
		exit(0);
	}
	else if(strcmp(function,builtinfunction[2])==0){
		//pid

		printf("Current Process ID : %d\n",getpid());
		return 1; 
	}
	else if(strcmp(function,builtinfunction[3])==0){

		//ppid
		printf("Parent Process ID : %d\n",getppid());
		return 1; 
	}
	else if(strcmp(function,builtinfunction[4])==0){
		char * dirc;
		if(argvv[1]!=0){
		
		dirc = argvv[1];
                }
		else{


		
		dirc = getenv("HOME");
		
	}
		chdir(dirc);	
		return 1; 

		//cd
	}
	else if(strcmp(function,builtinfunction[5])==0){
		char cwd[1024];
		printf("%s\n",getcwd(cwd,sizeof(cwd)));
		return 1; 
		//pwd
	}
	else if(strcmp(function,builtinfunction[6])==0){
		
			
			
			if(setenv(argvv[1], argvv[2],500)!=0){
				setenv(argvv[1], "0",500);
				
			}
			return 1; 
			
		
		
		//set
	}
	else if(strcmp(function,builtinfunction[7])==0){
		
		

		printf("%s",getenv(argvv[1]));
		printf("\n");
		return 1; 
		//get
	}
	else if(strcmp(function,builtinfunction[8])==0){
		//jobs
	}
	else {
		//cmd
	}
	}


/*
function to decide what to do from the command line,if function returns 1 then it is a built in command
and it worked otherwise it is not a builtinfucntion */
int decide(char *argv,char **argvv){
	int i=0;
	int whattoreturn=0;
	
	for ( i = 0; i <10; i++)
	{
		if(strcmp(argv,builtinfunction[i])==0){

			whattoreturn=function(argv,argvv);
			
		}
	}
	return whattoreturn;

}

/*function to start running a process if it is not a built in command */

int ProcessStart(char *argv,char **argvv){
	
	int pp;
	
	

	pp = fork();

	//if it is a parent
	if(pp>0){
		//if it is a background process, dont wait for child
		if(background==1){
			background=0;
			
			return 0;
		}
		//wait for child if it is not a background process
		else{
			waitpid(pp,0,0);
			return 0;
			
		}
	}
	//if it is a child then execute 
	else if(pp==0){
	     //print the pid and name of program
		 printf("	\n [%d]",getpid());
         printf(" %s  \n\n",argv);
         //excute 
		 execvp(argv,argvv);
		 //dignose if there is error and print
	 	 perror("\0");

	}
	//if there is an error with making the process
	else{
		printf("fork returned an error");
		return -1;
	}

	
	

	 		
	 		

		
		
		
	}
	





int main(int argc, char **argv) {
	
	char* shell= "308sh>";
	
	//check if there is user input for -p
	
	if(argv[1]!=0){
	if(strcmp(argv[1],"-p")==0){
		shell=argv[2];
	}
}
	
	
	while(1){
		//print the user prompt either 308sh> or user input
		printf("%s",shell);
		
		//Parse and read from terminal
		//--------------------------------
		char command[100];
		char *word[100];
		//get input from command line
		fgets(command, sizeof(command), stdin);

		//store the words in the line inside an array
		int i=0;
	 	char* token = strtok(command, " "); 
	 	word[0]=token;
	 	while (token != NULL) { 
 		i++;
	       token= strtok(NULL, " "); 
	       word[i]=token;
	      
		
	    }

		//-----------------------------------

		
		//-----fgets is weird it adds \n on the last input so this is to remove that
		int thelength = strlen(word[i-1]);
		char *booga= word[i-1];
		booga[thelength-1] = 0;
		word[i-1]=booga;
		//-----fgets is weird it adds \n on the last input

		//if decide is not builtin command then excute, if it returns 0 then it is not a builtin func 
		if(decide(word[0],word)!=1){
			//check if it is background process or not 
			if(strcmp(word[i-1],"&")==0){ 
				background=1;
				//remove the & before passing to execution 
				word[i-1]=0;
			}
			//start a process and pass in argv
			
			if(ProcessStart(word[0],word)==0){
				//if everthing is good then child was executed
				printf("Child exited normally\n");
			}

			}
		

	}
		
	


	}
	 
		
	


