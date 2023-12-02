#ifndef TILE_BAG
#define TILE_BAG

#include "splashkit.h"
#include <vector>

enum square_kind
{
    DOUBLE_LETTER,
    TRIPLE_LETTER,
    DOUBLE_WORD,
    TRIPLE_WORD,
    REGULAR
};

enum tile_kind
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    BLANK
};

// Returns the bitmap corresponding to the given tile kind
inline bitmap tile_bitmap(tile_kind kind)
{
    switch(kind)
    {
        case A:
            return bitmap_named("tileA");
        case B:
            return bitmap_named("tileB");
        case C:
            return bitmap_named("tileC");
        case D:
            return bitmap_named("tileD");
        case E:
            return bitmap_named("tileE");
        case F:
            return bitmap_named("tileF");
        case G:
            return bitmap_named("tileG");
        case H:
            return bitmap_named("tileH");
        case I:
            return bitmap_named("tileI");
        case J:
            return bitmap_named("tileJ");
        case K:
            return bitmap_named("tileK");
        case L:
            return bitmap_named("tileL");
        case M:
            return bitmap_named("tileM");
        case N:
            return bitmap_named("tileN");
        case O:
            return bitmap_named("tileO");
        case P:
            return bitmap_named("tileP");
        case Q:
            return bitmap_named("tileQ");
        case R:
            return bitmap_named("tileR");
        case S:
            return bitmap_named("tileS");
        case T:
            return bitmap_named("tileT");
        case U:
            return bitmap_named("tileU");
        case V:
            return bitmap_named("tileV");
        case W:
            return bitmap_named("tileW");
        case X:
            return bitmap_named("tileX");
        case Y:
            return bitmap_named("tileY");
        case Z:
            return bitmap_named("tileZ");
        case BLANK:
            return bitmap_named("tileBLANK");
        default:
            return bitmap_named("tileE");
    }
};

// tile_data struct with members letter, score, kind, selected, snapped, multiplier and sprite
struct tile_data
{
    char letter;                
    int score;                   
    tile_kind kind;
    bool selected;
    bool snapped;
    square_kind multiplier;
    sprite tile_sprite;
    
    // square_data struct with members square_x, square_y, kind and occupied
    struct square_data
    {
        int square_x;
        int square_y;
        square_kind kind;
        bool occupied;
    };
    
};

// Initialises the board squares with their default values
void initialise_board_squares(std::vector<tile_data::square_data> &board_squares);

// Initialises the tile bag with the available tiles
void initialise_tile_bag(std::vector<tile_data> &tile_bag);

// Deals tiles from the tile bag to the player's hand
void deal_tiles(std::vector<tile_data> &tile_bag, std::vector<tile_data> &hand);


#endif // !TILEBAG_H

