#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <ctime>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#define STUDENT_UID 608010

using namespace std;
struct stat attr;


uid_t getuid(void);
uid_t geteuid(void);

int validateUser()
{
	// Verify that the user is the student
	int userID = getuid();
	
	if (userID == STUDENT_UID)
	{ 
		cout << "Student user verified!\n";
		return 0;
	}
	else
	{
		fprintf(stderr, "Error: student id does not match\n");
		exit(EXIT_FAILURE);
	}
}

int validateCredentials()
{
	// Validating user credentials 		
	cout << "Please enter your password\n";
	// Create process id and status
	pid_t pid;			
	int status;			
	char *cmd[2]  = {"kinit",NULL}; 
	// Create child process
	pid = fork(); 						
	if (pid == 0) { /* Child */			
        	if (execvp(cmd[0], cmd) != 0)	{	
        		perror("Error: failed to execute child process");
        		exit(1);
		}
	}
       	else if (pid > 0) { /* Parent */
        	waitpid(-1, &status, 0);
		if (status == 0)
		{

			cout << "Password Accepted into UCD CAS!\n";
			return 0;
		}
		else
		{
		 fprintf(stderr, "Error: Password incorrect, exiting now...\n");
		 exit(EXIT_FAILURE);
		}
	} 
	else 
	{
        	perror("fork");
		exit(1); 
	}	
	
	return 0;
}

int fileOwnership()
{
	stat("sniff.txt", &attr);
	 // Check if student owns the file
	if (attr.st_uid != STUDENT_UID)
	{
		fprintf(stderr, "Error: student is not the owner!\n");
		exit(EXIT_FAILURE);
	}
	// Check if student has execute permissions
	if (!(attr.st_mode & S_IXUSR))
	{
		fprintf(stderr, "Error: Student does not have execute permissions and Groups/Others may have permissions!\n");
		exit(EXIT_FAILURE);
	}
	// Check if anyone else has permissions
	if ((attr.st_mode & S_IRGRP) || (attr.st_mode & S_IWGRP) || (attr.st_mode & S_IXGRP) || (attr.st_mode & S_IROTH) || (attr.st_mode & S_IWOTH) || (attr.st_mode & S_IXOTH))
	{
		fprintf(stderr, "Error: Group or Others have read, write, or execute permissions!\n");
                exit(EXIT_FAILURE);
	}


	return 0;    
}

int checkFile()
{
	// Check if file exists in current working directory
	if (access("sniff.txt", F_OK) != -1)
	{
		cout << "sniff.txt file exists!\n";
		return 0;
	}
	else 
	{
		fprintf(stderr, "Error: sniff.txt file does not exist!\n");
		exit(EXIT_FAILURE);
	}
}

int changePermissions()
{	
	// Trying to change file permissions to root
	if (chown("sniff.txt",0,95) == -1)
	{
		fprintf(stderr,"Error: could not give file to root!\n");
		return -1;
	}
	if (chmod("./sniff",04550) == -1)
	{
		perror("Error: could not change permissions!\n"); // use perror
		return -1;
	}	
	else
		cout << "Permissions were successfully changed to root!\n";
	return 0;
	
}

int fileTime()
{
	// Checking if the file has been created or modified over a minute ago
	int bound = 60;
	time_t my_time = time(NULL); 
	time_t fileTime = attr.st_mtime;
	time_t currentTime = my_time;
	// Calculate time difference between file creation/modification and current time
	if (currentTime - fileTime > bound) 
	{
		fprintf(stderr,"Error: last modified time: %ld seconds\n",(currentTime - fileTime));
		exit(EXIT_FAILURE);
		
	}
	return 0;
}

int main() 
{	
	// Problem 1
	validateUser();
	// Problem 2
	validateCredentials();
	// Problem 3
	checkFile();
	// Problem 4
	fileOwnership();
	// Problem 5
	fileTime();
	// Problem 6
	changePermissions();
	
	return 0;
}
