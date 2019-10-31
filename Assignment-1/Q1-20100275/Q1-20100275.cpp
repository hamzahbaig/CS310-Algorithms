#include<iostream>
#include<fstream>
#include <ctype.h>
#include <string>
#include<vector>

using namespace std;

// First i am reading the file and storing the chemicals and chemicals with which they react in a 2D array.
// In this 2D array am storing the chemcials at i index and chemicals with which they react at j index.
// I loop through the all chemicals.. I pick one chemical and put in one empty box because for first iteration both boxes would be empty
// Then at next iteration i pick the chemical from the list and see wheter it fits in first box or in second box. So for one chemical i linearly check all
// chemicals already there in the box.. and to check that wheter they react or not i acces the 2D array which is a constant time access.

// ORDER OF COMPLEXITY : O (N^2) Where N is the number of chemicals.  
// SPACE COMPLEXITY : O(N^2)
void making_2D_array(int total_chemicals,char **&chemicals_array) {

	chemicals_array = new char*[total_chemicals];

	for(int i =0 ; i< total_chemicals ; i++) {

		chemicals_array[i] = new char[total_chemicals];
	}
}

void filling_up_the_chemicals(char **&chemicals_array,char chemicals, string reactive_chemicals) {
	
	if(reactive_chemicals != "") {
		int chemical = (chemicals-48); // chemical
		int danger; // to which it is reactive
		string to_react;
		to_react = reactive_chemicals.substr(2,1);
		danger =(to_react[0]-48);
		
		chemicals_array[chemical][danger] = 'Y';

		while(reactive_chemicals.substr(3,1) != "") {
			
			reactive_chemicals = reactive_chemicals.substr(4);
			to_react = reactive_chemicals.substr(2,1);
			danger = (to_react[0] - 48);

			chemicals_array[chemical][danger] = 'Y';
		}
	}
}

int reading_file(string filename, char **&chemicals_array) {

	string chemicals;
	string reactive_chemicals;
	ifstream fout; 
	fout.open(filename + ".txt");
	int counter = 0;
	int total_chemicals;

	while (fout) {

		if (counter == 0) {

			char temp;
			fout >> temp;
			counter ++;
		}
		else if (counter == 1) {

			fout >> total_chemicals;
			making_2D_array(total_chemicals,chemicals_array);
			counter++;
		}
		else {

			fout >> chemicals;
			getline(fout,reactive_chemicals);
			filling_up_the_chemicals(chemicals_array,chemicals[1],reactive_chemicals);
		}
	}
	return total_chemicals;
}


string check_which_box(int chemical, char **&chemicals_array, vector<int>&box) {

	for(int i =0 ; i < box.size() ; i++) {

		if(chemicals_array[chemical][box[i]] ==  'Y') {
			return "colision";
		}
	}
	return "no colision";
	
}



string putting_into_boxes(vector <int> &history, int total_chemicals,char **&chemicals_array, vector<int>& box1, vector<int>& box2) {

	string result = "Yes";
	for(int i =0 ; i <total_chemicals; i++) {

		string check_box1 = check_which_box(i,chemicals_array,box1);
		string check_box2 = check_which_box(i,chemicals_array,box2);

		if (check_box1 == "no colision" && check_box2 == "no colision") {
			history.push_back(i);
			box1.push_back(i);
		}

		else if(check_box1 == "colision" && check_box2 == "no colision") {
			history.push_back(i);
			box2.push_back(i);
		}

		else if (check_box1 == "no colision" && check_box2 == "colision") {
			history.push_back(i);
			box1.push_back(i);
		} 

		else if (check_box1 == "colision" && check_box2 == "colision") {

			history.push_back(i);
			result = "No";


		}
	}

	return result;

}

void printing_the_box_elements(vector<int>box) {

	for (int i=0; i < box.size() ; i++ ) {

		cout << "C" << box[i] << ", ";
	}
	cout << endl;
}



int main() 
{
	char **chemicals_array;
	int total_chemicals;
	string filename;
	string result;
	
	cout << "Enter filename: ";
	cin >> filename;
	total_chemicals = reading_file(filename, chemicals_array);
	vector<int> box1;
	vector<int> box2;

	cout << "TOTOAL CHWEMICALS= " << total_chemicals  << endl << endl;


	vector<int> history ;
	result = putting_into_boxes(history, total_chemicals,chemicals_array, box1, box2);

	if (result == "Yes") {

		cout << result << endl;
		printing_the_box_elements(box1);
		printing_the_box_elements(box2);

	} else if (result == "No") {

		cout << result << endl;
		int len = history.size();
		for (int i =0 ; i < len; i++ ) {
			if (i == len - 1) {
					cout << "(C" << i << " could not be placed in any box because it reacts with one of the chemicals present in both boxes.)";
			}
			else {
				cout << "C" << i << "->" ;
			}
		}
	}


}