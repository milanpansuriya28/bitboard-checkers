#include "bitboard_checkers.h"


// 1. Bit Manipulation Functions
// -----------------------------------------------------
uint64_t SetBit(uint64_t value, int position) {
    return value | (1ULL << position);
}

uint64_t ClearBit(uint64_t value, int position) {
    return value & ~(1ULL << position);
}

uint64_t ToggleBit(uint64_t value, int position) {
    return value ^ (1ULL << position);
}

int GetBit(uint64_t value, int position) {
    return (value >> position) & 1ULL;
}

int CountBits(uint64_t value) {
    int count = 0;
    for (int i = 0; i < 64; i++)
        if (GetBit(value, i)) count++;
    return count;
}

void PrintBinary(uint64_t value) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", GetBit(value, i));
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

void PrintHex(uint64_t value) {
    printf("0x%016llX\n", value);
}

// Coordinate helpers for game 
// -------------------------------------------
int CoordinateToPosition(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return -1;
    return row * BOARD_SIZE + col;
}

void PositionToCoordinate(int position, int* row, int* col) {
    *row = position / BOARD_SIZE;
    *col = position % BOARD_SIZE;
}

// Initialization for game
// -------------------------------------
void InitializeGame(GameState* game) {
    game->red_pieces = 0;
    game->red_kings = 0;
    game->black_pieces = 0;
    game->black_kings = 0;
    game->current_turn = RED;
    game->game_over = 0;

    // putting pieces on dark squares of board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 1) {
                int pos = CoordinateToPosition(row, col);
                if (row < 3)
                    game->black_pieces = SetBit(game->black_pieces, pos);
                else if (row > 4)
                    game->red_pieces = SetBit(game->red_pieces, pos);
            }
        }
    }
}


// makeing  Board display
// ----------------------------------
void PrintBoard(GameState* game) {
    printf("\n    0 1 2 3 4 5 6 7\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        printf("%d | ", row);
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 0) {
                printf("  "); 
                continue;
            }

            int pos = CoordinateToPosition(row, col);
            if (GetBit(game->red_kings, pos)) printf("R ");
            else if (GetBit(game->red_pieces, pos)) printf("r ");
            else if (GetBit(game->black_kings, pos)) printf("B ");
            else if (GetBit(game->black_pieces, pos)) printf("b ");
            else printf(". ");
        }
        printf("|\n");
    }
    printf("    0 1 2 3 4 5 6 7\n");
    printf("Turn: %s\n", game->current_turn == RED ? "Red" : "Black");
}


// pieces Move logic 
// referance : https://youtu.be/eRvCLaa-3Rk?si=6ehJm11jLCxfZ7HH
// ----------------------------------------------------------------------------------------------
int IsValidMove(GameState* game, int from_row, int from_col, int to_row, int to_col) {
    int from_pos = CoordinateToPosition(from_row, from_col);
    int to_pos = CoordinateToPosition(to_row, to_col);
    if (from_pos == -1 || to_pos == -1) return 0;

    // piece can not move to an occupied block
    uint64_t all = game->red_pieces | game->red_kings | game->black_pieces | game->black_kings;
    if (GetBit(all, to_pos)) return 0;

    // Checking piece place 
    int is_red = GetBit(game->red_pieces, from_pos) || GetBit(game->red_kings, from_pos);
    int is_black = GetBit(game->black_pieces, from_pos) || GetBit(game->black_kings, from_pos);
    if (game->current_turn == RED && !is_red) return 0;
    if (game->current_turn == BLACK && !is_black) return 0;

    // checcking the direction 
    // referance : How to use the abs() function : https://youtu.be/VcEHkVStszM?si=zxfbuP6uaIOkWumO
    int row_diff = to_row - from_row;
    int col_diff = abs(to_col - from_col);

    // Non-king piece rules
    int is_king = GetBit(game->red_kings, from_pos) || GetBit(game->black_kings, from_pos);
    if (!is_king) {
        if (game->current_turn == RED && row_diff >= 0) return 0;
        if (game->current_turn == BLACK && row_diff <= 0) return 0;
    }

    // Normal move for piece
    if (abs(row_diff) == 1 && col_diff == 1)
        return 1;

    // Capture move
    if (abs(row_diff) == 2 && col_diff == 2) {
        int mid_row = from_row + row_diff / 2;
        int mid_col = from_col + (to_col - from_col) / 2;
        int mid_pos = CoordinateToPosition(mid_row, mid_col);

        int opponent_piece;
        if (game->current_turn == RED) {
            opponent_piece = GetBit(game->black_pieces, mid_pos) || GetBit(game->black_kings, mid_pos);
        } else {
            opponent_piece = GetBit(game->red_pieces, mid_pos) || GetBit(game->red_kings, mid_pos);
        }

        return opponent_piece;
    }

    return 0;
}

