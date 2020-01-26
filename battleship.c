#include "battleship.h"

void welcome_screen(int* choice) {

	// Welcome screen and rules
	printf("----- Welcome to Battleship! -----\n\n");
	printf("Rules of the game:\n");
	printf("1. This is a 2 player game\n");
	printf("2. Player1 is you and Player2 is the computer\n");
	printf("3. The player who goes first is randomly choosen\n");
	printf("4. Each player takes turns calling out coordinates\n");
	printf("   A shot can be either a miss or a hit.\n");
	printf("5. Once a ship has lost all it's lives, it is a sunken ship\n");
	printf("6. First player to sink the others ships is the winner\n");
	system("pause");
	
	// Give player choice for placement of ships
	do {
		system("cls");
		printf("Please select from the following menu:\n");
		printf("1. Enter the positions of the ship manually\n");
		printf("2. Allow the program to randomly select positions of ships\n");
		scanf("%1d", choice);
	} while (*choice != 1 && *choice != 2);
}

void create_gameboard(char board1[][MAX_ROWS], char board2[][MAX_ROWS]) {
	for (int x = 0; x < MAX_COLS; x++) {
		for (int y = 0; y < MAX_ROWS; y++) {
			board1[x][y] = '~';
			board2[x][y] = '~';
		}
	}
}

int is_first(void) {
	int player1 = 0, player2 = 0, dice, player_first = 1;

	for (int i = 0; i < 100; i++) {
		dice = rand() % 6 + 1;

		if (dice > 3) {
			player1++;
		}
		else {
			player2++;
		}
	}
	if (player1 > player2) {
		player_first = 0;
	}

	return player_first;
}

void get_coords(int coords[], int size) {
	char y;
	for (int i = 0; i < size * 2; i += 2) {
		scanf(" %1c", &y);
		y -= 49;
		coords[i + 1] = y - '0';

		scanf("%1d", &coords[i]);
	}
}

int check_ships_placement(char board[][MAX_ROWS], int coords[], int size) {
	int x = 0, y = 1, num, isGood = 1, sameR = 1, sameC = 1;

	// check if same row or same col
	num = coords[x];
	for (x = 2; x < size; x += 2) {
		if (coords[x] != num) {
			sameR = 0;
		}
	}
	num = coords[y];
	for (y = 3; y < size; y += 2) {
		if (coords[y] != num) {
			sameC = 0;
		}
	}
	if (sameC == sameR) {
		isGood = 0;
	}

	// check if coordinates taken
	for (int i = 0; i < size; i += 2) {
		if (board[coords[i]][coords[i + 1]] != '~') {
			isGood = 0;
		}
	}

	// check if coordinates within boundaries
	for (int i = 0; i < size; ++i) {
		if (coords[i] > 9 || coords[i] < 0) {
			isGood = 0;
		}
	}

	return isGood;
}

void manually_place(char board[][MAX_ROWS]) {
	char ships[5] = { 'c','b','r','s','d' };
	int carrier[10], battleship[8], cruiser[6], submarine[6], destroyer[4],
		i;

	do { // place carrier ship
		CLEAR;
		show_single_board(board);
		printf("Please enter 5 cells to place the Carrier(c) across:\n");
		printf("EX: a1 a2 a3 a4 a5\n\n");
		get_coords(carrier, 5);
		
	} while (!check_ships_placement(board, carrier, 10));
	for (i = 0; i < 10; i += 2) {
		board[carrier[i]][carrier[i + 1]] = ships[0];
	}

	do { // place battleship
		CLEAR;
		show_single_board(board);
		printf("Please enter 4 cells to place the Battleship(b) across:\n");
		printf("EX: b1 b2 b3 b4\n\n");
		get_coords(battleship, 4);

	} while (!check_ships_placement(board, battleship, 8));
	for (i = 0; i < 8; i += 2) {
		board[battleship[i]][battleship[i + 1]] = ships[1];
	}

	do { // place cruiser
		CLEAR;
		show_single_board(board);
		printf("Please enter 3 cells to place the Cruiser(r) across:\n");
		printf("EX: a0 b0 c0\n\n");
		get_coords(cruiser, 3);

	} while (!check_ships_placement(board, cruiser, 6));
	for (i = 0; i < 6; i += 2) {
		board[cruiser[i]][cruiser[i + 1]] = ships[2];
	}

	do { // place submarine
		CLEAR;
		show_single_board(board);
		printf("Please enter 3 cells to place the Submarine(s) across:\n");
		printf("EX: f3 f4 f5\n\n");
		get_coords(submarine, 3);

	} while (!check_ships_placement(board, submarine, 6));
	for (i = 0; i < 6; i += 2) {
		board[submarine[i]][submarine[i + 1]] = ships[3];
	}

	do { // place destroyer
		CLEAR;
		show_single_board(board);
		printf("Please enter 2 cells to place the Destroyer(d) across:\n");
		printf("EX: d4 d5\n\n");
		get_coords(destroyer, 2);

	} while (!check_ships_placement(board, destroyer, 4));
	for (i = 0; i < 4; i += 2) {
		board[destroyer[i]][destroyer[i + 1]] = ships[4];
	}

	CLEAR;
	show_single_board(board);
	printf("This will be your ship grid\n");
	PAUSE;
}

