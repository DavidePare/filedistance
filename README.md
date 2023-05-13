# Levenshtein distance in C
Different Features:
  -h or --help: command to see al command
  filedistance distance file1 file2 : calculate the distance between file1 and file2
  filedistance apply inputfile filem outputfile : taken inputfile apply the operation inside filem and save it to outputfile
  filedistance search inputfile dir : print all the distances between inputfile and all the content inside the specific dir 
  filedistance searchall inputfile dir limit : print all the distances (=<limit) between inputfile and all the content inside the specific dir 
  
 
Operation TYPE|Position|NewValue. Different types: DEL,ADD,SET.

Example of filem:
ADD 1 65 will add the letter A in the first 1 of the file.
