#include <stdio.h> 
#include <string.h> 

#include "mpi.h" 

int main(int argc, char **argv)
{ 
    int rank; 
    int turn;
    int message; 
    MPI_Init(&argc, &argv); 
    char port_name[MPI_MAX_PORT_NAME]; 
    MPI_Comm intercomm; 
    MPI_Status status; 
    strcpy(port_name, argv[1]); 
    printf("attempt to connect\n"); 
    for (int i = 0; i < 5; i++)
	{
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm); 
    MPI_Recv(&turn, 1, MPI_INT, 0, 6, intercomm, &status); 
    printf("First turn is for player # %d \n", turn); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    scanf("%d", &message); 
    MPI_Send(&message, 1, MPI_INT, 0, 5, intercomm); 
    MPI_Recv(&rank, 1, MPI_INT, 0, 6, intercomm, &status); 
    printf("First sent %d\n", rank); 
    }
    MPI_Finalize(); 
    return 0; 

} 




