#include <stdio.h>

//This program splits a text file into quarters.

//There are several ways to find the line count in a file. An instant time function we can use is "fseek" but it only returns byte size. The bash command "wc -l" gives you the lines of a txt file. Other than these options we would have to read the file and get the line count after that.  

FILE *openforwrite(int filecounter) {
	char fileoutputname[15];

	sprintf(fileoutputname, "file_part%d", filecounter);
	return fopen(fileoutputname, "w");
}

int main(int argc, char** argv) {
	FILE *ptr_readfile;
	FILE *ptr_writefile;
	char line [512]; /* or some other suitable maximum line size */
	int filecounter=1, linecounter=1;

	ptr_readfile = fopen(argv[1],"r");
	fseek(ptr_readfile,0L,SEEK_END);
	int sz = ftell(ptr_readfile); //Returns the byte size of the file
	rewind(ptr_readfile); //Sets pointer back to beginning
	int split = sz/4; // Finds the size at which we want to split the file (in bytes, which is way more difficult than lines). 
	
	if (!ptr_readfile)
		return 1;

	ptr_writefile = openforwrite(filecounter);

	while (fgets(line, sizeof line, ptr_readfile)!=NULL) {
		if (linecounter == split) {
			fclose(ptr_writefile);//stops writing to file after 25% through. 
			linecounter = 1;
			filecounter++;
			ptr_writefile = openforwrite(filecounter);	
			if (!ptr_writefile)
			return 1;
		}
		fprintf(ptr_writefile,"%s\n", line);
		linecounter++;
	}
	fclose(ptr_readfile); //All four text files have been created and are reading for parallel usage
	return 0;
}
