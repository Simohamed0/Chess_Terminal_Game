#include "King.hpp"


King::King(Color couleur) : Piece(couleur) {
    
    m_type = king;
}


int King::piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    (void)echiquier;
    if (!AdjacentVH(d_pos, f_pos))
        return INVALIDE_MOVEMENT;
        
    return OK;
}


bool King::already_moved() const {
    return has_already_moved;
}


void King::has_been_moved() {
    has_already_moved = true;
}
