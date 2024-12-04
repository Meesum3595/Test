#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_sum = 0;
    int global_sum = 0;
    
    // Array of numbers to sum
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array_size = 10;
    
    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    
    // Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Calculate how many elements each process will handle
    int elements_per_process = array_size / size;
    int start = rank * elements_per_process;
    int end = start + elements_per_process;
    
    // Each process calculates its local sum
    local_sum = 0;
    for(int i = start; i < end; i++) {
        local_sum += numbers[i];
    }
    
    // Reduce all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Process 0 prints the result
    if (rank == 0) {
        printf("Array elements: ");
        for(int i = 0; i < array_size; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\nGlobal sum = %d\n", global_sum);
    }
    
    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
