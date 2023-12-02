#ifndef TURN
#define TURN

#include "splashkit.h"
#include "tiles.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "word.h"

// Called at the start of each player turn to let them play their tiles and update their score
// Parameters: 
// - player_score: the player's score
// - tile_bag: a vector of tile_data structs representing the bag of tiles still available
// - hand: vector of tile_data structs representing the player's hand
// - word: the current word being played by the player
// - board: vector of tile_data structs representing tiles played in previous turns
// - board_squares: vector of square_data strucrs representing the board
void play_turn(int &player_score, std::vector<tile_data> &tile_bag, std::vector<tile_data> &hand, std::vector<tile_data> &word, std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares);


// Called when the game is over to display the final score and message
// Parameter:
// - player_score: the player's score
// - tile_bag: a vector of tile_data structs representing the bag of tiles still available
// - word: the current word being played by the player
// - board: vector of tile_data structs representing tiles played in previous turns
// - board_squares: vector of square_data strucrs representing the board
void game_over(int &player_score, std::vector<tile_data> &tile_bag, std::vector<tile_data> &word, std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares);

#endif // !TURN_H
