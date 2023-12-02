#include "splashkit.h"
#include "turn.h"
#include "tiles.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "word.h"
#include <vector>
#include <algorithm>

void create_word(std::vector<tile_data>& hand, std::vector<tile_data>& word)
{
    // Loop through the hand vector
    for (int i = 0; i < hand.size(); i++)
    {   
        if (hand[i].snapped == true)
        {
            // Add the tile to the word vector
            word.push_back(hand[i]);
        }
    }

    // Remove all snapped tiles from hand vector
    hand.erase(std::remove_if(hand.begin(), hand.end(), [](const tile_data& tile){ return tile.snapped; }), hand.end());
    
    // Reset positions of tiles in hand
    for (int i = 0; i < hand.size(); i++)
    {   
        sprite_set_x(hand[i].tile_sprite, 0);
        sprite_set_y(hand[i].tile_sprite, 0);      
    }
}

int update_player_score(int &player_score, std::vector<tile_data> &board, std::vector<tile_data> &word, bool is_double_word, bool is_triple_word)
{
    // Loop through the word vector 
    int word_score = 0;
    for (int i = word.size() - 1; i >= 0; i--)
    {
        switch (word[i].multiplier)
        {
            case REGULAR:
                // Add the letter score to the player score
                word_score += word[i].score;
                break;
            
            case DOUBLE_LETTER:
                // Add double the letter score to the player score
                word_score += 2 * word[i].score;
                break;
            
            case TRIPLE_LETTER:
                // Add triple the letter score to the player score
                word_score += 3 * word[i].score;
                break;
                
            case DOUBLE_WORD:
                // Add the letter score to the player score and flag is_double_word
                word_score += word[i].score;
                is_double_word = true;
                break;
                
            case TRIPLE_WORD:
                // Add the letter score to the player score and flag is_triple_word
                word_score += word[i].score;
                is_triple_word = true;
                break;
            }      
         
        // Add the tile to the board vector
        board.push_back(word[i]);
    }

    // Remove all elements from the word vector
    word.clear();
    
    if (is_double_word == true)
    {
        // double the word score
        word_score *= 2;
    }
    
    if (is_triple_word == true)
    {
        // triple the word score
        word_score *= 3;
    }
    
    return player_score += word_score;
}

