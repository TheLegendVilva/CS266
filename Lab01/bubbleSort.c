#include<stdio.h>
void bubbleSort(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i;j++){
            if(arr[j]>=arr[j+1]){
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}

int main(){
    int arr[] = {23,12,123,54,22,65,76,2,33,89};
     for(int i=0;i<10;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    bubbleSort(arr,10);
    for(int i=0;i<10;i++){
        printf("%d ",arr[i]);
    }


}