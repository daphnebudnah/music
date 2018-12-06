1.#include   <mpi.h>
#include<stdio.h>
  
  void main(int argc, char *argv[])
  {
	int rank,size;
	double param[6],mine;
	int sndcnt,rcvcnt;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	sndcnt=1;
	mine=23.0+rank;
	if(rank==3) rcvcnt=1;

	MPI_Gather(&mine,sndcnt,MPI_DOUBLE,param,rcvcnt,MPI_DOUBLE,3,MPI_COMM_WORLD);

	if(rank==3)
		for(i=0;i<size;++i) 
		  printf("PE:%d param[%d] is %f \n",rank,i,param[i]);  

	MPI_Finalize();
}

2.#include <stdio.h>
#include "mpi.h"
#include <string.h>
int main (int argc, char *argv[])
{ 
	 int rank;
	char msg[12]="HELLO MSRIT";

 	  MPI_Init (&argc, &argv);

   MPI_Comm_rank (MPI_COMM_WORLD, &rank);


   if (rank == 0) strcpy(msg,"HELLO MSRIT");

   MPI_Bcast ((void *)&msg, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

   printf ("process id:%d received message %s\n", rank, msg);

   // Wait for every process to reach this code


   MPI_Barrier (MPI_COMM_WORLD);

   MPI_Finalize();


   return 0;


}
