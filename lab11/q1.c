#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define MEMORY_SIZE 256
#define BLOCK_SIZE 16

int memory[MEMORY_SIZE / BLOCK_SIZE];

int get_buddy_index(int index, int size) {
    return index ^ (size / BLOCK_SIZE);
}

void split(int index, int size) {
    memory[index] = -size;
    memory[get_buddy_index(index, size)] = -size;
}

void merge(int index, int size) {
    int buddy_index = get_buddy_index(index, size);
    if (memory[buddy_index] == -size) {
        memory[index] = 0;
        memory[buddy_index] = 0;
        merge(fmin(index, buddy_index), size * 2);
    } else {
        memory[index] = 0;
        memory[buddy_index] = 0;
    }
}

int allocate(int size) {
    int rounded_size = pow(2, ceil(log2(size)));
    if (rounded_size > MEMORY_SIZE) {
        return -1;
    }
    int index = 0;
    while (true) {
        if (memory[index] == 0 && -memory[index + (rounded_size / BLOCK_SIZE)] == rounded_size) {
            split(index, rounded_size);
            return index;
        }
        if (index >= MEMORY_SIZE / BLOCK_SIZE - 1) {
            return -1;
        }
        index += abs(memory[index]) / BLOCK_SIZE;
    }
}

void deallocate(int index) {
    int size = BLOCK_SIZE;
    while (true) {
        merge(index, size);
        if (index == 0 || index == MEMORY_SIZE / BLOCK_SIZE - 1) {
            break;
        }
        size *= 2;
        index = index / 2;
    }
}

int main() {
    srand(time(NULL));
    int sequence[20];
    int n = 0;
    for (int i = 0; i < 10; i++) {
        if (n == 0 || rand() % 2 == 0) {
            int size = pow(2, rand() % 4 + 4);
            printf("%d\n",size);
            sequence[n++] = size;
            printf("Allocated block of size %d\n", size);
        } else {
            int index = rand() % n;
            deallocate(sequence[index]);
            for (int j = index; j < n - 1; j++) {
                sequence[j] = sequence[j + 1];
            }
            n--;
            printf("Deallocated block at index %d\n", index);
        }
    }
    return 0;
}