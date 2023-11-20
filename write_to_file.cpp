#include <iostream>
#include <stdio.h>
#include <string.h>
#include "functions_definitions.h"

static int turn_counter = 0;

void write_to_file(const char table[][WIDTH])
{
    FILE* file;

    // Open the file using fopen_s
    if (fopen_s(&file, "state_of_the_game_readable.txt", "a") != 0) {
        return;
    }

    fprintf(file, "\n============================\nState of the game at turn %d\n============================\n", turn_counter);
    turn_counter++;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            fprintf(file, "%c", table[i][j]);
        }
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);
}

static int binary_turn_counter = 0;

void write_to_binary_file(const char table[][WIDTH])
{
    FILE* file_binary;

    // Open the file in binary write mode
    if (fopen_s(&file_binary, "state_of_the_game_binary", "ab") != 0) {
        return;
    }

    fprintf(file_binary, "\n============================\nState of the game at turn %d\n============================\n", binary_turn_counter);
    binary_turn_counter++;
    // Write the array to the file
    fwrite(table, sizeof(char), HEIGHT * WIDTH, file_binary);

    // Close the file
    fclose(file_binary);
}