#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM 1234

int page_table[256];
int empty = 1;
int full = 0;
int current_table_pointer = 0;
int find(int);
void randoom();
void fifo();

int main()
{
FILE *add1 = fopen("address1.txt", "w");
    srand(time(0));
    for(int i=0;i<NUM;i++){
        int u = rand()%1048576;
        fprintf(add1,"%d\n",u);
    }
    srand(time(0));
    fclose(add1);

    printf("fifo page replacement\n");
    fifo();

    empty = 1;
    full = 0;
    current_table_pointer = 0;

    for (int i = 0; i < 256; i++)
    {
        page_table[i] = -1;
    }

    printf("random page replacement\n");
    randoom();
    return 0;
}

void randoom()
{
    FILE *f = fopen("address1.txt", "r");
    int pageFault = 0;

    for (int i = 1; i <= NUM; i++)
    {
        int logical_addr = 0;
        fscanf(f, "%d", &logical_addr);
        int page_no = logical_addr >> 8;
        int offset = logical_addr ^ (page_no << 8);
        if (find(page_no) == 0)
        {
            pageFault++;
            if (empty)
            {
                page_table[current_table_pointer] = page_no;
                current_table_pointer++;
                if (current_table_pointer == 256)
                {
                    full = 1;
                    empty = 0;
                }
            }
            else if (full)
            {
                srand(time(0));
                int rd = rand() % 256;
                page_table[rd] = page_no;
            }
        }
    }
    printf("No. of page fault %d\n", pageFault);
}

void fifo()
{
    FILE *f = fopen("address1.txt", "r");
    int pageFault = 0;

    for (int i = 1; i <= NUM; i++)
    {
        int logical_addr = 0;
        fscanf(f, "%d", &logical_addr);
        int page_no = logical_addr >> 8;
        int offset = logical_addr ^ (page_no << 8);
        if (find(page_no) == 0)
        {
            pageFault++;
            if (empty)
            {
                page_table[current_table_pointer] = page_no;
                current_table_pointer++;
                if (current_table_pointer == 256)
                {
                    full = 1;
                    empty = 0;
                    current_table_pointer = 0;
                }
            }
            else if (full)
            {
                page_table[current_table_pointer] = page_no;
                current_table_pointer++;
                if (current_table_pointer == 256)
                    current_table_pointer = 0;
            }
        }
    }
    printf("No. of page fault %d\n", pageFault);
}

int find(int page_no)
{
    for (int i = 0; i < 256; i++)
    {
        if (page_table[i] == page_no)
            return 1;
    }
    return 0;
}

