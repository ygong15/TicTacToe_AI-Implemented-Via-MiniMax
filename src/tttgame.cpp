//  Created by Nathan Greenfield on 1/1/2020.
//  Copyright � 2020 Nathan Greenfield. All rights reserved.
#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame()
{
	// a nested loop to set each cell in the mboard to empty
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            currentState.mBoard[i][j] = GameState::Empty;
        }
    }
}

GameState TicTacToeGame::getBoard() const
{
    // return the private currentState variable
	return currentState;
}

bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state)
{
	// check if the input position is occupied
    if(currentState.mBoard[row][col] != GameState::Empty)
    {
        // return false if the cell is occupied
        return false;
    }
    // input the state at the cell and return true
    currentState.mBoard[row][col] = state;
    return true;
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state)
{
    // calculate row num
    unsigned short row = (square-1)/3;
    // calculate col num
    unsigned short col = (square-1)%3;
    return setSquareState(row, col, state);
}

char TicTacToeGame::getWinner()
{
	// a char to hold the result
    char rtnVal = ' ';
    // check if one of the rows has a winner
    rtnVal = getRowWin();
    if(rtnVal != ' ')
    {
        return rtnVal;
    }
    // check if one of the columns has a winner
    rtnVal = getColWin();
    if(rtnVal != ' ')
    {
        return rtnVal;
    }
    // check if one of the crosses has a winner
    rtnVal = getCrossWin();
    if(rtnVal != ' ')
    {
        return rtnVal;
    }
    // check if the game board is full, return N if it's full
    if(isFull())
    {
        rtnVal = 'N';
    }
    return rtnVal;
}

bool TicTacToeGame::isFull()
{
    //use a nested loop to check if the board is full
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(currentState.mBoard[i][j] == GameState::Empty)
            {
                return false;
            }
        }
    }
    return true;
}

char TicTacToeGame::getColWin()
{
    // check if cell 1, 4, 7 eqauls to each other
    if(currentState.mBoard[0][0] == currentState.mBoard[1][0] && currentState.mBoard[0][0] == currentState.mBoard[2][0])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][0] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][0] == GameState::O)
        {
            return 'O';
        }
    }
    // check if cell 2, 5, 8 are equal
    else if(currentState.mBoard[0][1] == currentState.mBoard[1][1] && currentState.mBoard[0][1] == currentState.mBoard[2][1])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][1] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][1] == GameState::O)
        {
            return 'O';
        }
    }
    // check if cell 3, 6, 9 aer equal
    else if(currentState.mBoard[0][2] == currentState.mBoard[1][2] && currentState.mBoard[0][2] == currentState.mBoard[2][2])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][2] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][2] == GameState::O)
        {
            return 'O';
        }
    }
    // return ' ' to represent no winners are found
    return ' ';
    
}

char TicTacToeGame::getRowWin()
{
    // check if cell 1, 2, 3 are equal
    if(currentState.mBoard[0][0] == currentState.mBoard[0][1] && currentState.mBoard[0][0] == currentState.mBoard[0][2])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][0] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][0] == GameState::O)
        {
            return 'O';
        }
    }
    // check if cell 4, 5, 6 are equal
    else if(currentState.mBoard[1][0] == currentState.mBoard[1][1] && currentState.mBoard[1][0] == currentState.mBoard[1][2])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[1][0] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[1][0] == GameState::O)
        {
            return 'O';
        }
    }
    // check if cell 7, 8, 9 are equal
    else if(currentState.mBoard[2][0] == currentState.mBoard[2][1] && currentState.mBoard[2][0] == currentState.mBoard[2][2])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[2][0] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[2][0] == GameState::O)
        {
            return 'O';
        }
    }
    // return ' ' to represent no winner found
    return ' ';
}

char TicTacToeGame::getCrossWin()
{
    // check if cell 1, 5, 9 are equal
    if(currentState.mBoard[0][0] == currentState.mBoard[1][1] && currentState.mBoard[0][0] == currentState.mBoard[2][2])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][0] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][0] == GameState::O)
        {
            return 'O';
        }
    }
    // check if cell 3, 5, 7 are equal
    else if(currentState.mBoard[0][2] == currentState.mBoard[1][1] && currentState.mBoard[0][2] == currentState.mBoard[2][0])
    {
        // if they are equaled, check if it's empty and return either X or O
        if(currentState.mBoard[0][2] == GameState::X)
        {
            return 'X';
        }
        else if(currentState.mBoard[0][2] == GameState::O)
        {
            return 'O';
        }
    }
    // return ' ' to represet no winner found
    return ' ';
    
}

