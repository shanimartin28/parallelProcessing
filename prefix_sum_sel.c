#include "mpi.h"
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int a,me,num,lit,size,d,partner,pdata=0,my_root=0,*data;
double timeDiff(struct timeval t1, struct timeval t2)
{
	double dif=(t1.tv_sec-t2.tv_sec)+(double)(t1.tv_usec-	t2.tv_usec)/1000000.0;
	return dif;
}
int isPowerOfTwo (unsigned int x)
{
	 while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
  		 x /= 2;
 	return (x == 1);
}

void readNumber(int n)
{	
	int i;
	num= n;
	printf("\n                num=\n",num);
	data = malloc(num*sizeof(int));
	srand((unsigned) me+1);
	for (i=0; i<num; i++) data[i] = rand()%99;
}




int main(int argc, char *argv[]) {
	int i,s,n,j,a,c,x;
	double time[6],min;
	struct timeval t1,t2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	
	readNumber(atoi(argv[1]));
	//readNumber(x);
	s=num/size;
	int data_me[s],data_recv[s],resp[s],msg[s];
	MPI_Scatter(	data, s,   MPI_INT,
						    &data_me,    s,   MPI_INT,
	                 	    my_root,
	                 	    MPI_COMM_WORLD);
	printf("my data in processor %d before reduction are ",me);
		for(i=0;i<s;i++)
			printf(" %d ",data_me[i]);
	printf("\n");
	for(c=0;c<s;c++){
		msg[c]=data_me[c];
		resp[c]=data_me[c];}
	d=log(size+1e-10)/log(2.0);//to use log2
	if(!isPowerOfTwo (size))
		d++;
	int b;
	
	for(a=0;a<6;a++){ //to make 6 repeated tests
		MPI_Barrier(MPI_COMM_WORLD);
		gettimeofday(&t1,NULL);
		for ( j = 0; j < d; j++ )
		{
 			partner = me ^ (int) pow(2,j);
			if(partner<size){
				MPI_Sendrecv(&msg, s, MPI_INT, partner, 123, &data_recv, s, MPI_INT, partner, 123, 	MPI_COMM_WORLD, &status);

			for(b=0;b<s;b++){
				if(data_recv[b]>msg[b])
					msg[b]=data_recv[b];
				if (partner<me&&data_recv[b]>resp[b]){ 
					resp[b]=data_recv[b];

				}
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	gettimeofday(&t2,NULL);
	printf("my data in processor %d after reduction are",me);
		for(i=0;i<s;i++)
			printf(" %d ",resp[i]);
		printf("\n");
	//fprintf(stderr,"\n %f\n",timeDiff(t2,t1));
	double diff=timeDiff(t2,t1);
	MPI_Reduce( &diff, &time[a], 1, MPI_DOUBLE, MPI_MAX, 0,MPI_COMM_WORLD);//to get the max time
	}
	min=time[0];
	for(a=1;a<6;a++){//to get minimum time for the multiple runtimes
		if(time[a]<min)
		min=time[a];
	}
	if(me==0)
		//fprintf(stderr,"\n min time for %d processors at input %d is %f\n",size,x,min);
		fprintf(stderr," %f\n",min);

	MPI_Finalize();
    return 0;
}


