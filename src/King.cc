#include "King.hpp"


King::King(Color couleur) : Piece(couleur) {
    
    m_type = king;
}


int King::Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    (void)echiquier;
    if (!AdjacentVH(d_pos, f_pos))
        return MOUVEMENT_INVALIDE;
        
    return OK;
}


bool King::sestDeplace() const {
    return sest_deplace;
}


void King::deplace() {
    sest_deplace = true;
}
