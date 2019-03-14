#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int myid, numprocs, left, right;
    int buffer[10], buffer2[10];
    int i;
    MPI_Request request;
    MPI_Status status;
 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
 
    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;
        
    MPI_Barrier(MPI_COMM_WORLD);
    for(i=0;i<10;i++)
    {
        printf("\n Current data in each Processor before sendrec, Processor id= %d Send Buffer element= %d \n\n ",myid,buffer[i]);
        printf("\n Current data in each Processor before sendrec, Processor id= %d Receive Buffer element= %d \n\n ",myid,buffer2[i]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Sendrecv(buffer,                        // [in] initial address of send buffer (choice)
                 10,                            // [in] number of elements in send buffer (integer)
                 MPI_INT,                       // [in] type of elements in send buffer (handle)
                 left,                          // [in] rank of destination (integer)
                 123,                           // [in] send tag (integer)
                 buffer2,                       // [out] initial address of receive buffer (choice)
                 10,                            // [in] number of elements in receive buffer (integer)
                 MPI_INT,                       // [in] type of elements in receive buffer (handle)
                 right,                         // [in] rank of source (integer)
                 123,                           // [in] receive tag (integer)
                 MPI_COMM_WORLD,                // [in] communicator (handle)
                 &status);                      // [out] status object (Status). 
                 
    MPI_Barrier(MPI_COMM_WORLD);
    for(i=0;i<10;i++)
    {
        printf("\n Current data in each Processor after sendrec, Processor id= %d Send Buffer element= %d \n\n ",myid,buffer[i]);
        printf("\n Current data in each Processor after sendrec, Processor id= %d Receive Buffer element= %d \n\n ",myid,buffer2[i]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
 
    MPI_Finalize();
    return 0;
}
