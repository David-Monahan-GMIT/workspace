#include <stdio.h>
#include <stdlib.h>
struct person {
   int age;
   float weight;
   char name[30];
};

int main()
{
   struct person *personPtr, *ptr;
   int i, num;

   printf("Enter number of persons: ");
   scanf("%d", &num);

   personPtr = (struct person*) malloc(num * sizeof(struct person));
   // Above statement allocates the memory for n structures with pointer personPtr pointing to base address */
   ptr = personPtr;
   for(i = 0; i < num; ++i,ptr++)
   {
       printf("Enter name, age and weight of the person respectively:\n");
       scanf("%s%d%f", &ptr->name, &ptr->age, &ptr->weight);
   }

   printf("Displaying Infromation:\n");
   for(i = 0; i < num; ++i)
       printf("%s\t%d\t%.2f\n", (ptr+i)->name, (ptr+i)->age, (ptr+i)->weight);

   return 0;
}



