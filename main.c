/*
	Author: Garett Pascual-Folster
	Date: 10/24/2019
	Description: A game of battleship
*/

#include "battleship.h"

int main(void) {
	FILE* stats = fopen("battleship.log", "w");
	char ships[MAX_COLS][MAX_ROWS], attack[MAX_COLS][MAX_ROWS];
	int choice, player, shot[2], winner, status;

	// player stats
	Stats player1 = { 0, 0, 0 }, player2 = { 0, 0, 0 };

	// welcome screen and ship placement
	welcome_screen(&choice);
	create_gameboard(ships, attack);
	srand(time(NULL));
	CLEAR;

	if (choice == 1) { // manually place ships
		manually_place(ships);
	}
	else if (choice == 2) { // randomlly place ships
		do {
			CLEAR;
			create_gameboard(ships, attack);
			randomly_place(ships);
			show_single_board(ships);
			printf("This will be your ships grid\n");
			printf("1. Keep placement\n");
			printf("2. Place ships again\n");
			scanf("%d", &choice);
		} while (choice == 2);
	}   
	randomly_place(attack);



	// choose first player
	player = is_first();

	while (!is_winner(ships, attack, &winner)) {
		CLEAR;
		display_game(ships, attack, player + 1);

		if (!player) { // if player 1
			printf("Enter a shot: ");
			do {
				get_coords(shot, 1);
				status = check_shot(attack, shot);
			} while (status == 2);

			// update board & output stats
			output_move(stats, attack, shot, 1, status);
			if (status) {
				player1.hits++;
			}
			else {
				player1.misses++;
			}
			player1.shots++;
			update_board(attack, shot, status);
		}
		else { // if computers turn
			do {
				shot[0] = rand() % 9 + 1;
				shot[1] = rand() % 9 + 1;
				status = check_shot(ships, shot);
			} while (status == 2);

			// update board
			output_move(stats, ships, shot, 2, status);
			if (status) {
				player2.hits++;
			}
			else {
				player2.misses++;
			}
			player2.shots++;
			update_board(ships, shot, status);
		}


		PAUSE;

		// switch players
		player -= pow(-1, player + 1);
	} // end of game

	//log winner to file
	fprintf(stats, "\nWinner is player %d\n", winner);
	fprintf(stats, "Player1 stats:\n");
	fprintf(stats, "Hits: %d\nMisses: %d\nShots: %d\nHit to miss ratio: %.2lf\n\n",
		player1.hits, player1.misses, player1.shots, (double)player1.hits / player1.misses);
	fprintf(stats, "Player2 stats:\n");
	fprintf(stats, "Hits: %d\nMisses: %d\nShots: %d\nHit to miss ratio: %.2lf\n\n",
		player2.hits, player2.misses, player2.shots, (double)player2.hits / player2.misses);
	fclose(stats);

	//display winner
	CLEAR;
	printf("CONGRATULATIONS PLAYER %d, YOU ARE THE WINNER!!!\n\n", winner);


	return 0;
}