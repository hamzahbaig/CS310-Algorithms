#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Description of code
// 
// First i read the file and store the probablities and Length in an array then 
// i compute (Length/Prob) and store the results for each entry in an array
// then i used the greedy algorithm that is pick the entry with the smallest value which means filling that rack
// has highest probablity. 
// When i get the order of rack
// i use nested loop the compute the calculations by using the formula given in handout


// Order of complexity for ordering of racks: O(n)
// Order of complexity for calulcating the time: O(n^2)// Description of code

// Space of Complexity: O(n)

void reOrdering(int totalEntries,int *&dummyLen,double *&dummyProb,int *len, double *prob,int *rackOrder)
{
	for(int i = 0 ; i < totalEntries; i++)
	{
		dummyLen[i] = len[rackOrder[i]-1];
		dummyProb[i] = prob[rackOrder[i]-1];

	}
}

double timeCalculation(int totalEntries,int *len,double *prob,int *rackOrder)
{	
	int *dummyLen = new int[totalEntries];
	double *dummyProb = new double[totalEntries];

	reOrdering(totalEntries,dummyLen,dummyProb,len,prob,rackOrder);

	cout << endl;

	double finalTime =0.0;
	cout << endl;
	for(int i =0; i<totalEntries;i++)
	{
		double sum_of_len = dummyLen[i];
		for(int j=0 ; j <i; j++)
		{
			sum_of_len += dummyLen[j];
		}
		double p = dummyProb[i];
		finalTime += (p*sum_of_len);
	}

	return finalTime;
}

int minFindOnCond(double *probArray,int totalEntries,char *tempArray)
{
	double min;
	int index;
	for(int i =0 ; i< totalEntries;i++)
	{
		if(tempArray[i] != '*')
		{
			min = probArray[i];
			index = i;
			break;
		}
	}
	for(int i = 0; i < totalEntries; i++)
	{

		if(probArray[i] < min && tempArray[i] != '*')
		{
			min = probArray[i];
			index = i;
		}
	}
	return index;
}

void rackOrderCal(int totalEntries,int* len,double* prob, int*&rackOrder)
{
	char *tempArray = new char[totalEntries];
	double *probArray = new double[totalEntries];
	for(int i =0; i< totalEntries; i++)
	{
		probArray[i] = len[i]/prob[i];
		tempArray[i] = '-';
	}
	cout << endl;
	for (int i =0 ; i< totalEntries; i++)
	{
		int index = minFindOnCond(probArray,totalEntries,tempArray);
		tempArray[index] = '*';
		rackOrder[i] = index +1;
	}
	
}

void reading_file(string filename,int &totalEntries,int *&len,double *&prob)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	string read_value;
	for(int i=0; i <2; i++)
	{
		if(i == 0)
		{
			char temp;
			fout >> temp;
			fout >> totalEntries;
			len = new int[totalEntries];
			prob = new double[totalEntries];
		}
		else
		{
			fout >> read_value;
			for(int i = 0 ; i<totalEntries;i++)
			{
				int val;
				char temp;
				fout >> val;
				fout >> temp;
				len[i] = val;
			}
			for(int i = 0 ; i< totalEntries; i++)
			{
				double val;
				char temp;
				fout >> val;
				fout >> temp;
				prob[i] = val;
			}
		}
	}
}

int main()
{

	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	int totalEntries;
	int *len;
	double *prob;
	int *rackOrder;

	reading_file(filename,totalEntries,len,prob);
	cout << "totalEntries: " << totalEntries << endl;
	
	rackOrder = new int[totalEntries];
	rackOrderCal(totalEntries,len,prob,rackOrder);

	cout << endl <<  "------ ORDERING OF RACK ------" << endl;
	for (int i =0; i< totalEntries; i++)
	{
		cout << "RackNo: " << rackOrder[i] << endl;
	}

	double finalTime = 	timeCalculation(totalEntries,len,prob,rackOrder);

	cout << "Final Time: " << finalTime << endl;


}