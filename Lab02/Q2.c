#include<stdio.h>

int main(){
    FILE *f1,*f2;
    //Adding the content of f1 to f2 at the end;
    f1 = fopen("text1.txt","r");
    f2 = fopen("text2.txt","a");
    char ch = fgetc(f1);
    while(ch != EOF){
        fprintf(f2,"%c",ch);
        ch = fgetc(f1);
    }
    return 0;
}