void randomly_place(char board[][MAX_ROWS]) {
	int ship_sizes[5] = { 10, 8, 6, 6, 4 },
		coordinates[10] = { 0 },
		i, j, x, y, direction, xory;
	char ships[5] = { 'c', 'b', 'r', 's', 'd' };

	for (i = 0; i < 5; i++) { // for each ship
		
		do {
			x = rand() % 9 + 1;
			y = rand() % 9 + 1;
			xory = rand() % 2; // 0 = x; 1 = y;
			do {
				direction = rand() % 3 - 1; // either -1 or 1
			} while (!direction);

			if (xory) {
				for (j = 0; j < ship_sizes[i]; ++j) { // change y by direction
					coordinates[j++] = x;
					coordinates[j] = y += direction;
				}
			}
			else {
				for (j = 0; j < ship_sizes[i]; ++j) { // change x by direction
					coordinates[j++] = x += direction;
					coordinates[j] = y;
				}
			}
			// checks if coordinates are good
		} while (!check_ships_placement(board, coordinates, ship_sizes[i]));

		// places ships on board if good
		for (j = 0; j < ship_sizes[i]; j += 2) {
			board[coordinates[j]][coordinates[j + 1]] = ships[i];
		}
	}
}

int check_shot(char board[][MAX_ROWS], int pos[]) {
	int status = 1, x = pos[0], y = pos[1];
	if (board[x][y] == '~') {
		status = 0;
	}
	else if (board[x][y] == '*') {
		status = 2;
	}
	else if (board[x][y] == 'm') {
		status = 2;
	}

	return status;
}

int is_winner(char board1[][MAX_ROWS], char board2[][MAX_ROWS], int *winner) {
	int isWinner = 0, player1 = 1, player2 = 1, x, y, z;
	char ships[5] = { 'c','b','r','s','d' };

	for (x = 0; x < MAX_COLS; ++x) {
		for (y = 0; y < MAX_ROWS; ++y) {
			for (z = 0; z < 5; ++z) {
				if (board1[x][y] == ships[z]) {
					player2 = 0;
				}
				if (board2[x][y] == ships[z]) {
					player1 = 0;
				}
			}
		}
	}

	if (player1 || player2) {
		isWinner = 1;
	}

	if (player1) {
		*winner = 1;
	}
	else if (player2) {
		*winner = 2;
	}

	return isWinner;
}

void update_board(char board[][MAX_ROWS], int shot[], int isHit) {
	if (isHit) {
		board[shot[0]][shot[1]] = '*';
		printf("%c%d was a hit!\n", shot[1] + 65, shot[0]);
	}
	else {
		board[shot[0]][shot[1]] = 'm';
		printf("%c%d was a miss\n", shot[1] + 65, shot[0]);
	}
}

void show_single_board(char board[][MAX_ROWS]) {
	int x, y;
	char yCoor = 'A';
	
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	}	printf("+---+\n|   |");
	for (x = 0; x < MAX_COLS; ++x) {
		printf(" %d |", x);
	}	printf("\n");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	}	printf("+---+\n");
	for (y = 0; y < MAX_ROWS; ++y) {

		printf("| %c |", yCoor++);
		for (x = 0; x < MAX_COLS - 1; ++x) {
			printf(" %c  ", board[x][y]);
		}	printf(" %c |\n", board[x][y]);

		printf("+---+");
		for (x = 0; x < MAX_COLS - 1; ++x) {
			if (y < MAX_ROWS - 1) { printf("    "); }
			else { printf("----"); }
		}	
		if (y < MAX_ROWS - 1) { printf("   |\n"); }
		else { printf("---+\n"); }
	}

}

