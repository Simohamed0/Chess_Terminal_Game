#include "Piece.hpp"


Piece::Piece(Color m_color) : m_color(m_color) {}


Piece::~Piece(){}


Color Piece::getColor() const {
    return m_color;
}

Type Piece::getType() const {
    return m_type;
}


int Piece::Mouvement_EstValide(const char* d_pos, const char* f_pos, Piece* Board[][8], Color j_tour) const {

        
    if (j_tour != this->m_color)
        return WRONG_PLAYER;
    
    const int col = f_pos[0] - 'a';
    const int ligne = f_pos[1] - '1';
    if (Board[col][ligne] != NULL) {
        if (Board[col][ligne]->getColor() == this->m_color)
            return OCCUPIED_CASE;
    }


    int erreur = this->piece_movement(d_pos, f_pos, Board);
    if (erreur)
        return erreur;
    return GOOD;
}


bool Piece::M_Diagonal(const char* d_pos, const char* f_pos) const {
    int delta_x = abs(f_pos[0] - d_pos[0]);
    int delta_y = abs(f_pos[1] - d_pos[1]);

    if (delta_x == delta_y) {
        if (delta_x)
            return true;
    }
    return false;
}


bool Piece::M_Ligne(const char* d_pos, const char* f_pos) const {
    if (d_pos != f_pos) {
        if ((d_pos[0] == f_pos[0] || d_pos[1] == f_pos[1]))
                return true;
    }
    return false;
}


bool Piece::AdjacentVH(const char* d_pos, const char* f_pos) const {
    int delta_x = abs(f_pos[0] - d_pos[0]);
    int delta_y = abs(f_pos[1] - d_pos[1]);

    if (delta_x == 1 || delta_y == 1)
        if (delta_x + delta_y <= 2)
            return true;

    return false;
}

