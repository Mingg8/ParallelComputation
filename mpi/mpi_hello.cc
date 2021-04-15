#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    cout << "hello" << endl;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        cout << "Hello, world! :from " << size << "processes" << endl;
    }
    MPI_Finalize();
    return 0;
}