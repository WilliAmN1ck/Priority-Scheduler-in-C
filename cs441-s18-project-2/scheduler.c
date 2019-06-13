/*
 *
 *
 * CS 441/541: CPU Scheduler (Project 1)
 */
#include "scheduler.h"

/*typedef struct Process {
 int procId = 0;
 int burst = 0;
 int priority = 0;
 int waitTime = 0;
 int turnAroundTime = 0;
 }Proc;*/

//FILE *fd;
//int numProcesses;

int main(int argc, char **argv) {
    FILE *fd = NULL;
    procPtr = NULL; //pointer to the first element of the Proc[]
    numProcesses = 0;
    int lineCount = 0;
    
    char * fgetsRtn = NULL;
    char * cmdArg = NULL;
    int mode = 0;
    int quantum = 0;
    char * fileName = NULL;
    
    //reading in cmdline args
    int count = 0; //counter var for cmdLine arguments
    for(count = 1; count < argc; count++) {
        cmdArg = strdup(argv[count]);
        if(!strcmp(cmdArg, "-s")){ //at -s so read the mode
            count++;
            cmdArg = strdup(argv[count]);
            mode = strtol(cmdArg,NULL, 10);
            if(mode <= 0 || mode > 4) {
                //printf("Did not enter a correct mode. \n");
                return -1;
            } else {
                printScheduler(mode);
                //call function to print correct scheduler info
            }
        } else if (!strcmp(cmdArg, "-q")){ //at -q so read the next number
            count++;
            cmdArg = strdup(argv[count]);
            quantum = strtol(cmdArg, NULL, 10);
        } else { //at what should be the name of the .txt file
            fileName = strdup(cmdArg);
            fd = fopen(cmdArg, "r");
        }
        if(cmdArg != NULL) {
            free(cmdArg);
            cmdArg = NULL;
        }
    }
    //end of reading in cmdline args
    
    printf("Quantum      : %d\n",quantum);
    printf("Sch. File    : %s\n",fileName);
    readData(fd); //read in process information from file
    printf("-------------------------------\n");
    arrivalOrder();
    
    printProcessInfo(); //prints process information segment
    printf("-------------------------------\n");
    sortData(mode, quantum);
    
    free(procPtr);
    free(cmdArg);
}

void setTimes(Proc *ptr) {
    int i = 0;
    Proc *temp = NULL;
    Proc *temp2 = NULL;
    int curProc = 0;
    //make a method
    for(i=0;i < numProcesses; i++) { //calculate  + store waitTimes
        temp = &ptr[i];
        curProc = i+1;
        temp2 = &ptr[curProc];
        while(curProc < numProcesses) {
            temp2 = &ptr[curProc];
            temp2->waitTime = temp2->waitTime+ temp->burst;
            curProc = curProc +1;
        }
        temp->turnAroundTime = temp->waitTime + temp->burst;
        //increment turnAround times
    }
}

