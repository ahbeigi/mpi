#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    float A[2], B[2];
    MPI_Status status1, status2;
    MPI_Request request10, request11, request20, request21;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    if (size < 2) { MPI_Finalize(); return -1; }

    if (rank == 0) {
        A[0] = 1.0f;
        A[1] = 2.0f;

        // Send and Receive
        MPI_Isend(&A, 2, MPI_FLOAT, 1, 10, MPI_COMM_WORLD, &request10);
        MPI_Recv(&B, 2, MPI_FLOAT, 1, 20, MPI_COMM_WORLD, &status1);
        printf("Process %d sent     A=[%f, %f]\n", rank, A[0], A[1]);
        printf("Process %d received B=[%f, %f]\n", rank, B[0], B[1]);
    }

    if (rank == 1) {
        B[0] = 3.0f;
        B[1] = 4.0f;

        // Send and Receive
        MPI_Isend(&B, 2, MPI_FLOAT, 0, 20, MPI_COMM_WORLD, &request10);
        MPI_Recv(&A, 2, MPI_FLOAT, 0, 10, MPI_COMM_WORLD, &status1);
        printf("Process %d sent     B=[%f, %f]\n", rank, B[0], B[1]);
        printf("Process %d received A=[%f, %f]\n", rank, A[0], A[1]);
    }

    MPI_Wait(&request10, &status1);
    MPI_Finalize();
    return 0;
}

