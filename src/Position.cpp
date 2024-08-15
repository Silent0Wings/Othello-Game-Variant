#include "Position.h"

// Static constant declaration for elements that belong to the class not the instance
char const* Position::BLACK = new char('@');  // BLACK piece symbol @
char const* Position::WHITE = new char('O');  // WHITE piece symbol o
char const* Position::EMPTY = new char(' ');  // EMPTY position symbol

// Constructor
Position::Position()
{
	Current = new char();
	set_Empty();  // Initialize as an empty position.
}
// Constructor with an initial character value
Position::Position(const char C)
{
	Current = new char(' ');
	if (C == 'W')
	{
		set_White();  // Initialize as a white piece.
	}
	else if (C == 'B')
	{
		set_Black();  // Initialize as a black piece.
	}
	else
	{
		set_Empty();  // Initialize as an empty position.
	}
}

// Setters
 // Set the value to empty
void Position::set_Empty()
{
	*Current = *EMPTY;  // Set the current position to empty.
}
// Set the value to white
void Position::set_White()
{
	*Current = *WHITE;  // Set the current position to a white piece.
}
// Set the value to black
void Position::set_Black()
{
	*Current = *BLACK;  // Set the current position to a black piece.
}

// Getters
// Check if the value is white
bool Position::is_White() const
{
	return (*Current == *WHITE);  // Check if the value contains a white piece.
}
// Check if the value is black
bool Position::is_Black() const
{
	return (*Current == *BLACK);  // Check if the value contains a black piece.
}
// Get the current position value as a string 
const char* Position::get_Current() const
{
	return Current;  // Get the current position.
}
// Get the current position symbol as a character 
const char Position::get_Symbol() const
{
	if (*Current == *WHITE)
	{
		return 'W';  // Return 'W' if the value contains a white piece.
	}
	else if (*Current == *BLACK)
	{
		return 'B';  // Return 'B' if the value contains a black piece.
	}
	else
	{
		return ' ';  // Return ' ' if the value is empty.
	}
}
// Check if the value is empty
bool Position::is_Empty() const
{
	return (*Current == *EMPTY);  // Check if the value is empty.
}
// Get the value of the static member empty
const char* Position::get_Empty_Static()
{
	return EMPTY;
}
// Get the value of the static member white
const char* Position::get_White_Static()
{
	return WHITE;
}
// Get the value of the static member black
const char* Position::get_Black_Static()
{
	return BLACK;
}

// Operations
// switch_Element the value value between white and black
void Position::switch_Element()
{
	if (is_Empty())
	{
		return;  // If the value is empty, do nothing.
	}
	else if (is_White())
	{
		set_Black();  // If the value is white, set it as white.
	}
	else if (is_Black())
	{
		set_White();  // If the value is black, set it as black.
	}
}
// Compare positions for equality 
bool Position::equal(const Position* temp) const
{
	return (*(this->Current) == *(temp->Current));  // Check if two positions are equal.
}
// Virtual function to check if a position can be played
bool Position::canPlay() const
{
	return is_Empty();  // Check if a piece can be played in this position (if it's empty).
}

// Delete static dynamic members
void Position::static_Delete()
{
	delete WHITE; // Deleting static member variables is unusual and might lead to issues
	delete BLACK; // Deleting static member variables is unusual and might lead to issues
	delete EMPTY; // Deleting static member variables is unusual and might lead to issues
	WHITE = nullptr;
	BLACK = nullptr;
	EMPTY = nullptr;

}


// Destructor
Position::~Position()
{
	if (Current != nullptr)
	{
		delete Current; // Check if Current was allocated with new[], use delete[] if it was
	}
	Current = nullptr; // Set the pointer to null
}