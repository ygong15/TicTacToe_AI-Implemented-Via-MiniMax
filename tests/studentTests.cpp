#include "catch.hpp"
#include "tttgame.h"
#include "tttgameai.h"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests -- only add sections
TEST_CASE("Student tests", "[student]") 
{
	SECTION("Default tttgame constructor")
	{
        TicTacToeGame myGame;
        GameState cur = myGame.getBoard();
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                REQUIRE(cur.mBoard[i][j] == GameState::Empty);
            }
        }
	}
    
    SECTION("setSquareState(row, col, state), isFull()")
    {
        // create a game and get the board
        TicTacToeGame myGame;
        GameState cur = myGame.getBoard();
        // check if the board isFull
        REQUIRE(!myGame.isFull());
        
        // set the board to partially filled
        myGame.setSquareState(0, 1, GameState::X);
        myGame.setSquareState(1, 1, GameState::O);
        myGame.setSquareState(2, 0, GameState::X);
        REQUIRE(!myGame.isFull());
        
        // make the board full
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                myGame.setSquareState(i, j, GameState::X);
            }
        }
        // isFull() needs to return true
        REQUIRE(myGame.isFull());
    }
    
    SECTION("setSquareState(square, state)")
    {
        // create a game and get the board
        TicTacToeGame myGame;
        GameState cur = myGame.getBoard();
        // check if the board isFull
        REQUIRE(!myGame.isFull());
        
        // set the board to partially filled
        myGame.setSquareState(1, GameState::X);
        myGame.setSquareState(2, GameState::O);
        myGame.setSquareState(9, GameState::X);
        REQUIRE(!myGame.isFull());
        
        // check if the setSquareState will return false when setting an occupied cell
        REQUIRE(!myGame.setSquareState(1, GameState::O));
        REQUIRE(!myGame.setSquareState(2, GameState::X));
        REQUIRE(!myGame.setSquareState(9, GameState::O));
        
        // make the board full
        for(int i = 1; i < 10; i++)
        {
            myGame.setSquareState(i, GameState::O);
        }
        
        // isFull() needs to return true
        REQUIRE(myGame.isFull());
        
    }
    
    SECTION("getWinner(), getColWin(), getRowWin(), getCrossWin()")
    {
        // initialize a game
        TicTacToeGame myGameRow;
        // place two X on 1 and 2
        myGameRow.setSquareState(1, GameState::X);
        myGameRow.setSquareState(2, GameState::X);
        // all of the get win fucntions should return ' '
        REQUIRE(myGameRow.getColWin() == ' ');
        REQUIRE(myGameRow.getRowWin() == ' ');
        REQUIRE(myGameRow.getCrossWin() == ' ');
        REQUIRE(myGameRow.getWinner() == ' ');
        // create a row winner with X
        myGameRow.setSquareState(3, GameState::X);
        REQUIRE(myGameRow.getColWin() == ' ');
        REQUIRE(myGameRow.getRowWin() == 'X');
        REQUIRE(myGameRow.getCrossWin() == ' ');
        // getWinner should return X
        REQUIRE(myGameRow.getWinner() == 'X');
        
        // create a cross winner with O
        TicTacToeGame myGameCross;
        myGameCross.setSquareState(1, GameState::O);
        myGameCross.setSquareState(5, GameState::O);
        myGameCross.setSquareState(9, GameState::O);
        REQUIRE(myGameCross.getCrossWin() == 'O');
        REQUIRE(myGameCross.getColWin() == ' ');
        REQUIRE(myGameCross.getRowWin() == ' ');
        REQUIRE(myGameCross.getWinner() == 'O');
        
        // create a cross winner with O
        TicTacToeGame myGameCol;
        myGameCol.setSquareState(1, GameState::O);
        myGameCol.setSquareState(4, GameState::O);
        myGameCol.setSquareState(7, GameState::O);
        REQUIRE(myGameCol.getCrossWin() == ' ');
        REQUIRE(myGameCol.getColWin() == 'O');
        REQUIRE(myGameCol.getRowWin() == ' ');
        REQUIRE(myGameCol.getWinner() == 'O');
        
        // create a tie game
        TicTacToeGame myGameTie;
        myGameTie.setSquareState(1, GameState::X);
        myGameTie.setSquareState(2, GameState::O);
        myGameTie.setSquareState(3, GameState::X);
        myGameTie.setSquareState(4, GameState::O);
        myGameTie.setSquareState(5, GameState::X);
        myGameTie.setSquareState(6, GameState::O);
        myGameTie.setSquareState(7, GameState::O);
        myGameTie.setSquareState(8, GameState::X);
        myGameTie.setSquareState(9, GameState::O);
        REQUIRE(myGameTie.getCrossWin() == ' ');
        REQUIRE(myGameTie.getColWin() == ' ');
        REQUIRE(myGameTie.getRowWin() == ' ');
        REQUIRE(myGameTie.getWinner() == 'N');
    }
    
    SECTION("getGameState, getScore")
    {
        // check for row winner
        GameState* myState = new GameState();
        REQUIRE(!isFull(*myState));
        myState->mBoard[0][0] = GameState::X;
        myState->mBoard[0][1] = GameState::X;
        myState->mBoard[0][2] = GameState::X;
        REQUIRE(!isFull(*myState));
        REQUIRE(getColWin(*myState) == ' ');
        REQUIRE(getRowWin(*myState) == 'X');
        REQUIRE(getCrossWin(*myState) == ' ');
        REQUIRE(IsGameOver(*myState));
        REQUIRE(GetScore(*myState) == -1.0);
        delete  myState;
        
        myState = new GameState();
        REQUIRE(!isFull(*myState));
        myState->mBoard[0][0] = GameState::O;
        myState->mBoard[1][0] = GameState::O;
        myState->mBoard[2][0] = GameState::O;
        REQUIRE(!isFull(*myState));
        REQUIRE(getColWin(*myState) == 'O');
        REQUIRE(getRowWin(*myState) == ' ');
        REQUIRE(getCrossWin(*myState) == ' ');
        REQUIRE(IsGameOver(*myState));
        REQUIRE(GetScore(*myState) == 1.0);
        delete  myState;
        
        myState = new GameState();
        REQUIRE(!isFull(*myState));
        myState->mBoard[0][0] = GameState::O;
        myState->mBoard[1][1] = GameState::O;
        myState->mBoard[2][2] = GameState::O;
        REQUIRE(!isFull(*myState));
        REQUIRE(getColWin(*myState) == ' ');
        REQUIRE(getRowWin(*myState) == ' ');
        REQUIRE(getCrossWin(*myState) == 'O');
        REQUIRE(IsGameOver(*myState));
        REQUIRE(GetScore(*myState) == 1.0);
        delete  myState;
        
        myState = new GameState();
        REQUIRE(!isFull(*myState));
        myState->mBoard[0][0] = GameState::O;
        myState->mBoard[0][1] = GameState::X;
        myState->mBoard[0][2] = GameState::O;
        myState->mBoard[1][0] = GameState::X;
        myState->mBoard[1][1] = GameState::O;
        myState->mBoard[1][2] = GameState::X;
        myState->mBoard[2][0] = GameState::X;
        myState->mBoard[2][1] = GameState::O;
        myState->mBoard[2][2] = GameState::X;
        REQUIRE(isFull(*myState));
        REQUIRE(getColWin(*myState) == ' ');
        REQUIRE(getRowWin(*myState) == ' ');
        REQUIRE(getCrossWin(*myState) == ' ');
        REQUIRE(IsGameOver(*myState));
        REQUIRE(GetScore(*myState) == 0.0);
        delete  myState;
    }
    
    SECTION("copyBoard")
    {
        // initialize a root board
        GTNode* root = new GTNode();
        // fill three cells in the root board
        root->mState.mBoard[0][0] = GameState::X;
        root->mState.mBoard[1][0] = GameState::X;
        root->mState.mBoard[2][0] = GameState::X;
        REQUIRE(getColWin(root->mState) == 'X');
        // create a child board
        GTNode* child = new GTNode();
        // call the copy funtion to see if child board gets successfully copied
        copyBoard(root, child);
        REQUIRE(child->mState.mBoard[0][0] == GameState::X);
        REQUIRE(child->mState.mBoard[1][0] == GameState::X);
        REQUIRE(child->mState.mBoard[2][0] == GameState::X);
        REQUIRE(getColWin(child->mState) == 'X');
        // empty the root board
        root->mState.mBoard[0][0] = GameState::Empty;
        root->mState.mBoard[1][0] = GameState::Empty;
        root->mState.mBoard[2][2] = GameState::Empty;
        REQUIRE(getColWin(root->mState) == ' ');
        // child should still have the column win
        REQUIRE(getColWin(child->mState) == 'X');
        
    }
    
    
    
}


