/*
	Program to calculate the prefix sum on a Hyper-Cube using all to all broadcast using algorithm.	
*/

#include <stdio.h>
#include <math.h>
#include<mpi.h>

#define HypercubeDimension 3
#define Nodes 8 

main (int argc, char *argv[]){

  /* Define each Node(Processor) with a Node ID , Node Value and Process Id. */
  typedef struct {
    int Node_Id;
    int Node_Value;
    int Process_Id;
  } node;


  /* Declare all the required variables. */
  node Node;
  int i, j, k, length;
  int partner, numprocs , message, my_id;
  int destination_node, msg_dest_tag;
  int source_node, msg_src_tag, root;
  int rank, receive_data;

  /* Declare output variable as prefixsum_result. */
  node prefixsum_result[Nodes];
  MPI_Status Status;

  /* MPI initialization. */
  MPI_Init(&argc, &argv);

  /* Get the number of processes.*/
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  /* Determine the rank of this process. */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  
  /* printf("Nodes available: \n");
  printf("**********************\n");
  printf ( "  The number of processes available is %d.\n", numprocs );
  printf("Hello World from Node %d\n",my_id);
  printf("**********************\n"); */

  /* Assign the rank of the process to the var rank. */
  rank = my_id;  

  /* Assign the values for Node_Id and Node_Value as the Rank of the Node.*/
  Node.Node_Id = my_id;
  Node.Node_Value = rank;

  /* Provide the message value as that of the Node value.*/
  message = Node.Node_Value;
   
 
  /* Loop for i = 0; 1; : : : ; d-1 , where d is the HypercubeDimension */
  for (i = 0; i < HypercubeDimension; i++){
    /*printf("**********************\n");  
    printf("Loop iteration: %d\n",i);  */
     
    partner = Node.Node_Id ^ (int) pow(2,i);

    /*
    printf("Current node : %d \n",Node.Node_Id);     
    printf("Computed partner : %d \n",partner);     
    printf("Current node message value: %d \n",message); */

  
    /* Send messsage to partner and at the same time receive data from partner. */
    destination_node = partner ;
    msg_dest_tag = Node.Node_Id; 
    MPI_Send(&message,              /* message buffer */
             1,                     /* one data item */
             MPI_INT,               /* data item is an integer */
             destination_node,      /* rank of the destination node */
             msg_dest_tag,          /* user chosen message tag */
             MPI_COMM_WORLD);       /* default communicator world*/
             
    /* printf("Destination node : %d \n",destination_node);       
    printf("Destination message tag : %d \n",msg_dest_tag); */      

    source_node = partner ;
    msg_src_tag = partner; 
    MPI_Recv(&receive_data,         /* message buffer */
             1,                     /* one data item */
             MPI_INT,               /* data item is an integer */
             source_node,           /* rank of the sending process(partner)*/
             msg_src_tag,           /* user chosen message tag */
             MPI_COMM_WORLD,        /* default communicator world*/
             &Status);              /* info about the received message */


    /* printf("Source node : %d \n",source_node);       
    printf("Source message tag : %d \n",msg_src_tag); */    
    
    /* Add the received data to the message. */
    message+= receive_data;


    /* If partner < me then, add the received data to node value. */
    if (partner < Node.Node_Id) 
    {
      Node.Node_Value += receive_data;
    }
    
  }
  

  Node.Process_Id = getpid();
  
  /*
  printf("Obtain the result at root\n");
  printf("Use of MPI_Gather to gather all the values from a group of processes"); */

  root = 0; 
  MPI_Gather(&Node,                 /* sending node message buffer */
             sizeof(node),          /* number of elements in send buffer */
             MPI_CHAR,              /* data type of send buffer elements */
             &prefixsum_result,     /* address of receive buffer */
             sizeof(node),          /* number of elements for any single receive */
             MPI_CHAR,              /* data type of recv buffer elements */
             root,                  /* rank of receiving process */
             MPI_COMM_WORLD);       /* default communicator world*/
  
  if(my_id == 0) {
   for(j=0;j<Nodes;j++)
   {
     printf("******************\n");  
     printf (" Node ID = %d.\n", prefixsum_result[j].Node_Id);
     printf("Content of result buffer --> %d\n",prefixsum_result[j].Node_Value);    
     printf("Content of message buffer --> %d\n",message);
   }
    printf("******************\n");  
  }

  MPI_Finalize();
  
}
