/*
 * Author: Ben Power
 * Written: 07/02/2025
 * Updated: 07/02/2025
 * Description: The function prototype(s) used for sorting the list of songs
 *
 */

#ifndef __GUARD_SORTER // Protects against recursive/repeat inclusions
#define __GUARD_SORTER

#include "song_data.h" // This is needed to define the 'song' type

void ToLower(char string[]);
void SortSongs(song song_list[], int num_songs);

#endif // __GUARD_SORTER
