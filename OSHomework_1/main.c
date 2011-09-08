//
//  main.c
//  OSHomework_1
//
//  Created by Kurry Tran on 9/8/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#define N 2
#define MAX 25 /* maximum number of letter communicated */
#define BUFFER_SIZE 2048
#define NEW_DIRECTORY     "testdir"
#define TEST_FILE         "test.file"
#define TEST_DATA         "Hello World!"
#define USER_ID           "user_id_"
#define PARENT_DIRECTORY  ".."

char  InitialFile[BUFFER_SIZE];
char  LinkName[BUFFER_SIZE];
char  InitialDirectory[BUFFER_SIZE] = ".";
char  Buffer[32];
int   FilDes = -1;
int   BytesRead;
int   BytesWritten;
uid_t UserID;



/*
 http://publib.boulder.ibm.com/infocenter/iseries/v5r3/index.jsp?topic=%2Fifs%2Frzaaxcfunctionexample.htm
 Example: Integrated file system C functions
 Source: IBM Example System Calls 

 */


void CleanUpOnError(int level)
{
    printf("Error encountered, cleaning up.\n");
    switch ( level )
    {
        case 1:
            printf("Could not get current working directory.\n");
            break;
        case 2:
            printf("Could not create file %s.\n",TEST_FILE);
            break;
        case 3:
            printf("Could not write to file %s.\n",TEST_FILE);
            close(FilDes);
            unlink(TEST_FILE);
            break;
        case 4:
            printf("Could not close file %s.\n",TEST_FILE);
            close(FilDes);
            unlink(TEST_FILE);
            break;
        case 5:
            printf("Could not make directory %s.\n",NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 6:
            printf("Could not change to directory %s.\n",NEW_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 7:
            printf("Could not create link %s to %s.\n",LinkName,InitialFile);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 8:
            printf("Could not open link %s.\n",LinkName);
            unlink(LinkName);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 9:
            printf("Could not read link %s.\n",LinkName);
            close(FilDes);
            unlink(LinkName);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 10:
            printf("Could not close link %s.\n",LinkName);
            close(FilDes);
            unlink(LinkName);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 11:
            printf("Could not unlink link %s.\n",LinkName);
            unlink(LinkName);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 12:
            printf("Could not change to directory %s.\n",PARENT_DIRECTORY);
            chdir(PARENT_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 13:
            printf("Could not remove directory %s.\n",NEW_DIRECTORY);
            rmdir(NEW_DIRECTORY);
            unlink(TEST_FILE);
            break;
        case 14:
            printf("Could not unlink file %s.\n",TEST_FILE);
            unlink(TEST_FILE);
            break;
        default:
            break;
    }
    printf("Program ended with Error.\n"\
           "All test files and directories may not have been removed.\n");
}









int main (int argc, const char * argv[])
{
   // char line[MAX]; /* character array (string) for reading */ 
   // int numbers[N];
   // int i;
    
    
    pid_t pid; /* variable to record process id of child */
    
    pid = fork(); /* create a new process  */
    
    /* Check for error in spawning child process */
    
    if (-1 == pid) 
    {
        perror("error in fork");
        exit(1);
    }
    
    /* check if this is the new child process */
    
    if (0 == pid) 
    { /* processing for child */
        printf("This output comes from the child process\n");
        printf("Parent report: my pid = %d\n", getpid());
       
    }
    else {
        /* processing for parent */
        
        printf("This output comes from the parent process.\n");
        printf("Parent report: my pid = %d child's pid = %d\n", getpid(), pid);
    }
    

    
    /**********************************
     // reading user input
     
     #define N 10
     
     int numbers[N];
     int i 
     
     for (i = 0; i < N; i++){
     
        scanf("%d", &numbers[i]);
     }
     
     
     
     ************************************/
    
    
    /*
    SYSTEM CALL HANDLER
     
     It is not possible for user-space applications to exectute
     kernel code directly. They cannot simple make a function call
     to a method existing in kernel-space because the kernel exists
     in protected memory space. 
    
    
     Instead, user-space applications must somehow signal to the kernel that 
     they want to execute a system call and have the system switch to kernel
     mode, where the system call can be executed in kernel-space by the
     kernel on behalf of the application.
    
    
     The mechanism to signal the kernel is a software interrupt: Incur 
     an exception, and the system will switch to kernel mode and 
     execute the exception handler.The exception handler, 
     in this case, is actually the system call handler.
    
    
    
    
    
    
    
    
    
    
    
    
    */
    
    /*
    
    
    In Linux, each system call is assigned a syscall number. This is
     a unique number to reference a specific system call. When a
     user-space process exectues a system call, the syscall number
     identifies which syscall was executed; the process dos not refer
     to the syscall by name. 
    
    
    - Syscall numbers are important; when the system call is assigned,
     it cannot be changed. 
     
      Linux provides a “not implemented” system call, sys_ni_syscall(),
     which does nothing except return -ENOSYS, 
     the error corresponding to an invalid system call.
    
     This function is used to “plug the hole” in the rare event that
     a syscall is removed or otherwise made unavailable.
    
     The kernel keeps a list of all registered system calls in the 
     system call table, stored in the sys_call_table. 
    
     This table is architecture; on x86-64 it is defined 
     in arch/i386/kernel/syscall_64.c.
    
    
    */
    
    
    
    
    /*****************
    char line[BUFFER_LENGTH];
    char *p;
    
     p = fgets(line, BUFFER_LENGTH,stdin);
     
     for (i = 0; i < BUFFER_LENGTH; i++){
     
     if(isspace(line[i])){
     printf("Index of whitespace:%d",i);
     }
    
     -exec command {} \; run the Unix command on each file matched by find. Very useful condition.

    
    *****************/
    
    /*
     EXEC COMMAND
     
     exec - Invoke subprocesses
     
     This command treates its arguments as the specification of one or more subprocesses 
     to execute. The arguments take the form of a standard shell pipeline where each arg
     becomes one word of a command, and each distinct command becomes a subprocess.
     
     
     If the initial arguments to exec start with - then they are treated command-line 
     switches and are not part of the pipeline specification.
     
     
    
     
     
     */
    
    
    
    
    /***********************************
     
     Interprocess communication in Unix may be accomplished 
     at a low level by using pipes. A Unix pipe is a circular
     buffer maintained by the operating system. Typically,
     one or more processes write data into the buffer; another 
     process reads the data from the pipe.
     
     While Unix handles the internals of pipe communication, programs 
     communicates through pipes at a slightly more conceptual level. 
     More specifically, the use of pipes involves four main steps
     
     Note: Continue notes later in section. 
     
     
     
     
     
     
     
     
     **********************************/
    
    

    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

