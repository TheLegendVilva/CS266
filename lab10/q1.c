#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int main(){
    //Random generation og address
    int n=1;
    srand(time(NULL));
    for(n=0; n<4; n++){
        printf("%04d\n", rand()%10000);
    }
    return 0;
}