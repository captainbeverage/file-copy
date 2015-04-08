#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;

int main() {
	string readFilename;
	string writeFilename;
	string path;
	unsigned char readString[512];
	ssize_t	sizeOfRead = 0;

	cout << "Enter source filename to read: ";
	cin >> readFilename;

	// Reading file
	int fID = open(readFilename.c_str(),O_RDONLY);

	if (fID == -1) 
		cout << "Error opening file.";
	else {
		cout << "Worked correctly: ";
		sizeOfRead = read(fID,(void*)readString,512);
	}

	// Write to file
	cout << "Enter the path for the destination file: ";
	cin >> path;

	cout << "Enter destination filename to write: ";
	cin >> writeFilename;

	// try to open file first to get file descripter
	int fileDescripter = open(writeFilename.c_str(), O_WRONLY);

	// If it doesn't exist create it
	if (fileDescripter == -1)		
		fileDescripter = creat(writeFilename.c_str(), 0600);	

	// Write to file, will be 0 if nothing was written, -1 if failed
	write(fileDescripter, (void*)readString, sizeOfRead);

	while (sizeOfRead >= 512) {	
		sizeOfRead = read(fID,(void*)readString,512);
		// Write to file, will be 0 if nothing was written, -1 if failed
		write(fileDescripter, (void*)readString, sizeOfRead);
	}

	// if (id == 0)
	// 	cout << "\n\nNothing was written to file\n";
	// else if (id == -1)
	// 	cout << "\n\nError while writing to file\n";
	// else {
	// 	cout << "\n\nFile written to successfully\n";
	// 	int colseId = close(fileDescripter);
	// }

	return 0;
}