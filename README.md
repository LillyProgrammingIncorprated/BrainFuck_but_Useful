This is my take on brainfuck. It isn't anything special, it's just a general improvement to make it from a jokey challange language to an actually useful challange language. The added features are thus:
1- "If pointed cell nonzero" statements
2- File I/O
3- Generic I/O (as in, ability to input numbers as numbers and not as ASCII characters)
4- Functions with an optional argument
5- Error messages in case you fuck up

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
    
    
4- Functions
  You can now make functions to be later called! You can only have 1 function at a time and can't overwrite it till called, and it can only be called once. This encourages thinking ahead and using functions only when absolutely necessary. (Also it fits BF's style, and it's much easier to code)
  To create a function, you use 'f'. Then, if you want it to take an argument, you put 'a' after it with no space between them. The argument it takes will be the cell pointed to. When it takes an argument, all operations that have to do with the tape will be done on the basis that it will start out with pointing to that cell.
  After f/fa you put '{' to start the block of code to be executed upon function call. If an accompanying '}' is not found, it will give an error. 
  If any character is put between the 'a' or '{' then it will give a Syntax Error.
  EXAMPLE:
  
    fa{+++++++++++++++++++++++++++++++++++++++++++++++++++.}
    f
    f{[-]++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.[-]}
    f
    f{
    +++++++++++++++++++++++++++++++++++++++++++++++++.[-]}
    f
    OUTPUT: 3Z1
  
  
Installation & Use
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
gcc brainfuck.c -o BFI

./BFI *filename*.bf (optional) /*file to be edited*
    
