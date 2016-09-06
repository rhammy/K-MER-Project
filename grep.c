#include<stdio.h>
#include<string.h>

//------------------------------------------------------------------------------------------------------------------------------------------
typedef struct node {
  int data;
  struct node *next;
}newNode;

newNode *arrays[10];

void linkedListStartup(){
	int i;
	for(i = 0;i<6;i++){
		arrays[i]= malloc(sizeof(newNode));
		arrays[i]=NULL;
	}
}

void addNode(int index,int val){
	newNode *placer =  (newNode*) malloc(sizeof(newNode));
	placer->data = val;
	placer->next = arrays[index];
	arrays[index] = placer;
}
void printIndex(int index){
	newNode *current = arrays[index];
	while(current!=NULL){
		printf("%i\n",current->data);
		current = current->next;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------

struct sequence {			// Creating a STRUCT of type sequence. In the struct, it contains a string of the sequence. 
		char seqString[200];	// The variable in the sequence structure is 
	};	

struct sequence ofSequences[8];		// Creating an array of sequence STRUCTURES. 
					// Need at most two lists, One to hold kmer's, second to hold sequences. 

void healthkmerGrep(char txtFile[]){		// This method will search for k-mer's with count #0 and copy that kmer into array
	FILE *fileScanner = fopen(txtFile,"r");		// Opening file to begin file stream.
	char buff[100];						// Creating a space to import data from file.
	
	int counter =0; 					// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){		// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
								// This line will grep for for 0's then add kmer to list. 
		/*Grep code----------------
		---------------------------*/
		strcpy(ofSequences[counter].seqString,buff);	// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);		// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}
void sickkmerGrep(char txtFile[]){		// This method uses results from healthy kmer and greps to determine if present in sick kmer. 
	FILE *fileScanner = fopen(txtFile,"r");		// Opening file to begin file stream.
	char buff[100];						// Creating a space to import data from file.
	
	int counter =0; 					// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){		// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
								// This line will grep if healthy kmer != 0 then keep that kmer in the list. If still 0, remove kmer from list. 
		/*Grep code----------------
		---------------------------*/
		strcpy(ofSequences[counter].seqString,buff);	// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);		// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}
void sicksequenceGrep(char txtFile[]){		// This method will grep each kmer from fasta file, then add each sequence to a fasta file.
	FILE *fileScanner = fopen(txtFile,"r");		// Opening file to begin file stream.
	char buff[100];						// Creating a space to import data from file.
	
	int counter =0; 					// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){		// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
								// This line will grep the sequence then add whole sequence to output file.
		/*Grep code----------------
		---------------------------*/
		strcpy(ofSequences[counter].seqString,buff);	// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);		// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}

main(int argc, char *argv[]){
	healthy = argv[1];					//Take in 3 files from command line (healthy kmer, sick kmer, sick fasta)
	sick = argv[2];
	sickFST = argv[3];
	healthkmerGrep(healthy);				//Enter each file into grep method
	sickkmerGrep(sick);
	sicksequenceGrep(sickFST);
	sequenceSetup("Tester Kmer File.txt");
	linkedListStartup();
	addNode(1,17);
	addNode(1,61);
	addNode(1,93);
	addNode(2,5);
	addNode(2,12);
	addNode(2,15);
	printIndex(1);
	printIndex(2);
	
}
