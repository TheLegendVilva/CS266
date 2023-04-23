#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 256 // page size in bytes
#define PAGE_TABLE_SIZE 256 // number of pages in page table
#define TLB_SIZE 16 // number of entries in TLB
#define FRAME_SIZE 256 // frame size in bytes
#define PHYSICAL_MEMORY_SIZE 32768 // total size of physical memory in bytes

// Structure for page table entry
typedef struct {
    int frame_num; // frame number in physical memory
    int valid; // whether the entry is valid or not
} page_table_entry;

// Structure for TLB entry
typedef struct {
    int page_num; // page number in virtual address
    int frame_num; // frame number in physical memory
    int last_access_time; // time of last access
} tlb_entry;

// Function to extract page number from logical address
int get_page_number(int logical_address) {
    return (logical_address >> 8) & 0xFF;
}

// Function to extract page offset from logical address
int get_page_offset(int logical_address) {
    return logical_address & 0xFF;
}

// Function to translate logical address to physical address
int translate_address(int logical_address, page_table_entry* page_table, tlb_entry* tlb) {
    int page_num = get_page_number(logical_address);
    int page_offset = get_page_offset(logical_address);
    int frame_num;
    int physical_address;

    // Check TLB first
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].page_num == page_num && tlb[i].last_access_time != -1) {
            // TLB hit
            frame_num = tlb[i].frame_num;
            physical_address = (frame_num * FRAME_SIZE) + page_offset;
            tlb[i].last_access_time = 0;
            for (int j = 0; j < TLB_SIZE; j++) {
                if (j != i && tlb[j].last_access_time != -1) {
                    tlb[j].last_access_time++;
                }
            }
            return physical_address;
        }
    }

    // TLB miss, check page table
    if (page_table[page_num].valid) {
        // Page table hit
        frame_num = page_table[page_num].frame_num;
        physical_address = (frame_num * FRAME_SIZE) + page_offset;
        // Add to TLB
        int lru_index = -1;
        int max_last_access_time = -1;
        for (int i = 0; i < TLB_SIZE; i++) {
            if (tlb[i].last_access_time == -1) {
                lru_index = i;
                break;
            } else if (tlb[i].last_access_time > max_last_access_time) {
                max_last_access_time = tlb[i].last_access_time;
                lru_index = i;
            }
        }
        tlb[lru_index].page_num = page_num;
        tlb[lru_index].frame_num = frame_num;
        tlb[lru_index].last_access_time = 0;
        for (int i = 0; i < TLB_SIZE; i++) {
            if (i != lru_index && tlb[i].last_access_time != -1) {
                tlb[i].last_access_time++;
            }
        }
        return physical_address;
    }

    // Page table miss, generate page fault
    printf("Page fault!\n");
    return -1;
}

int main() {
// Initialize page table and TLB
    page_table_entry page_table[PAGE_TABLE_SIZE];
    tlb_entry tlb[TLB_SIZE];
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    page_table[i].valid = 0;
    }
    for (int i = 0; i < TLB_SIZE; i++) {
    tlb[i].last_access_time = -1;
}
// Open file containing logical addresses
    FILE* file = fopen("address.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read logical addresses from file and translate to physical addresses
    int logical_address;
    int physical_address;
    int page_fault_count = 0;
    int translation_count = 0;
    int x = fscanf(file, "%d", &logical_address);
    while (x != EOF) {
        logical_address = x >>8;
        physical_address = translate_address(logical_address, page_table, tlb);
        if (physical_address == -1) {
            page_fault_count++;
        }
        translation_count++;
        int value = rand() % 256; // simulate getting value from physical memory
        printf("Logical address: %d, Physical address: %d, Value: %d\n", logical_address, physical_address, value);
        x = fscanf(file, "%d", &logical_address);
    }

    // Print statistics
    printf("Translation count: %d\n", translation_count);
    printf("Page fault count: %d\n", page_fault_count);
    printf("Page fault rate: %.2f%%\n", (float)page_fault_count / translation_count * 100);

    // Close file
    fclose(file);

    return 0;
}
