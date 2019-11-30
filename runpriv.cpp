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

uid_t getuid(void);
uid_t geteuid(void);

// TODO
// Add exit codes
// Problem 6
// README
// PLACE IN LAB DIRECTORY!!!
// Clean up code


int main() 
{	
	// Problem 1
	open("sniff.txt", O_RDWR|O_CREAT, 0700);
	int userID = getuid();
	
	if (userID == STUDENT_UID) 
		cout << "Student user verified\n";
	
	else
		fprintf(stderr, "Error: student id does not match\n");
	
	// Ensure only student has permissions (hack)
	//chmod("sniff.txt", S_IRWXU);

	// Problem 2 
	string cmd = "kinit ";
	const char *command = cmd.c_str();
	// First call command to enter password (give actual error)
	if (system(command) != 0) 
	{
		fprintf(stderr, "Error: password incorrect\n");
		exit(0);
	}

	// Problem 3
	if (access("sniff.txt", F_OK) != -1)
		cout << "sniff.txt file exists\n";
	else
		fprintf(stderr, "Error: sniff.txt file does not exits\n");

	// Problem 4 
	// Create attributes for sniff.txt
	struct stat attr;
    stat("sniff.txt", &attr);

	// Check if student has all permissions
	// Check if specific ownership of the file
	if ((attr.st_uid & S_IRWXU) && !(attr.st_mode & S_IRWXG) && !(attr.st_mode & S_IRWXO)) // check to see if student owns file and has all permissions
		cout << "Student owns file and has all permissions\n";
	
	else{
		fprintf(stderr, "Error: student does not own file and others have permissions\n");
		// Add an exit code
	}
	
	// first check if student  is the owner
		// if so then can change the permissions

	// else error

	// Problem 5 
	// Calculate time difference between file creation/modification and current time
	time_t my_time = time(NULL); 
	time_t time1 = attr.st_mtime;
	time_t time2 = my_time;
	if (time2 - time1 > 60) 
	{
		fprintf(stderr,"Error: last modified time: %ld seconds\n",(time2 - time1));
		// How to exit properly
		//exit(0);
	}
    


	// Problem 6 here

	if (chown("sniff.txt",0,4550) == -1)
	{
		fprintf(stderr,"Error: could not give file to root\n");
	}
	
			// check if return value of kinit is 
			// chmod IUSR
			// stat for problem 4, check against macro for ownership
			// st.mode from stat 
			// divide by 8 for bits
			// 655

			// problem 6 use chown and chmod

	// How can I excute the password at the same time

	//string cmd = "kinit ";
	//cmd = cmd + password;
	//string txt = "a";
	//const char *command = cmd.c_str();
	//const char *x = txt.c_str();
	
	// First call command to enter password (give actual error)
	//if (system(command) != 0) {
	//	cout << "ERROR: password incorrect\n";
	//}
	//system(x);

	//char *cmd[2] = {password, NULL};
	//if (execvp(cmd[0], cmd) == STUDENT_UID){
	//	cout << "dsfs";
	//}
	//cout << value;




	return 0;
}
