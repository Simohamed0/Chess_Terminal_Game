#include "Rook.hpp"



Rook::Rook(Couleur couleur) : Piece(couleur) {
    type = rook;
}


int Rook::Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    if (!M_Ligne(d_pos, f_pos))
        return MOUVEMENT_INVALIDE;
    
    if (!DetectionObstacle(d_pos, f_pos, echiquier))
        return OBSTACLE;

    return OK;
}


bool Rook::DetectionObstacle(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';
    int delta_x = f_x - d_x;
    int delta_y = f_y - d_y;

    int increment = ((f_x > d_x || f_y > d_y) ? 1 : -1);
    int i = 0;

    if (!delta_x) {
        i = d_y + increment;
        while (i != f_y)
        {
            if (echiquier[d_x][i] != NULL)
                return false;
            i+=increment;
        }
    }

    if (!delta_y) {
        i = d_x + increment;
        while (i != f_x)
        {
            if (echiquier[i][d_y] != NULL)
                return false;
            i+=increment;
        }
    }

    return true;
}


bool Rook::sestDeplace() const {
    return sest_deplace;
}


void Rook::deplace() {
    sest_deplace = true;
}