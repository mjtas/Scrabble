#ifndef WORD
#define WORD

#include "splashkit.h"
#include "turn.h"
#include "tiles.h"
#include "draw_board.h"
#include "tile_bag.h"
// Add snapped tiles to the word vector and remove them from the hand vector
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - word: vector of tile_data structs representing the word created this turn
void create_word(std::vector<tile_data>& hand, std::vector<tile_data>& word);

// Update the player's score with the word score, adds tiles in word vector to board vector, deletes all tiles in word vector
// Parameters:
// - player_score: the player's score
// - board: vector of tile_data structs representing tiles played in previous turns
// - word: vector of tile_data structs representing the word created this turn
// - is_double_word: a tile in the word is on a double word score square
// - is_triple_word: a tile in the word in on a triple word score square
int update_player_score(int &player_score, std::vector<tile_data> &board, std::vector<tile_data> &word, bool is_double_word, bool is_triple_word);



#endif // !WORD_H

