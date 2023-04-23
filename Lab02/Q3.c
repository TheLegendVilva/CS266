#include<stdio.h>

int main(){
    FILE *fp;
    fp = fopen("q3f1.txt","a+");
    int n = 128;
    char c = fgetc(fp);
    
    while(c!=EOF){
        printf("%c,%d.",c,128+c-65);
        c = fgetc(fp);
    }
}