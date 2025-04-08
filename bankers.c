#include <stdio.h>
#include <stdbool.h>

int main() {
    // Declare variables
    int n, m; // n = number of processes, m = number of resources
    int i, j, k;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
    
    // Available resources vector
    int available[m];
    printf("\nEnter the available resources:\n");
    for(i = 0; i < m; i++) {
        printf("Available resource %d: ", i);
        scanf("%d", &available[i]);
    }
    
    // Maximum demand matrix
    int maximum[n][m];
    printf("\nEnter the maximum demand matrix:\n");
    for(i = 0; i < n; i++) {
        printf("For process %d:\n", i);
        for(j = 0; j < m; j++) {
            printf("Maximum demand for resource %d: ", j);
            scanf("%d", &maximum[i][j]);
        }
    }
    
    // Allocation matrix
    int allocation[n][m];
    printf("\nEnter the allocation matrix:\n");
    for(i = 0; i < n; i++) {
        printf("For process %d:\n", i);
        for(j = 0; j < m; j++) {
            printf("Allocated resource %d: ", j);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Update available resources after getting all allocations
    for(j = 0; j < m; j++) {
        int total_allocated = 0;
        for(i = 0; i < n; i++) {
            total_allocated += allocation[i][j];
        }
        available[j] -= total_allocated;
    }
    
    // Calculate need matrix: need = maximum - allocation
    int need[n][m];
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    
    // Display entered data
    printf("\nAvailable Resources:\n");
    for(i = 0; i < m; i++) {
        printf("%d ", available[i]);
    }
    
    printf("\n\nMaximum Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    
    printf("\nAllocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    // Initialize tracking arrays for safety check
    bool finished[n];
    for(i = 0; i < n; i++) {
        finished[i] = false;    // No process is finished initially
    }
    
    int work[m];
    for(i = 0; i < m; i++) {
        work[i] = available[i]; // Work = initially available resources
    }
    
    int safe_sequence[n];
    int count = 0;
    
    // Main Banker's Algorithm loop
    while(count < n) {          // Try until all processes are sequenced
        bool found = false;     // Flag to track if we found a safe process
        for(i = 0; i < n; i++) {
            if(finished[i] == false) {  // Consider only unfinished processes
                bool can_allocate = true;
                
                // Check if process i's resource needs can be met
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if(can_allocate) {
                    // Process i can safely complete - add its resources back
                    for(j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    safe_sequence[count] = i;    // Add to safe sequence
                    finished[i] = true;          // Mark as finished
                    count++;                     // Increment count of safe processes
                    found = true;                // We found a safe process
                }
            }
        }
        
        if(found == false) {    // No process could be allocated safely
            break;              // System is unsafe
        }
    }

    // Final safety check and output
    if(count < n) {
        printf("\nSystem is in UNSAFE state!\n");
    } else {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe sequence: ");
        for(i = 0; i < n; i++) {
            printf("P%d ", safe_sequence[i]);
            if(i < n - 1) {
                printf("-> ");
            }
        }
        printf("\n");
    }
    
    return 0;
}
