#include "includes.h"

/* Turn a Port 1 OFF */
void main (void)
{
  OSInit();
  P1 = 0x00;
  OSStart();
}
