/*
 * =====================================================================================
 *
 *       Filename:  life.h
 *
 *    Description:  The header for the game of life project
 *
 *        Version:  1.0
 *        Created:  11/08/2012 10:51:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ross Guarino (eos@csh.rit.edu)
 *   Organization:  Computer Science House
 *
 * =====================================================================================
 */

/**
 *gets the board value at the location
 */
int getBoard( int row, int column);
/**
 *sets the board value given to the new value
 */
void setBoard( int row, int column, int value);
/**
 * Flushes the buffer to the specified row
 */
void flushBuffer( int row);
/**
 * pushed the value onto the buffer
 */
void pushBuffer(int row, int column, int value);
/**
 * Runs through the game once
 */
void gameTick();
/**
 * Print the board to standard out, also checks to see if
 * the board it empty. Returns true if the board is empty
 */
bool printBoard();
/**
 * Randomly fills the board
 */
void generateGame();
