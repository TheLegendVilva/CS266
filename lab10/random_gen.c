#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
   int i;
   short int nums[200];
   FILE *fp;
   
   // open the file for writing
   fp = fopen("address.txt", "w");
   
   // seed the random number generator
   srand(time(NULL));
   
   // generate 100 random 16-bit decimal numbers and write them to the file
   for (i = 0; i < 200; i++) {
      nums[i] = rand() % 1048576; // generates a random number between 0 and 65535
    //   if(nums[i]>10000)
        fprintf(fp, "%d\n", nums[i]); // write the number to the file
    //   else
        // continue;
   }
   
   // close the file
   fclose(fp);
   
   return 0;
}
