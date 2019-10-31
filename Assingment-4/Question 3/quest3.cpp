#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;
vector<int> S1;
vector<int> S2;
int Sum1 = 0;
int Sum2 = 0;
bool result = false;

bool findDifference(vector<int>myArray, int size, int diff,int index,int sum1,int sum2)
{
	if(index == size)
	{
		if(abs(sum1-sum2) == diff)
		{
			Sum1 = sum1;
			Sum2 = sum2;
			result = true;
		}
	}
	else
	{
		bool cond1,cond2;
		S1.push_back(myArray[index]);
		cond1 = findDifference(myArray,size,diff,index+1,(sum1+myArray[index]),sum2);
		if(!cond1)
		{
			S1.pop_back();
			S2.push_back(myArray[index]);
			cond2 = findDifference(myArray,size,diff,index+1,sum1,sum2+myArray[index]);
			if(!cond2)
			{
				S2.pop_back();
			}
		}
	}
	return result;
	 
}
void reading_file(string filename,vector<int> & myArray,int& diff, int& size)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	string temp;
	fout>>temp;
	fout >> diff;
	fout >> temp;
	int value;
	while(fout>>value)
	{
		size++;
		myArray.push_back(value);
	}

}

int main()
{
	int diff;
	vector<int> myArray;
	int size=0;
	string filename;
	bool result;
	cout << "Enter Filename: ";
	cin >> filename;
	reading_file(filename,myArray,diff,size);
	result = findDifference(myArray,size,diff,0,0,0);
	if(result)
	{
		cout << "POSSIBLE" << endl;
		cout << "S1: ";
		for(int i=0; i< S1.size(); i++)
		{
			cout << S1[i] << " ";
		}
		cout << " --> SUM1: " << Sum1 << endl;
		cout << "S2: ";
		for(int i=0; i< S2.size(); i++)
		{
			cout << S2[i] << " ";
		}
		cout << " --> SUM2: " << Sum2 << endl;
		cout << "Difference: " << Sum1 << "-" << Sum2 << " = " << abs(Sum1-Sum2);
	}
	else
	{
		cout << "NOT POSSIBLE!!" << endl;
	}

}


