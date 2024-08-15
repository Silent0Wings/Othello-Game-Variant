#include "Board.h"

// Constructor
Board::Board() :Board(false)
{

};
// Constructor
Board::Board(bool def = true)
{
	// Initialize the board
	initialise_Board();
	initialise_Board_Frame();
	initialise_Board_Legal_Moves();
	if (def)
		default_Layout();

	// Set initial game state variables
	Turn_Counter = 0;
	Current_Turn = 'B';
	Winner = ' ';

	Draw = false;
	Forfeit = false;
	Forced_Save = false;
	Last_Turn_No_Moves = false;
	Last_Two_Turns_No_Moves = false;
};
Board::Board(int arr[8][8]) //constructor that accept a 2d array and build the constructor
{
	// Initialize the board with the provided array
	initialise_Board(arr);
	initialise_Board_Frame();
	initialise_Board_Legal_Moves();

	// Set initial game state variables
	Turn_Counter = 0;
	Current_Turn = 'B';
	Winner = ' ';

	Draw = false;
	Forfeit = false;
	Forced_Save = false;
	Last_Turn_No_Moves = false;
	Last_Two_Turns_No_Moves = false;

};

// Initialization :
// Initialize the game board to an empty state
void Board::initialise_Board()
{
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{
			if (board[i][j] != nullptr && board[i][j]->is_Empty() == false)
			{
				delete board[i][j];
			}
			board[i][j] = new Position();
		}
	}
}
// Initialize the game board based on a provided array
void Board::initialise_Board(int arr[8][8])
{
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{
			if (board[i][j] != nullptr)
			{
				delete board[i][j];
			}

			if (arr[i][j] == 1)
			{
				board[i][j] = new Position('W');
			}
			else if (arr[i][j] == 2)
			{
				board[i][j] = new Position('B');
			}
			else
			{
				board[i][j] = new Position();
			}
		}
	}
}
// Initialize or reset the array of positions for legal moves to its empty state
void Board::initialise_Board_Legal_Moves()
{
	//sets everything to unplayable position since by default since a playable position is decided by piece layout and player turn
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{
			if (Available_Moves[i][j] != nullptr)
			{
				if (Available_Moves[i][j]->canPlay())
				{
					(Available_Moves[i][j]) = new UnplayablePosition();
				}
			}
			else
			{
				(Available_Moves[i][j]) = new UnplayablePosition();
			}
		}
	}
}
// Initialize Board Frame: Initializes or resets the values of the frame that will house the printed values.
void Board::initialise_Board_Frame() {
	for (size_t i = 0; i < 18; i++) {
		Board_Frame[i] = "";
	}
	Board_Frame[0] = "\n    1 | 2 | 3 | 4 | 5 | 6 | 7 | 8=X";
	Board_Frame[1] = "\n  |===============================|";
	Board_Frame[2] = "\n1:|   |   |   |   |   |   |   |   |";
	Board_Frame[3] = "\n  |-------------------------------|";
	Board_Frame[4] = "\n2:|   |   |   |   |   |   |   |   |";
	Board_Frame[5] = "\n  |-------------------------------|";
	Board_Frame[6] = "\n3:|   |   |   |   |   |   |   |   |";
	Board_Frame[7] = "\n  |-------------------------------|";
	Board_Frame[8] = "\n4:|   |   |   |   |   |   |   |   |";
	Board_Frame[9] = "\n  |-------------------------------|";
	Board_Frame[10] = "\n5:|   |   |   |   |   |   |   |   |";
	Board_Frame[11] = "\n  |-------------------------------|";
	Board_Frame[12] = "\n6:|   |   |   |   |   |   |   |   |";
	Board_Frame[13] = "\n  |-------------------------------|";
	Board_Frame[14] = "\n7:|   |   |   |   |   |   |   |   |";
	Board_Frame[15] = "\n  |-------------------------------|";
	Board_Frame[16] = "\n8:|   |   |   |   |   |   |   |   |";
	Board_Frame[17] = "\n=Y|===============================|";
}
// Reset the values of the game board to empty positions
void Board::reset_Board()
{
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{
			board[i][j]->set_Empty();
		}
	}
}
// Initialize the game board with a default layout
void Board::default_Layout()
{
	int temp = 5;
	std::cout << "Enter a default layout choice: (0 for standard, 1 for non-standard)";
	std::cin >> temp;
	if (temp < 0 || temp > 1)
		temp = 0;

	int temp2 = 5;
	if (temp == 1)
	{
		std::cout << "Enter a non-standard layout choice(2x2): (1 to 4) and 6 ||for Four-by-Four(4x4) Starting Position";
		std::cin >> temp2;
		if (temp2 < 1 || (temp2 > 4 && temp2 != 6))
			temp2 = 4;
	}

	switch (temp2)
	{
	case (1):
	{
		// Set the game board to a specific non-standard layout
		make_Move('W', 2, 2);
		make_Move('B', 2, 3);
		make_Move('B', 3, 2);
		make_Move('W', 3, 3);
		break;
	}
	case (2):
	{
		// Set the game board to another non-standard layout
		make_Move('W', 4, 2);
		make_Move('B', 4, 3);
		make_Move('B', 5, 2);
		make_Move('W', 5, 3);
		break;
	}
	case (3):
	{
		// Set the game board to another non-standard layout
		make_Move('W', 2, 4);
		make_Move('B', 2, 5);
		make_Move('B', 3, 4);
		make_Move('W', 3, 5);
		break;
	}
	case (4):
	{
		// Set the game board to another non-standard layout
		make_Move('W', 4, 4);
		make_Move('B', 4, 5);
		make_Move('B', 5, 4);
		make_Move('W', 5, 5);
		break;
	}
	case (5):
	{
		// Set the game board to yet another non-standard layout
		make_Move('W', 3, 3);
		make_Move('B', 3, 4);
		make_Move('B', 4, 3);
		make_Move('W', 4, 4);
		break;
	}
	case (6):
	{
		// Set the game board to a Four-by-Four Starting Position
		make_Move('W', 2, 2);
		make_Move('W', 3, 2);
		make_Move('W', 2, 3);
		make_Move('W', 3, 3);
		make_Move('B', 4, 2);
		make_Move('B', 5, 2);
		make_Move('B', 4, 3);
		make_Move('B', 5, 3);
		make_Move('W', 4, 4);
		make_Move('W', 5, 4);
		make_Move('W', 4, 5);
		make_Move('W', 5, 5);
		make_Move('B', 2, 4);
		make_Move('B', 3, 4);
		make_Move('B', 2, 5);
		make_Move('B', 3, 5);
		break;
	}
	}
}
// Resets  everything completely.
void Board::full_Reset(bool defaulting = true)
{
	initialise_Board();
	initialise_Board_Legal_Moves();
	initialise_Board_Frame();
	reset_Board();
	if (defaulting)
		default_Layout();

	// Reset initial game state variables
	Turn_Counter = 0;
	Current_Turn = 'B';
	Winner = ' ';

	// Reset bool
	Is_Running = false;
	Draw = false;
	Forfeit = false;
	Forced_Save = false;
	Last_Turn_No_Moves = false;
	Last_Two_Turns_No_Moves = false;

}

