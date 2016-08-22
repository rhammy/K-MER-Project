
#include<stdio.h>
#include<string.h>

struct sequence {					// Creating a STRUCT of type sequence. In the struct, it contains a string of the sequence. 
		char seqString[200];	// The variable in the sequence structure is 
	};	

struct sequence ofSequences[8];		// Creating an array of sequence STRUCTURES. 

void sequenceSetup(char txtFile[]){
	FILE *fileScanner = fopen(txtFile,"r");	// Opening file to begin file stream.
	char buff[100];											// Creating a space to import data from file.
	
	int counter =0; 										// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){						// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
		strcpy(ofSequences[counter].seqString,buff);		// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);				// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}

main(){
	sequenceSetup("Tester Kmer File.txt");
}
