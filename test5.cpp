#include <iostream>
#include <iomanip>
#include "SnakeMatrix.h"

#define M 5
#define N 6

using namespace std;

int main(int argc, char* argv[])
{
	int **A = new int *[M];
	for( int i=0; i<M; i++)
	{
		A[i] = new int[N];
	}

	Solution(M,N,A);

	cout << "snake matrix: " << endl;
	for( int i=0; i<M; i++)
	{
		for( int j=0; j<N; j++)
			cout << setw(4) << A[i][j] <<' ';
		cout << endl;
	}
	return 0;
}
