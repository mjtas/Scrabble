#include "splashkit.h"
#include "turn.h"
#include "tiles.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "word.h"



void play_turn(int &player_score, std::vector<tile_data> &tile_bag, std::vector<tile_data> &hand, std::vector<tile_data> &word, std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares)
{   
    // Wait for the player to press the "0" key to submit their word  
    while (true)
    {
        // Process events to check for any updates
        process_events();
          
        // Draw the game board, including the current score and the tiles played so far
        draw_board(player_score, tile_bag, board, board_squares);

        // Display the current hand of tiles that the player can play
        display_hand(hand, board, board_squares);

        // Refresh the screen to update any changes       
        refresh_screen(60);
        
        // Check if the NUM_0_KEY is pressed and break out of the loop if it is
        if (key_typed(NUM_0_KEY))
        {
            break;
        }
        
        // Check if the NUM_9_KEY is pressed and break out of the loop if it is
        if (key_typed(NUM_9_KEY))
        {
            break;
        }
    }     
    
    // Remove snapped tiles from the hand vector and add them to the word vector
    create_word(hand, word);
    
    // Update the player's score based on the tiles played
    bool is_double_word = false;
    bool is_triple_word = false;
    update_player_score(player_score, board, word, is_double_word, is_triple_word);

    // Deal new tiles to the player's hand
    deal_tiles(tile_bag, hand);
 }

void game_over(int &player_score, std::vector<tile_data> &tile_bag, std::vector<tile_data> &word, std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares)
{
    // Draw the game board with the final score
    draw_board(player_score, tile_bag, board, board_squares);
    // Display the game over message
    draw_text("*GAME OVER*", COLOR_BLACK, 10, 50);
    // Refresh the screen to update the changes
    refresh_screen();
    // Wait for a few seconds before exiting the game
    delay(4000);
}
