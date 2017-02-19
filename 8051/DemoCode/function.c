
void function1(void);
void function2(int);
void function3(int,int);
int function4(int,int,int);




int main(void)
{
int i=0,j=1,k=2,l=3;

function1();
function2(j);
function3(j,k);
i=function4(j,k,l);
}

void function1(void){}

void function2(int a){
int x;
x=a;
}

void function3(int a, int b){
int x, y;
x=a;
y=b;
}

int function4(int a, int b, int c){
int x,y,z;
x=a;
y=b;
z=c;
return (x+y+z);
}
