#include "splashkit.h"
#include "tile_bag.h"
#include "tiles.h"
#include "draw_board.h"
#include <vector>
#include <cmath>

#define BOARD_SIZE 15
#define SQUARE_SIZE 40
#define BOARD_OFFSET_X 100
#define BOARD_OFFSET_Y 150
#define SNAP_DISTANCE 20

// Checks if the mouse is over the specified tile in the hand
bool is_mouse_over_tile(std::vector<tile_data>& hand, int i)
{
    tile_data &tile = hand[i];
    
    return mouse_x() > sprite_x(tile.tile_sprite) && mouse_x() < sprite_x(tile.tile_sprite) + sprite_width(tile.tile_sprite) && mouse_y() > sprite_y(tile.tile_sprite) && mouse_y() < sprite_y(tile.tile_sprite) + sprite_height(tile.tile_sprite);
}

// Checks if the mouse is clicked on the specified tile in the hand
bool is_mouse_clicked_on_tile(std::vector<tile_data>& hand, int i)
{
    bool is_mouse_over = is_mouse_over_tile(hand, i);
    bool is_clicked = mouse_down(LEFT_BUTTON);
    
    return is_mouse_over && is_clicked;
}

// Checks if there is a collision between the selected tile and other tiles in the hand
bool tile_collision(std::vector<tile_data>& hand, int selected_tile_index, int new_x, int new_y)
{
    // Iterate through hand tiles to check for collisions
    for (int j = 0; j < hand.size(); ++j)
    {
        if (selected_tile_index != j)
        {
            // Get the sprites for the tile being compared
            sprite tile_sprite_j = hand[j].tile_sprite;

            // Check if tile sprites overlap
            if (new_x < sprite_x(tile_sprite_j) + sprite_width(tile_sprite_j) &&
                new_x + sprite_width(hand[selected_tile_index].tile_sprite) > sprite_x(tile_sprite_j) &&
                new_y < sprite_y(tile_sprite_j) + sprite_height(tile_sprite_j) &&
                new_y + sprite_height(hand[selected_tile_index].tile_sprite) > sprite_y(tile_sprite_j))
            {
                return true;
            }
        }
    }
    return false;
}

// Updates the position of the selected tile based on mouse movement
void update_tile_position(std::vector<tile_data>& hand, std::vector<tile_data>& board, int selected_tile_index, std::vector<tile_data::square_data>& board_squares)
{   
    tile_data &tile = hand[selected_tile_index];

    // Calculate the new position of the tile based on mouse movement
    int new_x = mouse_x() - (sprite_width(tile.tile_sprite) / 2);
    int new_y = mouse_y() - (sprite_width(tile.tile_sprite) / 2);
        
    // Update position if no overlap with other tiles
    if ((new_x >= 0 && new_x <= screen_width() && new_y >= 0 && new_y <= screen_height()) && (!tile_collision(hand, selected_tile_index, new_x, new_y)))
    {
        sprite_set_x(tile.tile_sprite, new_x);
        sprite_set_y(tile.tile_sprite, new_y);
        
    }
}

// Unsnap the tile from the board and update the corresponding square data
void unsnap_tile(tile_data& tile, std::vector<tile_data::square_data>& board_squares)
{
    for (int k = 0; k < board_squares.size(); k++)
    {
        tile_data::square_data &square = board_squares[k];
        
        if (square.occupied && sprite_x(tile.tile_sprite) >= square.square_x &&
            sprite_x(tile.tile_sprite) <= square.square_x + SQUARE_SIZE &&
            sprite_y(tile.tile_sprite) >= square.square_y &&
            sprite_y(tile.tile_sprite) <= square.square_y + SQUARE_SIZE)
        {
            square.occupied = false;
            tile.snapped = false;
            tile.multiplier = REGULAR;
            break;
        }
    }
}