void display_game(char ships[][MAX_ROWS], char attack[][MAX_ROWS], int player_turn) {
	int x, y;
	char symbols[5] = { 'c', 'b', 'r', 's', 'd' };

	// Display battleship title and grid title
	for (x = 0; x < 45; ++x) {
		printf("#");
	}
	printf("%10s%-10s", "BATTL", "ESHIP");
	for (x = 0; x < 45; ++x) {
		printf("#");
	} printf("\n\n");
	printf("%23s%-22s%20s%22s%-23s\n", "Ship ", "Grid", "", "Attac", "k Grid");

	// display x coordinates for both board
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	} printf("+---+%20s","");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	} printf("+---+\n");
	printf("|   ");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("| %d ", x);
	} printf("|%20s|   ", "");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("| %d ", x);
	} printf("|\n");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	} printf("+---+%20s", "");
	for (x = 0; x < MAX_COLS; ++x) {
		printf("+---");
	} printf("+---+\n");

	// display rest of board
	char yCoor1 = 'A', yCoor2 = yCoor1;
	for (y = 0; y < MAX_ROWS; ++y) {

		// ships grid
		printf("| %c |", yCoor1++);
		for (x = 0; x < MAX_COLS - 1; ++x) {
			printf(" %c  ", ships[x][y]);
		} printf(" %c |", ships[x][y]);

		// legends
		if (y == 0) { printf("%10s%-10s", "-Leg", "end-"); }
		else if (y == 1) { printf("%11s%-9s", "~ = e", "mpty"); }
		else if (y == 2) { printf("%11s%-9s", "m = m", "iss"); }
		else if (y == 3) { printf("%11s%-9s", "* = H", "it!"); }
		else { printf("%20s", ""); }

		// attack grid
		printf("| %c |", yCoor2++);
		for (x = 0; x < MAX_COLS - 1; ++x) {
			if (attack[x][y] == 'c' ||
				attack[x][y] == 'b' ||
				attack[x][y] == 'r' ||
				attack[x][y] == 'r' ||
				attack[x][y] == 's' ||
				attack[x][y] == 'd') {
				printf(" ~  ");
			}
			else {
				printf(" %c  ", attack[x][y]);
			}
		} 
		if (attack[x][y] == 'c' ||
			attack[x][y] == 'b' ||
			attack[x][y] == 'r' ||
			attack[x][y] == 'r' ||
			attack[x][y] == 's' ||
			attack[x][y] == 'd') {
			printf(" ~ |\n");
		}
		else {
			printf(" %c |\n", attack[x][y]);
		}

		// line
		printf("+---+");
		for (x = 0; x < MAX_COLS - 1; ++x) {
			if (y != 9) { printf("    "); }
			else { printf("----"); }
		} 
		if (y != 9) { printf("   |%20s+---+", ""); }
		else { printf("---+%20s+---+", ""); }

		for (x = 0; x < MAX_COLS - 1; ++x) {
			if (y != 9) { printf("    "); }
			else { printf("----"); }
		}
		if (y != 9) { printf("   |\n"); }
		else { printf("---+\n"); }
	}

	// ships lives
	printf("%-65s%-45s\n", "Ship Lives", "Ship Lives");
	for (int ship = 0; ship < 5; ++ship) {
		printf("%c:", symbols[ship]);
		if (!ship_lives(ships, symbols[ship])) {
			printf("%-15s", "Ship sunk");
		}
		else {
			for (x = 0; x < ship_lives(ships, symbols[ship]); ++x) {
				printf("%-3s", " <3");
			}
			for (x = 0; x < 5 - ship_lives(ships, symbols[ship]); ++x) {
				printf("%3s", "   ");
			}
		}
		printf("%48s", "");

		printf("%c:", symbols[ship]);
		if (!ship_lives(attack, symbols[ship])) {
			printf(" Sunk");
		}
		for (x = 0; x < ship_lives(attack, symbols[ship]); ++x) {
			printf("%-3s", " <3");
		} printf("\n");
	} printf("\n");

	// which players turn
	for (x = 0; x < 45; ++x) {
		printf("#");
	}
	printf("%10s%d%c%-8s", "Player ", player_turn, 's', " Turn");
	for (x = 0; x < 45; ++x) {
		printf("#");
	} printf("\n\n");

}

int ship_lives(char board[][MAX_ROWS], char shipSymbol) {
	int lives = 0, row = 0, col;

	for (; row < MAX_ROWS; ++row) {
		for (col = 0; col < MAX_COLS; ++col) {
			if (board[col][row] == shipSymbol) {
				lives++;
			}
		}
	}

	return lives;
}

void output_move(FILE* stats, char board[][MAX_ROWS], int pos[], int player, int isHit) {
	char ship = '\0';
	int sunk = 1, count = 0;

	if (isHit) {
		fprintf(stats, "Player %d hit on %c%d\n", player, pos[1] + 65, pos[0]);
		ship = board[pos[0]][pos[1]];
		for (int x = 0; x < MAX_COLS; ++x) {
			for (int y = 0; y < MAX_ROWS; ++y) {
				if (board[x][y] == ship) {
					++count;
				}
			}
		}

		if (count > 1) { sunk = 0; };

		if (sunk) {
			fprintf(stats, "Player %d sunk %c\n", player, ship);
		}
	}
	else {
		fprintf(stats, "Player %d missed on %c%d\n", player, pos[1] + 65, pos[0]);
	}

}