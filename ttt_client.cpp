#include <stdio.h> 
#include <string.h> 

#include "mpi.h" 

int main(int argc, char **argv)
{ 
    int rank; 
    int turn;
    int cell;
    int finish = 0;
    int message; 
    MPI_Init(&argc, &argv); 
    char port_name[MPI_MAX_PORT_NAME]; 
    MPI_Comm intercomm; 
    MPI_Status status; 
    strcpy(port_name, argv[1]); 
    printf("attempt to connect\n"); 
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm); 
    MPI_Recv(&turn, 1, MPI_INT, 0, 6, intercomm, &status);      
    printf("First turn is for player # %d \n", turn); 
    while (finish != 1)
	{
        MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm); 
        MPI_Recv(&cell, 1, MPI_INT, 0, 6, intercomm, &status);         
        MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
        scanf("%d", &message); 
        MPI_Send(&message, 1, MPI_INT, 0, 5, intercomm);  
        // MPI_Recv(&finish, 1, MPI_INT, 0, 6, intercomm, &status); 
        printf("Player picked: %d \n", cell);
        if (cell == 999)
        {
            printf("Game is over \n");
            MPI_Comm_disconnect(&intercomm);
        }
    }
            MPI_Finalize();
            
            return 0; 

} 




