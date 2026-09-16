/*
 * Author: Ben Power
 * Written: 15/02/2025
 * Updated: 19/02/2025
 * Description: Function definitions for the shuffle.h file
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "song_data.h"
#include "shuffle.h"

#define MAX_GAP 5

/*
 * A function which returns the distance between duplicate songs in our list of songs
 * Takes: A list of songs, the size of the list, the start index, the index to ignore the song ID to check for
 * Returns: An int specifying the distance (eg. index 0 and index 1 return 1, index 2 and index 0 return -2)
 */
int GetDistance(song song_list[], int size, int start_index, int ignore_index, int id_to_check)
{
	for (int index = 0; index < size; index++)
	{
		// Skip the original song at ignore_index
		if (index == ignore_index)
		{
			continue;
		}

		song this_song = song_list[index];
		if (this_song.Id == id_to_check)
		{
			int distance = index - start_index;
			return distance;
		}
	}

	// This should never return unless the call is illegal
	return 0;
}

/*
 * A function which takes a list of songs and a larger list, duplicates the list of songs and then shuffles them
 * Uses the Fisher-Yates algorithm for shuffling
 * Takes: A list of songs, an int specifying the size of the list of songs
 * Returns: void
 */
void ShuffleList(song song_list[], int size)
{
	int gap_size = (size / 2) < MAX_GAP ? (size / 2) : MAX_GAP; // Half the size, up to a specified maximum
	srand(time(NULL)); // Initialise the random number seed

	// Duplicate the list of songs
	for (int index = 0; index < size; index++)
	{
		song_list[size + index] = song_list[index];
	}

	// Shuffling; back to front
	for (int index = (size * 2) - 1; index > 0; index--)
	{
		song curr_song = song_list[index];

		int index_to_move = rand() % (index + 1);
		song song_to_move = song_list[index_to_move];

		// Update the list
		song placeholder = curr_song;
		song_list[index] = song_to_move;
		song_list[index_to_move] = placeholder;
	}

	// Detect and solve songs which have been repeated too soon
	// We start by iterating over every song in the list (except the final one), front to back
	for (int index = 0; index < (size * 2) - 1; index++)
	{
		song this_song = song_list[index];
		int this_id = this_song.Id;

		// Distance should always return a positive here
		// Iteration moves left to right, and we should have resolved the conflict after the first (leftmost) instance
		int distance = GetDistance(song_list, (size * 2), index, index, this_id);
		if (distance <= gap_size && (distance > 0))
		{
			int start_index = index + distance + gap_size + 1;

			// Loop through every index searching for a valid replacement
			for (int inner_index = start_index; ; inner_index++)
			{
				// Wrap to the start of the list to avoid out of bounds errors
				if (inner_index >= (size * 2))
				{
					inner_index = 0;
				}

				// We have exhausted all elements (shouldn't happen, but just in case)
				if ((inner_index < index + gap_size) && ((index + gap_size) - inner_index) <= gap_size)
				{
					break;
				}

				// Check if the song at the new index can swap and still fulfil the requirement
				song song_at_index = song_list[inner_index];
				int new_distance = GetDistance(song_list, (size * 2), index, inner_index, song_at_index.Id);

				// Absolute Value
				if (new_distance < 0)
				{
					new_distance *= -1;
				}

				if (new_distance > gap_size)
				{
					// We found a match, so swap the songs
					song_list[inner_index] = song_list[index];
					song_list[index] = song_at_index;
					break;
				}
			}
		}
	}
}



