#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Description of my code 
//
// First i read the file and store the row entries in a row array and the 
// and coloumn entries in coloumn array then for each array ith element i do greedy search and find the
// column whose priority (no of game pieces are max) and fills a 2D array. I keep this thing go on untill all row and column array
// entries go to zero.

// DATA STRUCTURES:
// 1D heap array for row
// 1D heap array for column
// 2D heap array for game_board


// Order of Complexity : O(n^3)
// Space Complexity : O(n^2)

void creatring2Darray(int total_entries, char **&game_board)
{
	game_board = new char*[total_entries];

	for(int i = 0; i<total_entries; i++)
	{
		game_board[i] = new char[total_entries];
	}

	for(int i=0 ; i<total_entries;i++)
	{
		for(int j=0; j<total_entries; j++)
		{
			game_board[i][j] = '-';
		}
	}
}

void print2DArray(char **array, int size)
{

	for(int i =0 ; i< size; i++)
	{
		for(int j =0 ; j < size ;j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

int largest_index(int *col, int total_entries,char **game_board, int row)
{
	int max = 0,index=0;
	//int index = 0;
	for(int i =0 ; i < total_entries ; i ++)
	{
		if(col[i] > max && game_board[row][i] != '*' )
		{
			max = col[i];
			index = i; 
		}
	}
	return index;
}


void game_board_fill(int*&row, int*&col, int total_entries, char **&game_board)
{

	creatring2Darray(total_entries,game_board);
	int index;
	for(int i =0 ;i < total_entries ;i++)
	{
		int cond = row[i];
		for(int j =0 ; j <cond; j++)
		{
			if(row[i] > 0)
			{
				index = largest_index(col,total_entries,game_board, i);
				game_board[i][index] = '*';
				row[i]--;
				cout << "(" << i+1 << "," <<index+1<<")";
				col[index]--;
				
			} 
		}
		cout << endl;
	}
	cout << endl;
	print2DArray(game_board,total_entries);
	
}
void reading_file(string filename, int &total_entries, int *&row, int *&col)
{
	ifstream fout;
	filename = filename + ".txt";
	fout.open(filename.c_str());
	int counter = 0;
	string read_value;
	for(int i = 0; i<3;i++)
	{
		if(counter == 0)
		{
			char temp;
			fout >> temp;
			fout >> total_entries;
			cout << "Total Entries: " << total_entries << endl;
			row = new int[total_entries];
			col = new int[total_entries];
			counter++;
		}
		else
		{
			fout >> read_value;
			if(read_value == "Row")
			{
				for(int i =0 ; i<total_entries; i++)
				{
					int val;
					fout >> val;
					row[i] = val;
				}
			}
			else
			{
				for(int i =0 ; i<total_entries; i++)
				{
					int val;
					fout >> val;
					col[i] = val;
				}
			}
		}
	}
}

int main()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	int total_entries;
	int *row;
	int *col;
	char **game_board;
	reading_file(filename,total_entries,row,col);
	cout << endl;
	

	game_board_fill(row,col,total_entries,game_board);
}