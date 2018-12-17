# 2048-Game
C++ Implementation for 2048 game (can be played using keyboard)

To compile, enter in command line: g++ main.cpp -o main
To run, enter in command line: ./main

This Implementation has two options at the beginning: the user can enter a txt file to start the game in an initial configuration (for e.g. input.txt) which is read by the program.

If the input file can not be read by the program the game will start with the initial configuration:

0 0 0 0

0 0 0 0

0 0 0 0

0 0 0 2

Controls for the game are:

'a' : merging everything left

'd' : merging everything right

's' : merging everything down

'w' : merging everything up

Notes:
If the program reads an invalid input character it will only print the invalid command and not the grid. Until a valid move is played, there will be no printing of the game grid.

If the input character is valid but the move does not cause a merge due to the position of the numbers in the grid the program will not print again the grid with a '2' added in a random position - it will wait until a valid move is played.

If the input character is valid and generates a merge the program will print the merged grid with a '2' added in a random position and take inputs from the user.

Finally if no moves are allowed or the game has completed with no further merges, the game will print "GAME OVER" and stop (check by entering game_over.txt at beginning of game).
