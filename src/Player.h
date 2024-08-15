#pragma once
#include <string>

class Player
{
private:
	std::string name; // Private member variable to store the player's name
	char Symbol = ' '; // Private member variable to store the player's symbol (default is a space character)

public:
	// Constructors
	Player();// Default constructor with empty name and space symbol

	Player(const std::string temp); // Parameterized constructor that sets the player's name

	// Setters
	void set_Symbol(const char temp); // Setter for the player's symbol

	void set_Name(const std::string temp); // Setter for the player's name

	// Getters
	char get_Symbol() const; // Getter to retrieve the player's symbol

	std::string get_Name() const;// Getter to retrieve the player's name

	bool equal(const Player) const;
};
