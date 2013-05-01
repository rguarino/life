/*
 * =====================================================================================
 *
 *       Filename:  life.cpp
 *
 *    Description:  Conway's game of life implementation because I never did this in
 *    	 highschool. Instead of copying the board I used a buffer to resuce the amount of
 *    	 memory used by the program. The basic idea is that every row that is two rows above
 *    	 the current row we can flush the boffer too. This way we only need to keep track of
 *    	 two extra rows in the buffer and flush them out the the game once that game row is not
 *    	 needed for calculations anymore.
 *
 *        Version:  1.0
 *        Created:  11/08/2012 10:32:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ross Guarino(eos@csh.rit.edu)
 *   Organization:  Computer Science House
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include "life.h"

//Globals
const int HEIGHT = 10;
const int WIDTH = 30;
char board[HEIGHT][WIDTH];
char buffer[2][WIDTH];

using namespace std;

int main(int argc, char* argv[]){

	/*
	printBoard();
	cout<<"----------------"<<endl;
	generateGame();
	cout<<"----------------"<<endl;
	printBoard();
	pushBuffer(0,0,0);
	pushBuffer(0,1,0);
	pushBuffer(0,2,0);
	pushBuffer(0,3,0);
	pushBuffer(0,4,0);
	pushBuffer(0,5,0);
	pushBuffer(0,6,0);
	pushBuffer(0,7,0);
	pushBuffer(0,8,0);
	pushBuffer(0,9,0);
	flushBuffer( 0);
	cout<<"----------------"<<endl;
	printBoard();
	cout<<"----------------"<<endl;
	gameTick();
	printBoard();
	cout<<"----------------"<<endl;
	*/


	//If no arguments are made play forever
	if( argc == 1){
		while( true){
			int generation = 0;
			generateGame();
			bool empty = false;
			while( generation <= 50 &&  !empty ){
				gameTick();
				cout<<"Generation: "<<generation<<endl;
				generation++;
				empty = printBoard();
				usleep(500000);
			}
		}
	}
	//If an argument is given play the gam
}

void generateGame(){
	srand ( time(NULL) );
	for( int r=0; r<HEIGHT; r++){
		for( int c=0; c<WIDTH; c++){
			setBoard( r, c, rand()%2 );
		}
	}
	for( int r=0; r<HEIGHT; r++){
		for( int c=0; c<WIDTH; c++){
			if( rand()%2 == 1){
				setBoard( r, c, 0 );
			}
		}
	}
}

int getBoard( int row, int column){
	return board[row][column];
}

void setBoard( int row, int column, int value){
	board[row][column] = value;
}

bool printBoard(){
	bool empty = true;;
	int value;
	cout<<"----------"<<endl;
	for( int r=0; r <HEIGHT; r++){
		cout<<"|";
		for( int c=0; c<WIDTH; c++){
			value = getBoard( r, c);
			if( value == 0){
				cout<<" ";
			}else{
				cout<<"#";
			}
			if( value == 1){ empty = false;}
		}
		cout<<"|"<<endl;
	}
	cout<<"----------"<<endl;

	return empty;
}

void pushBuffer(int row, int column, int value){
	buffer[row][column] = value;
}

void flushBuffer(int row){
	if( row >= 0){
		for( int i=0;i<WIDTH; i++){
			setBoard( row, i, buffer[0][i] );
			buffer[0][i] = buffer[1][i];
		}
	}
	else{
		//If it is less than 0 then we know we are flushing the first time and we need to
		//get rid of the old data
		for( int i=0; i<WIDTH; i++){
			buffer[0][i]= buffer[1][i];
		}
	}
}

void gameTick(){
	int value;
	int neighbors;
	for( int r=0; r<HEIGHT; r++){
		for( int c=0; c<WIDTH; c++){
			value = getBoard(r, c);
			neighbors = 0;
			//cout<<"Starting to count neighbors"<<endl;
			//Check north west
			if( r>0 && c >0 && getBoard(r-1,c-1) == 1){
				neighbors++;
			}
			//Check north
			if( r>0 && getBoard(r-1,c) == 1){
				neighbors++;
			}
			//Check north east
			if(r>0 && c< WIDTH-1 && getBoard(r-1,c+1) == 1){
				neighbors++;
			}
			//Check east
			if( c<WIDTH-1 && getBoard( r,c+1) == 1){
				neighbors++;
			}
			//Check south east
			if( r<HEIGHT-1 && c <WIDTH-1 && getBoard(r+1,c+1) == 1){
				neighbors++;
			}
			//Check south
			if( r<HEIGHT-1 && getBoard(r+1,c) == 1){
				neighbors++;
			}
			//Check south west
			if( r<HEIGHT-1 && c > 0 && getBoard(r+1,c-1) == 1){
				neighbors++;
			}
			//Check west
			if( c>0 && getBoard(r,c-1) == 1){
				neighbors++;
			}

			//cout<<"Finished counting neighbors"<<endl;
			if(value == 1 && neighbors < 2){
				//Not enough
				//cout<<"L";
				pushBuffer(1,c,0);
			}
			else if(value == 1 && neighbors == 2){
				//Just right
				//cout<<"2";
				pushBuffer(1,c,1);
			}
			else if(value == 1 && neighbors == 3){
				//Just right
				//cout<<"3";
				pushBuffer(1,c,1);
			}
			else if(value == 1 && neighbors > 3){
				//Over crowded
				//cout<<"O";
				pushBuffer(1,c,0);
			}
			else if( value == 0 && neighbors == 3){
				//Birth!
				//cout<<"B";
				pushBuffer(1,c,1);
			}else{
				//cout<<"E";
				pushBuffer(1,c,0);
			}
		}

		//cout<<"Finished pushing"<<endl;
		//we need to flush here
		flushBuffer(r-1);
		//cout<<endl;
	}
	//cout<<"Finished"<<endl;
	//Need to flush the last line
	flushBuffer( HEIGHT-1);

}//gameTick();
