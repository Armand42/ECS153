This program demonstrates the complexities of managing privileges by creating
a file called "sniff.txt" and manipulating its privileges. 

Dependencies
------------
Requires C++ installed (any version will work)

To compile the program, a Makefile is included.
Make sure you are in the lab3-nasseri directory that contains the Makefile and the program.

Type in "make" into the command line and the program will compile.

To run the program type "./runpriv" and the program will execute.

A file called "sniff.txt" will be created with restricted permissions.

Be sure to correctly enter the password for the authentication credential
in the UC Davis Central Authentication System or else the program will
throw an error and terminate.

The program will proceed to validate that the only the user has permissions to the file
sniff.txt and will check for any modifications to the file.

If all information prompted to the user is inputted correctly, the program
will finish execution without printing any error messages.