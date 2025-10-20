//referance : How to create and use header files (.h) : https://youtu.be/mR8P0NU-ues?si=GxxLlpFmcC3yzVXr
#ifndef BITBOARD_CHECKERS_H
#define BITBOARD_CHECKERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BOARD_SIZE 8
#define RED 0
#define BLACK 1

// referance : I Learned about typedef struct : https://youtu.be/Bw3sUC6Txus?si=IBjiDffSDi1KDQvO
// structure use in game 
typedef struct {
    uint64_t red_pieces;      
    uint64_t red_kings;       
    uint64_t black_pieces;   
    uint64_t black_kings;    
    int current_turn;        
    int game_over;
} GameState;

// functions for bit manipulation
uint64_t SetBit(uint64_t value, int position);
uint64_t ClearBit(uint64_t value, int position);
uint64_t ToggleBit(uint64_t value, int position);
int GetBit(uint64_t value, int position);
int CountBits(uint64_t value);
void PrintBinary(uint64_t value);
void PrintHex(uint64_t value);

// helper function in game
int CoordinateToPosition(int row, int col);
void PositionToCoordinate(int position, int* row, int* col);

// logic use in game
void InitializeGame(GameState* game);
void PrintBoard(GameState* game);
int IsValidMove(GameState* game, int from_row, int from_col, int to_row, int to_col);
int MakeMove(GameState* game, int from_row, int from_col, int to_row, int to_col);
int CheckWinCondition(GameState* game);
void MakeAIMove(GameState* game);

#endif
