#include "mpi.h"
#include <stdio.h>

int main( int argc, char *argv[] )
{
    double t1, t2;
    int i;

    MPI_Init( 0, 0 );
    t1 = MPI_Wtime();
    for(i=0;i<100000;i++)
    {
        printf("a");
    }
    t2 = MPI_Wtime();
    printf("MPI_Wtime measured a 1 second sleep to be: %1.2f\n", t2-t1);
    fflush(stdout);
    MPI_Finalize( );
    return 0;
}
