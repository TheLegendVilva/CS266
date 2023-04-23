#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 10
#define MAX_ARRIVAL_TIME 30
#define MIN_CPU_BURST_TIME 5
#define MAX_CPU_BURST_TIME 25

typedef struct {
    int pid;
    float arrival_time;
    float cpu_burst_time;
    float waiting_time;
    float turnaround_time;
} Process;

int random_int(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int cmp_arrival_time(const void* a, const void* b) {
    const Process* p1 = (const Process*)a;
    const Process* p2 = (const Process*)b;

    if (p1->arrival_time < p2->arrival_time) {
        return -1;
    } else if (p1->arrival_time > p2->arrival_time) {
        return 1;
    } else {
        return 0;
    }
}

void hrrn_scheduling(Process processes[], int n) {
    // Initialize variables
    int i, j, current_time = 0;
    float cpu_utilization = 0.0, avg_turnaround_time = 0.0, avg_waiting_time = 0.0;

    // Process the tasks
    for (i = 0; i < n; i++) {
        // Find the process with the highest response ratio
        float max_rr = -1.0;
        int max_rr_index = -1;
        for (j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].cpu_burst_time > 0) {
                float rr = (current_time - processes[j].arrival_time + processes[j].cpu_burst_time) / (float)processes[j].cpu_burst_time;
                if (rr > max_rr) {
                    max_rr = rr;
                    max_rr_index = j;
                }
            }
        }

        // Update CPU utilization
        if (max_rr_index != -1) {
            cpu_utilization += 1.0 / n;
            processes[max_rr_index].cpu_burst_time--;
            if (processes[max_rr_index].cpu_burst_time == 0) {
                processes[max_rr_index].turnaround_time = current_time + 1 - processes[max_rr_index].arrival_time;
                processes[max_rr_index].waiting_time = processes[max_rr_index].turnaround_time - processes[max_rr_index].cpu_burst_time;
                avg_turnaround_time += processes[max_rr_index].turnaround_time / (float)n;
                avg_waiting_time += processes[max_rr_index].waiting_time / (float)n;
            }
        }

        // Increment current time
        current_time++;
    }

    // Print results
    printf("HRRN Scheduling\n");
    printf("CPU Utilization: %.2f%%\n", cpu_utilization * 100);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%.10f\t\t%.10f\n", processes[i].pid, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Create an array of processes
    Process processes[NUM_PROCESSES];
    int i;
    for (i = 0; i < NUM_PROCESSES; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = random_int(0, MAX_ARRIVAL_TIME);
        processes[i].cpu_burst_time = random_int(MIN_CPU_BURST_TIME, MAX_CPU_BURST_TIME);
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    // Sort the processes by arrival time
    qsort(processes, NUM_PROCESSES, sizeof(Process), cmp_arrival_time);

    // Run the HRRN scheduling algorithm
    hrrn_scheduling(processes, NUM_PROCESSES);

    return 0;
}


