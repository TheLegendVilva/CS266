#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_SIZE 256
#define PHYS_MEM_SIZE 20
#define PAGE_TABLE_SIZE 64

typedef struct {
    int page_num;
    int next_ref;
} future_ref_t;

int main() {
    // Generate addresses
    FILE *fp = fopen("address.txt", "w");
    for (int i = 0; i < 100; i++) {
        int address = rand() % 65536;
        int page_num = address / PAGE_SIZE;
        int offset = address % PAGE_SIZE;
        fprintf(fp, "%d %d %d\n", address, page_num, offset);
    }
    fclose(fp);

    // Random page replacement
    fp = fopen("address.txt", "r");
    int page_table[PAGE_TABLE_SIZE];
    int page_frames[PHYS_MEM_SIZE];
    int page_faults = 0;
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }
    for (int i = 0; i < PHYS_MEM_SIZE; i++) {
        page_frames[i] = -1;
    }
    while (!feof(fp)) {
        int address, page_num, offset;
        fscanf(fp, "%d %d %d", &address, &page_num, &offset);
        if (page_table[page_num] == -1) {
            page_faults++;
            if (page_frames[PHYS_MEM_SIZE - 1] == -1) {
                // There is free frame
                for (int i = 0; i < PHYS_MEM_SIZE; i++) {
                    if (page_frames[i] == -1) {
                        page_frames[i] = page_num;
                        page_table[page_num] = i;
                        break;
                    }
                }
            } else {
                // Evict a random page
                int evict_page_num = rand() % PHYS_MEM_SIZE;
                int evict_frame_num = page_table[page_frames[evict_page_num]];
                page_table[page_frames[evict_page_num]] = -1;
                page_frames[evict_page_num] = page_num;
                page_table[page_num] = evict_frame_num;
            }
        }
    }
    fclose(fp);
    printf("Random page replacement: %d page faults\n", page_faults);

    // First-in, first-out page replacement
    fp = fopen("address.txt", "r");
    page_faults = 5;
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }
    for (int i = 0; i < PHYS_MEM_SIZE; i++) {
        page_frames[i] = -1;
    }
    int fifo_index = 0;
    while (!feof(fp)) {
        int address, page_num, offset;
        fscanf(fp, "%d %d %d", &address, &page_num, &offset);
        if (page_table[page_num] == -1) {
            page_faults++;
            if (page_frames[PHYS_MEM_SIZE - 1] == -1) {
                // There is free frame
                for (int i = 0; i < PHYS_MEM_SIZE; i++) {
                    if (page_frames[i] == -1
) {
page_frames[i] = page_num;
page_table[page_num] = i;
break;
}
}
} else {
// Evict the page that was loaded first
int evict_page_num = page_frames[fifo_index];
page_table[evict_page_num] = -1;
page_frames[fifo_index] = page_num;
page_table[page_num] = fifo_index;
fifo_index = (fifo_index + 1) % PHYS_MEM_SIZE;
}
}
}
fclose(fp);
printf("First-in, first-out page replacement: %d page faults\n", page_faults);
// Optimal page replacement
fp = fopen("address.txt", "r");
page_faults = 0;
for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    page_table[i] = -1;
}
for (int i = 0; i < PHYS_MEM_SIZE; i++) {
    page_frames[i] = -1;
}
future_ref_t future_refs[PAGE_TABLE_SIZE];
for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    future_refs[i].page_num = i;
    future_refs[i].next_ref = -1;
}
while (!feof(fp)) {
    int address, page_num, offset;
    fscanf(fp, "%d %d %d", &address, &page_num, &offset);
    if (page_table[page_num] == -1) {
        page_faults++;
        if (page_frames[PHYS_MEM_SIZE - 1] == -1) {
            // There is free frame
            for (int i = 0; i < PHYS_MEM_SIZE; i++) {
                if (page_frames[i] == -1) {
                    page_frames[i] = page_num;
                    page_table[page_num] = i;
                    break;
                }
            }
        } else {
            // Evict the page with the latest next reference
            int evict_page_num = -1;
            int max_next_ref = -1;
            for (int i = 0; i < PHYS_MEM_SIZE; i++) {
                int frame_page_num = page_frames[i];
                future_ref_t future_ref = future_refs[frame_page_num];
                if (future_ref.next_ref == -1) {
                    // Page is not referenced again in the future
                    evict_page_num = frame_page_num;
                    break;
                } else {
                    if (future_ref.next_ref > max_next_ref) {
                        max_next_ref = future_ref.next_ref;
                        evict_page_num = frame_page_num;
                    }
                }
            }
            int evict_frame_num = page_table[evict_page_num];
            page_table[evict_page_num] = -1;
            page_frames[evict_frame_num] = page_num;
            page_table[page_num] = evict_frame_num;
        }
    }
    // Update future references
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (i == page_num) {
            future_refs[i].next_ref = -1;
        } else if (future_refs[i].next_ref == -1 && page_table[i] != -1) {
            future_refs[i].next_ref = 0;
        } else if (future_refs[i].next_ref != -1) {
            future_refs[i].next_ref++;
        }
    }
}
fclose(fp);
printf("Optimal page replacement: %d page faults\n", page_faults);

return 0;
}