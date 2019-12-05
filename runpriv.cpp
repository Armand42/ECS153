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
#include <fcntl.h>
#define STUDENT_UID 608010

using namespace std;
struct stat attr;


uid_t getuid(void);
uid_t geteuid(void);

// TODO (Main issues so far)
// Check if file has been modified condition (Remember you only have 60 seconds to continue program)
// Subprocess?
// Problem 6 problems
// symlink
// verify sniff is only a file - use stat and mode
// Clean up code


// FIX CONDITIONALS TO ENSURE STUDENT OWNS EVERYTHING PROPERLY!!!
int validateUser()
{
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
	string cmd = "kinit ";
	const char *command = cmd.c_str();
	// First call command to enter password (give actual error)
	cout << "Please enter your password\n";
	if (system(command) != 0) 
	{
		fprintf(stderr, "Error: Password incorrect, exiting now...\n");
		exit(EXIT_FAILURE);
		
	}
	cout << "Password Accepted into UCD CAS!\n";
	return 0;
}

int fileOwnership()
{
	stat("sniff.txt", &attr);

	if (attr.st_uid != STUDENT_UID)
	{
		fprintf(stderr, "Error: student is not the owner!\n");
		exit(EXIT_FAILURE);
	}
	// Check if student has all permissions
	// Check if specific ownership of the file
	if ((attr.st_mode & S_IXUSR) && (attr.st_mode & S_IRUSR) && (attr.st_mode & S_IWUSR) && !(attr.st_mode & S_IRWXG) && !(attr.st_mode & S_IRWXO))
	{ // check to see if student owns file and has all permissions
		cout << "Student owns file and has all permissions!\n";
		return 0;
	}
	else{
		fprintf(stderr, "Error: student does not own file and others have permissions!\n");
		exit(EXIT_FAILURE);
		
	}
}

int checkFile()
{
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
	if (chown("sniff.txt",0,95) == -1)
	{
		fprintf(stderr,"Error: could not give file to root!\n");
		return -1;
	}
	if (chmod("./sniff",04550) == -1)
	{
		fprintf(stderr,"Error: could not change permissions!\n");
		return -1;
	}	
	else
		cout << "Permissions were successfully changed to root!\n";
	return 0;
	
}
// Problem becuase u didnt create file in program
int fileTime()
{
	//struct stat time_stat;
	//stat("sniff.txt",&time_stat);
	//struct tm * timeInfo = localtime(&time_stat.st_mtime);
	//printf("File time and date: %s", asctime(timeInfo));

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
