# CS441/541 Project 2

## Author(s): Nick Williams

TODO


## Date: February 16, 2018

TODO


## Description: This program reads processor information and sorts it according to the selected algorithm
    Does not handle SJF and Priority fully, but gets close.

TODO


## How to build the software: Compile in the terminal/shell
first type make in the terminal to compile the software and then
type: ./scheduler.c -s "#(1-4)" "Name of File" -q "#(Quantum number)"

TODO


## How to use the software: Type the following arguments in any order
1: "-s" followed by a number 1-4 to select a sorting algorithm (1 = FCFS, 2 = SJF, 3 = Priority, 4 = Round-Robin)
2: "-q" followed by a desired quantum number (only required for Round-Robin)
3: "nameOfTextFile" type the name of the text file that the process information is to be read from

TODO


## How the software was tested
 The software was testing using the "given-tests" folder as well as my own created tests in "tests" folder.
 test1: tests RR with a low quantum and high processor bursts
 test2: tests RR with a high quantum and low processor bursts
 test3: a test file with no data to check if the program can exit without getting stuck
 test4: tests equal priorities for the priority scheduler
 test5: tests equal bursts for SJF scheduler

TODO

## Test Suite
Not sure what this is....
TODO


## Known bugs and problem areas
FCFS works to my knowledge
SJF does not correctly copy the Waiting  Time & Turnaround Time and does not display both correctly to output
Priority does not correctly copy the Turnaround Time  and does not display it correctly to output
    flips around the last two numbers... tried fixing in a for loop
RoundRobin works as far as my test cases went
When running make check, it gets stuck at the fourth test
    Also, does not get the last column number correct for some of the tests when running make check

TODO
