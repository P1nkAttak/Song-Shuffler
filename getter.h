/*
 * Author: Ben Power
 * Written: 07/02/2025
 * Updated: 07/02/2025
 * Description: The function prototype(s) used for retrieving song information from the user
 *
 */

#ifndef __GUARD_GETTER // Protects against recursive/repeat inclusions
#define __GUARD_GETTER

#include <stdbool.h>
#include "song_data.h" // This is needed to define the 'song' type

bool ReadString(char write_array[], unsigned int max_chars);
int PopulateList(song list_to_fill[]);

#endif // __GUARD_GETTER
