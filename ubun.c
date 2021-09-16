#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/utsname.h>
#include<sys/wait.h>
#include<unistd.h>
#include<dirent.h>

char* readline()
{
	int position=0;
	int size=1024;
	char *line=malloc(sizeof(char)*size);
	
	if(!line)
	{
		fprintf(stderr,"Allocation error !!..\n");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		char c=getchar();
		
		if(c!=EOF && c!='\n')
		{
			line[position++]=c;
		}
		else
		{
			line[position]='\0'; //if we reach EOF replace it with null char
			return line;
		}
		
		
		if(position >= size)
		{
			size*=2;
			line=realloc(line,size); //if the line size is greater than allocated one, realloc the same
			if(!line)
			{
				fprintf(stderr,"Allocation error !!..\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	return line;
	
}

char** splitline(char *cmd)
{
	int size=64;
	int position=0;
	char *delimiter=" \t\r\n";
	char **tokens = malloc(sizeof(char)*size);
	
	if(!tokens)
	{
		fprintf(stderr,"Allocation error !!..\n");
		exit(EXIT_FAILURE);
	}
	
	char *token;
	token=strtok(cmd,delimiter);
	while(token!=NULL)
	{
		tokens[position++]=token;
		
		if(position >= size)
		{
			size*=2;
			tokens=realloc(tokens,size*sizeof(char*));
			
			if(!tokens)
			{
				fprintf(stderr,"Allocation error !!..\n");
				exit(EXIT_FAILURE);
			}
		}
		
		token=strtok(NULL,delimiter);
	}
	
	tokens[position]=NULL;
	return tokens;
}

char *builtin_cmd[] = {"changeTo","listCmd","workingSpace","Leave","calculator","createFile","deleteFile","systemInfo","listFiles","clearAll"};


int cd(char **args)
{
	if(args[1]==NULL)
	{
		fprintf(stderr,"Expected arguments for \"cd\" \n");
	}
	else if(chdir(args[1]) != 0)
	{
		perror("Error in changing dir");
	}
	return 1;
}

int help(char *args)
{
	printf("We're here to help U :)\n");
	int i;
	if(args==NULL)
	{
		system("sleep 0.5");
		system("clear");
		system("./help1.py");
		system("sleep 0.5");
		int n=sizeof(builtin_cmd)/sizeof(char *);
		for(i=0;i<n;i++)	
		{
			printf(" %s\n",builtin_cmd[i]);	
			system("sleep 0.5");
		}	
	}
	else if(strcmp(args,"changeTo") == 0)
	{
		printf("\x1b[33m" "This is documentation for 'changeTo' command - \n" "\x1b[0m");
		system("sleep 0.3");
		printf("\x1b[32m" "Usage : \n" "\x1b[0m");
		system("sleep 0.5");
		printf("Just type the command and give the 'file name' as argument\n");
		system("sleep 0.5");
		printf( "Example - ""\x1b[36m" "changeTo .." "\x1b[0m" "   ---> this command let's you to go to previous dir\n");
	}
	else if(strcmp(args,"calculator") == 0)
	{
		printf("\x1b[33m" "This is documentation for 'calculator' - \n" "\x1b[0m");
		system("sleep 0.3");
		printf("\x1b[32m" "Usage : \n" "\x1b[0m");
		system("sleep 0.5");
		printf("Just type the command and it will prompts you for an expression to calculate\n");
		system("sleep 0.5");
		printf( "Example - ""\x1b[36m" "calculator" "\x1b[0m" "   ---> this command prompts you to write ans expression\n");
		printf("Input - 2+3\nOutput - 5\n");	
	}
	else if(strcmp(args,"createFile") == 0)
	{
		printf("\x1b[33m" "This is documentation for 'createFile' command - \n" "\x1b[0m");
		system("sleep 0.3");
		printf("\x1b[32m" "Usage : \n" "\x1b[0m");
		system("sleep 0.5");
		printf("Just type the command and give the 'file name' as argument\n");
		system("sleep 0.5");
		printf( "Example - ""\x1b[36m" "createFile newFile.txt" "\x1b[0m" "   ---> this command creates new file with the given name\n");	
	}
	else if(strcmp(args,"deleteFile") == 0)
	{
		printf("\x1b[33m" "This is documentation for 'deleteFile' command - \n" "\x1b[0m");
		system("sleep 0.3");
		printf("\x1b[32m" "Usage : \n" "\x1b[0m");
		system("sleep 0.5");
		printf("Just type the command and give the 'file name' as argument\n");
		system("sleep 0.5");
		printf( "Example - ""\x1b[36m" "deleteFile newFile.txt" "\x1b[0m" "   ---> this command deletes new file with the given name\n");	
	}
	else if(strcmp(args,"systemInfo") == 0)
	{
		printf("\x1b[33m" "This is documentation for 'systemInfo' command - \n" "\x1b[0m");
		system("sleep 0.3");
		printf("\x1b[32m" "Usage : \n" "\x1b[0m");
		system("sleep 0.5");
		printf("Just type the command\n");
		system("sleep 0.5");
		printf( "Example - ""\x1b[36m" "systemInfo" "\x1b[0m" "   ---> this command prints the system Information directly\n");	
	}	
	else
	{
		printf("Please recheck the command you've typed :)\n");
	}
	return 1;
}

int pwd()
{
	char s[100];
	getcwd(s,100);
	printf("Current Working Directory = %s\n",s);
	return 1;
}

int calculator()
{
	pid_t pid;
	int status=1;
	char *args[] = {"./calc.py",NULL};
	if ((pid = fork()) > 0) 
	{
    	waitpid(pid, &status, 0);
	}
	else 
	{
  		execvp(args[0],args);
	}	
	return 1;
}

int systeminfo()
{

   struct utsname buf1; 
   if(uname(&buf1)!=0) 
   { 
      perror("uname doesn't return 0, so there is an error"); 
   } 
   printf("System Name = %s\n", buf1.sysname); 
   system("sleep 0.5");
   printf("Node Name = %s\n", buf1.nodename); 
   system("sleep 0.5");
   printf("Version = %s\n", buf1.version); 
   system("sleep 0.5");
   printf("Release = %s\n", buf1.release); 
   system("sleep 0.5");
   printf("Machine = %s\n", buf1.machine);
   system("sleep 0.5");
   return 1;
}

int deleteFile(char *args)
{
	system("rm $args");
	printf("File deleted Successfully !!\n");
}
int listFiles()
{
   struct dirent *files;
   DIR *dir = opendir(".");
   if (dir == NULL)\
   {
      printf("Directory cannot be opened!" );
      return 0;
   }
    system("clear");
    system("./list.py");
    system("sleep 1");
    system("clear");
   puts("Files are -\n");
   while ((files = readdir(dir)) != NULL)
   {
   printf("%s\n", files->d_name);
   system("sleep 0.5");
   }
   closedir(dir);
   return 1;
}

int clearAll()
{
	system("clear");
	return 1;
}

int createFile(char *args)
{
	char data[1000];

    /* File pointer to hold reference to our file */
    FILE * fPtr;

    fPtr = fopen(args, "w");

    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        return 0;
    }
    
    printf("Enter contents to store in file : \n");
    fgets(data,1000, stdin);
    fputs(data, fPtr);
    fclose(fPtr);
    printf("File created and saved successfully. :) \n");
    return 1;
}

int executeline(char **args)
{
	if(strcmp(args[0],"listCmd") == 0)
	{
		help(args[1]);	
	}
	else if(strcmp(args[0],"workingSpace") == 0)
	{
		pwd();
	}
	else if(strcmp(args[0],"leave") == 0)
	{
		return 0;
	}
	else if(strcmp(args[0],"changeTo") == 0)
	{
		cd(args);
	}
	else if(strcmp(args[0],"calculator") == 0)
	{
		calculator();
	}
	else if(strcmp(args[0],"systemInfo") == 0)
	{
		systeminfo();
	}
	else if(strcmp(args[0],"listFiles") == 0)
	{
		listFiles();
	}
	else if(strcmp(args[0],"clearAll") == 0)
	{
		clearAll();
	}
	else if(strcmp(args[0],"createFile") == 0)
	{
		createFile(args[1]);
	}
	else if(strcmp(args[0],"deleteFile") == 0)
	{
		deleteFile(args[1]);
	}
	else
	{
		pid_t pid,wpid; //two process id's  -- one for currently running process and the latter one for waiting process
		int status;
		pid=fork();
		
		if(pid==0)  //child process is created
		{
			if(execvp(args[0],args) == -1)
			{
				perror("Error in  Child Process ! :<");
			}
			exit(EXIT_FAILURE);
		}
		else if(pid<0)
		{
			perror("Child process was unsuccessful!!");
		}
		else //parent process
		{
			do
			{
	      		wpid = waitpid(pid, &status, WUNTRACED);
	    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
		
	return 1;
}

void loop()
{
	int status;
	char *cmd;
	char **args;
	printf("\n");
	do
	{
		printf("\x1b[32m" "user@OS > " "\x1b[0m");
		
		cmd=readline();
		args=splitline(cmd);
		status=executeline(args);
		
		free(cmd);
		free(args);
	}while(status);
}




void main()
{
	pid_t pid;
	int status=1;
	system("clear");
	system("sleep 1");
	system("./start.py");
	system("sleep 1");
	system("clear");
	system("sleep 1");
	char *args[] = {"./f.py",NULL};
	if ((pid = fork()) > 0) 
	{
    	waitpid(pid, &status, 0);
	}
	else 
	{
  		execvp(args[0],args);
	}
	loop();
}

