#pragma once

class Position
{
private:
	// Static member variables for the possible position values.
	static char const* BLACK;
	static char const* WHITE;
	static char const* EMPTY;
	char* Current = nullptr; // Pointer to the current position value.

public:
	// Constructors
	Position(); // Default constructor
	Position(const char C); // Constructor with an initial character value

	// Setters
	void set_Empty(); // Set the value of empty
	void set_White(); // Set the value of white
	void set_Black(); // Set the value of black

	// Getters
	bool is_White() const; // Check if value of is white
	bool is_Black() const; // Check if value of is black
	const char* get_Current() const; // Get the current position value as a string 
	const char get_Symbol() const; // Get the current position symbol as a character 
	bool is_Empty() const; // Check if the value is empty
	static const char* get_Empty_Static(); // // Get the value of the static member empty
	static const char* get_White_Static(); // // Get the value of the static member white
	static const char* get_Black_Static(); // // Get the value of the static member black

	// Operations
	void switch_Element(); // switch_Element the value value between white and black
	bool equal(const Position* temp) const; // Compare positions for equality (Consider using a const pointer or reference)
	virtual bool canPlay() const; // Virtual function to check if a position can be played

	// Delete static dynamic members
	static void static_Delete();

	// Destructor
	~Position();
};