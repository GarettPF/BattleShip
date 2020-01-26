#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define CLEAR system("cls")
#define PAUSE system("pause")

typedef struct stats {
	int misses;
	int hits;
	int shots;
} Stats;

/*
Function: welcome_screen;
Description: Welcome screen with the rules of the game;
	@param *choice		manual/auto ship placement
	@return void;
*/
void welcome_screen(int *choice);

/*
Function: create_gameboard;
Description: initializing the gameboards to empty '~';
	@param board1		first board;
	@param board2		second board;
	@return void;
*/
void create_gameboard(char board1[][MAX_ROWS], char board2[][MAX_ROWS]);

/*
Function: is_first;
Description: picks which player goes first;
	@param void;
	@return		player number to go first;
*/
int is_first(void);

/*
Function: get_coords;
Description: Gets the x and y coords of any size;
	@param coords		the list of coords to save to;
	@param size			number of coords pairs to get;
	@return void;
*/
void get_coords(int coords[], int size);

/*
Function: check_ships_placement;
Description: checks whether the placement of a ship is valid;
	@param board		gameboard to check;
	@param coords		the coords of ship;
	@param size			the size of the ship;
	@param				1 if good, 0 if not;
*/
int check_ships_placement(char board[][MAX_ROWS], int coords[], int size);

/*
Function: manually_place;
Description: manually place the ships;
	@param board		board to place ships;
	@return				void;
*/
void manually_place(char board[][MAX_ROWS]);

/*
Function: randomly_place;
Description: function to randomly place the ships;
	@param board		board to place ships randomly;
	@return				void;
*/
void randomly_place(char board[][MAX_ROWS]);

/*
Function: check_shot;
Description: check if shot is valid and in the board;
	@param board		board to check the shot on;
	@param pos			position of the shot;
	@return				1 if good, 0 if not;
*/
int check_shot(char board[][MAX_ROWS], int pos[]);

/*
Function: is_winner;
Description: checks if there is a winner;
	@param board1		player1 board;
	@param board2		player2 board;
	@param *winner		output to player number that is winner;
	@return				1 if winner exist, 0 if not;
*/
int is_winner(char board1[][MAX_ROWS], char board2[][MAX_ROWS], int *winner);

/*
Function: update_board;
Description: updates the board to the symbol of shot;
	@param board1		board to update;
	@param shot			coord of shot;
	@param isHit		status of shot;
	@return void;
*/
void update_board(char board[][MAX_ROWS], int shot[], int isHit);

/*
Function: show_single_board;
Description: function to show a single board (used for ship placement);
	@param board		board to show;
	@return void;
*/
void show_single_board(char board[][MAX_ROWS]);

/*
Function: display_game;
Description: function to show up my TA on my GUI skills in CMD; jk James :)
	@param ships		ship board;
	@param attack		attack board;
	@param player_turn	the current players turn;
	@return void;
*/
void display_game(char ships[][MAX_ROWS], char attack[][MAX_ROWS], int player_turn);

/*
Function: ship_lives;
Description: Get the amount of lives for a given ship;
	@param board		board to check ships;
	@param shipSymbol	Ship symbol to check on board;
	@return				the amount of lives;
*/
int ship_lives(char board[][MAX_ROWS], char shipSymbol);

/*
Function: output_move;
Description: outputs the current move to statistics log;
	@param *stats		file to output to;
	@param board		game board to check sunken ships;
	@param pos			position of shot called;
	@param player		players turn;
	@param isHit		whether shot was a hit or not;
	@return void;
*/
void output_move(FILE *stats, char board[][MAX_ROWS], int pos[], int player, int isHit);