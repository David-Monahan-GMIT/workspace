/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                           All Rights Reserved
*
*                                                 V2.00
*
*                                              
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Example file . 
* By:   Junmin Zheng(zhengjunm@263.net) .
* You can run the file and see executing in "Serial #1 window" 
* of dScope51 which has integrated to Keil C51 V6.20
* 
*********************************************************************************************************
*/

#include "includes.h"

#ifdef MONITOR51                         /* Debugging with Monitor-51 needs   */
char code reserve [3] _at_ 0x23;         /* space for serial interrupt if     */
#endif                                   /* Stop Exection with Serial Intr.   */
                                         /* is enabled                        */
/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASKSTART_STK_SIZE            128      
#define  TASK_STK_SIZE                  64       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                       4      /* Number of identical tasks                          */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK           TaskStk[N_TASKS][TASK_STK_SIZE];     /* Tasks stacks                                  */
OS_STK           TaskStartStk[TASKSTART_STK_SIZE];
char             TaskData[N_TASKS];                   /* Parameters to pass to each task               */
OS_EVENT         *MySem;
OS_EVENT         *AckMbox;
OS_EVENT         *TxMbox;
INT8U            err;
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern void EnablePrintf(unsigned char Crystal,unsigned int BaudRate );
extern void TimerInitiate(unsigned char Crystal,unsigned char Frequence);
void   TaskStart(void *dataa) KCREENTRANT;  /* Function prototypes of Startup task           */
void   Tasksecond(void *dataa) KCREENTRANT;      /* Function prototypes of tasks                  */
void   Taskthird(void *dataa) KCREENTRANT;    
/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/
float a=1024;
int *first=10;
int *second=20;
int *third=30; 
void main (void) 
{
   IE=0;
   OSInit();   /* Initialize uC/OS-II*/
   EnablePrintf(12,1200);      
     		    
   printf ("This is the test programme\n"); 
   printf ("The port to 8051 made by Junmin Zheng \n");  
   printf ("\n");
   MySem   =OSSemCreate(1);
   AckMbox =OSMboxCreate((void *)0);
   TxMbox  =OSMboxCreate((void *)0);
   OSTaskCreate(TaskStart, (void *)first, (void *)&TaskStartStk[TASKSTART_STK_SIZE], 0);
   OSTaskCreate(Tasksecond, (void *)second, (void *)&TaskStk[0][TASK_STK_SIZE], 1);
   OSTaskCreate(Taskthird, (void *)third, (void *)&TaskStk[1][TASK_STK_SIZE], 2);
   OSStart(); /* Start multitasking    */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/

void TaskStart (void *dataa) KCREENTRANT
{  
    int *t=0,f=0;
    TimerInitiate(12,OS_TICKS_PER_SEC);   
	t=(int *)dataa;
	f=t;
     /* Prevent compiler warning  */

for(;;)
{         a=a/2;
          OSSemPend(MySem,0,&err);
          printf("this is the first task function\n");
          printf("f=%d  ",f); 
          printf("a=%f\n",a);
		  printf ("\n");
		  OSSemPost(MySem);
          //OSTimeDlyHMSM(0, 0, 10, 0);                         
          OSTimeDly(30);
    }
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void Tasksecond (void * pvdata) KCREENTRANT
{   
  char txmsg=0;/*must be initiated at the first place,if you don't do that,you will crash*/
  pvdata=pvdata;
  txmsg='A';
    for (;;) {

		while(txmsg<='Z'){
		  OSMboxPost(TxMbox,(void *)&txmsg);
            
		    OSSemPend(MySem,0,&err);
			printf("this is the second task function\n");
	        printf("the second task send message %c to the third task\n",txmsg);
		    printf("\n");
            OSSemPost(MySem);

		  OSMboxPend(AckMbox,0,&err);
		  txmsg++;
		}
		  txmsg='A';
		 // OSTimeDly(0);                            
          
   } 
   
}


void Taskthird(void * pvdata) KCREENTRANT
{
    char *rxmsg=0;
	int b=0;
	pvdata=pvdata;
    for (;;) {
	        b=b+1;  
	        rxmsg=(char*)OSMboxPend(TxMbox,0,&err);

            OSSemPend(MySem,0,&err);
			printf("this is the third task function\n");
            printf("a=%f  ",a);
            printf("b=%d\n",b);
			printf("the third task receive message %c from the second task\n",*rxmsg);            
			printf ("\n");
		    OSSemPost(MySem);
  	        
			
			OSMboxPost(AckMbox,(void *)1);
	        
            //OSTimeDlyHMSM(0, 0, 1, 0);
			//OSTimeDly(200);                            /* Delay 2 clock tick */
             
	}
}

