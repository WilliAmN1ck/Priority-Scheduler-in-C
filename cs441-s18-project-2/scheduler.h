/*
 *
 *
 * CS 441/541: CPU Scheduler (Project 1)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/******************************
 * Defines
 ******************************/


/******************************
 * Structures
 ******************************/
typedef struct Process {
    int procId;
    int burst;
    int priority;
    int waitTime;
    int turnAroundTime;
}Proc;


/******************************
 * Global Variables
 ******************************/
//FILE *fd; //the file to read from -- delete?
int numProcesses;
Proc *procPtr; //points to address of first process in array of processes?
//or else can use feof(FILE *fd) for checking when at EOF
//char *line;//variable to temporarily store a readline in

/******************************
 * Function declarations
 ******************************/
void printProcessInfo(); //prints process info & maybe arrival order before it
void readData(); //reads in the file data
void debugProc(Proc *p);
void sortData(int mode, int quantum);
void printScheduler(int x);
void arrivalOrder();
void setTimes(Proc *ptr);
//void calcTurnAround(int **array);
//void freeStuff();

