#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

#define N 8
double A[N][N];
double b[N];
double x[N];
double new_x[N];
int mab_iter;
double norm;

double rand_num() {
    int rand_num = rand() % 10000;
    return rand_num/10000.0;
}

void print_mat() {
    cout << "A : " << endl;
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
	        cout << A[i][j] << " ";
	    }
	    cout << endl;
	}
	cout << "b : " << endl;
	for (int i = 0; i < N; i ++) {
	    cout << b[i] << " ";
	}
	cout << endl;

	cout << "x : " << endl;
	for (int i = 0; i < N; i++) {
	    cout << x[i] << " ";
	}
	cout << endl;
}

// Ax = b
int main() {
	struct timeval tv1, tv2;
	struct timezone tz;
	double elapsed;
	mab_iter = 200;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			A[i][j] = rand_num();
		}
		b[i] = rand_num();
	}

	for (int i = 0; i < N; i++) {
	    double sum = 0;
	    for (int j = 0; j < N; j++) {
	        sum += A[j][i];
	    }
	    A[i][i] = sum;
	}

    gettimeofday(&tv1, &tz);
    int itr = 1;
    while (itr < mab_iter) {
        #pragma omp parallel
        {
            int i, k;
            double sum;
            #pragma omp for private(sum)
            for (i=0; i < N; i++) {
                sum = 0.0;
                for (k = 0; k < N; k++) {
                    if (k != i) {
                        sum += A[i][k]*x[k];
                    }
                }
                new_x[i] = (b[i] - sum)/A[i][i];
            }

            norm = 0;
            #pragma omp for private(i)
            for (i = 0; i < N; i++) {
                norm += (x[i] - new_x[i])*(x[i] - new_x[i]);
                x[i] = new_x[i];
            }
        }
        itr++;
    }
    cout << norm << endl;
    cout << "iteration: " << itr << endl;
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec- tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1e-6;
    printf("elapsed time = %f seconds. \n", elapsed);

    print_mat();
    return 0;
}
