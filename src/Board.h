#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include "Position.h"
#include "UnplayablePosition.h"
#include <stdlib.h>
#include <cmath>        
class Board
{
private:
	size_t const* Board_Size = new size_t(8);  // Size of the board (8x8).
	Position* board[8][8] = {};  // The main game board.
	Position* Available_Moves[8][8] = {};  // Available move positions (Polymorphism unplayablePosition or Position is stored in this array).
	std::string Board_Frame[18] = {};  // Frame for drawing the piece of the board.
	const char av_mov = '~';  // Symbol for available moves.
	bool Last_Turn_No_Moves = false;  // Flag to check if there were no moves last turn.
	bool Last_Two_Turns_No_Moves = false;  // Flag to check if there were no moves last two turns.

public:
	int Turn_Counter = 1;  // Keep track of the turn number.
	char Current_Turn = 'B';  // Keeps track of the current player Piece Color 
	char Winner = ' ';  // Keeps track of the current player Piece Color 
	bool Is_Running = false;  // Flag to stop the game at any point.
	bool Draw = false;  // Flag to declare a draw.
	bool Forfeit = false;  // Flag to declare a forfeit.
	bool Forced_Save = false;  // Flag to stop the game for saving purposes.

	// Constructor
	Board();  // Default constructor.
	Board(bool);  // Default constructor.
	Board(int[8][8]);  // Constructor with initial board setup.

	// Initialize Values
public:
	void initialise_Board();	// Initialize the game board.
	void initialise_Board(int[8][8]);  // Initialize the board with a given layout.
	void initialise_Board_Legal_Moves(); // Initialize the legal moves to all unavailable
	void initialise_Board_Frame(); // Initialize the frame where we draw the piece of each player inside
	void reset_Board();// Reset the values of the game board to empty positions
	void default_Layout();  // Set the default layout.
	void full_Reset(bool);  // Resets  everything completely.
private:

	// Legal Moves Operations

	// This method calculates legal moves and marks them on the board.
	// This method spreads legal moves from a starting position in every Direction to check for available moves possible.
	bool legal_Moves(bool);

	// This method spreads legal moves from a starting position to check for available moves possible.
	//allows the Legal Moves behavior to be checked in all direction since the code is repetitive
	void legal_Moves_Direction(size_t, size_t, size_t, size_t);
public:

	// Player Operations
	// Get and process player input.
	void input_Behavior();

	// Win Operation
	// Check for a win condition.
	bool win_Check();
	// Get a message indicating the win status.
	std::string win_Message();

	// Board Operations
	// Draw Board: Draws the current state of the game board.
	void drawBoard(bool);
	// Count the number of BLACK pieces on the board.
	int number_Blacks() const;
	// Count the number of WHITE pieces on the board.
	int number_Whites() const;

private:
	// Check if the board is full.
	bool board_Is_Full() const;
	// Check if the board is empty.
	bool Board_Is_Empty() const;


	// Board Position Operation
	// Make a move on the board.
	bool make_Move(const int, const int);
	bool make_Move(const char, const int, const int);

	// switching Behavior pieces after making a move.
	void switching_Behavior(int const, int const);
	//allows the spread behavior to propagate in all direction since the code is repetitive
	void switching_Behavior_Direction(const size_t X_Pos, const size_t Y_Pos, const size_t Direction_X, const size_t Direction_Y);
public:

	// Saving board
	// Convert the board state to a string for saving.
	std::string board_to_String() const;

	// Destructor
	~Board();
};