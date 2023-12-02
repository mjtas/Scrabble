#include "splashkit.h"
#include "draw_board.h"
#include "tile_bag.h"
#include "tiles.h"
#include "word.h"

#define BOARD_SIZE 15
#define SQUARE_SIZE 40
#define BOARD_OFFSET_X 100
#define BOARD_OFFSET_Y 150

void draw_board(const int &player_score, const std::vector<tile_data> &tile_bag, const std::vector<tile_data> &board, std::vector<tile_data::square_data> &board_squares)
{
    clear_screen(COLOR_DARK_GREEN);
    
    //Draw the score box
    fill_rectangle (COLOR_LINEN, 0, 0, 900, 70);
    draw_text("SCORE: "+ std::to_string(player_score), COLOR_BLACK, 10, 10);
    draw_text("TILES REMAINING: "+std::to_string(tile_bag.size()), COLOR_BLACK, 10, 30);
    draw_text("Press '0' to submit word", COLOR_BLACK, 560, 10);
    draw_text("Press '9' to end game", COLOR_BLACK, 560, 30);
    
    // Draw the board background
    fill_rectangle(COLOR_LINEN, BOARD_OFFSET_X, BOARD_OFFSET_Y, BOARD_SIZE*SQUARE_SIZE, BOARD_SIZE*SQUARE_SIZE);  
    
    // Draw the premium squares
    for (int i = 0; i < board_squares.size(); i++)
    {
         tile_data::square_data &square = board_squares[i];
         int x_value = ((square.square_x - BOARD_OFFSET_X) / SQUARE_SIZE);
         int y_value = ((square.square_y - BOARD_OFFSET_Y) / SQUARE_SIZE);
         
         // Draw the double letter score squares
                if (((x_value == 0 || x_value == 7 || x_value == 14) && (y_value == 3 || y_value == 7 || y_value == 14)) ||
                    ((x_value == 2 || x_value == 12) && (y_value == 6 || y_value == 8)) ||
                    ((x_value == 3 || x_value == 11) && (y_value == 0 || y_value == 7 || y_value == 14)) ||
                    ((x_value == 6 || x_value == 8) && (y_value == 2 || y_value == 6 || y_value == 8 || y_value == 12)))

                {
                    
                    fill_rectangle(COLOR_LIGHT_BLUE, square.square_x, square.square_y, SQUARE_SIZE, SQUARE_SIZE);
                    square.kind = DOUBLE_LETTER;                
                }

                // Draw the triple letter score squares
                if (((x_value == 5 || x_value == 9) && (y_value == 1 || y_value == 5 || y_value == 9 || y_value == 13)) ||
                    ((x_value == 1 || x_value == 13) && (y_value == 5 || y_value == 9)))
                {
                    tile_data::square_data &square = board_squares[i];
                    fill_rectangle(COLOR_DARK_BLUE, square.square_x, square.square_y, SQUARE_SIZE, SQUARE_SIZE);
                    square.kind = TRIPLE_LETTER;
                }

                // Draw the double word score squares
                if (((x_value == 1 || x_value == 13) && (y_value == 1 || y_value == 13)) ||
                    ((x_value == 2 || x_value == 12) && (y_value == 2 || y_value == 12)) ||
                    ((x_value == 3 || x_value == 11) && (y_value == 3 || y_value == 11)) ||
                    ((x_value == 4 || x_value == 10) && (y_value == 4 || y_value == 10)) ||
                    (x_value == 7 && y_value == 7))
                {
                    tile_data::square_data &square = board_squares[i];
                    fill_rectangle(COLOR_LIGHT_PINK, square.square_x, square.square_y, SQUARE_SIZE, SQUARE_SIZE);
                    square.kind = DOUBLE_WORD;
                }

                // Draw star
                if (x_value == 7 && y_value == 7)
                {
                    tile_data::square_data &square = board_squares[i];
                    int cx = square.square_x + SQUARE_SIZE / 2;
                    int cy = square.square_y + SQUARE_SIZE / 2;
                    int r = SQUARE_SIZE / 2;

                    fill_triangle(COLOR_BLACK, cx, cy - r, cx - r / 2, cy + r / 2, cx + r / 2, cy + r / 2);
                    fill_triangle(COLOR_BLACK, cx, cy + r, cx - r / 2, cy - r / 2, cx + r / 2, cy - r / 2);
                }

                // Draw the triple word score squares
                if (((x_value == 0 || x_value == 7 || x_value == 14) && (y_value == 0 || y_value == 14)) ||
                    ((x_value == 0 || x_value == 14) && (y_value == 7)))
                {
                    tile_data::square_data &square = board_squares[i];
                    fill_rectangle(COLOR_RED, square.square_x, square.square_y, SQUARE_SIZE, SQUARE_SIZE);
                    square.kind = TRIPLE_WORD;
                }
            }
    
    // Draw the board grid lines
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            int square_x = BOARD_OFFSET_X + x * SQUARE_SIZE;
            int square_y = BOARD_OFFSET_Y + y * SQUARE_SIZE;

            // Draw the grid lines
            draw_line(COLOR_DARK_GREEN, square_x, square_y, square_x + SQUARE_SIZE, square_y);
            draw_line(COLOR_DARK_GREEN, square_x, square_y, square_x, square_y + SQUARE_SIZE);
        }
    }
    
    // Draw the tiles in the board vector
    if (!board.empty())  
    {
        for (int i = 0; i < board.size(); ++i)
        {
            // Get the sprite for the current tile
            sprite tile_sprite = board[i].tile_sprite;
            draw_sprite(tile_sprite);
        }
    }
}


