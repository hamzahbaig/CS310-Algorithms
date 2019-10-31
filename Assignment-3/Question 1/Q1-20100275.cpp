#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// DESCRIPTION OF CODE
// SPACE COMPLEXITY O(n^2)
// TIME COMPLEXITY O(n^2)

// USED GALLE-SHAPELY ALGORITHM

// I AM USING 2D ARRAY ONE 2D ARRAY IS FOR PLANES PREFERENCES AND ONE 2D ARRAY
// IS FOR AIRPORTS. THEN FREE AIRPORTS WILL PROPOSE THE PLANES AND USING THE STABLE MATCHING PROBLEM 
// THAT IS IF PLANES GET BETTER PROPOSAL THEY REJECT THE CURRENT PROPOSAL 
// AND ACCEPT THE NEW PROPOSAL AND IF NEW PROPOSAL IS NOT BETTER THAN CURRENT POPOSAL
// THEN RETAIN THE CURRENT PROPOSAL.
// KEEP RUNNING WHILE ALL THE ENTRIES ARE MAPPED.

bool itsBetter(int** planes,int current_airport,int airport,int plane,int total_entries)
{
	
	for(int i=0; i<total_entries;i++)
	{
		if(planes[plane][i] == airport+1)
		{
			return true;
		}
		if(planes[plane][i] == current_airport+1)
		{
			return false;
		}
	}
}

int extractingNumber(string a)
{
	if(a.length() == 2)
	{
		return stoi(a.substr(1,a.length()-1));
	}
	else
	{
		return stoi(a.substr(1,a.length()-2));
	}
}

void fillingUpTheArray(ifstream &fout, int **&TwoDArray, int total_entries)
{

	for(int i=0; i < total_entries; i++)
	{
		string entry;
		fout >> entry;
		for(int j=0; j < total_entries; j++)
		{
			string prefered_entry;
			fout >> prefered_entry;
			TwoDArray[i][j] = extractingNumber(prefered_entry);
		}
	}
}

void initalisingArrays(int **&planes, int **&airports, int &total_entries, int *&danger)
{
	danger = new int[total_entries];
	planes = new int*[total_entries];
	airports = new int*[total_entries];
	for(int i=0; i< total_entries; i++)
	{
		danger[i] = -1;
		planes[i] = new int[total_entries];
		airports[i] = new int[total_entries];
	}
}

void reading_file(string filename, int **&planes, int **&airports, int &total_entries, int *&danger)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	string temp;
	string dangerEntries;
	fout >> temp;
	fout >> total_entries;
	cout << "Total Entries: " << total_entries << endl;

	initalisingArrays(planes,airports,total_entries,danger);
	
	fillingUpTheArray(fout, planes, total_entries);
	fillingUpTheArray(fout, airports, total_entries);
	fout >> temp;
	while(fout >> dangerEntries)
	{
		int i;
		int value;
		i = extractingNumber(dangerEntries)-1;
		fout >> dangerEntries;
		value = extractingNumber(dangerEntries);
		danger[i] = value;
	}


}

int* stableMatching(int **airports, int**planes, int total_entries, int*danger)
{
	int *pairs =new int[total_entries];
	int freeAirports[total_entries];
	for(int i=0 ; i<total_entries; i++)
	{
		freeAirports[i] = true;
		pairs[i] = -1;
	}
	int freeCount = total_entries;
	while(freeCount > 0)
	{
		int airport;
		for(airport=0; airport <total_entries; airport++)
		{
			if(freeAirports[airport] == true)
			{
				break;
			}
		}

		for(int j=0; j < total_entries; j++)
		{
			int plane = airports[airport][j]-1;

			if(pairs[plane] == -1)
			{
				if(airport != danger[plane]-1)
				{
					pairs[plane] = airport+1;
					freeAirports[airport] = false;
					freeCount--;
					break;
				}
				else
				{
					continue;
				}
				
			}
			else
			{
				int current_airport = pairs[plane]-1;

				if(itsBetter(planes,current_airport,airport,plane,total_entries) && airport != danger[plane]-1)
				{
					pairs[plane] = airport+1;
					freeAirports[airport] = false;
					freeAirports[current_airport] = true;
					break;
				}
			}
			
		}
	}
	return pairs;
}

void printing(int *pairs,int total_entries)
{
	for(int i=0; i<total_entries;i++)
	{
		for(int j=0 ; j<total_entries; j++)
		{
			if(i+1 == pairs[j])
			{
				cout << "A" << i+1 << "   P" << j+1 << endl; 
				break;	
			}
		}
	}
}
int main()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	int **planes;
	int **airports;
	int *danger;
	int total_entries;
	reading_file(filename,planes,airports,total_entries, danger);

	cout << endl;
	int *pairs = stableMatching(airports,planes,total_entries,danger);

	cout << "----- STABLE MATCHING ------" << endl;
	
	printing(pairs,total_entries);

	//cout << "P" << i+1 << "   A" << pairs[i] << endl;


}