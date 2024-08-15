#pragma once

#include "Player.h"
#include "Board.h"

class Game
{
private:
	Player first;
	Player second;
	Player* Current = nullptr;
	Board* board = nullptr;
	bool Completed = false;
	Player* Winner = nullptr;
public:
	// Constructor
	Game(Player p1, Player p2);

	// Destructor
	~Game();

	// Game Operations
	void start(); // Start the game
	void play(); // Play the game Contains game loop
	void switch_Player_Turn(); // switch_Element the turn between players
	void player_Naming();// This Input both Player names
	void reset(bool); // Reset the entire game class
	
	// Printing the command list
	void print_Commands() const; // Print available game commands
	void input_Pause();// a method that demands a random input to continue the program

	// Game Loading and Saving
private:
	void load(); // Load a saved game
	void save(); // Save the current game state


};