#include    <reg52.h>
#include "os_cpu.h"

void function1(void) KCREENTRANT;
void function2(int) KCREENTRANT;
void function3(int,int) KCREENTRANT;
int function4(int,int,int) KCREENTRANT;




int main(void)
{
int i=0,j=1,k=2,l=3;

function1();
function2(j);
function3(j,k);
i=function4(j,k,l);
}

void function1() KCREENTRANT{}

void function2(int a) KCREENTRANT{
int x;
x=a;
}

void function3(int a, int b) KCREENTRANT{
int x, y;
x=a;
y=b;
}

int function4(int a, int b, int c) KCREENTRANT{
int x,y,z;
x=a;
y=b;
z=c;
return (x+y+z);
}
