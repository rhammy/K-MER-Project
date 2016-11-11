#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//------------------------------------------------------------------------------------------------------------------------------------------
struct kmer_s{
	char kmerChars[20]; 
	
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

/*Adding a node into a hash table. Utilizes @createNode*/
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
	if (current == targetTable->table[location]){ //Add at the beginning of a list
		newEntry->next = current;
		targetTable->table[location] = newEntry;
	}else{ //Add at the end of a list
	 previous->next = newEntry;
	}	
}

void removeNode(struct hashtable_s *targetTable,int location,struct kmer_s import){
	struct node_s * toRemove = NULL;
	struct node_s * current = NULL;
	struct node_s * previous = NULL;
	toRemove = createNode(import); //create an instance of what we WANT TO REMOVE
	current = targetTable->table[location];
	while(current!=NULL){
		if((strcmp(current->data.kmerChars,toRemove->data.kmerChars)==0)){
			if(previous == NULL){ //At the start of the list
			 targetTable->table[location] = current -> next;
			return;
			}else{ // Any where else in the list
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


void printTable(struct hashtable_s *targetTable){
	int i;
	for(i=0;i<targetTable->size;i++){
		struct node_s * current = NULL;
		current = targetTable -> table[i];
		printf("Index i: %i\n", i);
		while(current != NULL){
			printf("%s\n",current->data.kmerChars);
			current = current->next;
		}
	}
}


unsigned long hashCode(unsigned char *str)
{
    unsigned long hashCode = 5381;
    int c;

    while (c = *str++)
        hashCode = ((hashCode << 5) + hashCode) + c; /* hash * 33 + c */

    return hashCode;
}

void populateTable(struct hashtable_s *targetTable, char *fileName){
	FILE *fp = fopen(fileName,"r");	
	char space[100];								
	while(fgets(space,200,fp)!=NULL){	
		char temp[20];
		int holder = 0;
		memset(&temp[0], 0, sizeof(temp));
		while(space[holder]!=' '){
			temp[holder]=space[holder];
			holder++;
		}
		struct kmer_s newKmer;
		strcpy(newKmer.kmerChars,temp);
		unsigned long index = hashCode(newKmer.kmerChars);
		index = index % targetTable->size;
		addNode(targetTable,index,newKmer);	
	}	
}

void locateUnique(struct hashtable_s *targetTable, char *fileName){
	FILE *fp = fopen(fileName,"r");	
	char space[100];								
	while(fgets(space,200,fp)!=NULL){	
		char temp[20];
		int holder = 0;
		memset(&temp[0], 0, sizeof(temp));
		while(space[holder]!=' '){
			temp[holder]=space[holder];
			holder++;
		}
		struct kmer_s newKmer;
		strcpy(newKmer.kmerChars,temp);
		unsigned long index = hashCode(newKmer.kmerChars);
		index = index % targetTable->size;
		removeNode(targetTable,index,newKmer);	
		}
}

void searchThroughFasta(struct hashtable_s *targetTable,char *fileName){
	FILE *fp = fopen(fileName,"r");
	FILE *fileOutput = fopen("output.txt","w+");
	int fastaCounter=1;
	int DNAid;
	int matchesFound = 0;
	char space[500];
	while(fgets(space,500,fp)!=NULL){
		if(space[0]== '>'){
			DNAid=atoi(space+1);
			continue;
		}
		int i;
		for(i=0;i<targetTable->size;i++){
			int foundKmer = 0;
			struct node_s * current = NULL;
			current = targetTable -> table[i];
			while(current != NULL){
				if((strstr(space, current->data.kmerChars)) == NULL){
				current = current->next;
				}else{
					printf("kmer '%s' was found in DNAid %i:\n",current->data.kmerChars,DNAid);
					puts("");
					printf("%s\n",space);
					fprintf(fileOutput,">%i\n",fastaCounter);
					fprintf(fileOutput,"%s",space);
					puts("");
					foundKmer = 1;
					fastaCounter++;
					break;
				}
			}
			if (foundKmer == 1){
				matchesFound++;
				break;
			}
		}
	}
	if(matchesFound == 0){
		puts("No matches were found");
	}
}

main(int argc, char** argv){  

	struct hashtable_s *testTable = createHashTable(250000);
	populateTable(testTable, argv[1]);
	printTable(testTable);
	puts("");
	locateUnique(testTable, argv[2]);
	printTable(testTable);
	puts("");
	searchThroughFasta(testTable, argv[3]);
	
}
