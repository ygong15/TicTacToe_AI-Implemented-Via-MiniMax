//  Created by Nathan Greenfield on 1/1/2020.
//  Copyright � 2020 Nathan Greenfield. All rights reserved.
#pragma once
#include <vector>
#include "tttgamedata.h"

struct GTNode
{
	// Current state of game
	GameState mState;

	// Children nodes with future states
	std::vector<GTNode*> mChildren;
};

// Function: IsGameOver
// Purpose: Return whether the game is over or not
// Input: A GameState
// Returns: bool
bool IsGameOver(const GameState& state);

// Function: GenStates
// Purpose: Generates the game tree starting at the inputted root
// Input: A GTNode pointer with the 1st state completed
//		A boolean to indicate who's turn it is (true means it's X's turn)
// Returns: Nothing
void GenStates(GTNode* root, bool xPlayer);

// Function: GetScore
// Purpose: Examines the inputted game board to determine a winner
// Input: A game state representing a game board
// Returns: Everything is relative to O, so...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float GetScore(const GameState& state);

// Function: MinPlayer
// Purpose: Determines the minimum score this branch (or leaf) can yield
// Input: A GameTree node
// Returns: The game score meaning...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float MinPlayer(const GTNode* node);

// Function: MaxPlayer
// Purpose: Determines the maximum score this branch (or leaf) can yield
// Input: A GameTree node
// Returns: The game score meaning...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float MaxPlayer(const GTNode* node);

// Function: MinimaxDecide
// Purpose: Determines which subtree leads to O winning
// Input: A GameTree node
// Returns: The GTNode* with the winning game state
const GTNode* MinimaxDecide(const GTNode* root);

// Function: pickMove
// Purpose: Decides which square the AI should select
// Input: A game state with the current board's state
// Returns: The square number (1 through 9) the AI selects
unsigned pickMove(const GameState& board);

// Function: isFull
// Purpose: Decides whether the current game board is full
// Input: A game state with the current board's state
// Returns: true or false
bool isFull(const GameState& currentState);

// Function: getColWin
// Purpose: Determin if a winner is presented in one of the three columns
// Input: None
// Returns: a char representing the winner (X or O) or ' ' representing none
char getColWin(const GameState& currentState);

// Function: getRowWin
// Purpose: Determin if a winner is presented in one of the three rows
// Input: None
// Returns: a char representing the winner (X or O) or ' ' representing none
char getRowWin(const GameState& currentState);

// Function: getCrossWin
// Purpose: Determin if a winner is presented in one of the two crosses
// Input: None
// Returns: a char representing the winner (X or O) or ' ' representing none
char getCrossWin(const GameState& currentState);

// Function: copyBoard
// Purpose: copy elements in the root board into the child board
// Input: 1. const GTNode* root,
//        2. GTNode* child
// Returns: none
void copyBoard(const GTNode* root, GTNode* child);

// Function: getMove
// Purpose: copy elements in the root board into the child board
// Input: 1. const GTNode* root,
//        2. GTNode* child
// Returns: none
unsigned getMove(const GameState& before, const GameState& after);
