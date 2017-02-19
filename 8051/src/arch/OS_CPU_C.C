/********************************************************************************************************

********************************************************************************************************/

#define  OS_CPU_GLOBALS
#include "includes.h"

#undef data
#undef pdata
#undef xdata
#undef idata


/* Local variable definitions */
OS_EXT OS_TCB *OSTCBHighRdy;
data INT8U RxBuffer = 0;
INT8U data SaveSP;

/* External variable definitions */
extern idata INT8U Stack[1];
extern INT8U xdata * data C_XBP;

/* Local function definitions */
void LoadCtx() KCREENTRANT;


/********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable 
*              interrupts.  Failure to do this will make your system crash!
**********************************************************************************************************/
OS_STK *OSTaskStkInit (void (*task)(void *pd) KCREENTRANT, void *ptd, OS_STK *ptos, INT16U opt) KCREENTRANT
{
  INT8U *stk;

  /* 'opt' is not used, prevent warning */
  opt = opt;
  
  /* Get pointer to the top of the stack */                       
  stk = (INT8U *)(ptos);                

  /* Save the ptd to external stack */
  stk -= sizeof(void *);    
  *(void**)stk = ptd;

  /* The value should be loaded to PC next time when this task is running*/
  stk -= sizeof(INT16U);
  *(INT16U*)(stk) = (INT16U)(task);

    /* The value should be loaded to PC next time when this task is running*/
  stk -= sizeof(INT16U);
  *(INT16U*)(stk) = (INT16U)(task);

  /* Following is the registers pushed into hardware stack */
  *--stk = 'A';                 /* ACC */
  *--stk = 'B';                 /* B   */
  *--stk = 'H';                 /* DPH */
  *--stk = 'L';                 /* DPL */
  *--stk = PSW;                 /* PSW */
  *--stk = 0;                   /* R0  */

  stk -= sizeof(void *);        /* R1,R2,R3 */
  *(void**)stk = ptd;            /* functions args */       

  *--stk = 0x04;                /* R4  */
  *--stk = 0x05;                /* R5  */
  *--stk = 0x06;                /* R6  */
  *--stk = 0x07;                /* R7  */
  *--stk = 0x80;                /* IE, EA is enabled  */

  /* Next is calculating the hardware stack pointer */
  *--stk = (INT8U)(Stack-1) + 14 + sizeof(INT16U) + sizeof(INT16U);

  /* Return the top-of-stack address */
  return ((void *)stk);
}


/*
***********************************************************************************************************
* OSStartHighRdy: START MULTITASKING
*     
* Duty:     a) Call OSTaskSwHook() then,
*           b) Set OSRunning to TRUE,
*           c) Switch to the highest priority task.
*
***********************************************************************************************************
*/
void OSStartHighRdy(void) KCREENTRANT
{
  OSTaskSwHook();
  
  OSRunning = 1;

  C_XBP = OSTCBHighRdy->OSTCBStkPtr;

  LoadCtx();
}

/**********************************************************************************************************
* C_OSCtxSw is the c part of OSCtxSw.
* When control passes to this function, the processor registers have been saved in external stack
***********************************************************************************************************/
void C_OSCtxSw(void) KCREENTRANT
{
  OSTCBCur -> OSTCBStkPtr = C_XBP;
  OSTaskSwHook();
  OSTCBCur = OSTCBHighRdy;
  OSPrioCur = OSPrioHighRdy;
  C_XBP = OSTCBCur -> OSTCBStkPtr;
  LoadCtx();
}

/**********************************************************************************************************
* void OSIntCtxSw(void)
* 
***********************************************************************************************************/
void OSIntCtxSw(void) KCREENTRANT
{
#pragma ASM
        CLR EA
        MOV SP, SaveSP
#pragma ENDASM

  C_XBP = OSTCBCur->OSTCBStkPtr;

#pragma ASM
        EXTRN   CODE(_?KCOSCtxSw)
        MOV   A, #LOW  _?KCOSCtxSw
        PUSH  ACC
        MOV   A, #HIGH _?KCOSCtxSw
        PUSH  ACC
        RETI
#pragma ENDASM
}

