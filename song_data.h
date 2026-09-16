/*
 * Author: Ben Power
 * Written: 19/02/2025
 * Updated: 07/02/2025
 * Description: Defines the 'song' type and a few definitions used in the project
 *
 */

#ifndef __GUARD_SONG // Protects against recursive/repeat inclusions
#define __GUARD_SONG

//-- Definitions
#define MAX_ARTISTS 4
#define MAX_SONGS 3 // Per artist
#define MAX_CHARACTERS 80 // Per artist/song name (NOT including the null character)

//-- Type Definitions

// A song, with various fields to define metadata
typedef struct song_info
{
	char Artist[MAX_CHARACTERS + 1];
	char Title[MAX_CHARACTERS + 1];
	int Id;
} song;

#endif // __GUARD_SONG
