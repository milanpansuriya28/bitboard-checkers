#include "bitboard_checkers.h"

/*This code references many fundamental concepts from a game programming playlist
that I found incredibly helpful while learning and structuring my programs.
Playlist: https://youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&si=CwTY65-_tf_sbLnx
I've referred to this multiple times to understand game logic, loops, and general C fundamentals for this project.*/

// test bit functions
void TestBitFunctions() {
    printf("---Testing Bit Operations ---\n");
    
    uint64_t test = 0;
    
    // Test SetBit
    test = SetBit(test, 2);
    printf("After setting bit 2: ");
    PrintBinary(test);
    
    // Test ClearBit
    test = SetBit(test, 8);
    test = ClearBit(test, 2);
    printf("After setting bit 8 and clearing bit 2: ");
    PrintBinary(test);
    
    // Test ToggleBit
    test = ToggleBit(test, 9);
    printf("After toggling bit 9: ");
    PrintBinary(test);
    
    // Test CountBits
    printf("Number of 1s: %d\n", CountBits(test));
    
    // Test GetBit
    printf("Bit 8 is: %d\n", GetBit(test, 8));
    printf("Bit 2 is: %d\n", GetBit(test, 2));
    
    printf("Hex value: ");
    PrintHex(test);
    printf("\n");
}
// Main game loop
void PlayGame() {
    GameState game;
    InitializeGame(&game);

    printf("Welcome to Bitboard Checkers\n");
    printf("_____You are RED.\n");
    printf("_____The computer is BLACK.\n");
    printf("Enter moves as: from_row from_col to_row to_col\n");
    printf("Example: 5 0 4 1 (moves from 5,0 to 4,1)\n");
    printf("quit = type -1.\n");

    while (!game.game_over) {
        PrintBoard(&game);

        // If it's Red's turn
        if (game.current_turn == RED) {
            int from_row, from_col, to_row, to_col;

            printf("Your move: ");
            if (scanf("%d", &from_row) != 1 || from_row == -1) {
                printf("You quit the game.\n");
                break;
            }

            if (scanf("%d %d %d", &from_col, &to_row, &to_col) != 3) {
                printf("Invalid input! Use: from_row from_col to_row to_col\n");
                while (getchar() != '\n'); //  Using getchar(): https://youtu.be/TW3yNJU5geg?si=qEePnugtJ3mm1LxZ
                continue;
            }

            if (!MakeMove(&game, from_row, from_col, to_row, to_col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
        } 
        // If it's Black's turn
        else {
            MakeAIMove(&game);
        }
    }

    if (game.game_over)
        printf("Game over.\n");
}



int main() {
    TestBitFunctions();
    PlayGame();
    return 0;
}
