# CS 3503 Project 1 - Bitboard Checkers

## Author
Milan H. Pansuriya

## Description
This is my implementation of Owl Tech's bitboard-based checkers game. I created a complete checkers game using bit manipulation techniques where each piece on the board is represented by a single bit in 64-bit integers. The game features two-player functionality with a simple AI opponent, proper move validation, piece capturing, king promotion, and win condition detection.

## Key Features
- Bit Manipulation Library: Complete set of functions for bit operations (set, clear, toggle, get, count)
- Bitboard Game Engine: Uses 64-bit integers to represent game state efficiently
- Full Checkers Rules: Valid moves, captures, king promotion, and win conditions
- AI Opponent: Computer player that makes valid moves for the black pieces
- Clean Display: ASCII board representation with coordinate system
- Input Validation: Proper move checking and error handling
  
## Build Instructions
gcc -o checkers main.c bitboard_checkers.c
./checkers

## How to Play
1.Run the program and you'll see the checkers board
2.You play as RED (represented by 'r' for regular pieces and 'R' for kings)
3.The computer plays as BLACK (represented by 'b' and 'B')
4.Enter moves in the format: from_row from_col to_row to_col
5.Example: 5 0 4 1 moves a piece from row 5, column 0 to row 4, column 1
6.Type -1 to quit the game

## Project Structure
- bitboard_checkers.h - Header file with type definitions and function declarations
- bitboard_checkers.c - Core game logic and bit manipulation functions
- main.c - Main game loop and testing functions

## Technical Highlights
- Uses bitwise operations for all game logic
- Efficient board representation using four 64-bit integers (red pieces, red kings, black pieces, black kings)
- Coordinate system that maps between board positions and bit positions
- Complete move validation including capture detection and king promotion

## Notes
This project was a great learning experience in low-level programming. The most challenging part was implementing the move validation logic while properly handling both regular pieces and kings. I discovered that using bitboards makes certain operations very efficient (like checking if squares are occupied) while making other operations more complex. The project helped me deeply understand how bitwise operations work in practical applications.

One interesting discovery was how the coordinate system maps to bit positions - it took some trial and error to get the board display and movement directions correct. I also learned about the importance of using unsigned integers for bit manipulation to avoid unexpected behavior with signed shifts.

## References
- Some resources that were helpful while completing this assignment:
- Typedef struct and creating custom data types: [YouTube Video](https://youtu.be/Bw3sUC6Txus?si=IBjiDffSDi1KDQvO)
- Fundamentals of game programming concepts: [YouTube Playlist](https://youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&si=CwTY65-_tf_sbLnx)
- Creating and using header files (.h): [YouTube Video](https://youtu.be/mR8P0NU-ues?si=GxxLlpFmcC3yzVXr)
- Using abs() for absolute value calculations: [YouTube Video](https://youtu.be/VcEHkVStszM?si=zxfbuP6uaIOkWumO)
- Using getchar() for reading single character input: [YouTube Video](https://youtu.be/TW3yNJU5geg?si=qEePnugtJ3mm1LxZ)
