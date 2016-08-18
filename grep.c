#include<stdio.h>
#include<string.h>

main()
{
	FILE *fileScanner = fopen("Tester Kmer File.txt","r");	// Opening file to begin file stream.
	char buff[100];											// Creating a space to import data from file.
	
	struct sequence {										// Creating a STRUCT of type sequence. In the struct, it contains a string of the sequence. 
		char seqString[50];									// The variable in the sequence structure is 
	};
	
	struct sequence ofSequences[8];							// Creating an array of sequence STRUCTURES. 
	
	int counter =0; 										// Counter to keep a place in the array. 
	while(fgets(buff,100,fileScanner)){						// Getting strings from the file one by one until no more lines avaiable.
		strcpy(ofSequences[counter].seqString,buff);		// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);				// Simple print statement to display the variable from each array index. 
		counter++;
	}
	
}

