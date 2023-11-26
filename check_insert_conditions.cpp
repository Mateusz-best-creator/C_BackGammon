#include "functions_definitions.h"

bool check_insert_conditions(Board* table_s, Player* player_AI, int i, int j, const char AI_pawn_char, int dice_value)
{
	int player_1_pawns_on_bar = 0;
	int player_AI_pawns_on_bar = 0;

	for (int i = 0; i < BAR_SIZE; ++i)
	{
		if (table_s->player_1_bar[i] == 'B') { player_1_pawns_on_bar++; }
		if (table_s->player_2_bar[i] == 'R') { player_AI_pawns_on_bar++; }
	}

	// Empty column
	if (table_s->pawns[i + dice_value][0] == 'E')
	{
		table_s->pawns[i][j] = 'E';
		table_s->pawns[i + dice_value][0] = AI_pawn_char;
		return true;
	}
	// Zbicie piona
	else if (table_s->pawns[i + dice_value][0] == 'B' && table_s->pawns[i + dice_value][1] == 'E')
	{
		table_s->pawns[i][j] = 'E';
		table_s->pawns[i + dice_value][0] = AI_pawn_char;
		update_bar_pawns(table_s->player_1_bar, 'B', player_1_pawns_on_bar);
		return true;
	}
	// Column is arleady occupied by AI pawns and we are able to insert the pawn
	else if (table_s->pawns[i + dice_value][0] == AI_pawn_char)
	{
		for (size_t k = 0; k < NUMBER_OF_ROWS_IN_COLUMN; ++k)
		{
			if (table_s->pawns[i + dice_value][k] == 'E')
			{
				table_s->pawns[i + dice_value][k] = 'R';
				table_s->pawns[i][j] = 'E';
				return true;
			}
		}
	}

	return false;
}

