# Othello Game Variant - README
![Example](https://github.com/Silent0Wings/Othello-Game-Variant/blob/2f09b01cafeff74f0012f17e44f92abeb4be3d97/Othello.png)

## Project Overview
Project Repport .[here](https://github.com/Silent0Wings/Othello-Game-Variant/blob/2f09b01cafeff74f0012f17e44f92abeb4be3d97/Github.pdf).
UML Design .[here](https://github.com/Silent0Wings/Othello-Game-Variant/blob/2f09b01cafeff74f0012f17e44f92abeb4be3d97/UML%20Game.pdf)
This project is an implementation of a variant of the classic board game Othello. The game is developed using object-oriented programming principles, with a focus on flexibility and extensibility. The game supports various starting positions, unplayable squares, and includes functionality for saving and loading game states.

## Features

- **Customizable Starting Positions:** Players can choose from different starting configurations for the game.
- **Unplayable Squares:** Certain squares on the board are unplayable, adding a new strategic element to the game.
- **ASCII-Based Board Display:** The game board is displayed using ASCII characters, making it easy to run in any console or terminal.
- **Save/Load Functionality:** Players can save their current game state to a file and load it later to continue playing.
- **Object-Oriented Design:** The game is built using a modular, object-oriented approach, making it easy to understand and extend.

## Project Structure

The project is organized into several classes, each responsible for a specific part of the game's functionality:

- **Piece:** Represents the individual pieces on the board (white, black, or empty).
- **Board:** Manages the game board, including initialization, move validation, and display.
- **Player:** Handles player attributes such as name and assigned symbol (white or black).
- **Game:** Controls the game flow, including player turns, command input, and game state management.
- **Position:** Represents a board position, with methods to determine if a move is valid.
- **UnplayablePosition:** A subclass of Position that represents squares where pieces cannot be placed.

## How to Run the Game

### Compile the Code

Ensure you have a C++ compiler installed on your system. Compile the source files using your preferred compiler.
# Game Menu

## Overview
When the game starts, you will be presented with a menu with the following options:

- **Quit**
- **Load a Game**
- **Start a New Game**

## Gameplay
Follow the on-screen instructions to play the game. Players take turns entering coordinates to place their pieces on the board. The game will handle:

- **Turn management**
- **Move validation**
- **Display of the current state of the board after each move**

## Saving and Loading
You can save the current game state at any time and load it later to continue from where you left off.

## Future Improvements
- **Graphical User Interface (GUI)**: Implementing a GUI would enhance the user experience by providing a visual representation of the board and pieces.
- **Networked Multiplayer**: Allowing players to compete over a network would add a new dimension to the game.
- **AI Opponent**: Adding an AI opponent would enable single-player mode against the computer.

## License
This project is licensed under the MIT License. Feel free to use, modify, and distribute this software.
