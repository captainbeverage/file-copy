/*
  This program copies the contents of a file to another file. It gets the path/filename for the source
  and destination from the user, and attempts to open those files. If there are errors, it notifies
  the user, and tries to get a new path/filename. If the destination file does not exist, it creates
  one. The program then reads the contents of the copied file, 512 bytes at a time, and writes them to
  the new file.

  Authors: Jordan Harris, Erik Crosby, Mike Ries
**/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;

#define SIZE 512

int main() {
	string readFile;			 // Holds the source path/filename
	string writeFile;			 // Holds the destination path/filename
	unsigned char buffer[SIZE];  // Buffer to hold the characters (size is 512)
	ssize_t	sizeOfRead = SIZE;   // Holds the number of characters read, initialized to 512

	// Gets the path/filename of the file to copy from the user
	cout << "Enter the path and filename for the file to copy: ";
	cin >> readFile;

	// Attempts to open the file. If the file cannot be opened, it gives an error to the user and gets a
	// new path/filename to open
	int readID = open(readFile.c_str(),O_RDONLY);
	while (readID == -1) {
		cout << "Error opening file to copy." << endl;
		cout << "Enter the path and filename for the file to copy: ";
		cin >> readFile;
		readID = open(readFile.c_str(),O_RDONLY);
	}

	// Gets the path/filename of the destination file from the user
	cout << "Enter the path and filename for the destination file: ";
	cin >> writeFile;

	// Attempts to open the destination file. If the file does not exist, it creates the file. If the file
	// cannot be opened, it gives an error to the user and gets a new path/filename to open/create
	int writeID = open(writeFile.c_str(), O_WRONLY | O_CREAT, 0666);
	while (writeID == -1) {
		cout << "Error opening destination file." << endl;
		cout << "Enter the path and filename for the destination file: ";
		cin >> writeFile;
		writeID = open(writeFile.c_str(), O_WRONLY | O_CREAT, 0666);
	}

	// Continually reads the source file and writes to the destination file until all data has been copied
	while (sizeOfRead >= SIZE) {	
		sizeOfRead = read(readID,(void*)buffer, SIZE);
		write(writeID, (void*)buffer, sizeOfRead);
	}

	// Closes the files and exits the program
	close(readID);
	close(writeID);
	cout << "Copy complete" << endl;
	return 0;
}