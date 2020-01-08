//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h" 
#include "gameState.h"

void playMove(gameState& game_state) {
    // check if the clicked row and column is empty
    if (game_state.get_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn()) == 0) {
        game_state.set_moveValid(true);
        if (game_state.get_turn() == true) { // if X player's turn then place an X and change to O's turn
            game_state.set_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn(), 1);
            game_state.set_turn(false);
        } else { // if O player's turn then place an O and change to X's turn
            game_state.set_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn(), -1);
            game_state.set_turn(true);
        }
    } else
        game_state.set_moveValid(true);

    // go through the entire board to check if the board is full
    int draw = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game_state.get_gameBoard(i, j) != 0)
                draw++;
        }
    }

    // check through each case to see if a player has won, it is a draw or game is continued
    if (game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(0, 1) && game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(0, 2) && game_state.get_gameBoard(0, 0) != 0) {
        game_state.set_winCode(1);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(1, 0) == game_state.get_gameBoard(1, 1) && game_state.get_gameBoard(1, 0) == game_state.get_gameBoard(1, 2) && game_state.get_gameBoard(1, 0) != 0) {
        game_state.set_winCode(2);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(2, 0) == game_state.get_gameBoard(2, 1) && game_state.get_gameBoard(2, 0) == game_state.get_gameBoard(2, 2) && game_state.get_gameBoard(2, 0) != 0) {
        game_state.set_winCode(3);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(1, 0) && game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(2, 0) && game_state.get_gameBoard(0, 0) != 0) {
        game_state.set_winCode(4);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(0, 1) == game_state.get_gameBoard(1, 1) && game_state.get_gameBoard(0, 1) == game_state.get_gameBoard(2, 1) && game_state.get_gameBoard(0, 1) != 0) {
        game_state.set_winCode(5);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(0, 2) == game_state.get_gameBoard(1, 2) && game_state.get_gameBoard(0, 2) == game_state.get_gameBoard(2, 2) && game_state.get_gameBoard(0, 2) != 0) {
        game_state.set_winCode(6);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(1, 1) && game_state.get_gameBoard(0, 0) == game_state.get_gameBoard(2, 2) && game_state.get_gameBoard(0, 0) != 0) {
        game_state.set_winCode(7);
        game_state.set_gameOver(true);
    } else if (game_state.get_gameBoard(2, 0) == game_state.get_gameBoard(1, 1) && game_state.get_gameBoard(2, 0) == game_state.get_gameBoard(0, 2) && game_state.get_gameBoard(2, 0) != 0) {
        game_state.set_winCode(8);
        game_state.set_gameOver(true);
    } else {
        game_state.set_winCode(0);
        if (draw == 9) game_state.set_gameOver(true); // the game is over if the board is full (draw)
        else game_state.set_gameOver(false); // the game is to be continued
    }
}

