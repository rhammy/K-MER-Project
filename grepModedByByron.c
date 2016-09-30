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


void printTableIndex(struct hashtable_s *targetTable,int location){
	struct node_s * current = NULL;
	current = targetTable -> table[location];
	while(current != NULL){
		printf("%s\n",current->data.kmerChars);
		current = current->next;
	}
	//puts("");
}
void printTableFasta(struct hashtable_s *targetTable,char *fname, int location){
	struct node_s * current = NULL;
	current = targetTable -> table[location];
	while(current != NULL){
		Search_in_File(fname,current->data.kmerChars);
		current = current->next;
	}
	//puts("");
}


int hashCode(char charArray[]){
	int stringLength=strlen(charArray);
	int i;
	int hashNumber = 0;
	for(i=0;i<stringLength;i++){
		char letter = charArray[i];
		int exponentiate;
		exponentiate = pow(letter,i);
		hashNumber+=exponentiate;	
	}
	if(hashNumber < 0){
		hashNumber*=-1;
	}
	return hashNumber;
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






main(int argc, char **argv){  
	char *sick = argv[1];
	char *healthy = argv[2];
	char *fasta = argv[3];

	struct hashtable_s *testTable = createHashTable(20);

	FILE *fileScanner = fopen(sick,"r");	
	char buff[100];								
	while(fgets(buff,200,fileScanner)!=NULL){	
		char strTmp[20];
		int buffHolder = 0;
		memset(&strTmp[0], 0, sizeof(strTmp));
		while(buff[buffHolder]!=' '){
			strTmp[buffHolder]=buff[buffHolder];
			buffHolder++;
		}
		struct kmer_s newKmer;
		strcpy(newKmer.kmerChars,strTmp);
		int index = hashCode(newKmer.kmerChars);
		index = index % testTable->size;
		addNode(testTable,index,newKmer);	
	}	
		
	int i;

puts("");				


	FILE *fileChecker = fopen(healthy,"r");	
	char check[100];								
	while(fgets(check,200,fileChecker)!=NULL){	
		char strTmp[20];
		int buffHolder = 0;
		memset(&strTmp[0], 0, sizeof(strTmp));
		while(check[buffHolder]!=' '){
			strTmp[buffHolder]=check[buffHolder];
			buffHolder++;
		}
		struct kmer_s newKmer;
		strcpy(newKmer.kmerChars,strTmp);
		int index = hashCode(newKmer.kmerChars);
		index = index % testTable->size;
		removeNode(testTable,index,newKmer);	
		}
	
	for(i = 0;i<testTable->size;i++){
	printTableIndex(testTable,i);
	}
	for(i = 0;i<testTable->size;i++){
	printTableFasta(testTable,fasta,i);
	}
}
