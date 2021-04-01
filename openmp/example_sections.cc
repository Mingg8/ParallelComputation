#include <stdio.h>
#include <omp.h>
#include <sys/time.h>

#define N 10000
    double A[N][N];
    double x[N];
    double y_1[N];
    double y_2[N];

int main() {
	struct timeval tv1, tv2;
	struct timezone tz;
	double elapsed;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			A[i][j] = 2;
		}
		x[i] = 2;
	}

    gettimeofday(&tv1, &tz);
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            printf("Thread %d: ", omp_get_thread_num());
            for (int i=0; i < N; i++) {
                double sum = 0.0;
                for (int k = 0; k < N; k++)
                    sum += A[i][k]*x[k];
                y_1[i] = sum;
            }
        }

        #pragma omp section
        {
        printf("Thread %d: ", omp_get_thread_num( ));
        for (int i=0; i < N; i++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++)
                sum += A[i][k]*x[k];
            y_2[i] = sum;
            }
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec- tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1e-6;
    printf("elapsed time = %f seconds. \n", elapsed);
}