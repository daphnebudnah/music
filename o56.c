#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4
int main (int argc, char *argv[])
{
int i, nthreads, tid;
float a[N], b[N], c[N], d[N];
/* Some initializations */
for (i=0; i<N; i++) {
a[i] = i * 1.5;
b[i] = i + 22.35;
c[i] = d[i] = 0.0;
}
#pragma omp parallel shared (a,b,c,d,nthreads) private(i,tid)
{
tid = omp_get_thread_num();
if (tid == 0)
{
nthreads = omp_get_num_threads();
printf("Number of threads = %d\n", nthreads);
}
printf("Thread %d starting...\n",tid);
#pragma omp sections nowait
{
#pragma omp section
{
printf("Thread %d doing section 1\n",tid);
for (i=0; i<N; i++)
{
c[i] = a[i] + b[i];
printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
}
}
#pragma omp section
{
printf("Thread %d doing section 2\n",tid);
for (i=0; i<N; i++)
{
d[i] = a[i] - b[i];
printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
}
}
} /* end of sections */
printf("Thread %d done.\n",tid);
} /* end of parallel section */
}

#include <stdio.h>
#include <omp.h>
#define N 100000000
#define TRUE 1
#define FALSE 0

int main(int argc, char **argv )
{
char host[80];
int *a;
int i, k, threads, pcount;
double t1, t2;
int found;

/* Set number of threads equal to argv[1] if present */
if (argc > 1)
{
threads = atoi(argv[1]);
if (omp_get_dynamic())
{
omp_set_dynamic(0);
printf("called omp_set_dynamic(0)\n");
}
omp_set_num_threads(threads);
}
printf("%d threads max\n",omp_get_max_threads());

a = (int *) malloc((N+1) * sizeof(int));
// 1. create a list of natural numbers 2, 3, 4, ... none of which is marked.
for (i=2;i<=N;i++) a[i] = 1;
// 2. Set k = 2, the first unmarked number on the list.
k = 2;

t1 = omp_get_wtime();
// 3. Repeat
#pragma omp parallel firstprivate(k) private(i,found)
while (k*k <= N)
{
// a. Mark all multiples of k between k^2 and N
#pragma omp for

for (i=k*k; i<=N; i+=k) a[i] = 0;
// b. Find the smallest number greater than k that is unmarked
// and set k to this new value until k^2 > N
found = FALSE;
for (i=k+1;!found;i++)
{
if (a[i]){ k = i; found = TRUE; }
}

}
t2 = omp_get_wtime();
printf("%.2f seconds\n",t2-t1);

// 4. The unmarked numbers are primes
pcount = 0;
for (i=2;i<=N;i++)
{
if( a[i] )
{
pcount++;
//printf("%d\n",i);
}
}
printf("%d primes between 0 and %d\n",pcount,N);

}