void sortData(int mode, int quantum) {
    Proc *temp = NULL;
    
    double totalWait = 0;
    double avgWait = 0;
    double totalTurn = 0;
    double avgTurnAround = 0;
    printf("Running...\n");
    printf("##################################################\n");
    printf("# #  CPU  Pri    W    T\n");
    int i = 0; //loop counter variable
    //setTimes();
    if( mode == 1) { //FCFS
        setTimes(procPtr);
        for(i = 0; i < numProcesses; i++) { //print the  processor information
            temp = &procPtr[i];
            printf("# %-5d  %-5d  %-5d  %-5d  %-5d\n" ,temp->procId, temp->burst,temp->priority,temp->waitTime, temp->turnAroundTime);
            totalWait = totalWait + temp->waitTime;
            totalTurn = totalTurn + temp->turnAroundTime;
        }
        
    } else if (mode == 2) {//SJF
        Proc tempArr[numProcesses]; //new array of processes sorted by bursts
        //tempArr = (Proc *)malloc(sizeof(Proc) * numProcesses);
        int j = 0;
        int arrivalOrder[numProcesses];
        Proc lowest ={0};
        Proc tempp = {0};
        //copy values into temp array
        for(i = 0; i < numProcesses; i++) {
            tempArr[i] = procPtr[i];
            arrivalOrder[i] = tempArr[i].procId;
            //printf("procId of tempArr[%d] is: %d\n",i,tempArr[i].procId);
        }
        //sort the temp array by burst length
        for(i=0; i < numProcesses; i++) {
            lowest = tempArr[i];
            j = 0;
            for(j = i + 1; j < numProcesses; j++) {
                if(tempArr[j].burst < lowest.burst) {
                    tempp = lowest;
                    tempArr[i] = tempArr[j];
                    tempArr[j] = lowest;
                    lowest = tempArr[i];
                }
            }
        }
        setTimes(&tempArr[0]);
        for(i = 0; i < numProcesses; i++) { //print the  processor information
            j = 0;
            while(j < numProcesses) {
                if (arrivalOrder[i] == tempArr[j].procId){
                    temp = &tempArr[j];
                    printf("# %-5d %-5d %-5d %-5d %-5d\n" ,temp->procId, temp->burst,temp->priority,temp->waitTime, temp->turnAroundTime);
                    totalWait = totalWait + temp->waitTime;
                    totalTurn = totalTurn + temp->turnAroundTime;
                }
                j++;
            }
            
        }
    } else if (mode == 3) { //priority
        Proc tempArr[numProcesses]; //new array of processes sorted by bursts
        //tempArr = (Proc *)malloc(sizeof(Proc) * numProcesses);
        int j = 0;
        int arrivalOrder[numProcesses];
        Proc lowest ={0};
        Proc tempp = {0};
        //copy values into temp array
        for(i = 0; i < numProcesses; i++) {
            tempArr[i] = procPtr[i];
            arrivalOrder[i] = tempArr[i].procId;
            //printf("procId of tempArr[%d] is: %d\n",i,tempArr[i].procId);
        }
        //sort the temp array by priority length
        for(i=0; i < numProcesses; i++) {
            lowest = tempArr[i];
            j = 0;
            for(j = i + 1; j < numProcesses; j++) {
                if(tempArr[j].priority < lowest.priority) {
                    tempp = lowest;
                    tempArr[i] = tempArr[j];
                    tempArr[j] = lowest;
                    lowest = tempArr[i];
                }
            }
        }
        setTimes(&tempArr[0]);
        for(i = 0; i < numProcesses; i++) { //print the  processor information
            j = 0;
            while(j < numProcesses) {
                if (arrivalOrder[i] == tempArr[j].procId){
                    temp = &tempArr[j];
                    printf("# %-5d %-5d %-5d %-5d %-5d\n" ,temp->procId, temp->burst,temp->priority,temp->waitTime, temp->turnAroundTime);
                    totalWait = totalWait + temp->waitTime;
                    totalTurn = totalTurn + temp->turnAroundTime;
                }
                j++;
            }
            
        }
    } else if (mode == 4){ //RR
        int arrivalOrder[numProcesses];
        int leftOverQuantum = 0;
        Proc tempArr[numProcesses];
        int tempBursts[numProcesses]; //stores bursts values
        int posB4 = 0;
        int posAfter = 0;
        int tempPos = numProcesses;
        for(i = 0; i < numProcesses; i++) { //copy over processes and original arrival order ID's
            tempArr[i] = procPtr[i];
            arrivalOrder[i] = tempArr[i].procId;
            tempArr[i].turnAroundTime = tempArr[i].burst; //copy over times to save for calculations
            tempBursts[i] = procPtr[i].burst;
            //printf("tempBursts[%d] is: %d\n", i, tempBursts[i]);
        }
        leftOverQuantum = quantum;
        int l = 0;
        for(i=0; i<numProcesses;i++) {
            if(tempArr[i].burst != 0 && tempArr[i].burst >= quantum) {
                //only do one burst
                tempArr[i].burst = tempArr[i].burst - quantum;
                //printf("using full quantum for %d\n", tempArr[i].procId);
                for(l = 0; l< numProcesses; l++) { //increment wait times for processes left
                    if(tempArr[l].burst != 0 && i != l) {
                        //printf("incrementing wait time for: %d\n", tempArr[l].procId);
                        tempArr[l].waitTime = tempArr[l].waitTime + quantum;
                    }
                }
                if( i == numProcesses-1) { //at last process but need to check if all done
                    //printf("WE HERE NOW!");
                    i = -1; //start over and check again
                }
            } else if ( tempArr[i].burst == 0) { //no burst left in this one so keep checking //rest
                //printf("its 0?! bursts for %d is %d\n",tempArr[i].procId, tempArr[i].burst);
                posAfter = numProcesses;
                posB4 = numProcesses;
                tempPos = numProcesses;
                for(l=0; l<numProcesses;l++) {
                    if(tempArr[l].burst != 0 && l > i) { // another process after this to be done
                        //printf("process after %d is %d\n", tempArr[i].procId, tempArr[l].procId);
                        posAfter = l;
                        if(l < tempPos) {
                            tempPos = l;
                        }
                        
                    } else if (tempArr[l].burst != 0 && l <= i && posAfter == numProcesses) {//another process b4 this one
                        //printf("....%d...\n", tempArr[l].procId);
                        if (l < posB4) {
                            posB4 = l;
                        }
                    }
                }
                if(tempPos != numProcesses) { //something left after this position
                    i = tempPos-1;
                    //printf("I has been CHANGED to: %d\n", i);
                } else if (posB4 != numProcesses){ //something left b4 this position
                    i = posB4-1;
                    //printf("I has been changed to: %d\n", i);
                }
                tempPos = numProcesses;
                posB4 = numProcesses;
                posAfter =numProcesses;
            } else { //will not use up all of quantum
                int tempPos = i;
                if(tempArr[i].burst > 0 && tempArr[i].burst < leftOverQuantum) { //will need to check
                    //other processes after this one to use leftOverQuantum
                    //printf("this is happening at %d\n", tempArr[i].procId);
                    leftOverQuantum = quantum - tempArr[i].burst;
                    tempArr[i].burst = 0;
                    for(l=0; l < numProcesses; l++) {//increment other waitTimes if they have yet to be
                        //processed
                        if(tempArr[l].burst != 0) {
                            tempArr[l].waitTime = tempArr[l].waitTime + (quantum - leftOverQuantum);
                            //printf("incrementing for %d with a waitTime of %d\n", tempArr[l].procId, tempArr[l].waitTime);
                        }
                    }
                }//end of if
                if(i == numProcesses-1) {
                    i = -1; //go thru and check one more time
                }
            }
            //may need to put this above while loop
            
            leftOverQuantum = quantum;
        }//end of for loop
        for(i=0; i < numProcesses; i ++) {
            tempArr[i].turnAroundTime = tempArr[i].turnAroundTime + tempArr[i].waitTime;
        }
        int j = 0;
        //setTimes(&tempArr[0]);
        for(i = 0; i < numProcesses; i++) { //print the  processor information
            j = 0;
            while(j < numProcesses) {
                if (arrivalOrder[i] == tempArr[j].procId){
                    temp = &tempArr[j];
                    printf("# %-5d %-5d %-5d %-5d %-5d\n" ,temp->procId, tempBursts[i],temp->priority,temp->waitTime, temp->turnAroundTime);
                    totalWait = totalWait + temp->waitTime;
                    totalTurn = totalTurn + temp->turnAroundTime;
                }
                j++;
            }
            
        }
    } else {
        //should not reach here
        //did not enter in a valid mode so break and exit with -1 status
        //exit(-1);
    }
    
    avgWait = totalWait/numProcesses;
    avgTurnAround = totalTurn/numProcesses;
    printf("##################################################\n");
    //Avg waiting time...
    printf("# Avg. Waiting Time   :  %-2.2f\n", avgWait);
    //AVG turnaround time....
    printf("# Avg. Turnaround Time:  %2.2f\n", avgTurnAround);
    printf("##################################################\n");
}

