#include "Knight.hpp"



Knight::Knight(Couleur couleur) : Piece(couleur) {
    type = knight;
}


int Knight::Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    (void)echiquier;
    if (!Mouvement_L(d_pos, f_pos))
        return MOUVEMENT_INVALIDE;

    return OK;
}


bool Knight::Mouvement_L(const char* d_pos, const char* f_pos) const {
    const int delta_x = abs(f_pos[0] - d_pos[0]);
    const int delta_y = abs(f_pos[1] - d_pos[1]);

    if (delta_x + delta_y == 3)
        if (delta_x != 0 && delta_y != 0)
            return true;
    return false;    
}
