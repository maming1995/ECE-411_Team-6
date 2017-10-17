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
int diagonal(int ret, int row, int colun, bool up, bool right);//find out the diagonal number of blocks from the input
void initialize(int board[][B_DIM]);
//main
int main(){
	int board[8][8];
	QUEENS = 0;
	//initialize board
	initialize(board);
	do{
		display(board);
	}while(move(board));
	return 0;
}
//initialize the board
void initialize(int board[][B_DIM]){
	for(int i = 0; i < B_DIM; ++i){
		for(int j = 0; j < B_DIM; ++j){
			board[i][j] = TRUE;
		}
	}
}

//return the value equevelent to how many squars in diagonal direction
int diagonal(int ret, int row, int column, bool right, bool up){
		if(ret == 8)								return ret;
	else	if(abs(right*(B_DIM-1)-ret) == column || abs(up*(B_DIM-1)-ret) == row)	return ret;
	else										return diagonal(ret+1,row,column,right,up);
}

//after placing a queen, we want all cells that can no longer hold a queen blacked out
void black_out(int board[][B_DIM],int row, int column, bool set){
	int upL,upR,downL,downR;
	downL = diagonal(FALSE,row,column,FALSE,FALSE);cout << '\n' <<"DOWN LEFT: " << downL << '\n';
	downR = diagonal(FALSE,row,column,TRUE ,FALSE);cout << '\n' <<"DOWN RIGHT: " << downR << '\n';
	upR   = diagonal(FALSE,row,column,TRUE , TRUE);cout << '\n' <<"UP RIGHT: " << upR<< '\n';
	upL   = diagonal(FALSE,row,column,FALSE, TRUE);cout << '\n' <<"UP LEFT: " << upL << '\n';
	for(int i = 0;B_DIM > i; ++i){
		board[B_DIM-1-row][i]      = set;
		board          [i][column] = set;
	}
	//diagonal sets
	for(int i = 0; downR > i; ++i)board[B_DIM-  row+i][column+i+1] = set;//down and to the right
	for(int i = 0;   upR > i; ++i)board[B_DIM-2-row-i][column+i+1] = set;//up   and to the right
	for(int i = 0; downL > i; ++i)board[B_DIM-  row+i][column-i-1] = set;//down and to the  left
	for(int i = 0;   upL > i; ++i)board[B_DIM-2-row-i][column-i-1] = set;//Up   and to the  left
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
	for(int i = 0; i < 8; ++i){
		cout <<  8 - i << "- ";
		for(int j = 0; j < 8; ++j){
			cout <<"[";
			cout << board[i][j];
			cout << "]";
		}
		cout <<"\n";
	}
	cout << LETTERS;
	cout << "Queens placed: " << QUEENS << '\n';
}
