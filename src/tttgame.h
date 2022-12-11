//  Created by Nathan Greenfield on 1/1/2020.
//  Copyright � 2020 Nathan Greenfield. All rights reserved.
#pragma once
#include "tttgamedata.h"

// Represents the current TicTacToe Game
class TicTacToeGame
{
public:

	// Function: Constructor
	// Purpose: Creates a GameState with empty spots
	// Input: None
	// Returns: None
	TicTacToeGame();

	// Function: getBoard
	// Purpose: Return the current GameState
	// Input: None
	// Returns: The current game state
	GameState getBoard() const;

	// Function: setSquareState
	// Purpose: Claims the entered state for the inputted player
	// Input:	1. Unsigned short for row
	//			2. Unsigned short for column
	//			3. The player's symbol (X or O)
	// Returns: boolean -- true if the spot was set successfully
	// Note: Uses the row/column to identify a board position
	bool setSquareState(unsigned short row, unsigned short col, GameState::SquareState state);

	// Function: setSquareState
	// Purpose: Claims the entered state for the inputted player
	// Input:	1. Unsigned short spot number
	//			2. The player's symbol (X or O)
	// Returns: boolean -- true if the spot was set successfully
	// Note: Uses the number ordering to indicate a spot
	//		1 is upper left corner, 9 is lower, right corner
	bool setSquareState(unsigned short square, GameState::SquareState state);

	// Function: getWinner
	// Purpose: Determines if there's a game winner
	// Input: None
	// Returns: Character to determine winner
	//			'X' to indicate X player wins
	//			'O' to indicate O player wins
	//			'N' to indicate tie game
	//			' ' to indicate no winner yet
	char getWinner();

    // Function: isFull
    // Purpose: Determines if the current game board is full
    // Input: None
    // Returns: 1. true indicating the board is full
    //          2. false indicating the board is not full
    bool isFull();
    
    // Function: getColWin
    // Purpose: Determin if a winner is presented in one of the three columns
    // Input: None
    // Returns: a char representing the winner (X or O) or ' ' representing none
    char getColWin();
    
    // Function: getRowWin
    // Purpose: Determin if a winner is presented in one of the three rows
    // Input: None
    // Returns: a char representing the winner (X or O) or ' ' representing none
    char getRowWin();
    
    // Function: getCrossWin
    // Purpose: Determin if a winner is presented in one of the two crosses
    // Input: None
    // Returns: a char representing the winner (X or O) or ' ' representing none
    char getCrossWin();
    
    
private:
	// Represents the current game state
	// Update this variable as the game progresses
	GameState currentState;
};

