#include "includes.h"

/* CONSTANTS */    
#define  TASK_STK_SIZE  32

/* VARIABLES */
OS_STK InitTaskStk[TASK_STK_SIZE];

/* FUNCTION PROTOTYPES */
void   InitTask(void *args) KCREENTRANT;
sbit P1_0  = P1^0;

/*
 * MAIN
 */
void main (void)
{
  OSInit();

  OSTaskCreate(InitTask, (void *)0, (void *)&InitTaskStk[TASK_STK_SIZE - 1], 0);

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
  
  while(1)
  {
    OSCtxSwCtr = 0;
    P1_0 = ~P1_0;
    OSTimeDlyHMSM(0,0,1,0);
  }
}
