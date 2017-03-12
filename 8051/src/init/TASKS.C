/**
* David Monahan
* 19/02/2017
* Embedded System Assignment 02
* Program to demonstrate the task and semaphore functionality of the uC/OS 2 
* This program creates 4 tasks, the first 3 are all pended on semaphores posted
* by the fourth task. The fourth task is watching pins 0, 1 and 2 on Port 1 and
* posting to semaphores based on what it sees. The pins are constantly being 
* changed by a loop in the init task.
**/

#include "includes.h"

/* CONSTANTS */    
#define  TASK_STK_SIZE  64
#define  N_TASKS        4

/* Structures */
// Structure to hold the required data for the first 3 tasks
typedef struct TASK_PARAM {
	char ID;  // Task id
	INT8U wait;	 // timeout/delay	
	OS_EVENT* Sem; // Semaphore to use
	INT8U err;
} taskParam;

// Structure to hold the semaphores being passed to the fourth task
typedef struct TASK_SEMS {
	OS_EVENT* sem1;
	OS_EVENT* sem2;
	OS_EVENT* sem3;
} taskSems;

/* VARIABLES */

static INT8U p0, p1, p2; // variables to hold past data on pins
static INT8U i = 0; // flag variable
OS_STK InitTaskStk[TASK_STK_SIZE];	 
OS_STK TaskStk[N_TASKS][TASK_STK_SIZE];

static taskParam t1, t2, t3; // Declare strcutures
static taskSems sems;


/* FUNCTION PROTOTYPES */
void   InitTask(void *args) KCREENTRANT;
void   Task1(void *args) KCREENTRANT;
void   Task2(void *args) KCREENTRANT;
void   Task3(void *args) KCREENTRANT;

// Map port pins												  
sbit P1_0  = P1^0;
sbit P1_1  = P1^1;
sbit P1_2  = P1^2;
sbit P1_3  = P1^3;

/*
 * MAIN
 */


void main (void) {  
  OSInit();
 
	// Setup the structures for each task
	t1.ID = '1';
	t1.wait = 0;
	t1.Sem = OSSemCreate(0);  

	t2.ID = '2';
	t2.wait = 0;
	t2.Sem = OSSemCreate(0);

	t3.ID = '3';
	t3.wait = 50;
	t3.Sem = OSSemCreate(0);

	sems.sem1 = t1.Sem;
	sems.sem2 = t2.Sem;
	sems.sem3 = t3.Sem;

// init task
OSTaskCreate(InitTask, (void *)0, (void *)&InitTaskStk[TASK_STK_SIZE - 1], 0);
// start
  OSStart();
}

/*
 * STARTUP TASK
 */
void InitTask (void *args) KCREENTRANT
{
  args = args;

  /* init the system */
  initSystem();
  // function to allow writing to the serial port
    SetupComms();

// Create tasks, pass them the addresses to their data structures, specify stacks and priorities
  OSTaskCreate(Task1, (void *) &t1, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 1);
  OSTaskCreate(Task1, (void *) &t2, (void *)&TaskStk[1][TASK_STK_SIZE - 1], 2);
  OSTaskCreate(Task1, (void *) &t3, (void *)&TaskStk[2][TASK_STK_SIZE - 1], 3);
  OSTaskCreate(Task2, (void *) &sems, (void *)&TaskStk[3][TASK_STK_SIZE - 1], 4);

// While loop to switch the port pins in a regular sequence with a delay between each one so we can see the response
  while(1)
  {
    OSCtxSwCtr = 0;
    OSTimeDlyHMSM(0,0,2,0);
	P1_0 = ~P1_0;
	OSTimeDlyHMSM(0,0,2,0);
	P1_1 = ~P1_1;
	OSTimeDlyHMSM(0,0,2,0);
	P1_2 = ~P1_2;
  }
}

/*
 * TASKS
 */
void Task1(void *args) KCREENTRANT
{
// structure pointer pointed at the passed address
  struct TASK_PARAM* tStruct = args;

  while(1)
  {
  // Pend on the passed semaphore	
   OSSemPend (tStruct->Sem, tStruct->wait, &tStruct->err);   
   
   // Switch statement to allow the task to execute the correct response for it's task data
   switch(tStruct->ID) {
   case '1' :
   case '2' : 
	if(tStruct->err == OS_NO_ERR) {
		SendChar(tStruct->ID);
	}
	break;
	case '3':
	if(tStruct->err == OS_NO_ERR){
		SendChar(tStruct->ID);
	} else if (tStruct->err == OS_TIMEOUT) { // Check for Timeout
		  SendChar('T'); 
		}
	break;
	}	 
    OSTimeDly(100); // Small delay to prevent higher priority tasks blocking out all other tasks                          
  }
}

void Task2(void *args) KCREENTRANT
{
// Structure pointer
  struct TASK_SEMS* semaphores = args;
	// Map current pin values to variables
  	p0 = P1_0;
	p1 = P1_1;
	p2 = P1_2;
  while(1)
  {
  // Check for each specified condition and post to the correct semaphore
  	 if(p0 == 0 && P1_0 == 1) {
	 	OSSemPost(semaphores->sem1);
	 }
	 if (p1 == 1 && P1_1 == 0) {
	 	OSSemPost(semaphores->sem2);
	 }
	 // Check for low -> high -> low transition using 2 if statements to avoid blocking
	 if (P1_2 == 0 && i == 1) {
	 	OSSemPost(semaphores->sem3);
		i = 0;
	 }
	 if (p2 == 0 && P1_2 == 1) {
	 	i = 1;
	 }
	 // update history variables
	p0 = P1_0;
	p1 = P1_1;
	p2 = P1_2;
	 OSTimeDly(100);
  }
}