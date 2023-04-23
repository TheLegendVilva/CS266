#include<stdio.h>

int main(){
    FILE *fp;
    fp = fopen("myFile.txt","r");
    int i=1;
    printf("%d ",i);
    char ch=fgetc(fp);
    while(ch!=EOF){
        if(ch == '\n'){
            printf("\n");
            i++;
            ch=fgetc(fp);
            if(ch==EOF){
                break;
            }
            printf("%d ",i);
            
        }
        printf("%c",ch);
        ch = fgetc(fp);
    }
    return 0;
}