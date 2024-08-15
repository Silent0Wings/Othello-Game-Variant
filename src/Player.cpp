#include "Player.h"

Player::Player() : name{ "" }, Symbol{ ' ' } // Default constructor with empty name and space symbol
{
}

Player::Player(const std::string temp) : name{ temp } // Parameterized constructor that sets the player's name
{

}

// Setters
void Player::set_Symbol(const char temp) // Setter for the player's symbol
{
	if (temp == 'W' || temp == 'w')
		Symbol = 'W';
	else if (temp == 'B' || temp == 'b')
		Symbol = 'B';
}

void Player::set_Name(const std::string temp) // Setter for the player's name
{
	name = temp;
}

// Getters
char Player::get_Symbol() const// Getter to retrieve the player's symbol
{
	return Symbol;
}

std::string Player::get_Name() const// Getter to retrieve the player's name
{
	return name;
}

bool Player::equal(const Player compared) const
{
	return((this->get_Name() == compared.get_Name()));
}
