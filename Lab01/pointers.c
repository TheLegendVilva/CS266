#include<stdio.h>

int main(){
    int a = 12;
    int *p = &a;
    printf("The address of variable a is: %p\n",p);
    printf("The value at address %p is %d",p,*p);
}