#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// DESCRIPTION OF CODE
// SPACE COMPLEXITY O(n^2)
// TIME COMPLEXITY O(n^2)
// 
// ALGORITHM IS SAME AS QUEST1 
// USING GALLE-SHAPELY ALGORITHM

bool itsBetter(int **teams,int current_locaion,int locaion,int team,int total_entries)
{
	
	for(int i=0; i<total_entries;i++)
	{
		if(teams[team][i] == locaion+1)
		{
			return true;
		}
		if(teams[team][i] == current_locaion+1)
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



int* stableMatching(int **locations, int **teams, int total_entries)
{
	int *pairs =new int[total_entries];
	int freeLocations[total_entries];
	for(int i=0 ; i<total_entries; i++)
	{
		freeLocations[i] = true;
		pairs[i] = -1;
	}
	int freeCount = total_entries;
	while(freeCount > 0)
	{
		int locaion;
		for(locaion=0; locaion <total_entries; locaion++)
		{
			if(freeLocations[locaion] == true)
			{
				break;
			}
		}

		for(int j=0; j < total_entries; j++)
		{
			int team = locations[locaion][j]-1;

			if(pairs[team] == -1)
			{
				pairs[team] = locaion+1;
				freeLocations[locaion] = false;
				freeCount--;
				break;
			}
			else
			{
				int current_locaion = pairs[team]-1;

				if(itsBetter(teams,current_locaion,locaion,team,total_entries))
				{
					pairs[team] = locaion+1;
					freeLocations[locaion] = false;
					freeLocations[current_locaion] = true;
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
				cout << "L" << i+1 << "   T" << j+1 << endl; 
				break;	
			}
		}
	}
}


void initalisingArrays(int **&locations, int **&teams, int &total_entries)
{
	locations = new int*[total_entries];
	teams = new int*[total_entries];
	for(int i=0; i< total_entries; i++)
	{
		locations[i] = new int[total_entries];
		teams[i] = new int[total_entries];
	}
	for(int i=0;i<total_entries;i++)
	{
		for(int j=0; j<total_entries; j++)
		{
			locations[i][j] = -1;
		}
	}
}

void initalisingTeamsArray(ifstream &fout, int **&teams, int total_entries)
{
	string temp;
	for(int k=0 ;k<total_entries;k++)
	{
		fout >> temp;
		int i = extractingNumber(temp)-1;
		int j=0;
		for(int l=0; l<total_entries*2;l++)
		{
			fout >> temp;
			if(temp != "-," && temp!= "-")
			{
				int value = extractingNumber(temp);
				teams[i][j] = value;
				j++;
			}
		}
	}
}

int freeSlot(int **locations, int k,int total_entries)
{
	for(int i= total_entries-1; i >=0; i--)
	{
		if(locations[k][i] == -1)
		{
			return i;
		}
	}
}

void initalisingLoactionArray(int **&locations,int **teams, int total_entries)
{
	for(int i=0; i< total_entries;i++)
	{
		for(int j=0; j<total_entries; j++)
		{	
			int k = teams[j][i] - 1;
			int l = freeSlot(locations,k,total_entries);
			locations[k][l] = j+1;

		}
	}
}

void reading_file(string filename, int **&locations, int **&teams, int &total_entries)
{
	filename = filename + ".txt";
	ifstream fout;
	fout.open(filename.c_str());
	string temp;
	fout >> temp;
	fout >> total_entries;
	cout << "Total Entries: " << total_entries << endl;

	initalisingArrays(locations,teams,total_entries);
	
	initalisingTeamsArray(fout, teams, total_entries);
	
	initalisingLoactionArray(locations,teams,total_entries);
	
}

int main()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	int **locations;
	int **teams;
	int total_entries;
	reading_file(filename,locations,teams,total_entries);


	cout << endl;
	int *pairs = stableMatching(locations,teams,total_entries);

	cout << "----- STABLE MATCHING ------" << endl;
	
	printing(pairs,total_entries);

	// cout << "P" << i+1 << "   A" << pairs[i] << endl;


}