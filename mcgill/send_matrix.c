#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[])
{
    int rank, size, count, dest, source, tag;
    int matrix[4][4], i, j;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) { MPI_Finalize(); return -128; }

    if (rank == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                matrix[i][j] = i * 4 + j;
            }
        }
        count = 16;
        dest = 1;
        tag = 20;

        MPI_Send(&matrix, 16, MPI_INT, 1, 20, MPI_COMM_WORLD);
        printf("Process %d sent matrix=\n", rank);
    }

    if (rank == 1) {
        count = 16;
        source = 0;
        tag = 20;

        MPI_Recv(&matrix, 16, MPI_INT, 0, 20, MPI_COMM_WORLD, &status);
        printf("Process %d received matrix=mat\n", rank);
    }

    if (rank < 2) {
        for (i = 0; i < 4; i++) {
            printf("%2d %2d %2d %2d\n",
                matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
        }
    }

    printf("Done! Sleeping before exit...");
    sleep(10);
    MPI_Finalize();
    return 0;
}

