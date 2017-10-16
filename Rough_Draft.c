//Team 6
//By Christopher Carlson

#include<iostream>
#include<cctype>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;
//constants
const bool TRUE  = 1;
const bool FALSE = 0;
const int B_DIM  = 8;//dimensions of board
const int LOW_END = -1;//dimension of board must be greater
const char LETTERS[] = "    |  |  |  |  |  |  |  |\n    A  B  C  D  E  F  G  H\n";//visual to help user know the column
//variables
volatile int QUEENS;
//prototypes
void display(int board[][B_DIM]);//displays the board
bool move(int board[][B_DIM]);//get's user's input returns false if the game is won or lost
int discern(char input);//check the column is a good input and returns a corresponding number. 8 = error
void black_out(int board[][B_DIM],int row, int column, bool set);//black out all unusable cells
void find_quadrant(bool quad[],int row,int colunm);//find out what quadrant we are in
int phase(int & input);
//main
int main(){
	int board[8][8];
	QUEENS = 0;
//	cout << QUEENS;
	//initialize board
	for(int i = 0; i < B_DIM; ++i){
		for(int j = 0; j < B_DIM; ++j){
			board[i][j] = TRUE;
		}
	}
	do{
		display(board);
	}while(move(board));
	return 0;
}
//returns the value it is given, while increasing the integer
int phase(int & input){
	int holder = input;
	++input;
//	cout <<"\nIn: " << holder << "\tOut: " << input;
	return holder;
}

//find out what quadrant we are in
void find_quadrant(bool quad[],int row,int column){
//	cout << "\nRow: " << row << "\nColumn: " << column << '\n';
	if(B_DIM/2 > column)	quad[0] = 0;else quad[0] = 1;
	if(B_DIM/2 > row)	quad[1] = 0;else quad[1] = 1;
//	cout <<"Quadrant: " << quad[1] << quad[0] << '\n';
}

//after placing a queen, we want all cells that can no longer hold a queen blacked out
void black_out(int board[][B_DIM],int row, int column, bool set){
	int upL,upR,downL,downR;
	int p = 0;
//	bool quad[2];//What quadrant are we in? Used for diagonal blacking.
//	find_quadrant(quad,row,column);
//	cout << "\nDown Left search";
		if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//0
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//1
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//2
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//3
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//4
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//5
	else	if(	   phase(p) == column ||	 p-1 == row)	downL = p-1;//6
	else								downL = p  ;//7
//	cout << "\nDL Phase: " << p;
	p = 0;
//	cout << "\nDown Right search";
		if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//0
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//1
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//2
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//3
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//4
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//5
	else	if(B_DIM-1-phase(p) == column ||	 p-1 == row)	downR = p-1;//6
	else								downR = p  ;//7
//	cout << "\nDR Phase: " << p << "\nDown Right: " << downR << '\n';;
	p = 0;
//	cout << "\nUp Left search";
//	cout << "\nRow: " << row;
		if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//0
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//1
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//2
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//3
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//4
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//5
	else	if(	   phase(p) == column || B_DIM-  p   == row)	upL   = p-1;//6
	else								upL   = p  ;//7
//	cout << "\nUL Phase: " << p << "\nUp Left: " << upL << '\n';
	p = 0;
//	cout << "\nUp Right search";
		if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//0
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//1
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//2
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//3
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//4
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//5
	else	if(B_DIM-phase(p)-1 == column || B_DIM-p == row)		upR   = p-1;//6
	else								upR   = p  ;//7
//	cout << "\nUR Phase: " << p;
	p = 0;

//	cout << "\ndownR: " << downR << "\ndownL: " << downL << "\nupL: " << upL << "\nupR: " << upR << '\n';
//	cout << "\nRow: " << row << "\tColumn: " << column << '\n';
	for(int i = 0;B_DIM > i; ++i){
		board[B_DIM-1-row][i] = set;
		board[i][column] = set;
	}
	//diagonal sets
	for(int i = 0;         downR > i; ++i)board[B_DIM-row+i][column+i+1] = set;//down and to the right
	for(int i = 0; upR > i; ++i)board[B_DIM-2-row-i][column+i+1] = set;//up   and to the right
	for(int i = 0;         downL > i; ++i)board[B_DIM-row+i][column-i-1] = set;//down and to the left
	for(int i = 0; upL > i; ++i)board[B_DIM-row-i-2][column-i-1] = set;//Up left
}

//discern the meaning of inputs A-H
int discern(char input){
		if('A' == input || 'a' == input)	return 0;
	else	if('B' == input || 'b' == input)	return 1;
	else	if('C' == input || 'c' == input)	return 2;
	else	if('D' == input || 'd' == input)	return 3;
	else	if('E' == input || 'e' == input)	return 4;
	else	if('F' == input || 'f' == input)	return 5;
	else	if('G' == input || 'g' == input)	return 6;
	else	if('H' == input || 'h' == input)	return 7;
	else						return 8;
}

//make a move
bool move(int board[][B_DIM]){
	int row;
	int clmn;
	char column;
	//get inputs
	cout << "\nPlease input the column then the row (i.e. f7)\nInput: ";
	cin >> column >> row;
	cout << "Column: " << column << "\nRow: " << row << '\n';
	//check values good and place queen
	clmn = discern(column);
	if(B_DIM   +1 > row
	&& LOW_END +1 < row
	&& B_DIM      > clmn
	&& LOW_END    < clmn){
//		cout << "\nGood input\n";
		if(board[B_DIM-row][clmn]){
			++QUEENS;
			black_out(board,row-1,clmn,FALSE);
			board[B_DIM-row][clmn] = 2;
		}else cout << "\nCannot place a Queen there.\n";
		return TRUE;
	}//else cout << "\nBad input\n";
	return FALSE;
}

//display the board
void display(int board[][B_DIM]){
//	int hold;
	for(int i = 0; i < 8; ++i){
//		cout << LETTER[i] << "  ";
		cout <<  8 - i << "- ";
		for(int j = 0; j < 8; ++j){
//			hold = board[i][j];
			cout <<"[";
			cout << board[i][j];
			cout << "]";
		}
		cout <<"\n";
	}
	cout << LETTERS;
	cout << "Queens placed: " << QUEENS << '\n';
}
