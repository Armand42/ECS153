#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define STUDENT_UID 608010

using namespace std;

uid_t getuid(void);
uid_t geteuid(void);




int main() 
{	
	open("sniff.txt", O_RDWR|O_CREAT, 0777);
	int userID = getuid();
	
	if (userID == STUDENT_UID) {
		cout << "Problem 1 Success\n";
	}
	else
		fprintf(stderr, "Error: student id does not match\n");
		
	string password;
	cout << "Please enter your password: ";
	getline(cin, password);
	cout << password << endl;


	if (access("sniff.txt", F_OK) != -1)
		cout << "File Exists\n";
	else
		fprintf(stderr, "Error: file does not exits\n");
	// How can I excute the password at the same time

	//string cmd = "kinit ";
	//cmd = cmd + password;
	//string txt = "a";
	//const char *command = cmd.c_str();
	//const char *x = txt.c_str();
	//system(command);
	//system(x);

	//char *cmd[2] = {password, NULL};
	//if (execvp(cmd[0], cmd) == STUDENT_UID){
	//	cout << "dsfs";
	//}
	//cout << value;




	return 0;
}