void readData(FILE *fd) {
    char *line = NULL;
    int lineCount = 0;
    char *cmdArg = NULL;
    char* fgetsRtn = NULL;
    int tempNum = 0;
    
    if(fd != NULL){ //file was found and can start reading
        line = (char*)(malloc(sizeof(char) * 256));
        
        while(0 == feof(fd)) { //reading in file line by line
            fgetsRtn = fgets(line, 256, fd); //256 = number of possible chars per line
            if(fgetsRtn == NULL){ //end of file
                break;
            }
            if(lineCount == 0 ) { //read in first line of file
                //fgetsRtn = fgets(line, 256, fd); //repeat?
                //do check of line to make sure it is a number
                numProcesses = strtol(line, NULL, 10); //reading in number of processes
                procPtr = (Proc *)malloc(sizeof(Proc) * numProcesses);
                Proc *np = NULL; //newProcess
                int j = 0;
                //initialize processes
                for(j=0;j<numProcesses; j++) {
                    np = &procPtr[j];
                    np->procId = 0;
                    np->burst = 0;
                    np->priority = 0;
                    np->waitTime = 0;
                    np->turnAroundTime = 0;
                }
                if (fgetsRtn == NULL || numProcesses <= 0) { //error checking file
                    break; //exit(1);
                }
                
                
            } else { //reading in a process => proc identifier, cpu burst & priority #'s
                int i = 0;
                tempNum = 0;
                cmdArg = strtok(line, " "); //parses line and grabs first number as string
                Proc *newProc = &procPtr[lineCount-1]; //initialize the new process to null;
                while(cmdArg != NULL) { //seperating the info in each line
                    
                    tempNum = strtol(cmdArg, NULL, 10); //convert first number to integer and store in tempNum
                    if(i == 0) { //reading in 3 numbers, this is the first = procId number
                        newProc->procId = tempNum;
                    } else if (i == 1) { //second number == burst
                        newProc->burst = tempNum;
                    } else if (i == 2) { //third number = priority
                        newProc->priority = tempNum;
                    }
                    i++;
                    cmdArg = strtok(NULL, " "); //parse & grab next thing in line
                }//end of while
                i = 0;
                debugProc(newProc);
                tempNum =0;
            }//end of else clause
            
            lineCount++;
            // free(line);
        } //end of reading file
    } else {
        printf("File was not found. \n");
        //return -1;
        exit(-1);
        //print error message and exit w/ negative status
    }
    //free(line); //added
}

