#include <iostream>
#include <fstream>
using namespace std;

int *lookUp;
string *description;
int maxRevenueValue = 0;

void utiliyFunc(int* RH, int* RL, int size, int index)
{
	if(RH[index] > RL[index])
	{
		lookUp[index] = RH[index];
		description[index] = "High";
		maxRevenueValue = maxRevenueValue + RH[index];
	}
	else
	{
		lookUp[index] = RL[index];
		description[index] = "Low";
		maxRevenueValue = maxRevenueValue + RL[index];
	}

}
void setter(int*RH, int*RL, string signal,int index)
{
	if(signal == "Low")
	{
		lookUp[index] = RL[index];
		description[index] = "Low";
		maxRevenueValue = maxRevenueValue + RL[index];
	}
	else if(signal == "High")
	{
		lookUp[index] = RH[index];
		description[index] = "High";
		maxRevenueValue = maxRevenueValue + RH[index];
		lookUp[index-1] = -1;
		description[index-1] = "Priming"; 
	}
}
void maxRevenue(int* RH,int* RL,int size,int index)
{
	if(index == 0)
	{	
		if(size == 1)
		{
			utiliyFunc(RH,RL,size,index);
		}
		if(lookUp[index] != -1)
		{
			utiliyFunc(RH,RL,size,index);
		}
	}

	else
	{	
		if(lookUp[index] == -1)
		{
			maxRevenue(RH,RL,size,index-1);
		}
		else if(RL[index] > RH[index])
		{
			setter(RH,RL,"Low",index);
			maxRevenue(RH,RL,size,index-1);
		}
		else if(RH[index] < RH[index-1])
		{
			if(index != 1)
			{
				if(RH[index-1] > (RH[index] + RL[index-2]) && RH[index-1] < (RH[index] + RH[index-2]))
				{

					setter(RH,RL,"High",index); 
					maxRevenue(RH,RL,size,index-1);
				}
				else if(RH[index] + RL[index-2] > RL[index] + RH[index-1])
				{
					setter(RH,RL,"High",index);  
					maxRevenue(RH,RL,size,index-1);
				}
				else
				{				
					setter(RH,RL,"Low",index); 
					maxRevenue(RH,RL,size,index-1);
				}
			}
			else
			{
				setter(RH,RL,"Low",index); 
				maxRevenue(RH,RL,size,index-1);
			}		
			
		}
		else if(RH[index] > (RL[index] + RL[index-1]))
		{
				setter(RH,RL,"High",index); 
				maxRevenue(RH,RL,size,index-1);
		}
		else
		{
			setter(RH,RL,"Low",index); 
			maxRevenue(RH,RL,size,index-1);
		}
	}
}

void reading_file(string filename, int*& RH, int*&RL, int& size)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	string temp;
	fout >> temp;
	fout >> size;
	RH = new int[size];
	RL = new int[size];
	fout >> temp;
	for(int i =0 ; i < size ;i++)
	{
		fout >> RH[i];
	}
	fout >> temp;
	for(int i =0 ; i < size ;i++)
	{
		fout >> RL[i];
	}

	
}

void initalising(int* &lookUp,int size)
{
	for(int i=0; i< size;i++)
	{
		lookUp[i] = 0;
	}
}
int main()
{
	string filename;
	int *RH;
	int *RL;
	int size;
	cout << "Enter Filename: ";
	cin >> filename;
	reading_file(filename,RH,RL,size);

	lookUp = new int[size];
	initalising(lookUp,size);
	description = new string[size];

	maxRevenue(RH,RL,size,size-1);

	for(int i=0;i<size;i++)
	{
		cout << "Week " << i+1 <<  " " <<  description[i] << ": " << lookUp[i] << endl;
	}
	cout << "MaxRevenue : " << maxRevenueValue;

}