#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


/// DESCRIPTION OF MY CODE
//
// first i do the file reading and store the number of stations in an array
// then using basic maths calculate the kms the car can move on the basis of given
// info that is T,R,F after that i use loop till i reach the Hospital and whenever petrol is about to finish
// i loop through the stations array and compute the closest and ecnomical stations(greedy algorithm) and keep check whether 
// i have covered the required distance.


// Order of Complexity: O(n^2)
// Space Complexity: O(n)

// DATA STRUCTURES USED
// single dimensional heap array.

int closest_station(double kms,int no_of_stations, int *&petrol_stations, int start)
{
	double diff = (kms - petrol_stations[start]);
	double closest = petrol_stations[start];
	int index = start;
	for(int i =start ; i < no_of_stations; i++)
	{
		if((kms - petrol_stations[i]) < diff && (kms - petrol_stations[i]) >= 0) 
		{
			diff = (kms - petrol_stations[i]);
			closest = petrol_stations[i];
			index = i;
		}

	}

	return index;
}

double calculate_min_time(int &no_of_stations,string filename,int &F,int &R,int &T,int &totalDistance,int *&petrol_stations)
{
	int fuelCap = T;
	int fuelUsed = T;
	int fuelLeft = T;
	double kms = (double) T/R;
	double totalTime = 0.0;
	int index,start = 0;
	int previous_stop = 0;
	double remaining_distance = totalDistance;
	double distance_covered = 0;
	while(remaining_distance * R > fuelCap)
	{
		index = closest_station(kms,no_of_stations,petrol_stations,start);
		distance_covered = petrol_stations[index]-previous_stop;
		cout << "L" << index+1 << " " << petrol_stations[index] << endl;
		remaining_distance = totalDistance - petrol_stations[index];
		fuelUsed = (distance_covered * R);
		fuelLeft = T-fuelUsed;
		start = index+1;

		if(remaining_distance * R > fuelCap)
		{
			totalTime += (double) (fuelUsed)/F;
			cout << totalTime << endl;
		
			kms += (double) distance_covered;
		}
		else
		{
			break;
		}
		
		previous_stop += distance_covered;

		

	}
	return totalTime += (double) (remaining_distance*R-(fuelLeft))/F;


	

}



void reading_file(int &no_of_stations,string filename,int &F,int &R,int &T,int &totalDistance,int *&petrol_stations)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	int counter = 0;
	while(fout)
	{
		string temp;
		fout >> temp;
		fout >> T;
		fout >> temp;
		fout >> R;
		fout >> temp;
		fout >> F;
		fout >> temp;
		fout >> no_of_stations;
		petrol_stations = new int[no_of_stations];
		for(int i =0; i< no_of_stations; i++)
		{
			fout >> temp;
			int val;
			fout >> val;
			petrol_stations[i] = val;
		}
		fout >> temp;
		fout >> totalDistance;
		break;
	}

	
}

int main()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	int F;
	int R;
	int T;
	int totalDistance;
	int no_of_stations;
	int *petrol_stations;

	reading_file(no_of_stations,filename,F,R,T,totalDistance,petrol_stations);
	
	double totalTime = calculate_min_time(no_of_stations,filename,F,R,T,totalDistance,petrol_stations);
	cout << "TotalTime: " << totalTime << endl;
}