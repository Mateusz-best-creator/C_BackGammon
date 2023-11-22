#include <iostream>
#include "functions_definitions.h"
#include "conio.h"

bool play(Player* player_1, Player* player_2, Board* table_s, int player_index, bool& start_a_new_game)
{
	textcolor(LIGHTGRAY);
	// Generate two random numbers and display them	
	int dice1, dice2;
	get_random_numbers(&dice1, &dice2);
	int dice_sum = dice1 + dice2;

	// Update dice values
	if (player_index == 1)
	{
		player_1->dice1 = dice1;
		player_1->dice2 = dice2;
	}
	else
	{
		player_2->dice1 = dice1;
		player_2->dice2 = dice2;
	}

	int zn = 0, background_color = 0, zero = 0;

	// Initialize start coordinates for our '*' pointer, roughly in the middle of the board
	int star_x = 55, star_y = 16;

	// Print the entire interface for player
	print_player_interface(player_index, player_1, player_2);

	// Print the top interface
	print_top_interface(player_1, player_2, true);

	bool inserting_element = false;

	do
	{
		if ((player_1->dice1 == 0 && player_1->dice2 == 0 && player_index == 1) ||
			(player_2->dice1 == 0 && player_2->dice2 == 0 && player_index == 2))
		{
			// It means that player cannot make another moves
			break;
		}
		
		// Determine player pawn sign ("R" or "B")
		char player_sign = player_index == 1 ? player_1->pawn_char : player_2->pawn_char;

		// Print table
		print_table(table_s);

		// Print interface for removed pawns
		print_removed_pawns_interface(player_1, player_2);

		// Set some visual attributes
		textbackground(background_color);

		// Put our star on the screen
		gotoxy(star_x, star_y);
		putch('*');

		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		zero = 0;
		zn = getch();
		background_color = 0; // Reset background color
		textbackground(background_color);

		move(table_s, zn, star_x, star_y, background_color,
			zero, inserting_element, player_sign, player_1, player_2);

		// After making some move check if the player won the game
		if (player_index == 1)
		{
			if (check_if_player_won(player_1))
			{
				start_a_new_game = true;
				return true;
			}
		}
		else
		{
			if (check_if_player_won(player_2))
			{
				start_a_new_game = true;
				return true;
			}
		}

	} while (zn != 'F' && zn != 'Q');
	clrscr();

	// Stop playing the game
	if (zn == 'Q') return true;
	return false;
}