int MakeMove(GameState* game, int from_row, int from_col, int to_row, int to_col) {
    // Checking  for valid moves
    if (!IsValidMove(game, from_row, from_col, to_row, to_col)) {
        printf("Invalid move! Try again.\n");
        return 0;
    }

    int from_pos = CoordinateToPosition(from_row, from_col);
    int to_pos = CoordinateToPosition(to_row, to_col);

    // Checking for capture move
    int row_diff = to_row - from_row;
    int col_diff = to_col - from_col;

    int captured_red = 0;
    int captured_black = 0;

    if (abs(row_diff) == 2 && abs(col_diff) == 2) {
        int mid_row = (from_row + to_row) / 2;
        int mid_col = (from_col + to_col) / 2;
        int mid_pos = CoordinateToPosition(mid_row, mid_col);

        // Determine witch color piece captured
        if (GetBit(game->red_pieces, mid_pos) || GetBit(game->red_kings, mid_pos)) {
            captured_red = 1;
        } else if (GetBit(game->black_pieces, mid_pos) || GetBit(game->black_kings, mid_pos)) {
            captured_black = 1;
        }

        // Removing captured piece
        game->red_pieces = ClearBit(game->red_pieces, mid_pos);
        game->red_kings = ClearBit(game->red_kings, mid_pos);
        game->black_pieces = ClearBit(game->black_pieces, mid_pos);
        game->black_kings = ClearBit(game->black_kings, mid_pos);
    }

    // Move player's piece
    if (GetBit(game->red_pieces, from_pos)) {
        game->red_pieces = ClearBit(game->red_pieces, from_pos);
        game->red_pieces = SetBit(game->red_pieces, to_pos);
    } else if (GetBit(game->red_kings, from_pos)) {
        game->red_kings = ClearBit(game->red_kings, from_pos);
        game->red_kings = SetBit(game->red_kings, to_pos);
    } else if (GetBit(game->black_pieces, from_pos)) {
        game->black_pieces = ClearBit(game->black_pieces, from_pos);
        game->black_pieces = SetBit(game->black_pieces, to_pos);
    } else if (GetBit(game->black_kings, from_pos)) {
        game->black_kings = ClearBit(game->black_kings, from_pos);
        game->black_kings = SetBit(game->black_kings, to_pos);
    }

    if (captured_red)
        printf("Black captured a Red piece!\n");
    else if (captured_black)
        printf("Red captured a Black piece!\n");

    if (game->current_turn == RED && to_row == 0 && GetBit(game->red_pieces, to_pos)) {
        game->red_pieces = ClearBit(game->red_pieces, to_pos);
        game->red_kings = SetBit(game->red_kings, to_pos);
        printf("Red crowned a King!\n");
    } else if (game->current_turn == BLACK && to_row == 7 && GetBit(game->black_pieces, to_pos)) {
        game->black_pieces = ClearBit(game->black_pieces, to_pos);
        game->black_kings = SetBit(game->black_kings, to_pos);
        printf("Black crowned a King!\n");
    }

    // Switch turns
    if (game->current_turn == RED) {
        game->current_turn = BLACK;
    } else {
        game->current_turn = RED;
    }

    // Checking winning condition
    game->game_over = CheckWinCondition(game);

    printf("Move successful!\n");
    return 1;
}

// Win Check
// -------------------------------------------
int CheckWinCondition(GameState* game) {
    int red_alive = (game->red_pieces | game->red_kings) != 0;
    int black_alive = (game->black_pieces | game->black_kings) != 0;

    if (!red_alive) {
        printf("Black wins! All red pieces captured.\n");
        return 1;
    }
    if (!black_alive) {
        printf("Red wins! All black pieces captured.\n");
        return 1;
    }
    return 0;
}

// i used AI moves for black color pieces (bonus)
//--------------------------------------------------
void MakeAIMove(GameState* game) {
    // Only move if it's Black's turn
    if (game->current_turn != BLACK || game->game_over) return;

    for (int from_row = 0; from_row < BOARD_SIZE; from_row++) {
        for (int from_col = 0; from_col < BOARD_SIZE; from_col++) {
            for (int to_row = 0; to_row < BOARD_SIZE; to_row++) {
                for (int to_col = 0; to_col < BOARD_SIZE; to_col++) {
                    if (IsValidMove(game, from_row, from_col, to_row, to_col)) {
                        printf("AI moved from %d,%d to %d,%d\n", from_row, from_col, to_row, to_col);
                        MakeMove(game, from_row, from_col, to_row, to_col);
                        return;
                    }
                }
            }
        }
    }

    // game over if no valid move is found
    printf("AI has no valid moves! Red wins by default.\n");
    game->game_over = 1;
}

