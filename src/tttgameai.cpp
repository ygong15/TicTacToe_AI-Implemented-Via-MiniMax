//  Created by Nathan Greenfield on 1/1/2020.
//  Copyright � 2020 Nathan Greenfield. All rights reserved.
// You can use this for the std::min / std::max functions
#include <algorithm>
#include "tttgameai.h"

bool isFull(const GameState& state)
{
    //use a nested loop to check if the board is full
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(state.mBoard[i][j] == GameState::Empty)
            {
                return false;
            }
        }
    }
    return true;
}

char getColWin(const GameState& currentState)
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

char getRowWin(const GameState& currentState)
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

char getCrossWin(const GameState& currentState)
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

void copyBoard(const GTNode* root, GTNode* child)
{
    // loop through all 9 cells in the root board
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            // copy the root board's cell values into the child board
            child->mState.mBoard[i][j] = root->mState.mBoard[i][j];
        }
    }
}

bool IsGameOver(const GameState& state)
{
    // if the board is full, the game is for sure over
	if(isFull(state))
    {
        return true;
    }
    // check the six possibilities to see if a winner is found
    else if(getColWin(state) == 'X' || getColWin(state) == 'O' ||
            getRowWin(state) == 'X' || getRowWin(state) == 'O' ||
            getCrossWin(state) == 'X' || getCrossWin(state) == 'O')
    {
        return true;
    }
    return false;
}

void GenStates(GTNode* root, bool xPlayer)
{
	// base case: if the game is over on the current board, we return
    if(IsGameOver(root->mState))
    {
        return;
    }
    // loop through the board, for each empty cell we build tree
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(root->mState.mBoard[i][j] == GameState::Empty)
            {
                // allocate a new child node
                GTNode* child = new GTNode();
                // copy root board into child board
                copyBoard(root, child);
                // fill the cell with corresponding symbol
                if(xPlayer)
                {
                    child->mState.mBoard[i][j] = GameState::X;
                }
                else
                {
                    child->mState.mBoard[i][j] = GameState::O;
                }
                // push back the child node into the children vector
                root->mChildren.push_back(child);
                // generate child nodes for the child with the reverse symbol
                GenStates(child, !xPlayer);
                
            }
        }
    }
    
}

float GetScore(const GameState& state)
{
    // default the game status to no winner found
    char status = ' ';
    // check column winner first
    status = getColWin(state);
    if(status == 'X')
    {
        return -1.0;
    }
    else if(status == 'O')
    {
        return 1.0;
    }
    // if no column winners are found, check row winner
    status = getRowWin(state);
    if(status == 'X')
    {
        return -1.0;
    }
    else if(status == 'O')
    {
        return 1.0;
    }
    // if no row winners are found, check cross winner
    status = getCrossWin(state);
    if(status == 'X')
    {
        return -1.0;
    }
    else if(status == 'O')
    {
        return 1.0;
    }
    // if no winner is presented it is a tide game, we dont need to check for continuity since the IsGameOver funciton will be checking that
	return 0.0;
}

float MinPlayer(const GTNode* node)
{
    // base case: the node is a leaf node, return the score
    if(node->mChildren.empty())
    {
        return GetScore(node->mState);
    }
    // initialize a vector to store each child nodes'score
    std::vector<float> score;
    for(auto& i : node->mChildren)
    {
        // calling the MaxPlayer to calculate each child nodes' score and store them in the vector
        score.push_back(MaxPlayer(i));
    }
    // return the minimum maximum score in the vector
    return *std::min_element(score.begin(), score.end());
    
}

float MaxPlayer(const GTNode* node)
{
    // base case: the node is a leaf node, return the score
    if(node->mChildren.empty())
    {
        return GetScore(node->mState);
    }
    // initialize a vector to store each child nodes'score
    std::vector<float> score;
    for(auto& i : node->mChildren)
    {
        // calling the MinPlayer to calculate each child nodes' score and store them in the vector
        score.push_back(MinPlayer(i));
    }
    // return the maximum mini score in the vector
    return *std::max_element(score.begin(), score.end());
    
}

const GTNode* MinimaxDecide(const GTNode* root)
{
    // default the move to the first child node
    GTNode* rtn = root->mChildren[0];
    // get the score of the first child node by calling the MinPlayer funciton
    float rtnVal = MinPlayer(root->mChildren[0]);
    // loop through all child nodes
    for(auto& i : root->mChildren)
    {
        // get the score of each child nodes
        float newVal = MinPlayer(i);
        // is the new score is bigger, value will be updated and the rtn node will be updated as wel
        if(newVal > rtnVal)
        {
            rtnVal = newVal;
            rtn = i;
        }
    }
    return rtn;
}

unsigned pickMove(const GameState& board)
{
    // create a new node to represent the current board
    GTNode* gameNode = new GTNode();
    // copy over the board into the new node
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            gameNode->mState.mBoard[i][j] = board.mBoard[i][j];
            
        }
    }
    // call the GenStates function to generate a game tree for the current board
    GenStates(gameNode, false);
    // decide which board do we want to produce
    const GTNode* move = MinimaxDecide(gameNode);
    // call the getMove function to get the cell number we need to move to
    return getMove(board, move->mState);
    
}

unsigned getMove(const GameState& before, const GameState& after)
{
    unsigned row;
    unsigned col;
    // loop through the board to find the chnaged cell
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(before.mBoard[i][j] != after.mBoard[i][j])
            {
                // get the row and col value for the changed cell
                row = i;
                col = j;
            }
        }
    }
    // calculate the int representing the cell between 1-9
    return 3 * row + col + 1;
}


