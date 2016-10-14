# K-MER-Project
Edwards Bioinformatics Research Lab: DNA sequencing programs

This C program takes in three arguments, a sick K-mer text file, healthy K-mer text file, and a fasta file of DNA sequences. The program outputs a fasta file of the unique, diseased DNA sequences. The program populates a hash table with diseased K-mer strings, then uses the hash function to identify which healthy K-mers strings are present in the table. If a match is found within the table, that data is removed, resulting in a table filled with only the unique diseased K-mers. The resulting diseased K-mers are then identified among the DNA sequences within the large fasta file. Finally, these unique seqeuences are returned in the form of a fasta file. 
