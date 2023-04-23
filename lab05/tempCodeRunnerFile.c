#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <pthread.h>
#include<stdbool.h>

int r,c;
int a[100][100];

void *scalarMultiplication(void* ptr){
    int c_;
    printf("Enter a scalar value:");
    scanf("%d",&c_);
    printf("After scalar Multiplication:\n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",c_*a[i][j]);
        }    
        printf("\n");
    }
    printf("\n");
    // fflush(stdout);
    // pthread_exit(0);
}
void *vectorMultiplication(void* ptr){
    int c_;
    printf("Enter a %d x _ matrix:",c);
    scanf("%d",&c_);
    int b[c][c_];
    for(int i=0;i<c;i++){
        for(int j=0;j<c_;j++){
            scanf("%d",&b[i][j]);
        }
    }
    int mul[r][c_];
    
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c_; j++) {
            mul[i][j] = 0;
            for (int k = 0; k < r; k++) {
                mul[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    printf("After vector Multiplication:\n");
    //print matrix:
    for(int i=0;i<r;i++){
        for(int j=0;j<c_;j++){
            printf("%d ",mul[i][j]);
        }
        printf("\n");
    }
}

void *transposeMatrix(void* ptr){
    int i,j;
    int transpose[c][r];
    for (i = 0;i < r;i++){
        for (j = 0; j < c; j++){
           transpose[j][i] = a[i][j];
        }
    }
    printf("Transpose of the main Matrix:\n");
    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
            printf("%d ",transpose[i][j]);
        }
        printf("\n");
    }
    
}

void checkInverse(void* ptr){
    printf("Enter a %d x %d matrix\n",c,r);
    int inv[c][r];
    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&inv[i][j]);
        }
    }
    
    int mul[r][r];
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            mul[i][j] = 0;
            for (int k = 0; k < r; k++) {
                mul[i][j] += a[i][k] * inv[k][j];
            }
        }
    }
    
    int eye[r][r];
    for(int i=0;i<r;i++){
        for(int j=0;j<r;j++){
            if(i==j){
                eye[i][j]=1;
            }
            else{
                eye[i][j]=0;
            }
        }
    }
    bool flag = true;
    for(int i=0;i<r;i++){
        for(int j=0;j<r;j++){
            if(eye[i][j] != mul[i][j]){
                flag=false;
                break;
            }
        }
        if(!flag){
            break;
        }
    }
    
    if(flag){
        printf("AB=I");
    }
    else{
        printf("AB!=I");
    }
    
}

void *forbeniusNorm(void* ptr){
    int ans;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            ans+=(a[i][j]*a[i][j]);
        }
    }
    printf("Forbenius Norm of Matrix: %lf",sqrt(ans));
}

void *FNorm(void* ptr){
    int arr[c];
    int sum=0;
    for(int i=0;i<c;i++){
        sum=0;
        for(int j=0;j<r;j++){
                sum+=a[j][i];
        } 
        arr[i]=sum;
    }
    int max=-10000;
    for(int i=0;i<c;i++){
        if(max<arr[i]){
            max=arr[i];
        }
    }
    printf("1-Norm = %d",max);
}

void *infNorm(void* ptr){
    int arr[c];
    int sum=0;
    for(int i=0;i<r;i++){
        sum=0;
        for(int j=0;j<c;j++){
                sum+=a[i][j];
        } 
        arr[i]=sum;
    }
    int max=-10000;
    for(int i=0;i<c;i++){
        if(max<arr[i]){
            max=arr[i];
        }
    }
    printf("inf-Norm = %d",max);
}

void *ulTriangularCheck(void* ptr){
    if(r!=c){
        printf("Not upper or lower triangular matrix.\n");
        return NULL;
    }
    bool flag=true;
    for (int i = 1; i < r; i++){
		for (int j = 0; j < i; j++){
			if (a[i][j] != 0){
				flag = false;
				break;
			}
		}
		if(!flag){
		    break;
		}
    }
    if(flag){
        printf("Lower triangular Matrix.\n");
        return NULL;
    }
    flag=true;
    for (int i = 1; i < c; i++){
		for (int j = 0; j < i; j++){
			if (a[j][i] != 0){
				flag = false;
				break;
			}
		}
		if(!flag){
		    break;
		}
    }
    if(flag){
        printf("Upper triangular Matrix.\n");
        return NULL;
    }
    else{
        printf("Not an upper or lower triangular matrix.");
    }
}

int main(){
    printf("Enter no. of rows:");
    scanf("%d",&r);
    printf("\n");
    printf("Enter no. of columns:");
    scanf("%d",&c);
    printf("Enter a %d x %d matrix:\n",r,c);
    // int a[r][c];
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&a[i][j]);
        }
    }
    
    
    pthread_t thread_1;
    pthread_create(&thread_1, NULL, scalarMultiplication,NULL);
    pthread_join(thread_1, NULL);
    
    pthread_t thread_2;
    pthread_create(&thread_2, NULL, vectorMultiplication,NULL);
    pthread_join(thread_2, NULL);
    printf("\n");
    pthread_t thread_3;
    pthread_create(&thread_3, NULL, transposeMatrix,NULL);
    pthread_join(thread_3, NULL);
    printf("\n");
    pthread_t thread_4;
    pthread_create(&thread_4,NULL,checkInverse,NULL);
    pthread_join(thread_4,NULL);
    printf("\n");
    pthread_t thread_5;
    pthread_create(&thread_5,NULL,forbeniusNorm,NULL);
    pthread_join(thread_5,NULL);
    printf("\n");
    pthread_t thread_6;
    pthread_create(&thread_6,NULL,FNorm,NULL);
    pthread_join(thread_6,NULL);
    printf("\n");
    pthread_t thread_7;
    pthread_create(&thread_7,NULL,infNorm,NULL);
    pthread_join(thread_7,NULL);
    printf("\n");
    pthread_t thread_8;
    pthread_create(&thread_8,NULL,ulTriangularCheck,NULL);
    pthread_join(thread_8,NULL);
    printf("\n");
    return 0;
}



