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

	int op = 1;
	int i = 0;
	double target = 0;

	#pragma omp parallel shared(A, coord, op, target) {
	    #pragma omp master {
	        while (op  && i < 50) {
	            for (j = 0; j < 10000; j++) {
	                if (a[i][j] == target) {
	                    coord[0] = i;
	                    coord[1] = j;
	                    op = 0;
	                }
	            }
	            i++;
	        }
	    }
	}


    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec- tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1e-6;
    printf("elapsed time = %f seconds. \n", elapsed);
    cout << y[0] << ", " << y[1] << ", "<<y[2] << endl;
    return 0;
}
