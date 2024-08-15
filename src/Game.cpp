#include "Game.h"

// Constructor
Game::Game(Player p1, Player p2) : first{ p1 }, second{ p2 }
{
	// Initialize the first player with the symbol 'W' (WHITE) and the second player with 'B' (BLACK).
	first.set_Symbol('W');
	second.set_Symbol('B');
	Completed = false;

	// Set the current player to the second player and initialize the board as nullptr.
	Current = &second;

	// Create a new game board.
	board = new Board();
}

// Game Operations
// This method handles starting the game, loading a saved game, or quitting.
void Game::start()
{
	bool terminate = false;
	while (terminate == false)
	{
		system("CLS");
		if (!Completed && !(board->Is_Running))
		{
			std::cout << "Enter A Command : ";
			std::string Command;
			print_Commands();
			std::cin >> Command;

			//Convert any string to lower case
			for (auto& x : Command)
				x = tolower(x);

			if (Command == "1" || Command == "quit")
			{
				terminate = true; // Quit the game.
				break;
			}
			else if (Command == "2" || Command == "load_a_game")
			{
				//the first player is decided inside the load function directly from the file
				try {// try is better here because if loading fails the game wont start since the load throws the exception
					load(); // Call the method to load a saved game.
					play(); // Start the game.

				}
				catch (char const* error)
				{
					std::cerr << error;
					input_Pause();

				}
				catch (const std::string error)
				{
					std::cerr << error;
					input_Pause();

				}


			}
			else if (Command == "3" || Command == "start_a_new_game")
			{
				reset(true);
				//the first player to play is the player variable second
				Current = &second;
				board->Current_Turn = Current->get_Symbol();
				player_Naming();
				play(); // Start the game.
			}
		}
		reset(false);//reset without asking for default layout

	}
}

// This method contains the main game loop.
void Game::play()
{
	Completed = false;
	board->Is_Running = true;
	//board->legal_Moves(false);
	board->drawBoard(true);
	std::cout << std::endl;

	while (board->Winner == ' ' && board->win_Check() && board->Is_Running && !(board->Forfeit) && !(board->Forced_Save) && !(board->Draw))
	{
		std::cout << "| Current turn is : " << ((board->Current_Turn == 'W') ? ("WHITE = '" + std::string(1, *(Position::get_White_Static())) + "' ") : ("BLACK = '" + std::string(1, *(Position::get_Black_Static())) + "' ")) << " | player : " << Current->get_Name() << std::endl;
		std::cout << "| Enter a negative number as input to forfeit the game" << std::endl;
		std::cout << "| Enter \"0 0\" as input to save the game" << std::endl;

		board->input_Behavior(); // Get player input.
		board->win_Check(); // Check if a player has won.
		if (board->Winner == ' ' && !(board->Forfeit) && !(board->Forced_Save) && board->Is_Running && !(board->Draw))
			switch_Player_Turn(); // switch_Element to the other player's turn.
		board->drawBoard(true);
		std::cout << std::endl;
		board->Turn_Counter++;
		if (!(board->Forced_Save))
			Winner = (first.get_Symbol() == board->Winner) ? &first : &second;//this establish the pointer Winner the address to the winning player 

	}
	if (Winner == nullptr && !(board->Forced_Save))
		Winner = (first.get_Symbol() == board->Winner) ? &first : &second;//this establish the pointer Winner the address to the winning player 
	board->drawBoard(true);
	std::cout << std::endl << "Current Score : " << "W : " << board->number_Whites() << " || " << "B : " << board->number_Blacks() << std::endl;
	std::cout << board->win_Message() << std::endl;//this use the board win message
	if (Winner != nullptr && !(board->Forced_Save))
		std::cout << "Winner is : " << Winner->get_Name() << std::endl;//and this one is decided in the game class

	if (board->Forced_Save && !(board->Forfeit))
	{
		Completed = true;
		std::cout << "Do you want to save this game? (Yes=1/No=0) ";
		int Command;
		std::cin >> Command;
		if (Command == 1)
		{
			save(); // Save the current game.
		}

	}
	input_Pause();
	Completed = true; //this confirms that the player loop died
}

// This method switches the current player's turn.
void Game::switch_Player_Turn()
{
	if (Current == &first)
		Current = &second;
	else if (Current == &second)
		Current = &first;

	board->Current_Turn = Current->get_Symbol();
}

// This Input both Player names
void Game::player_Naming() {

	if (board == nullptr)
		return;

	// Prompt the user to enter the name of the first player
	std::cout << "Enter The Name Of The First Player : ";
	std::string name1;
	std::cin >> name1;
	std::cout << std::endl;

	// Prompt the user to enter the name of the second player
	std::cout << "Enter The Name Of The Second Player : ";
	std::string name2;
	std::cin >> name2;
	std::cout << std::endl;

	// Check if the entered name for the first player is not empty and has a positive length
	if (name1.size() > 0 && name1.empty() == false)
		first.set_Name(name1); // Set the name of the first player

	// Check if the entered name for the second player is not empty and has a positive length
	if (name2.size() > 0 && name2.empty() == false)
		second.set_Name(name2); // Set the name of the second player
}

