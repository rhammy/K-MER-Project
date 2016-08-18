#include<stdio.h>



main()
{
char buffer[100];
FILE *file = fopen("Tester Kmer File.txt","r");

fgets(buffer,100,file);
puts(buffer);


}

