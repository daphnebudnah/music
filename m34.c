3.
#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[])
{
    int iproc;
    int MyRank, Numprocs, Root = 0;
    int value, sum = 0;
    int	Source, Source_tag;
    int Destination, Destination_tag;
    MPI_Status status;


    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    if(MyRank == Root){

       for(iproc = 1 ; iproc < Numprocs ; iproc++){
           Source     = iproc;
	   Source_tag = 0;

	   MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
		     MPI_COMM_WORLD, &status);
	   sum = sum + value;
       }
       printf("MyRank = %d, SUM = %d\n", MyRank, sum);
    }
    else{
	Destination     = 0;
	Destination_tag = 0;

	MPI_Send(&MyRank, 1, MPI_INT, Destination, Destination_tag, 
		  MPI_COMM_WORLD);
    }

    MPI_Finalize();

}
4.
#include <stdio.h>
#include <math.h>
#include "mpi.h"

double func(double x)
{
    return (4.0 / (1.0 + x*x));
}

int main(int argc,char *argv[])
{
    int    NoInterval, interval;
    int    MyRank, Numprocs, Root = 0; 
    double mypi, pi, h, sum, x;
    double PI25DT = 3.141592653589793238462643;

    /*....MPI initialisation....*/
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    if(MyRank == Root){
	printf("\nEnter the number of intervals : ");
	scanf("%d",&NoInterval);
    }
        
   /*....Broadcast the number of subintervals to each processor....*/ 
   MPI_Bcast(&NoInterval, 1, MPI_INT, 0, MPI_COMM_WORLD);

   if(NoInterval <= 0){
      if(MyRank == Root) 
	 printf("Invalid Value for Number of Intervals .....\n");
      MPI_Finalize();
      exit(-1);
   }

   h   = 1.0 / (double)NoInterval;
   sum = 0.0;
   for(interval = MyRank + 1; interval <= NoInterval; interval += Numprocs){
       x = h * ((double)interval - 0.5);
       sum += func(x);
   }
   mypi = h * sum;

   /*....Collect the areas calculated in P0....*/ 
   MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, Root, MPI_COMM_WORLD);

   if(MyRank == Root){
      printf("pi is approximately %.16f, Error is %.16f\n", 
						   pi, fabs(pi - PI25DT));
   }

   MPI_Finalize();