// Reset the entire game class
void Game::reset(bool val = true)
{
	// Reset
	board->full_Reset(val);
	Completed = false;
	Winner = nullptr;

	// Set the current player to the second player and initialize the board as nullptr.
	first.set_Symbol('W');
	second.set_Symbol('B');
	Current = &second;
}

// Printing the command list
// This method prints the list of available commands.
void Game::print_Commands() const
{
	std::cout << std::endl;
	std::cout << "1: (Command == \"1\" || Command == \"Quit\")" << std::endl;
	std::cout << "2: (Command == \"2\" || Command == \"Load_a_Game\")" << std::endl;
	std::cout << "3: (Command == \"3\" || Command == \"Start_a_New_Game\")" << std::endl;
}

// a method that demands a random input to continue the program
void Game::input_Pause()
{
	//Press enter to continue Behavior
	std::cout << "--{[*Press Enter to Continue*]}--";
	std::cin.ignore();
	std::cin.get();
}

// Game Loading and Saving
// This method loads a game from a file.
void Game::load() // Load a saved game
{
	if (board == nullptr)
		return;
	using namespace std;
	std::cout << "Enter the name of this file: (do not add file extension) ";
	std::string Path;
	std::cin >> Path;

	if (Path.find(".txt") != std::string::npos)
		throw "Error: Wrong file format (you entered .txt)\n";

	Path += ".txt";
	ifstream Infile;
	Infile.open(Path);
	if (!Infile.is_open() || !Infile || Path == "")
	{
		string temp = "";
		if (!Infile || !Infile.is_open())
			temp += "Error: error while opening input file\n";
		if (Path == "")
			temp += "Error: empty Location\n";
		throw temp;
	}
	else
	{
		int arr[8][8] = {};
		int counter = 0;
		int counterX = 0;
		char known_turn = ' ';

		string line1 = "";

		getline(Infile, line1);
		string line2 = "";
		getline(Infile, line2);

		//proccess the last known player turn
		//read the first name and its role
		std::string name1 = "";
		if (line1.find("\\=") != string::npos)
		{
			size_t temp_turn1 = line1.find("\\=");
			known_turn = line1[temp_turn1 + 2];
			name1 = line1.substr(0, temp_turn1);
			first.set_Name(name1);
		}

		//read the second name and its role
		std::string name2 = "";
		if (line2.find("\\=") != string::npos)
		{
			size_t temp_turn2 = line2.find("\\=");
			name2 = line2.substr(0, temp_turn2);
			second.set_Name(name2);


		}

		//reading the board from the text file
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				int num = 0;
				Infile >> num;
				arr[i][j] = num;
			}
		}

		Infile.close();
		board->initialise_Board(arr);

		//Deal with character assignment for loading files
		if (known_turn == 'W')
		{
			second.set_Symbol('B');

		}
		else
		{
			second.set_Symbol('W');
		}
		first.set_Symbol(known_turn);
		if (board != nullptr)
			board->Current_Turn = known_turn;
		Current = &first;

		// Print 2D array
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

}

// This method handles saving the current game state to a file.
void Game::save()
{
	if (board == nullptr)//if null we cant save 
		return;
	std::cout << "Enter the name of this save: (do not add file extension) ";
	std::string filePath;
	std::cin >> filePath;

	filePath += ".txt";

	std::string sourceString = "";
	if (board->Current_Turn == second.get_Symbol())
	{
		sourceString += (second.get_Name() + "\\=" + second.get_Symbol());
		sourceString += "\n";
		sourceString += (first.get_Name() + "\\=" + first.get_Symbol());
		sourceString += "\n";
	}
	else
	{
		sourceString += (first.get_Name() + "\\=" + first.get_Symbol());
		sourceString += "\n";
		sourceString += (second.get_Name() + "\\=" + second.get_Symbol());
		sourceString += "\n";

	}

	sourceString += board->board_to_String();

	try
	{
		std::ofstream outputFile(filePath);
		if (!outputFile.is_open() || !outputFile || filePath == "" || filePath.find(".txt") == std::string::npos)
		{
			std::string temp = "";
			if (!outputFile)
				temp += "Error: error while opening input file\n";
			if (filePath == "")
				temp += "Error: empty Location\n";
			else if (filePath.find(".txt") == std::string::npos)
				temp += "Error: Wrong file format\n";
			throw temp;
		}
		else
		{
			outputFile << sourceString;
			outputFile.close();
			if (outputFile.fail()) {
				throw "Error: Failed to write to the file.\n";
			}
			else {
				std::cout << "String saved to file: " << filePath << std::endl;
			}
		}
	}
	catch (char const* error)
	{
		std::cerr << error;
	}
	catch (const std::string error)
	{
		std::cerr << error;
	}
}

// Destructor
Game::~Game()
{
	if (board != nullptr) {
		delete board;
		board = nullptr;
	}
	Current = nullptr;
	Winner = nullptr;
}