/**********************************************************************************************************
* void OSTickISR(void)
* 
**********************************************************************************************************/
void OSTickISR(void) interrupt 1
{
  /* Must be called first at every hardware interrupt entry point */
  OSIntEnter();
    
  if(OSIntNesting == 1)
  {
    #pragma ASM
            PUSH IE
            CLR  EA
            MOV  SaveSP, SP
    #pragma ENDASM

    EA = 0;

    OSTCBCur->OSTCBStkPtr = C_XBP;
  }

  /* Must be called during tick isr */
  OSTimeTick();
  
  /* Must be called finally at every hardware interupt exit point */     
  OSIntExit();

  if(OSIntNesting==0)
  {
    EA = 0;

    C_XBP =OSTCBCur->OSTCBStkPtr;

    #pragma ASM
            MOV  SP, SaveSP
            POP  IE
    #pragma ENDASM
  }
}

/**********************************************************************************************************
* SetupComms(void)
* 
**********************************************************************************************************/
void initSystem(void) KCREENTRANT
{
  /* Setup Timer */
	TMOD = (TMOD & 0xF0) | 0x21;
  
  /* Freq=25Hz (Ticks per second) */
	TL0  = 0xF0;	
	TH0  = 0xF0;
	TR0  = 1;
	ET0  = 1;
	EA   = 1;
}

/**********************************************************************************************************
* SetupComms(void)
* 
**********************************************************************************************************/
void SetupComms(void) KCREENTRANT
{
  /* Set for 8,No parity,19200 baud */
  SCON  = 0x50;

  /* T1 as baud generator TH1=253=FD=9600  */
  TH1   = 0xFD;

  /* Double the baud rate approx. 19200 */
  PCON |= 0x80;

  /* Enable the serial interrupt */ 
  ES    = 1;

  /* Start running the timer */     
  TR1   = 1;
}

/**********************************************************************************************************
* void SendChar()
* 
**********************************************************************************************************/
void SendChar(unsigned char c) KCREENTRANT
{
//  TI = 1;
  int i;
  SBUF = c;
  for(i = 0; i < 30; i++);
}
/**********************************************************************************************************
* void SendChar()
* New function to send a string of text 
*
**********************************************************************************************************/
void SendString(char *s) KCREENTRANT {

INT8U i;
   while(*s != '\0') {
      SendChar(*s++);
      for(i = 0; i < 30; i++);
      }
}

/**********************************************************************************************************
* void Serial_ISR(void)
* Sample user ISR: Serial communication
**********************************************************************************************************/
void Serial_ISR(void) interrupt 4
{
  /* Do this first */
  /* Must be called first at every hardware interrupt entry point */
  OSIntEnter();

  /* Only at the outerest interrupt we do these. */
  if(OSIntNesting == 1)
  {
    #pragma ASM
            PUSH IE
            CLR  EA
            MOV  SaveSP, SP
    #pragma ENDASM

    EA = 0;

    OSTCBCur->OSTCBStkPtr = C_XBP;  
  }


  /* Deal with the type of Serial Interrupt */
  if(TI)
  {
    TI = 0;
  }
  else if(RI)
  {
    RI = 0;
    RxBuffer = SBUF;
  }


  /* Finally, before exit from ISR, must do as following. */
  /* Must be called finally at every hardware interupt exit point */
  OSIntExit();
  
  if(OSIntNesting == 0)
  {
    EA = 0;

    C_XBP = OSTCBCur->OSTCBStkPtr;

    #pragma ASM
            MOV  SP, SaveSP
            POP  IE
    #pragma ENDASM

  }
}


/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void) KCREENTRANT
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void) KCREENTRANT
{
}
#endif


/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb) KCREENTRANT
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb) KCREENTRANT
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void) KCREENTRANT
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void) KCREENTRANT
{
}

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb) KCREENTRANT
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void) KCREENTRANT
{
}


/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void) KCREENTRANT
{
}
#endif

#endif
