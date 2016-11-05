
#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int world_size, world_rank, name_len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Get_processor_name(processor_name, &name_len);

	sleep(10);
	printf("Hello world from processor %s, rank: %d"
		" out of %d processor\n",
		processor_name, world_rank, world_size);
	MPI_Finalize();
}
