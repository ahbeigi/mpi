# In dhis code, rank 0 sends a message to rank 1 and sleeps for 10 seconds, 
# rank 1 then prints the value.

#include <stdio.h>
#include "mpi.h"

void main(int argc, char* argv[])
{
	int rank, size, buffer = -1, tag = 10;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (size >= 2 && rank == 0)
	{
		buffer = 33;
		printf("on Rank %d buffer has been set. sleep for 10 seconds...\n", rank);
		sleep(10);
		MPI_Send(&buffer, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
	}
	
	if (size >= 2 && rank == 1)
	{
		MPI_Recv(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		printf("Rank %d\t buffer=%d\n", rank, buffer);
		if (buffer != 33) printf("fail!\n");
	}
	MPI_Finalize();
}
