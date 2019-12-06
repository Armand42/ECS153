This program demonstrates the complexities of managing privileges by creating
a file called "sniff.txt" and manipulating its privileges. 

Dependencies
------------
Requires C++ installed (any version will work)

To compile the program, a Makefile is included.
Make sure you are in the lab3-nasseri directory that contains the Makefile and the program.

Type in "make" into the command line and the program will compile.
(To remove any object files generated in the current directory type in "make clean").

To run the program type "./runpriv" and the program will execute.

The program will check if the "sniff.txt" file exists in the current working directory.

Be sure to correctly enter the password for the authentication credential
in the UC Davis Central Authentication System or else the program will
throw an error and terminate.

The program will proceed to validate that only the user has execute permissions to the file
sniff.txt and will check for any modifications to the file.

If all information prompted to the user is inputted correctly, the program
will finish execution without printing any error messages.
