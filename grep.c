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

void sequenceSetup(char txtFile[]){
	FILE *fileScanner = fopen(txtFile,"r");	// Opening file to begin file stream.
	char buff[100];						// Creating a space to import data from file.
	
	int counter =0; 					// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){		// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
		strcpy(ofSequences[counter].seqString,buff);	// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);		// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}

main(){
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
