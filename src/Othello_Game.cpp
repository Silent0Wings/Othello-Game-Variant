// Othello Game
// This program simulates an Othello (Reverse) game using the provided Game class.
//https://www.worldothello.org/about/about-othello/othello-rules/official-rules/english

#include "Game.h" // Include the Game class header

int main()
{
	// creates 2 players starting values
	Player p1("Player-1");
	Player p2("PLayer-2");

	// Check if the names of p1 and p2 are not the same	
	if (!p1.equal(p2))
	{
		// Create a dynamic instance of the Game class with players p1 and p2
		Game* Game0 = new Game(p1, p2);

		// Start the game
		Game0->start();

		// Delete the dynamic Game instance when the game is finished
		delete Game0;
	}

	//the delete method for the static members will be called at the end of the program
	Position::static_Delete();//deletes static dynamically allocated members inside of class Position alternative is using smart pointers
	return 0;
}