void printScheduler(int x) { //DONE
    //printf("made it again\n");
    char phrase[27] = "Scheduler    : ";
    //printf("%s\n", phrase);
    if(x == 1) { //first come first served
        strcat(phrase, "1 FCFS");
    } else if (x == 2) { // shortest job first
        strcat(phrase, "2 SJF");
    } else if (x == 3) { // priority
        strcat(phrase, "3 Priority");
    } else { //mode == 4 == round robin
        strcat(phrase, "4 RR");
    }
    printf("%s \n", phrase);
}

void debugProc(Proc *p) {
    int i = 0;
    //printf("single process info: %d, %d, %d\n",p->procId, p->burst, p->priority);
}

void arrivalOrder(){ //DONE
    int i = 0;
    printf("Arrival Order: ");
    Proc *temp = NULL;
    for(i = 0; i < numProcesses; i++) {
        temp = &procPtr[i];
        if( i < numProcesses-1) {
            printf("%d, ", temp->procId);
        } else {
            printf("%d\n", temp->procId);
        }
    }
}

void printProcessInfo() { //prints out the process information segment -- DONE
    printf("Process Information: \n");
    int i = 0;
    Proc *temp = NULL;
    for(i = 0; i < numProcesses; i++){
        temp = &procPtr[i];
        printf("%-5d\%-5d\%-5d\n" , temp->procId, temp->burst, temp->priority);
    }
}

