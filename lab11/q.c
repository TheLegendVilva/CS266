
#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>


#define MEMORY_SIZE 256 // MB

#define MIN_BLOCK_SIZE 1 // MB


// Function to find the closest power of 2 greater than or equal to n

int nextPowerOf2(int n) {

    int count = 0;

    while (n > 0) {

        n = n >> 1;

        count++;

    }

    return 1 << count;

}


// Function to allocate memory using Buddy System

void allocateMemory(int size, int* memory) {

    int blockSize = nextPowerOf2(size); // Find the smallest power of 2 greater than or equal to size

    bool allocated = false;


    printf("Allocating %d MB...\n", blockSize);


    // Find the first free block of required size

    for (int i = 0; i < MEMORY_SIZE; i++) {

        if (memory[i] == 0 && blockSize <= MEMORY_SIZE - i) {

            int j;

            for (j = i; j < i + blockSize; j++) {

                if (memory[j] != 0) {

                    break;

                }

            }

            if (j == i + blockSize) {

                allocated = true;

                for (int k = i; k < i + blockSize; k++) {

                    memory[k] = blockSize;

                }

                printf("Memory allocated successfully from address %d MB to %d MB.\n", i, i + blockSize - 1);

                break;

            }

        }

    }


    if (!allocated) {

        printf("Failed to allocate memory of size %d MB.\n", size);

    }

}


// Function to deallocate memory using Buddy System

void deallocateMemory(int address, int* memory) {

    int blockSize = memory[address]; // Get the size of the block to be deallocated


    printf("Deallocating memory from address %d MB...\n", address);


    // Merge the buddy blocks until a larger free block is formed

    while (blockSize < MEMORY_SIZE) {

        int buddyAddress = address ^ blockSize; // Find the buddy block address

        if (memory[buddyAddress] == blockSize) {

            int minAddress = (address < buddyAddress) ? address : buddyAddress;

            for (int i = minAddress; i < minAddress + 2 * blockSize; i++) {

                memory[i] = 0;

            }

            printf("Memory deallocated successfully from address %d MB to %d MB.\n", minAddress, minAddress + 2 * blockSize - 1);

            address = minAddress;

            blockSize *= 2;

        } else {

            break;

        }

    }

}


int main() {

    int memory[MEMORY_SIZE] = {0}; // Memory of 256 MB initialized to 0

    srand(time(0)); // Seed for random number generation


    // Generate random sequence of at least 10 memory requirements and releases

    printf("Random sequence of memory requirements and releases:\n");

    for (int i = 0; i < 20; i++) {

        int randomSize = rand() % (MEMORY_SIZE / 4) + 1; // Random size between 1 MB and 64 MB

            if (rand() % 2 == 0)

            { // 50% chance of allocating memory

                allocateMemory(randomSize, memory );

            }

            else { // 50% chance of deallocating memory

                int randomAddress = rand() % MEMORY_SIZE; // Random address to deallocate memory

                if (memory[randomAddress] != 0) { // Check if the block is allocated

                deallocateMemory(randomAddress, memory);

                }

                }

    }

    return 0;

}