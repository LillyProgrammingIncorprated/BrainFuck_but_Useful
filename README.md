This is my take on brainfuck. It isn't anything special, it's just a general improvement to make it from a jokey challange language to an actually useful challange language. The added features are thus:
1- "If pointed cell nonzero" statements
2- File I/O
3- Generic I/O (as in, ability to input numbers as numbers and not as ASCII characters)
4- Error messages in case you fuck up

1- If statements:
  They work the same as the loops but instead of looping it executes the code it has in the block. It uses the '(' and ')' as its beginning and end respectively. 
  EXAMPLE:
	
    +(>++++++++++++++++++++++++++++++++++++++++++++++++++++++++.)
    Output: 8
		
  EXAMPLE 2: 
	
    (>++++++++++++++++++++++++++++++++++++++++++++++++++++++++.)
    OUTPUT: NULL
    
		
2- File I/O:
  This allows for very basic file reading & writing as such: 
    Open file with '%'. Second call of '%' closes the file.
    Use '^' to write the ASCII value of the current cell to the file and advance the position indicator for the stream.
    Use 'v' to get ASCII value of character from file & copy it to currently pointed cell, and advance the position indicator for the stream.
    EXAMPLE:
    
    %
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++^>v.
    %
    OUTPUT: 8
    FILE: 8
		
  You have to add the location of the file as the second argument after the file you have your code in.
  EXAMPLE: 
	
    ./BFI *brainfuck_file* *file_to_be_edited*
    
		
3- Generic I/O
  You can use ':' to print the numeric value of the currently pointed cell.
  You can use ';' to get the numeric value of user input
  EXAMPLE:
	
    ++++++++:
    OUTPUT: 8
    
  EXAMPLE 2: 
	
    ;.
    INPUT: 97
    OUTPUT: a
    
    
Installation & Use
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
gcc brainfuck.c -o BFI

./BFI *filename*.bf (optional) /*file to be edited*
    
