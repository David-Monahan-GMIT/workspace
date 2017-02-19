/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                         (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*                                       80x86/80x88 Specific code
*                                          LARGE MEMORY MODEL
*
*                                          Borland C/C++ V4.51
*
* File         : OS_CPU.H
* By           : Jean J. Labrosse
*********************************************************************************************************
*/

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned char  OS_STK;                   /* Each stack entry is 16-bit wide                    */
typedef unsigned int  OS_CPU_SR;                /* Define size of CPU status register (PSW = 16 bits) */

#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
#define UBYTE          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD           INT16S                    /* ... uC/OS-II.                                      */
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U

/* 
*********************************************************************************************************
*                              Intel 80x86 (Real-Mode, Large Model)
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if 
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to 
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    1

#if      OS_CRITICAL_METHOD == 1
#define  OS_ENTER_CRITICAL()  EA=0                    /* Disable interrupts                        */
#define  OS_EXIT_CRITICAL()   EA=1                    /* Enable  interrupts                        */
#endif

#if      OS_CRITICAL_METHOD == 2
/*
 * As an undocumented keyword of keil c. __asm is supported in Keil C v6.20.
 * No other means to define assemble language code in a macro, I have to use it here.
 * If your compiler does not support __asm, use method 1 or 3 then.
 *
 *    A2 AF MOV C, EA
 *    C2 AF CLR EA   
 *    C0 D0 PUSH PSW
 */
#define  OS_ENTER_CRITICAL()    __asm DB 0A2H, 0AFH, 0C2H, 0AFH, 0C0H, 0D0H

/* 
 * D0 D0 POP PSW   
 * 92 AF MOV EA, C
 */
#define  OS_EXIT_CRITICAL()     __asm DB 0D0H, 0D0H, 092H, 0AFH
#endif

/*
*********************************************************************************************************
*                           Intel 80x86 (Real-Mode, Large Model) Miscellaneous
*********************************************************************************************************
*/
#define  OS_STK_GROWTH        1   /* Stack grows from HIGH to LOW memory on 8051 */
#define  uCOS                 1   /* Interrupt vector # used for context switch    */
#define  OS_TASK_SW()         OSCtxSw()

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
 * These macros are intended to be used to re-declare the uC/OS-II functions to be reentrant
 */
#define TASK_REENTRANT  large reentrant
#define KCREENTRANT     large reentrant

#ifdef __x86__
  /*
    - gets segment of far pointer fptr
    - returns unsigned integer value
  */
  #define FP_SEG(fptr) ((unsigned)((unsigned long)(fptr) >> 16))
  
  /*
    - gets offset of far pointer fptr
    - returns unsigned integer value
  */
  #define FP_OFF(fptr)	((unsigned)(fptr))
#endif

/*
 * Define this to avoid name conflicts with ucos
 */
#define data	ucos51_data
#define pdata	ucos51_pdata
#define xdata	ucos51_xdata
#define idata	ucos51_idata
/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/
