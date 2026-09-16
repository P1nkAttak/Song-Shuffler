/*
 * Author: Ben Power
 * Written: 05/02/2025
 * Updated: 19/02/2025
 * Description: Function definitions for the getter.h file
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "song_data.h"
#include "getter.h"

/*
 * Reads a string from the console and writes it to the specified array
 * Terminates automatically if a newline character is used or max_chars is reached
 * Takes: An array to write to, a number specifying the max number of characters
 * Returns: A boolean specifying whether anything was entered
 */
bool ReadString(char write_array[], unsigned int max_chars)
{
	unsigned int current_character = 0;

	while (current_character < max_chars)
	{
		char this_char = getchar();

		if (this_char == '\n') // Newline character means we terminate the loop
		{
			break;
		}

		write_array[current_character] = this_char;
		current_character += 1;
	}

	if (current_character == 0) // Nothing was entered
	{
		return false;
	}

	write_array[current_character] = '\0';
	return true;
}

/*
 * This function takes a list and fills it with songs based on input from the user
 * Takes: A pointer to a list where the songs will be input
 * Returns: NULL
 */
int PopulateList(song list_to_fill[])
{
	int num_songs = 0;
	char nums_to_words[][7] = {"first", "second", "third"};

	for (unsigned int artist_index = 0; artist_index < MAX_ARTISTS; artist_index++)
	{
		char current_artist[MAX_CHARACTERS + 1];
		printf("Enter an artist/group name: ");

		fflush(stdout);
		bool should_continue_artists = ReadString(current_artist, MAX_CHARACTERS);

		if (!should_continue_artists) // Nothing was entered as an artist, so we stop reading for artists
		{
			printf("\n"); // Needed to ensure consistent whitespace when fewer artists are entered
			break;
		}

		// Read songs for this artist
		printf("\n");
		for (unsigned int song_index = 0; song_index < MAX_SONGS; song_index++)
		{
			char current_song[MAX_CHARACTERS + 1];
			printf("Enter the %s song for %s: ", nums_to_words[song_index], current_artist);

			fflush(stdout);
			bool should_continue_songs = ReadString(current_song, MAX_CHARACTERS);

			if (!should_continue_songs) // Nothing was entered as a song, so we stop reading for this artist
			{
				break;
			}

			// Fill out the information gathered
			strcpy(list_to_fill[num_songs].Artist, current_artist);
			strcpy(list_to_fill[num_songs].Title, current_song);
			list_to_fill[num_songs].Id = num_songs + 1;
			num_songs++;
		}
		printf("\n");
		fflush(stdout);
	}

	return num_songs;
}
