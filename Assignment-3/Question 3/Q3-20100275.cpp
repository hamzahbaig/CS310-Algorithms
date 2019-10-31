#include <iostream>
#include <math.h>
#include <vector>
using namespace std;





// CODE DESCRIPTION..
// ORDOER OF COMPLEXITY O(n^2)
// SPACE COMPLEXITY O(n^2)

// RECURRANCE RELATION
// -> BASE CASE (n == 2) => c
//   			(n  > 2) => T(n) = 4T(n/2) + c



// FIRST WE HAVE A SQUEARE AND THEN WE DETECT THE DEFECTIVE BOX AND THEN WE ADD
// FAKE DEFECTIVE PIECES AND OTHER QUADRANT SO WE HAV SIMILAR PROBLEMS AND THEN USINGN POWER OF 
// DIVIDE AND CONQUER WE SOLVE THOSE SUBPROBLEMS AND GET SUB SOLUTIONS.
// COMBINING THOSE SUB SOLUTIONS WE GET FINAL BOARD WITH RIGHT ANGLES AND ONE DEFECTIVE BOX
char ch = 64;

void insert(char **gameboard, int row1, int col1, int row2, int col2, int row3, int col3)
{
	ch++;
	gameboard[row1][col1] = ch;
	gameboard[row2][col2] = ch;
	gameboard[row3][col3] = ch;


}

void initialisingBoard(char**&gameBoard, int n,int row, int col)
{
	gameBoard = new char*[n];
	for(int i=0; i<n;i++)
	{
		gameBoard[i] = new char[n];
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0; j<n ;j++)
		{
			if(i == row && j == col)
			{
				gameBoard[i][j] = '*';
			}
			else
			{
				gameBoard[i][j] = '-';
			}
		}
	}
}


void print(char **gameBoard, int n)
{
	cout << endl << "--- GAME BOARD ----" << endl;
	cout << endl << "  ";
	for(int i=0; i<n;i++)
	{
		cout << i << " ";
	}
	cout << endl;
	for(int i=0; i<n;i++)
	{
		cout << i << " ";
		for(int j=0 ;j<n;j++)
		{
			cout << gameBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void filingBoard(char **gameBoard,int row, int col, int n, int bb_r, int bb_c,int row1,int col1)
{

	if(n == 2)
	{
		ch++;
		for(int i=0; i < n; i++)
		{
			for(int j= 0; j<n ;j++)
			{
				if(gameBoard[i+row][j+col] == '-')
				{
					gameBoard[i+row][j+col] = ch;
					
				}
			}
		}
		return;
	}
	
	// finding the defective piece.
	for(int i=row; i<row1;i++)
	{
		for(int j=col; j<col1;j++)
		{
			if(gameBoard[i][j] != '-')
			{

				bb_r = i;
				bb_c= j;
			}
		}
	}

	// 1st Quadrant
	if(bb_r < row +n/2 && bb_c >= col+ n/2)
	{
		//cout << "1st Quadrant" << endl;
		insert(gameBoard, row + (n/2) -1,col + (n/2) -1, row+ n/2, col + (n/2) -1, row + n/2, col + n/2);
	}
	// 2nd Quadrant
	else if(bb_r < row + n/2 && bb_c < col + n/2)
	{
		//cout << "2nd Quadrant" << endl;
		insert(gameBoard,row + (n/2) -1,col +  (n/2), row + n/2, col + (n/2) -1,row + n/2,col + n/2);
	}
	// 3rd Quadrant
	else if(bb_r >= row + n/2 && bb_c < col + n/2)
	{
		insert(gameBoard, row + (n/2) -1 ,col + (n/2) -1, row + (n/2)-1, col + n/2, row + n/2, col + n/2);
		//cout << "3rd Quadrant" << endl;
	}
	// 4th Quadrant
	else if(bb_r >=row + n/2 && bb_c >= col + n/2)
	{
		//cout << "4th Quadrant" << endl;
		insert(gameBoard,row + (n/2)-1,col + (n/2)-1,row + n/2,col + (n/2)-1,row + (n/2)-1,col +(n/2));
	}

	filingBoard(gameBoard,row,col + n/2,n/2,bb_r,bb_c,n/2,n);
	filingBoard(gameBoard,row,col,n/2,bb_r,bb_c,n/2,n/2);
	filingBoard(gameBoard,  row+ n/2,col,n/2,bb_r,bb_c,n,n/2);
	filingBoard(gameBoard,row+ (n/2),col + (n/2),n/2,bb_r,bb_c,n,n);

	return;
}




int main()
{

	int n,row,col;
	char **gameBoard;
	cout << "Enter size of game board: ";
	cin >> n;
	cout << "---- Enter index for Blank box ---"<< endl;
	cout << "Enter row no: ";
	cin >> row;
	cout << "Enter col no: ";
	cin >> col;
	
	initialisingBoard(gameBoard,n,row,col);
	filingBoard(gameBoard,0, 0, n,row,col,8,8);
	print(gameBoard, n);


}


	