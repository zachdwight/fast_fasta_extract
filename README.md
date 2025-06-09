#FASTA Sequence Extractor
This C++ program reads a FASTA-formatted file, cleans the sequences by removing newline characters within them, and then extracts and prints the sequence corresponding to a specified ID.

##Features
FASTA Parsing: Reads and correctly interprets standard FASTA files.
Sequence Cleaning: Removes all newline and whitespace characters within sequences, concatenating them into a single continuous string.
Targeted Extraction: Allows you to specify a FASTA ID, and the program will return only the sequence associated with that specific ID.
Error Handling: Includes basic error handling for file opening issues and incorrect command-line usage.

##Build and Run

g++ fasta_search_and_scrub.cpp -o faster_fasta_extract

./faster_fasta_extract NC_045512.2.fasta NC_045512.2

##Output

Target NC_045512.2:
ATTAAAGGTTTATACCTTCCCAGGTAACAA....
