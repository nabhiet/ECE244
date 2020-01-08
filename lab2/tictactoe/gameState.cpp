//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.

#include "tictactoe.h"
#include "gameState.h"

// get the row that the mouse clicked
int gameState::get_clickedRow() {
    return clickedRow;
}

// get the column that the mouse clicked
int gameState::get_clickedColumn() {
    return clickedColumn;
}

// check if the row clicked is on the board and set the value
void gameState::set_clickedRow(int value) {
    if (value >= 0 && value < boardSize)
        clickedRow = value;
}

// check if the column clicked is on the board and set the value
void gameState::set_clickedColumn(int value) {
    if (value >= 0 && value < boardSize)
        clickedColumn = value;
}

// get the state of the move if valid or not
bool gameState::get_moveValid() {
    return moveValid;
}

// set whether the move is valid or not
void gameState::set_moveValid(bool value) {
    moveValid = value;
}

// get the state of the game if over or not
bool gameState::get_gameOver() {
    return gameOver;
}

// set whether the game is over or not
void gameState::set_gameOver(bool value) {
    gameOver = value;
}

// get the code of the game when done
int gameState::get_winCode() {
    return winCode;
}

// set the winCode during and after game is done and check that it is a valid case
void gameState::set_winCode(int value) {
    if (value >= 0 && value <= 8)
    winCode = value;
}

// get the state of which player is playing
bool gameState::get_turn() {
    return turn;
}

// set the state to who's turn it is
void gameState::set_turn(bool value) {
    turn = value;
}

// get the game board's value in a specific row and column
int gameState::get_gameBoard(int row, int col) {
    return gameBoard[row][col];
}

// set the game board's value in a specific row and column
void gameState::set_gameBoard(int row, int col, int value) {
    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize && (value == 1 || value == -1 || value == 0))
        gameBoard[row][col] = value;
}

