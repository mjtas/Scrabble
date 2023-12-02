#ifndef TILES
#define TILES

#include "splashkit.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "tiles.h"
#include "word.h"
#include <vector>


// Checks if the mouse is over the specified tile in the hand
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - i: the specified tile in the hand
bool is_mouse_over_tile(std::vector<tile_data>& hand, int i);

// Checks if the mouse is clicked on the specified tile in the hand
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - i: the specified tile in the hand
bool is_mouse_clicked_on_tile(std::vector<tile_data>& hand, int i);

// Checks if there is a collision between the selected tile and other tiles in the hand
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - selected_tile_index: index of selected tile
// - new_x: new x coordinate of tile
// - new y: new_y coordinate of tile
bool tile_collision(std::vector<tile_data>& hand, int selected_tile_index, int new_x, int new_y);

// Updates the position of the selected tile based on mouse movement
// Parameteres:
// - hand: vector of tile_data structs representing the player's hand
// - board: vector of tile_data structs representing tiles played in previous turns
// - selected_tile_index: index of selected tile
// - board_squaresvector of square_data structs representing the board
void update_tile_position(std::vector<tile_data>& hand, std::vector<tile_data>& board, int selected_tile_index, std::vector<tile_data::square_data>& board_squares);

// Unsnaps the tile from the board and update the corresponding square data
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - board_squares: vector of square_data structs representing the board
void unsnap_tile(std::vector<tile_data>& tile, std::vector<tile_data::square_data>& board_squares);

// Snaps the selected tile to the nearest board square if within range and updates the corresponding square data
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - selected_tile_index: index of selected tile
// - board: vector of tile_data structs representing tiles played in previous turns
// - board_squares: vector of square_data structs representing the board
void snap_tile(std::vector<tile_data>& hand, int selected_tile_index, std::vector<tile_data>& board, std::vector<tile_data::square_data>& board_squares);

// Updates the selected tile based on user interaction
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - i: index of current tile
// - board: vector of tile_data structs representing tiles played in previous turns
// - board_squares: vector of square_data structs representing the board
void update_selected_tile(std::vector<tile_data>& hand, int i, std::vector<tile_data>& board, std::vector<tile_data::square_data>& board_squares);

// Displays a player's hand of tiles on the screen
// Parameters:
// - hand: vector of tile_data structs representing the player's hand
// - board: vector of tile_data structs representing the tiles already played
// - board_squares: vector of square_data structs representing the board
void display_hand(std::vector<tile_data> &hand, std::vector<tile_data> &board, std::vector<tile_data::square_data>& board_squares);
    
#endif 
