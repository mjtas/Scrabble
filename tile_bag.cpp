#include "splashkit.h"
#include "tile_bag.h"
#include "tiles.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define BOARD_SIZE 15
#define SQUARE_SIZE 40
#define BOARD_OFFSET_X 100
#define BOARD_OFFSET_Y 150

void initialise_board_squares(std::vector<tile_data::square_data> &board_squares)
{   
    // Create the square_data and add to board_squares
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            tile_data::square_data square;
            square.square_x = BOARD_OFFSET_X + x * SQUARE_SIZE;
            square.square_y = BOARD_OFFSET_Y + y * SQUARE_SIZE;
            square.kind = REGULAR;
            square.occupied = false;
            board_squares.push_back(square);
        }
    }

}

// Use the tile_counts and tile_scores vectors to define how many tiles of each kind there should be and what their scores are, add tiles to the tile_bag vector, and create a sprite for each tile
void initialise_tile_bag(std::vector<tile_data> &tile_bag)
{
    // Define the number of tiles for each tile kind
    std::vector<int> tile_counts = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1, 2};
    
    // Define the scores for each tile kind
    std::vector<int> tile_scores = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};
    
    // Create the tiles and add them to the tile bag
    for (size_t i = 0; i < tile_counts.size(); ++i)
    {
        for (int j = 0; j < tile_counts[i]; ++j)
        {
            tile_data tile;
            tile.kind = static_cast<tile_kind>(i);
            tile.score = tile_scores[i];
            tile.letter = 'A' + i;
            tile.selected = false;
            tile.snapped = false;
            tile.multiplier = REGULAR;
            tile.tile_sprite = create_sprite(tile_bitmap(tile.kind));
            tile_bag.push_back(tile);
        }
    }
}

// Shuffle the tile_bag vector using random_shuffle, then removes tiles from the beginning of the tile_bag vector and add them to the hand vector until hand has 7 tiles or tile_bag is empty
void deal_tiles(std::vector<tile_data> &tile_bag, std::vector<tile_data> &hand)
{    
    // Randomly shuffle tile_bag
    srand(time(nullptr));
    random_shuffle(tile_bag.begin(), tile_bag.end());

    // Remove tiles from tile_bag
    for (; hand.size() < 7 && !tile_bag.empty();)
    {
        tile_data tile = tile_bag.front();
        tile_bag.erase(tile_bag.begin());
        hand.push_back(tile);
    }
}




