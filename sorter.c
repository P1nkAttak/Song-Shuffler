/*
 * Author: Ben Power
 * Written: 07/02/2025
 * Updated: 07/02/2025
 * Description: Function definitions for the sorter.h file
 *
 */

#include <stdbool.h>
#include <string.h>
#include "song_data.h"
#include "sorter.h"

/*
 * Converts all characters in a string into lowercase letters
 * Used to make the sorting algorithm case-insensitive
 * Takes: A string of characters to make lower
 * Returns: NULL
 */
void ToLower(char string[])
{
	for (int index = 0; index < MAX_CHARACTERS + 1; index++)
	{
		char curr_character = string[index];

		// Null character, so the string has ended
		if (curr_character == '\0')
		{
			return;
		}

		if (curr_character >= 'A' && curr_character <= 'Z')
		{
			curr_character -= 'A' - 'a';
			string[index] = curr_character;
		}
	}
}

/*
 * Takes and sorts a list of songs
 * Artist name takes priority, followed by the song titles themselves
 * Takes: An array of songs to sort, the number of songs in the array
 * Returns: NULL
 */
void SortSongs(song song_list[], int num_songs)
{
	// This outer loop controls the number of times we traverse each element of the array
	for (int outer_index = 0; outer_index < num_songs; outer_index++)
	{
		bool is_sorted = true; // A flag to determine if we can exit the loop early

		// This inner loop traverses each element of the array and compares it with the following element
		for (int inner_index = 0; inner_index < (num_songs - 1); inner_index++)
		{
			song this_song = song_list[inner_index];
			song next_song = song_list[inner_index + 1];

			// Convert the names to lowercase to avoid casing issues
			char artist_name_1[MAX_CHARACTERS + 1];
			char artist_name_2[MAX_CHARACTERS + 1];
			strcpy(artist_name_1, this_song.Artist);
			strcpy(artist_name_2, next_song.Artist);
			ToLower(artist_name_1);
			ToLower(artist_name_2);

			int difference = strcmp(artist_name_1, artist_name_2);

			// If difference is -1, then no sorting needs to be done as those artist names are already sorted
			// Otherwise, it is handled below

			if (difference == 1)
			{
				// Swap the two song's positions
				song temp_buffer = this_song;
				song_list[inner_index] = next_song;
				song_list[inner_index + 1] = temp_buffer;
				is_sorted = false; // We had to make a change, so we flip the flag
			}
			else if (difference == 0)
			{
				// The songs have the same artist, so now we check the song titles
				// This time, we also do not care if difference is 0, since no sorting needs applying to identical songs
				char song_name_1[MAX_CHARACTERS + 1];
				char song_name_2[MAX_CHARACTERS + 1];
				strcpy(song_name_1, this_song.Title);
				strcpy(song_name_2, next_song.Title);
				ToLower(song_name_1);
				ToLower(song_name_2);

				int title_diff = strcmp(song_name_1, song_name_2);

				if (title_diff == 1)
				{
					// Swap the two song's positions
					song temp_buffer = this_song;
					song_list[inner_index] = next_song;
					song_list[inner_index + 1] = temp_buffer;
					is_sorted = false; // We had to make a change, so we flip the flag
				}
			}
		}

		// Check after every inner loop if we can exit the outer loop early
		if (is_sorted)
		{
			break;
		}
	}
}