// legal_Moves: Legal moves that are available for each player turn.
bool Board::legal_Moves(bool Non_Destructive = true)
{
	// Initialize the legal moves board
	initialise_Board_Legal_Moves();

	// Iterate through the board to find legal moves for the current player
	for (size_t Y_Pos = 0; Y_Pos < *Board_Size; Y_Pos++)
	{
		for (size_t X_Pos = 0; X_Pos < *Board_Size; X_Pos++)
		{
			if (board[Y_Pos][X_Pos]->get_Symbol() != Current_Turn)
			{
				continue;
			}

			// Check available moves in all 8 directions
			legal_Moves_Direction(X_Pos, Y_Pos, 1, 0);       // Right
			legal_Moves_Direction(X_Pos, Y_Pos, -1, 0);      // Left
			legal_Moves_Direction(X_Pos, Y_Pos, 0, 1);       // Down
			legal_Moves_Direction(X_Pos, Y_Pos, 0, -1);      // Up
			legal_Moves_Direction(X_Pos, Y_Pos, 1, 1);       // Diagonal Down Right
			legal_Moves_Direction(X_Pos, Y_Pos, -1, 1);      // Diagonal Down Left
			legal_Moves_Direction(X_Pos, Y_Pos, 1, -1);      // Diagonal Up Right
			legal_Moves_Direction(X_Pos, Y_Pos, -1, -1);     // Diagonal Up Left
		}
	}

	// Count the number of available moves
	int number_of_moves = 0;
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{
			if (Available_Moves[i][j]->canPlay())
			{
				++number_of_moves;
			}
		}
	}

	// Determine if any legal moves are available
	bool decision = (number_of_moves > 0);

	if (Non_Destructive)
	{
		if (Last_Turn_No_Moves && decision == false)
		{
			// If no moves were found in the last turn and no moves are found in this turn, terminate to avoid an infinite loop
			Last_Two_Turns_No_Moves = true;
			return false;
		}
		else if (decision)
		{
			Last_Two_Turns_No_Moves = false;
			Last_Turn_No_Moves = false;
		}

		Last_Turn_No_Moves = (decision == false); // Set Last_Turn_No_Moves to true if no moves are found, else set it to false
	}

	if (decision)
	{
		Last_Two_Turns_No_Moves = false;
		Last_Turn_No_Moves = false;
	}
	return decision;
};
// This method distributes legal moves from a starting position to check for available moves possible.
//allows the Legal Moves behavior to be checked in all direction since the code is repetitive
void Board::legal_Moves_Direction(size_t X_Pos, size_t Y_Pos, size_t Direction_X, size_t Direction_Y)
{
	// Check available moves in a specific direction
	int Current_X = (int)X_Pos;
	int Current_Y = (int)Y_Pos;

	for (size_t i = 0; i < *Board_Size; i++)
	{
		Current_X += (int)Direction_X;
		Current_Y += (int)Direction_Y;

		if ((Current_X >= 0 && Current_X < 8) && (Current_Y >= 0 && Current_Y < 8))
		{
			if (board[Current_Y][Current_X]->is_Empty() && i == 0)
			{
				break;
			}
			else
			{
				if (board[Current_Y][Current_X]->get_Symbol() == Current_Turn)
				{
					break;
				}
				else if (board[Current_Y][Current_X]->get_Symbol() != Current_Turn && board[Current_Y][Current_X]->is_Empty() == false)
				{
					continue;
				}
				else if (board[Current_Y][Current_X]->is_Empty() && i != 0)
				{
					delete (Available_Moves)[Current_Y][Current_X];
					//a available position is by default position class since as long as it is empty can play return true
					(Available_Moves)[Current_Y][Current_X] = new Position();
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
}

// input_Behavior: This function handles player's input for making a move.
void Board::input_Behavior() {
	if (number_Blacks() == 0)
	{
		Is_Running = false;
		Winner = 'W';
		return;
	}
	else if (number_Whites() == 0)
	{
		Winner = 'W';
		Is_Running = false;
		return;
	}
	else
	{

		if (legal_Moves()) {
			bool Terminate = true;
			while (Terminate) {
				int X_Pos = -1, Y_Pos = -1;
				std::cout << "Enter Y position followed by X position separated by one space : ";
				std::cin >> Y_Pos >> X_Pos;
				--X_Pos;
				--Y_Pos;
				if ((X_Pos >= 0 && X_Pos < 8) && (Y_Pos >= 0 && Y_Pos < 8)) {
					if (Available_Moves[Y_Pos][X_Pos]->canPlay()) {
						if (make_Move(X_Pos, Y_Pos)) {
							switching_Behavior(X_Pos, Y_Pos);
							Terminate = false;
						}
						else {
							continue;
						}
						break;
					}
					else {
						std::cout << "Please Enter Valid Inputs: " << "X=" << X_Pos + 1 << " Y=" << Y_Pos + 1 << " Are not valid Inputs" << std::endl;
						continue;
					}
				}
				else {
					if (X_Pos == -1 && Y_Pos == -1)//this means input of (0 0) since we are subtracting -1 from each input axis
					{
						Is_Running = false;
						Forfeit = false;
						Forced_Save = true;
						Terminate = false;
					}
					else if ((X_Pos < 0 || Y_Pos < 0)) { //this means any negative value other than the <0 

						Winner = (Current_Turn == 'W') ? 'B' : 'W';//if the current player is white then the winner is black and vice versa
						Is_Running = false;
						Forfeit = true;
						Terminate = false;
					}

					else {
						continue;
					}
				}
			}
		}
		else {

			// Display options for the current player when no moves are available.
			std::cout << std::endl << "Current Player " << Current_Turn << " has no moves available";
			int no_move_behavior = 0;
			std::cout << std::endl << "Make a choice " << std::endl;
			std::cout << "0- Skip Turn " << std::endl;
			std::cout << "1- Save " << std::endl;
			std::cout << "2- Forfeit " << std::endl;
			std::cin >> no_move_behavior;
			switch (no_move_behavior) {
			case (0): // Skip Turn
				break;
			case (1): // Save Game
				Is_Running = false;
				Forfeit = false;
				Forced_Save = true;
				break;
			case (2): // Forfeit Game
				Is_Running = false;
				Forfeit = true;
				Forced_Save = false;

				break;
			}

		}
	}

}

// win_Check: Checks if the game is won or still running.
bool Board::win_Check() {
	if (Forfeit || Forced_Save) {
		return false;
	}
	else {
		if (board_Is_Full() || number_Blacks() == 0 || number_Whites() == 0 || (Last_Two_Turns_No_Moves && !legal_Moves(false))) {
			//If the board is full, if one of the player's pieces is reduced to 0, or if two consecutive turns pass without any player having a possible legal moves
			int temp = number_Whites() - number_Blacks();
			if (temp > 0) {
				Winner = 'W';
			}
			else if (temp < 0) {
				Winner = 'B';
			}
			else if (temp == 0) {
				Draw = true;
			}
			Is_Running = false;
			return false;
		}
		else {
			return true;
		}
	}
}
// win_Message: Generates a message to describe the game result.
std::string Board::win_Message() {
	if (Forfeit) {
		std::string test = (Current_Turn == 'W') ? "BLACK" : "WHITE";//it is reversed because the current player is forfeiting therefore the winner is alwayse not the current player
		return "Winner Is PLayer With " + test + " Pieces ";
	}
	else if (Forced_Save) {
		return "No one Won. Game is being saved to be resumed later.";
	}
	else {
		if (board_Is_Full() || number_Blacks() == 0 || number_Whites() == 0 || (Last_Two_Turns_No_Moves && !legal_Moves(false))) {
			//If the board is full, if one of the player's pieces is reduced to 0, or if two consecutive turns pass without any player having a possible legal moves
			int temp = number_Whites() - number_Blacks();
			if (Forfeit) //if a player forfeit
			{
				return std::string(1, Winner) + " Won By Forfeit!";
			}
			else {
				if (temp == 0) //number of whites = number of blacks then its a draw
				{
					return "No One Won. It's a Draw!";
				}
				else if (temp < 0 || temp>0) //who won is decided by the score (who has more pieces)
				{
					return "Winner is " + std::string(1, Winner) + "!";

				}
			}
		}
		else {
			return "No One Won!";
		}
	}
	return "No Decision";
}

// drawBoard: Draws the current state of the game board.
void Board::drawBoard(bool clear_val = true) // true clears the screen false dose not
{
	if (clear_val)
	{
		// Replace the system("CLS") with this code snippet
#ifdef _WIN32
		system("CLS");
#else
		system("CLEAR");
#endif
	}
	// Default offset calculated from the board frame representing the first empty position
	int Y = 2;
	int X = 5;
	legal_Moves(false);
	// Assign pieces to the board by legal moves and actual pieces
	for (size_t i = 0; i < *Board_Size; i++) {
		X = 5;
		for (size_t j = 0; j < *Board_Size; j++) {
			if (X < 35 && Y < 18) {
				Board_Frame[Y][X] = *board[i][j]->get_Current();
				if ((Available_Moves[i][j])->canPlay() && board[i][j]->is_Empty()) {
					Board_Frame[Y][X] = av_mov;
				}
				else if (!((Available_Moves[i][j])->canPlay()) && board[i][j]->is_Empty()) {
					Board_Frame[Y][X] = ' ';
				}
			}
			X += 4;
		}
		Y += 2;
	}
	// Draw the board line by line
	for (size_t i = 0; i < 18; i++) {
		std::cout << Board_Frame[i];
	}
	std::cout << std::endl << "| '" << std::string(1, *(Position::get_Black_Static())) << "' is black | '" << std::string(1, *(Position::get_White_Static())) << "' is white | '" << av_mov << "' is available moves ||" << std::endl;
}
// number_Blacks: Returns the number of black pieces on the board.
int Board::number_Blacks() const {
	int num_black = 0;
	for (size_t i = 0; i < *Board_Size; i++) {
		for (size_t j = 0; j < *Board_Size; j++) {
			if (board[i][j]->is_Black()) {
				num_black++;
			}
		}
	}
	return num_black;
}
// number_Whites: Returns the number of white pieces on the board.
int Board::number_Whites() const {
	int number_Whites = 0;
	for (size_t i = 0; i < *Board_Size; i++) {
		for (size_t j = 0; j < *Board_Size; j++) {
			if (board[i][j]->is_White()) {
				number_Whites++;
			}
		}
	}
	return number_Whites;
}

// Board Is Full: Checks if the game board is full.
bool Board::board_Is_Full() const {
	int num = 0;
	for (size_t i = 0; i < *Board_Size; i++) {
		for (size_t j = 0; j < *Board_Size; j++) {
			if (!board[i][j]->is_Empty()) {
				num++;
			}
		}
	}
	return (num == *Board_Size * *Board_Size);
}
// Board Is EMPTY: Checks if the game board is empty.
bool Board::Board_Is_Empty() const {
	for (size_t i = 0; i < *Board_Size; i++) {
		for (size_t j = 0; j < *Board_Size; j++) {
			if (board[i][j]->is_Empty() == false) {
				return false;
			}
		}
	}
	return true;
}

// Make Move: Attempts to make a move on the game board.
bool Board::make_Move(const int X, const int Y) {
	return make_Move(Current_Turn, X, Y);
}
// Make Move: Overloaded function to place a piece based on character (W or B) and position.
bool Board::make_Move(const char Val, const int X, const int Y) {
	if ((X >= 0 && Y >= 0) && (X < *Board_Size && Y < *Board_Size)) {
		if (board[Y][X]->is_Empty()) {
			if (Val == 'W') {
				board[Y][X]->set_White();
				return true;
			}
			else if (Val == 'B') {
				board[Y][X]->set_Black();
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return false;
}
// switching_Behavior pieces after making a move.
void Board::switching_Behavior(int const X_Pos, int const Y_Pos)//turn enemy pieces to the current players pieces in all 8 directions
{
	// Check available moves in all 8 directions
	switching_Behavior_Direction(X_Pos, Y_Pos, 1, 0);       // Right
	switching_Behavior_Direction(X_Pos, Y_Pos, -1, 0);      // Left
	switching_Behavior_Direction(X_Pos, Y_Pos, 0, 1);       // Down
	switching_Behavior_Direction(X_Pos, Y_Pos, 0, -1);      // Up
	switching_Behavior_Direction(X_Pos, Y_Pos, 1, 1);       // Diagonal Down Right
	switching_Behavior_Direction(X_Pos, Y_Pos, -1, 1);      // Diagonal Down Left
	switching_Behavior_Direction(X_Pos, Y_Pos, 1, -1);      // Diagonal Up Right
	switching_Behavior_Direction(X_Pos, Y_Pos, -1, -1);     // Diagonal Up Left
};
//allows the switching behavior to propagate in all direction since the code is repetitive
void Board::switching_Behavior_Direction(const size_t X_Pos, const size_t Y_Pos, const size_t Direction_X, const size_t Direction_Y)
{
	int Current_X = (int)X_Pos;
	int Current_Y = (int)Y_Pos;
	//check the Diagonal Up and Left  of the last placed piece
	for (size_t i = 0; i < *Board_Size; i++)
	{
		Current_Y += (int)Direction_Y;
		Current_X += (int)Direction_X;
		if ((Current_Y >= 0 && Current_Y < 8) && (Current_X >= 0 && Current_X < 8)) {
			if (board[Current_Y][Current_X]->is_Empty())
			{
				break;
			}
			else
			{
				if (board[Current_Y][Current_X]->get_Symbol() == Current_Turn && (std::abs(Current_Y - (int)Y_Pos) == 1 || abs(Current_X - (int)X_Pos) == 1))
				{
					break;
				}
				else if (board[Current_Y][Current_X]->get_Symbol() != Current_Turn)
				{
					continue;
				}
				else if (board[Current_Y][Current_X]->get_Symbol() == Current_Turn && (abs(Current_Y - (int)Y_Pos) != 1 && abs(Current_X - (int)X_Pos) != 1))
				{
					for (size_t j = 0; j < *Board_Size; j++)
					{
						Current_Y -= (int)Direction_Y;
						Current_X -= (int)Direction_X;
						if ((Current_Y >= 0 && Current_Y < 8) && (Current_X >= 0 && Current_X < 8)) {
							if (board[Current_Y][Current_X]->is_Empty())
							{
								break;
							}
							else if (board[Current_Y][Current_X]->get_Symbol() != Current_Turn)
							{
								//to be replaced
								/*if (Current_Turn == 'W')
								{
									board[Current_Y][Current_X]->set_White();
								}
								else if (Current_Turn == 'B')
								{
									board[Current_Y][Current_X]->set_Black();
								}*/
								board[Current_Y][Current_X]->switch_Element();
							}
							else
							{
								break;
							}
						}
					}
					break;
				}
			}
		}
		else
		{
			break;
		}

	}

}

//saving board
std::string Board::board_to_String()const//convert the board containing the position of pieces to a string that maps W to 1 B to 2 and empty to 0
{
	std::string output = "";
	for (size_t i = 0; i < *Board_Size; i++)
	{
		for (size_t j = 0; j < *Board_Size; j++)
		{


			if (board[i][j]->is_Empty()) {
				output += "0";
			}
			else if (board[i][j]->is_White()) {
				output += "1";
			}
			else if (board[i][j]->is_Black()) {
				output += "2";
			}
			else
			{
				output += "0";
			}

			if (j != (*Board_Size - 1))
				output += " ";

		}
		if (i != (*Board_Size - 1))
			output += '\n';
	}
	return output;
}

// Destructor
Board::~Board()
{
	if (Board_Size != nullptr)
	{
		if (board != nullptr)
		{
			for (size_t i = 0; i < *Board_Size; i++)
			{
				for (size_t j = 0; j < *Board_Size; j++)
				{
					if (board[i][j] != nullptr)
					{
						delete board[i][j];
					}
				}
			}
		}
		if (board != nullptr)
		{
			for (size_t i = 0; i < *Board_Size; i++)
			{
				for (size_t j = 0; j < *Board_Size; j++)
				{
					if (Available_Moves[i][j] != nullptr)
					{
						delete Available_Moves[i][j];
					}
				}
			}
		}
	}
	if (board != nullptr)
	{
		delete Board_Size;
	}
}