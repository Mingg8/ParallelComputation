#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

#define N 10000
    double A[N][N];
    double x[N];
    double y[N];

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
    #pragma omp parallel
    {
        int i, k;
        double sum;
        gettimeofday(&tv1, &tz);
        #pragma omp for private(i, k, sum)
        for (i=0; i < N; i++) {
            sum = 0.0;
            for (k = 0; k < N; k++)
                sum += A[i][k]*x[k];
            y[i] = sum;
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec- tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1e-6;
    printf("elapsed time = %f seconds. \n", elapsed);
    cout << y[0] << ", " << y[1] << ", "<<y[2] << endl;
    return 0;
}
