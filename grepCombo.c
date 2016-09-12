#include<stdio.h>
#include<stdlib.h>
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
//----------------------------------------------------------------------------------------------------------------------------------------------

struct healthyKmer {
	char kmerString [10]; //kmer length
};

struct healthyKmer healthyKmerArray[100];//number of kmers
int healthyKmerArrayCounter = 0; // Universal healthy Kmer Array counter to increment through

void printArrayIndex(int index){
	printf("%s\n",healthyKmerArray[index].kmerString);
}

void search0s(char fileString[]){
	FILE *fileScanner = fopen(fileString,"r");	// Opening file to begin file stream.
	char buff[100];								// Creating a space to import data from file.
	int counter =0;	
	
	while(fgets(buff,200,fileScanner)!=NULL){	
		char strTmp[20];
		char intTmp[20];
		int buffHolder = 0;
		int intCounter = 0;
		memset(&strTmp[0], 0, sizeof(strTmp));
		memset(&intTmp[0], 0, sizeof(intTmp));
		while(buff[buffHolder]!=' '){
			strTmp[buffHolder]=buff[buffHolder];
			buffHolder++;
		}
		buffHolder++;
		while(buff[buffHolder]!= '\0'){
			intTmp[intCounter]=buff[buffHolder];
			buffHolder++;
			intCounter++;
		}
		int x = atoi (intTmp);
		if(x == 0){
			strcpy(healthyKmerArray[healthyKmerArrayCounter].kmerString,strTmp);
			healthyKmerArrayCounter++;
		}
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
main(int argc, char *argv[]){  //As of now, takes in two command line arguments that are txt files and finds difference in K_MER's
	search0s(argv[1]);
	printKmerArray(argv[2]);
}
