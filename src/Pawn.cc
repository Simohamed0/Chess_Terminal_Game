#include "Pawn.hpp"


Pawn::Pawn(Color color) : Piece(color) {
    m_type = pawn;
}

int Pawn::piece_movement(const char* d_pos, const char* f_pos, Piece* Board[][8]) const {
    
    if (!AdjacentV(d_pos, f_pos, Board))
    {
        return INVALIDE_MOVEMENT;
    }

    if (!obstacle_detection(d_pos, f_pos, Board))
    {
        return OBSTACLE;
    }
    return GOOD;
}


bool Pawn::AdjacentV(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';
    int delta_y = f_y - d_y;
    int delta_x = abs(f_x - d_x);
    
    if (getColor() == BLACK)
    {
        delta_y = delta_y * (-1);
    }
    
    if (delta_x == 1 && delta_y == 1) 
    {
        if (echiquier[f_x][f_y] != NULL)
            return true;
    }
        

    if (delta_x == 0 && echiquier[f_x][f_y] == NULL) {
        
        if (!already_moved()) 
        {
            if ((delta_y == 1) || (delta_y == 2))
            {
                return true;
            }      
        }
        else if (delta_y == 1)
        {
                return true;
        }
    }   
    return false;    
    
}


bool Pawn::obstacle_detection(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_y = f_pos[1] - '1';
    int delta_y = abs(f_y - d_y);

    int increment = (this->getColor() == BLACK) ? -1 : 1;

    if (delta_y == 2)
        if (echiquier[d_x][d_y + increment] != NULL)
            return false;

    return true;
}

bool Pawn::is_enPassant() const {
    return En_passant;
}

void Pawn::enPassant() {
    En_passant = true;
}
void Pawn::not_enPassant() {
    En_passant = false;
}

bool Pawn::already_moved() const {
    return sest_deplace;
}

void Pawn::has_been_moved() {
    sest_deplace = true;
}
