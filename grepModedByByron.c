#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//------------------------------------------------------------------------------------------------------------------------------------------
struct kmer_s{
	char kmerChars[5]; 
};

struct node_s {
	struct kmer_s data;
	struct node_s *next;
};

struct hashtable_s {
	int size;
	struct node_s **table;	
};


/* Create a new hashtable. */
struct hashtable_s *createHashTable( int size ) {
	
	struct hashtable_s *newHashTable = NULL;
	int i;
	
	/* Allocate the table itself. */
	newHashTable = malloc( sizeof( struct hashtable_s ) );
	
	/* Allocate pointers to the head nodes. */
	newHashTable->table = malloc( sizeof( struct hashtable_s * ) * size );
	
	/* Setting each index containing a head node to Null*/
	for( i = 0; i < size; i++ ) {
		newHashTable->table[i] = NULL;
	}
	
	newHashTable -> size = size;
	
	return newHashTable;
}

/*Create new node to be entered into hashTable*/
struct node_s *createNode(struct kmer_s val){
	struct node_s *newNode;
	newNode = malloc(sizeof(struct node_s));
	newNode->data=val;
	newNode->next = NULL;
	return newNode;
}

void addNode(struct hashtable_s *targetTable,int location,struct kmer_s import){
	struct node_s * newEntry = NULL;
	struct node_s * current = NULL;
	struct node_s * previous = NULL;
	newEntry = createNode(import);
	current = targetTable -> table[location];
	
	while( current != NULL){
		previous = current;
		current = current->next;
	}
	if (current == targetTable->table[location]){ //table index is an empty list
		newEntry->next = current;
		targetTable->table[location] = newEntry;
	}else{ //add at the end of a list
	 previous->next = newEntry;
	}	
}

void removeNode(struct hashtable_s *targetTable,int location,struct kmer_s import){
	struct node_s * toRemove = NULL;
	struct node_s * current = NULL;
	struct node_s * previous = NULL;
	toRemove = createNode(import);
	current = targetTable->table[location];
	while(current!=NULL){
		if((strcmp(current->data.kmerChars,toRemove->data.kmerChars)==0)){
			if(previous == NULL){ 
			 targetTable->table[location] = current -> next;
			return;
			}else{
				previous->next = current -> next;
			return;
			}
		}
	previous = current;
	current = current -> next;
	}
	printf("No matches found\n");
	return;
}

void printTableIndex(struct hashtable_s *targetTable,int location){
	struct node_s * current = NULL;
	current = targetTable -> table[location];
	while(current != NULL){
		printf("%s\n",current->data.kmerChars);
		current = current->next;
	}
}


//----------------------------------------------------------------------------------------------------------------------------------------------

struct healthyKmer {
	char kmerString [10]; //kmer length
};

struct healthyKmer healthyKmerArray[100];//number of kmers
int healthyKmerArrayCounter = 0; // Universal healthy Kmer Array counter to increment through

void printArrayIndex(int index){
	printf("%s\n",healthyKmerArray[index].kmerString);
}

void splitFile(char fileString[]){
	FILE *fileScanner = fopen(fileString,"r");	// Opening file to begin file stream.
	char buff[100];								// Creating a space to import data from file.
	int lineCount = 1;
	while(fgets(buff,200,fileScanner)!=NULL){	
		char strTmp[20];
		int buffHolder = 0;
		memset(&strTmp[0], 0, sizeof(strTmp));
		while(buff[buffHolder]!=' '){
			strTmp[buffHolder]=buff[buffHolder];
			buffHolder++;
		}
	lineCount++;	
	}	
}

int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	
	if((fp = fopen(fname, "r")) == NULL) {
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

void printKmerArray(char *sickFile){ 	//ITERATES THE THE ARRAY OF HEALTHY KMERS Into a search function for the sick K-MER file to find the lines in which they occur. 
	int i;
	for(i = 0; i < healthyKmerArrayCounter;i++){
		Search_in_File(sickFile, healthyKmerArray[i].kmerString);
	}
}

main(){  
	struct kmer_s newKmer1;
	struct kmer_s newKmer2;
	struct kmer_s newKmer3;
	char newString1[] = "abc";
	char newString2[] = "efg";
	char newString3[] = "hij";
	strcpy(newKmer1.kmerChars,newString1);
	strcpy(newKmer2.kmerChars,newString2);
	strcpy(newKmer3.kmerChars,newString3);

	struct hashtable_s *newTable = createHashTable(10);
	
	addNode(newTable,3,newKmer1);
	addNode(newTable,3,newKmer2);
	addNode(newTable,3,newKmer3);
	
	printTableIndex(newTable,3);
	puts("");
	
	struct kmer_s dummyKmer;
	char newDummyString[]="efg";
	strcpy(dummyKmer.kmerChars,newDummyString);
	
	removeNode(newTable,3,dummyKmer);
	printTableIndex(newTable,3);
	
	
}
