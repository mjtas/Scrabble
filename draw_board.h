#ifndef DRAW_BOARD
#define DRAW_BOARD

#include "splashkit.h"
#include "tile_bag.h"
#include "tiles.h"
#include "word.h"


// Draw the board
// Parameters:
// - player_score: the player's score
// - tile_bag: vector of tile_data structs representing tiles still available
// - board: vector of tile_data structs representing tiles played in previous turns
// - board_squares: vector of square_data structs representing the board
void draw_board(const int &player_score, const std::vector<tile_data> &tile_bag, const std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares);


#endif
