/*
 * Author: Ben Power
 * Written: 05/02/2025
 * Updated: 15/02/2025
 * Description: The main file; controls the flow of the program
 *
 */

#include <stdio.h>
#include <string.h>
#include "song_data.h"
#include "sorter.h"
#include "getter.h"
#include "shuffle.h"

int main(void)
{
	// Display welcome message to user
	printf("Welcome!\n");
	printf("You will be prompted to enter an artist, followed by some songs that artist has produced.\n");
	printf("You can enter at max %d artists, and %d songs per artist.\n", MAX_ARTISTS, MAX_SONGS);
	printf("Press enter without typing anything to cancel and move on.\n");
	printf("\n");
	fflush(stdout);

	// Define our list of songs and fill it in with user input
	song song_list[MAX_ARTISTS * MAX_SONGS * 2]; // x2 since the shuffler duplicates each song later on
	int num_songs = PopulateList(song_list);

	if (num_songs == 0) // No songs were entered so we want to skip the rest of the execution process
	{
		printf("Your playlist is empty!\n");
		return 0;
	}

	// Sort the list of songs and display it to the user
	SortSongs(song_list, num_songs);

	printf("Sorted list of songs:\n");
	fflush(stdout);
	char curr_printing_artist[MAX_CHARACTERS + 1] = {'\0'}; // For printing the artist name before the group of songs
	for (int index = 0; index < num_songs; index++)
	{
		song curr_song = song_list[index];

		if (strcmp(curr_song.Artist, curr_printing_artist) != 0) // New artist, so print their name
		{
			printf("%s\n", curr_song.Artist);
			fflush(stdout);
			strcpy(curr_printing_artist, curr_song.Artist);
		}

		printf("  -  %s\n", curr_song.Title);
		fflush(stdout);
	}

	// Shuffle the list of songs and display it to the user
	printf("\nShuffled playlist:");
	fflush(stdout);
	ShuffleList(song_list, num_songs);

	for (int index = 0; index < num_songs * 2; index++)
		{
		song curr_song = song_list[index];

		printf("\n%2d. %s - %s", index + 1, curr_song.Artist, curr_song.Title);
		fflush(stdout);
	}
}
