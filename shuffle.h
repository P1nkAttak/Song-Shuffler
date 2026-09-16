/*
 * Author: Ben Power
 * Written: 15/02/2025
 * Updated: 15/02/2025
 * Description: The function prototype(s) used for shuffling the list of songs
 *
 */

#ifndef __GUARD_SHUFFLE // Protects against recursive/repeat inclusions
#define __GUARD_SHUFFLE

#include "song_data.h" // This is needed to define the 'song' type

int GetDistance(song song_list[], int size, int start_index, int ignore_index, int id_to_check);
void ShuffleList(song song_list[], int size);

#endif // __GUARD_SHUFFLE
