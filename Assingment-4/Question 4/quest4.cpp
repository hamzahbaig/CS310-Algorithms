#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string> result_string;
bool result = false;

bool checkValid(string s1, string s2, string s3)
{
	if(s3.length() == 0)
	{
		return result;
	}
	else
	{
		if(s3[0] == s1[0])
		{
			string temp = "S1: ";
			temp = temp + s1[0];
			result = true;
			int i;
			for(i=1; i< s1.length(); i++)
			{
				if(s3[i] != s1[i])
				{
					break;
				}
				temp = temp + s1[i];
			}
			result_string.push_back(temp);
			checkValid(s1.substr(i),s2,s3.substr(i));
		}
		else if(s3[0] == s2[0])
		{
			string temp = "S2: ";
			temp = temp + s2[0];
			result = true;
			int i;
			for(i=1; i< s2.length(); i++)
			{
				if(s3[i] != s2[i])
				{	
					break;
				}
				temp = temp + s2[i];
			}
			result_string.push_back(temp);
			checkValid(s1,s2.substr(i),s3.substr(i));
		}
		else
		{
			result = false;
		}
	}
	return result;
}

void reading_file(string filename,string& s1, string& s2, string& s3)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());	if(s2=="-")
	{
		s2 = "";
	}
	fout >> s3;

}

int main()
{
	// string s1 = "at";
	// string s2 = "xe";
	// string s3 = "xate";
	string s1,s2,s3,filename;
	cout << "Enter filename: ";
	cin >> filename;
	reading_file(filename,s1,s2,s3);

	fout >> s1;
	fout >> s2;
	if(checkValid(s1,s2,s3))
	{
		cout << "VALID!!" << endl;
		for(int i=0; i< result_string.size(); i++)
			{
				cout << result_string[i] << " " ;
			}
	}
	else
	{
		cout << "INVALID!!";
	}	

}