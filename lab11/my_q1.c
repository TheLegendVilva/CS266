Name Varun Vilvadrinath
Roll No. 202151195

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define MEMORY_SIZE 256
#define BLOCK_SIZE 16

int memory[MEMORY_SIZE/BLOCK_SIZE];
int occ[MEMORY_SIZE/BLOCK_SIZE];//if occupied 1 else 0


bool check(int *arr,int start,int size){
    int num=size/BLOCK_SIZE;
    for(int i=0;i<num;i++){
        if(arr[start+i] != 0){
            return false;
        }
    }
    return true;
}

void allocate(int size,int *mem256,int *mem128,int *mem64,int *mem32,int *mem16) {
    if (size > MEMORY_SIZE) {
        printf("Invalid\n");
        return;
    }
    
    if(size==16){
        int flag = 0;
        for(int i=0;i<sizeof(mem16)/sizeof(int);i++){
            if(occ[mem16[i]]==0){
                flag=1;
                for(int x=0;x<16/BLOCK_SIZE;x++)
                    occ[mem16[i]+x]=1;
                return;
            }
        }
        if(!flag){
            printf("No space for this process of size %d...\n",size);
        }
        return;
    }
    else if(size==32){
        int flag = 0;
        for(int i=0;i<sizeof(mem32)/sizeof(int);i++){
            if(check(occ,mem32[i],32)){
                flag=1;
                for(int x=0;x<32/BLOCK_SIZE;x++)
                    occ[mem32[i]+x]=1;
                return;
            }
        }
        if(!flag){
            printf("No space for this process of size %d...\n",size);
        }
        return;
    }
    else if(size==64){
        int flag = 0;
        for(int i=0;i<sizeof(mem64)/sizeof(int);i++){
            flag=1;
            if(check(occ,mem64[i],64)){
                for(int x=0;x<64/BLOCK_SIZE;x++)
                    occ[mem64[i]+x]=1;
                return;
            }
        }
        if(!flag){
            printf("No space for this process of size %d...\n",size);
        }return;
    }
    else if(size==128){
        int flag = 0;
        for(int i=0;i<sizeof(mem128)/sizeof(int);i++){
            if(check(occ,mem128[i],128)){
                for(int x=0;x<128/BLOCK_SIZE;x++)
                    occ[mem128[i]+x]=1;
                return;
            }
        }
        if(!flag){
            printf("No space for this process of size %d...\n",size);
        }return;
    }
    else if(size==256){
        int flag = 0;
        for(int i=0;i<sizeof(mem256)/sizeof(int);i++){
            if(check(occ,mem256[i],256)){
                flag=1;
                for(int x=0;x<sizeof(occ)/sizeof(int);x++)
                    occ[mem128[i]+x]=1;
                return;
            }
        }
        if(!flag){
            printf("No space for this process of size %d...\n",size);
        }return;
    }

}

void deallocate(int size,int *mem256,int *mem128,int *mem64,int *mem32,int *mem16){
    int rounded_size = pow(2, ceil(log2(size)));
    if (rounded_size > MEMORY_SIZE) {
        printf("Invalid");
        return;
    }
    
    if(rounded_size==16){
        for(int i=0;i<sizeof(mem16)/sizeof(int);i++){
            if(occ[mem16[i]]==1){
                for(int x=0;x<16/BLOCK_SIZE;x++)
                    occ[mem16[i]+x]=0;
            }
        }
    }
    else if(rounded_size==32){
        for(int i=0;i<sizeof(mem32)/sizeof(int);i++){
            if(occ[mem32[i]]==1){
                for(int x=0;x<32/BLOCK_SIZE;x++)
                    occ[mem32[i]+x]=0;
            }
        }
    }
    else if(rounded_size==64){
        for(int i=0;i<sizeof(mem64)/sizeof(int);i++){
            if(occ[mem64[i]]==1){
                for(int x=0;x<64/BLOCK_SIZE;x++)
                    occ[mem64[i]+x]=0;
            }
        }
    }
    else if(rounded_size==128){
        for(int i=0;i<sizeof(mem128)/sizeof(int);i++){
            if(occ[mem128[i]]==1){
                for(int x=0;x<128/BLOCK_SIZE;x++)
                    occ[mem128[i]+x]=0;
            }
        }
    }
    else if(rounded_size==256){
        for(int i=0;i<sizeof(mem256)/sizeof(int);i++){
            if(occ[mem256[i]]==1){
                for(int x=0;x<256/BLOCK_SIZE;x++)
                    occ[mem256[i]+x]=0;
            }
        }
    }
}




int main() {
    FILE *f = fopen("output.txt","w");
    srand(time(NULL));
    int sequence[20];
    //indexes from where which size blocks start
    int mem256[]={0};
    int mem128[MEMORY_SIZE/128];
    for(int i=0;i<MEMORY_SIZE/128;i++){
        mem128[i]=(128/BLOCK_SIZE)*i;
        // printf("%d",mem128[i]);
    } 
    printf("\n");
    int mem64[MEMORY_SIZE/64];
    for(int i=0;i<MEMORY_SIZE/64;i++){
        mem64[i]=(64/BLOCK_SIZE)*i;
        // printf("%d",mem128[i]);
    }
    int mem32[MEMORY_SIZE/32];
    for(int i=0;i<MEMORY_SIZE/32;i++){
        mem32[i]=(32/BLOCK_SIZE)*i;
        // printf("%d",mem128[i]);
    }
    int mem16[MEMORY_SIZE/16];
    for(int i=0;i<MEMORY_SIZE/16;i++){
        mem16[i]=(16/BLOCK_SIZE)*i;
        // printf("%d",mem128[i]);
    }

    //initializing occupied array
    for(int i=0;i<MEMORY_SIZE/BLOCK_SIZE;i++){
        occ[i]=0;
    }
    
    int n = 0;
    for (int i = 0; i < 10000; i++) {
        int random = rand()%2;
        if (n == 0 || random) {
            int size = pow(2, rand() % 5 + 4);
            printf("allocated %d\n",size);
            sequence[n++] = size;
            allocate(size,mem256,mem128,mem64,mem32,mem16);
            for(int i=0;i<MEMORY_SIZE/BLOCK_SIZE;i++){
                printf("%d",occ[i]);
            }
            printf("\n");
        }else {
            int index = rand() % n;
            int size=sequence[index];
            printf("deallocated %d\n",size);
            deallocate(size,mem256,mem128,mem64,mem32,mem16);
            for(int i=0;i<MEMORY_SIZE/BLOCK_SIZE;i++){
                printf("%d",occ[i]);
            }
            printf("\n");
        }
    }
    return 0;
}