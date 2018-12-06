5.
#include <stdio.h>
#include <mpi.h>
#include <string.h>
#define BUFFER_SIZE 32

int main(int argc,char *argv[])
{
	int  MyRank,Numprocs, Destination, iproc;
	int  tag = 0;
	int  Root = 3, temp = 1;
	char Message[BUFFER_SIZE];
	MPI_Init(&argc,&argv);
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
	MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);

	/* print host name, and send message from process with rank 0 to all other processes */
	if(MyRank == 3)        {
		system("hostname");
		strcpy(Message, "Hello India"); 
		for (temp=0; temp<Numprocs && temp!=3;temp++)
		{
			MPI_Send(Message, BUFFER_SIZE, MPI_CHAR, temp, tag,MPI_COMM_WORLD);
		}
	}
 	else {          
		system("hostname");
	   	MPI_Recv(Message, BUFFER_SIZE, MPI_CHAR, Root, tag,MPI_COMM_WORLD, &status);
		printf("\n%s in process with rank %d from Process with rank %d\n", Message,MyRank,Root);
  	}

  	MPI_Finalize();
}

6.
#include   <stdio.h>
#include   <mpi.h>
#include <string.h>
#include <stdlib.h>
  
  void main(int argc, char *argv[])
  {
	int rank,size;
	int param[6],mine;
	int part_str_len = 12;

  	char *my_string;
  	char *rcv_string;

	int sndcnt,rcvcnt,msndcnt,mrcvcnt;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if ((my_string = malloc(part_str_len*sizeof(char))) == NULL){
    MPI_Abort(MPI_COMM_WORLD,1);
  }
  if ((rcv_string = malloc(part_str_len*size*sizeof(char))) == NULL){
    MPI_Abort(MPI_COMM_WORLD,1);
  }

	sndcnt=1;
	msndcnt=12;
	mine=rank;
	strcpy(my_string,"Hello world");

  
 	if(rank==0) 
	{ 
	rcvcnt=1;
	mrcvcnt=12;
	}

	MPI_Gather(&mine,sndcnt,MPI_INT,param,rcvcnt,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Gather(my_string,msndcnt,MPI_CHAR,rcv_string,mrcvcnt,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0)
{
		for(i=0;i<size;i++) {
		  printf(" gathering process id:%d received %d and %s from process id:%d  \n",rank,param[i],&rcv_string[part_str_len*i],i); 
		}
}
		
	MPI_Finalize();
}

