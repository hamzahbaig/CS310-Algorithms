#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
struct Co_oridnates
{
	int row;
	int col;
};

vector<Co_oridnates> points;
vector<int> sums;


void print(int **sq, int size)
{
	for(int i=0; i< size; i++)
	{
		for(int j=0 ; j<size ; j++)
		{
			cout << sq[i][j] << " ";
		}
		cout << endl;
	}
}

Co_oridnates findMaxSumSubMatrix(int **sq, int k, int n)
{
	int sum[n][n];
	sum[0][0]  = sq[0][0];

	for(int i=1 ; i<n; i++)
	{
		sum[0][i] = sq[0][i] + sum[0][i-1];
	}

	for(int i = 1; i <n; i ++)
	{
		sum[i][0] = sq[i][0] + sum[i-1][0];
	}

	for(int i = 1; i <n; i++)
	{
		for(int j=1; j <n; j++)
		{
			sum[i][j] = sq[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}

	int total;
	int maximum = -9999999;
	Co_oridnates point;

	for(int i= k -1 ; i<n; i++)
	{
		for(int j = k-1; j<n; j++)
		{
			total = sum[i][j];
			if(i-k >=0)
			{
				total = total - sum[i-k][j];
			}
			if(j-k >=0 )
			{
				total = total - sum[i][j-k];
			}
			if(i-k>=0 && j-k >=0)
			{
				total = total + sum[i-k][j-k];
			}
			if(total > maximum)
			{
				maximum = total;
				point.row = i;
				point.col = j;
			}
		}
	}

	sums.push_back(maximum);
	return point;
}

void maximum_sum(int n)
{
	int max = sums[0];
	int index = 0;
	for(int i=0; i < n; i++)
	{
		if(sums[i] > max)
		{
			max = sums[i];
			index = i;
		}
	}

	cout << endl << "Top Right: (" << points[index].row-index << "," << points[index].col - index << ")" << endl; 
	cout << "Bottom Right: (" << points[index].row << "," << points[index].col << ")" << endl;
	cout <<endl<< "SUMS IS: " << sums[index]<< endl;
}

void reading_file(string filename, int &n, int** & sq)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());

	string temp;
	fout >> temp;
	fout >> n;
	int value;
	sq = new int*[n];
	for(int i= 0 ; i<n;i++)
	{
		sq[i] = new int[n];
	}
	fout >> temp;
	for(int i=0; i < n; i++)
	{
		for (int j=0 ; j<n ;j++)
		{
			fout >> sq[i][j];
			fout >> temp;
		}
	}
	


}
int main()
{
	int n;
	int **sq;
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	reading_file(filename,n,sq);
	// int sq[5][5] = { {1,8,33,-1,20},
	// 			{-10,2,23,-7,27},
	// 				{-27,8,6,7,32},
	// 				{-25,4,-67,4,4},
	// 				{3,11,5,4,5} };

	cout << "Total " << n << endl;
	print(sq,n);

	for(int i=1; i <= 5; i++)
	{
		points.push_back(findMaxSumSubMatrix(sq,i,n));
	}
	maximum_sum(n);

	// for(int i =0 ; i<5; i++)
	// {
	// 	cout << points[i].row << " " << points[i].col << " Sum: " << sums[i] << endl;
	// }
	



}