// Snaps the selected tile to the nearest board square if within range and updates the corresponding square data
void snap_tile(std::vector<tile_data>& hand, int selected_tile_index, std::vector<tile_data>& board, std::vector<tile_data::square_data>& board_squares)
{
    tile_data &tile = hand[selected_tile_index];
    
    int new_x = -1;
    int new_y = -1;
    int closest_distance = 9999;

    // Loop through the board squares and find closest square
    for (int k = 0; k < board_squares.size(); k++)
    {
        tile_data::square_data &square = board_squares[k];
        
        double distance = sqrt(pow(sprite_x(tile.tile_sprite) + sprite_width(tile.tile_sprite) / 2 - (square.square_x + SQUARE_SIZE / 2), 2) +
                               pow(sprite_y(tile.tile_sprite) + sprite_height(tile.tile_sprite) / 2 - (square.square_y + SQUARE_SIZE / 2), 2));


        if ((distance < closest_distance) && (square.occupied == false))
        {
            new_x = square.square_x + SQUARE_SIZE / 2;
            new_y = square.square_y + SQUARE_SIZE / 2;
            closest_distance = distance; 
        }
    }

    // Snap tile to closest square if it is within range
    if (closest_distance < SNAP_DISTANCE)
    {
        sprite_set_x(tile.tile_sprite, new_x - (sprite_width(tile.tile_sprite) / 2));
        sprite_set_y(tile.tile_sprite, new_y - (sprite_height(tile.tile_sprite) / 2));    
        tile.snapped = true;
        
        for (int k = 0; k < board_squares.size(); k++)
        {
            tile_data::square_data &square = board_squares[k];
        
            if ((new_x == square.square_x + SQUARE_SIZE / 2) && (new_y == square.square_y + SQUARE_SIZE / 2))
            {
                square.occupied = true;
                tile.multiplier = square.kind;
            }
        }

    }

    else
    {    // Tile is not within range, move it back
        sprite_set_x(tile.tile_sprite, 0);
        sprite_set_y(tile.tile_sprite, 0);
        tile.snapped = false;
        tile.multiplier = REGULAR;
    }

}

// Updates the selected tile based on user interaction
void update_selected_tile(std::vector<tile_data>& hand, int i, std::vector<tile_data>& board, std::vector<tile_data::square_data>& board_squares)
{
    static int selected_tile_index = -1;


    if (hand.empty())
        return;

    if (i < 0 || i >= hand.size())
        // Handle invalid index
        return;

    tile_data &tile = hand[i];
   
    if (is_mouse_clicked_on_tile(hand, i))
    {              
        if (selected_tile_index == -1)
        {
            tile.selected = true;
            selected_tile_index = i;            
        }
        else
        {
            // Clicked on another tile, deselect previous tile and select new one
            hand[selected_tile_index].selected = false;
            selected_tile_index = i;
            tile.selected = true;
        } 
    }
            
    // Update tile position if mouse is moved while a tile is selected
    if (selected_tile_index != -1 && mouse_down(LEFT_BUTTON))
    {
        if (hand[selected_tile_index].snapped)
        {
            unsnap_tile(hand[selected_tile_index], board_squares);
        }
       
        update_tile_position(hand, board, i, board_squares);
    }

    // Snap tile to nearest board square if mouse button is released
    if (!mouse_down(LEFT_BUTTON) && selected_tile_index != -1)
    {
        snap_tile(hand, selected_tile_index, board, board_squares);
        hand[selected_tile_index].selected = false;
        selected_tile_index = -1;        
     }
}

// Display a player's hand of tiles on the screen
void display_hand(std::vector<tile_data> &hand, std::vector<tile_data> &board, std::vector<tile_data::square_data>& board_squares)
{
    // Check if hand is empty
    if (hand.empty())
        return;
    
    // Iterate through each tile in the hand
    for (int i = 0; i < hand.size(); ++i)
    {
        int spacing = 50;
        int x = i * spacing + 10;
        int y = 800;
        
        // Get the sprite for the current tile
        sprite tile_sprite = hand[i].tile_sprite;
        
        // Set the position of the sprite if it doesn't have a current position
        if (sprite_x(tile_sprite) == 0 && sprite_y(tile_sprite) == 0)
        {
            sprite_set_x(tile_sprite, x);
            sprite_set_y(tile_sprite, y);
        }
        
        // Update position of selected tile
        update_selected_tile(hand, i, board, board_squares);   
             
        // Draw the sprite on the screen
        draw_sprite(tile_sprite);
                       
        // Draw rectangle around sprite if tile selected
        if (hand[i].selected)
        {
            draw_rectangle(COLOR_RED, sprite_x(tile_sprite), sprite_y(tile_sprite), sprite_width(tile_sprite), sprite_height(tile_sprite));
        }

    }
}


