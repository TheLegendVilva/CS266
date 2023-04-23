#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_TABLE_SIZE 64  // 2^6 entries
#define FRAME_SIZE 256  // 2^8 bytes
#define PHYSICAL_MEM_SIZE (FRAME_SIZE * 128)  // 32KB

int main() {
    // Initialize page table with random frame numbers
    srand(time(NULL));
    int page_table[PAGE_TABLE_SIZE];
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = rand() % 128;  // random frame number between 0 and 127
    }

    // Read logical addresses from file
    FILE* f =fopen("output.txt","w");
    FILE *fp;
    fp = fopen("address.txt", "r");
    if (fp == NULL) {
        printf("Error: Failed to open file\n");
        return 1;
    }
    int logical_address;
    int count=0;
    while (fscanf(fp, "%d", &logical_address) != EOF) {
        // Extract page number and offset from logical address
        int page_number = (logical_address >> 8) & 0xFFF;
        int offset = logical_address & 0xFF;

        // Look up frame number in page table
        if (page_number >= PAGE_TABLE_SIZE) {
            printf("Error: Invalid page number %d\n", page_number);
            continue;
        }
        int frame_number = page_table[page_number];

        // Calculate physical address
        int physical_address = frame_number * FRAME_SIZE + offset;

        // Check if physical address is within physical memory
        if (physical_address >= PHYSICAL_MEM_SIZE) {
            printf("Error: Invalid physical address %d\n", physical_address);
            continue;
        }

        

        // Output results
        fprintf(f,"Logical address: %d\n", logical_address);
        fprintf(f,"Physical address: %d\n", physical_address);
        // printf("Byte value: %d\n\n", byte);
        count++;
    }
    printf("%d",count);
    fclose(fp);
    return 0;
}

