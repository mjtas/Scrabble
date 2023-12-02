#include "splashkit.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "tiles.h"
#include "turn.h"
#include "word.h"



int main()
{
    // Process events to check for any updates
    process_events();
    
    // Load the resources needed for the game
    load_resource_bundle("game_bundle", "scrabble.txt");
    
    // Open a window to display the game   
    open_window("Scrabble", 800, 900);
    
    // Create vectors to hold the tiles in the game
    std::vector<tile_data> tile_bag = {};
    std::vector<tile_data> hand = {};
    std::vector<tile_data> board = {};
    std::vector<tile_data> word = {};
    std::vector<tile_data::square_data> board_squares = {};
    
    //Initalise board squares
    initialise_board_squares(board_squares);
    
    // Initialise the tile bag and deal tiles to the player's hand
    initialise_tile_bag(tile_bag);
    deal_tiles(tile_bag, hand);
    
    // Initialise the player's score to zero
    int player_score = 0;
    
    // Keep playing turns until the player quits or the tile bag is empty   
    while (true)
    {
        play_turn(player_score, tile_bag, hand, word, board, board_squares);
        
        // Check if the NUM_9_KEY is pressed and break out of the loop if it is
        if (key_typed(NUM_9_KEY))
        {
            break;
        }
    }     
    
    // End the game and display the player's final score
    game_over(player_score, tile_bag, word, board, board_squares);
    
    // Exit the program
    return 0;
}


