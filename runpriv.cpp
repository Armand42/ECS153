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

// Make sure to use actual errors


int main() 
{	
	// Problem 1
	open("sniff.txt", O_RDWR|O_CREAT, 0777);
	int userID = getuid();
	
	if (userID == STUDENT_UID) {
		cout << "Problem 1 Success\n";
	}
	else
		fprintf(stderr, "Error: student id does not match\n");
	
	// Problem 2 (Still need to validate check)
	string password;
	cout << "Please enter your password: ";
	getline(cin, password);
	cout << password << endl;

	// Problem 3
	if (access("sniff.txt", F_OK) != -1)
		cout << "File Exists\n";
	else
		fprintf(stderr, "Error: file does not exits\n");

	// Problem 4 here

	// first check if student  is the owner
		// if so then can change the permissions

	// else error

	// Problem 5 (Fix time validation)
	time_t my_time = time(NULL); 
	struct stat attr;
    stat("sniff.txt", &attr);
	printf("%s", ctime(&my_time)); 
	time_t t = attr.st_mtime;
	time_t t2 = my_time;
	if (t2 - t > 60) {
		cout << "ERROR: Modified file\n" << t2-t;
		//exit(0);
	}
    printf("Last modified time: %ld",(t2 - t));


	// Problem 6 here
	
			// check if return value of kinit is 
			// chmod IUSR
			// stat for problem 4, check against macro for ownership
			// st.mode from stat 
			// divide by 8 for bits
			// 655

			// problem 6 use chown and chmod

	// How can I excute the password at the same time

	string cmd = "kinit ";
	//cmd = cmd + password;
	//string txt = "a";
	const char *command = cmd.c_str();
	//const char *x = txt.c_str();
	
	// First call command to enter password (give actual error)
	if (system(command) != 0) {
		cout << "ERROR: password incorrect\n";
	}
	//system(x);

	//char *cmd[2] = {password, NULL};
	//if (execvp(cmd[0], cmd) == STUDENT_UID){
	//	cout << "dsfs";
	//}
	//cout << value;




	return 0;
}
