#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv)
{  
   int i, N, noprocs, nid, hepsi;
   float  sum = 0, Gsum;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &nid);
   MPI_Comm_size(MPI_COMM_WORLD, &noprocs);

   if(nid == 0)
   {  
          printf("Please enter the number of terms N -> ");    
          scanf("%d",&N);  
   }
   
   /* Broadcasts a message from the process with rank "root" to all other processes of the group.*/
   MPI_Bcast(&N,                /* starting address of buffer */
             1,                 /* number of entries in buffer */
             MPI_INT,           /* data type of buffer */
             0,                 /* rank of broadcast root*/
             MPI_COMM_WORLD);   /* communicator (handle) */
             
   //for(i = nid; i < N; i += noprocs)
   for(i = nid; i < N; i += noprocs)
   {
      if(i % 2)
         sum -= (float) 1 / (i + 1);
      else
         sum += (float) 1 / (i + 1);
   }
      /* MPI_Reduce(&sum,&Gsum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
       if(nid == 0)    printf("An estimate of ln(2) is %f \n",Gsum);
        hepsi = nid;
        printf("My rank is  %d Hepsi =%d \n",nid,hepsi);

        MPI_Allreduce(&nid,&hepsi,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
        printf("After All Reduce My rank is  %d Hepsi =%d \n",nid,hepsi);*/

        hepsi = nid;
        /* MPI_Scan performs a prefix reduction of the data stored in the buffer sendbuf
          at each process and returns the result in the buffer recvbuf.*/
        MPI_Scan(&nid,                /* starting address of send buffer */
                 &hepsi,              /* starting address of recieve buffer */
                 1,                   /* number of elements in input buffer */
                 MPI_INT,             /* data type of elements of input buffer */
                 MPI_SUM,             /* operation (handle)*/
                 MPI_COMM_WORLD);     /* communicator (handle) */
        printf("After Prefix Reduction My rank is  %d Hepsi =%d \n",nid,hepsi); 

        MPI_Finalize();
 return 0;
}
