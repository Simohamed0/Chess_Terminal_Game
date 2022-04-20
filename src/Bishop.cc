#include "Bishop.hpp"


Bishop::Bishop(Color couleur) : Piece(couleur) {
    m_type = bishop;
}


int Bishop::piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    
    if (!M_Diagonal(d_pos, f_pos))
    {
        return INVALIDE_MOVEMENT;
    }

    if (!obstacle_detection(d_pos, f_pos, echiquier))
    {
        return OBSTACLE;
    }
    return GOOD;
}


bool Bishop::obstacle_detection(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';
    int delta_x = f_x - d_x;
    int delta_y = f_y - d_y;

	int multiplier = ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0) ? 1 : -1);
    
	if (delta_x < 0) 
		for (int i = -1; i != delta_x; --i)
			if (echiquier[d_x + i][d_y + (i * multiplier)] != NULL)
				return false;

	if (delta_x > 0)
    	for (int i = 1; i != delta_x; ++i)
			if (echiquier[d_x + i][d_y + (i * multiplier)] != NULL) 
				return false;
	return true; 
}
