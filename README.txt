Natthaphong Kongkaew
CS344 Fall 2020
Assignment 2 : Files & Directories

*NOTE:    the program may result in Segmentation Fault (core dumped). I have not figure out how to fix it due to memory leak. 
          For now to make program run without the issue, I have tried
          try to choose the option 3 first ("Enter 3 to specify the name of a file") then specify the name of the files to be processed.
          After the repeat again, you can select any options (1-3).

-----------------------------------------
Files requires for compile the program
-----------------------------------------
*1. kongkaen.program2.c

-----------------------------------------
Files samples for testing the program
-----------------------------------------
*1. movies_1.c  (largest file)
*2. movies_2.c  (smallest file)

-----------------------------------------
Compiling code and usage
-----------------------------------------
*Run "gcc --std=gnu99 -o movies_by_year kongkaen.program2.c" to compile file
*Run "./movies_by_year"

*It will prompt user to choose options 1-2.
example:  1. Select file to process
          2. Exit the program

*User choose an option from keyboard input.

*User choose option 1:
*It will prompt user to choose again options 1-3.
ex: Which file you want to process?
    Enter 1 to pick the largest file
    Enter 2 to pick the smallest file
    Enter 3 to specify the name of a file

*Program will repeat the prompt user option 1-2:

*option 2 to exit the program.
