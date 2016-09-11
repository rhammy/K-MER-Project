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
					
int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	//gcc users
	//if((fp = fopen(fname, "r")) == NULL) {
	//	return(-1);
	//}

	//Visual Studio users
	if((fopen_s(&fp, fname, "r")) != NULL) {
		return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
   	return(0);
}

void healthkmerGrep(char txtFile[]){		// This method will search for k-mer's with count #0 and copy that kmer into array
	FILE *fileScanner = fopen(txtFile,"r");		// Opening file to begin file stream.
	char buff[100];						// Creating a space to import data from file.
	
	int counter =0; 					// Counter to keep a place in the array. 
	while(fgets(buff,200,fileScanner)!=NULL){		// Getting strings from the file one by one until no more lines avaiable.
		if(buff[0]=='>'){
			continue;
		}else{
								// This line will grep for for 0's then add kmer to list. 
		
		strcpy(ofSequences[counter].seqString,buff);	// Copying a string from the allocated buffer space into the array of structure's string variable.
		puts(ofSequences[counter].seqString);		// Simple print statement to display the variable from each array index. 
		counter++;
			}
		}
}

main(int argc, char *argv[]){
	result = Search_in_File(argv[1], argv[2]);
	if(result == -1) {
		perror("Error");
		printf("Error number = %d\n", errno);
		exit(1);
	}
	return(0);
}

}
