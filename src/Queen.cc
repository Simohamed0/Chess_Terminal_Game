#include "Queen.hpp"

Queen::Queen(Couleur couleur) : Piece(couleur) {
    type = queen;
}

int Queen::Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    if (!M_Diagonal(d_pos, f_pos) && !M_Ligne(d_pos, f_pos))
        return MOUVEMENT_INVALIDE;
    
    if (!DetectionObstacle(d_pos, f_pos, echiquier))
        return OBSTACLE;

    return OK;
}

bool Queen::DetectionObstacle(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';
    int delta_x = f_x - d_x;
    int delta_y = f_y - d_y;

    int increment = ((f_x > d_x || f_y > d_y) ? 1 : -1);
    int j = 0;
    
    if (!delta_x) 
    {
        j = d_y + increment;
        while (j != f_y)
        {
            if (echiquier[d_x][j] != NULL)
                return false;
            j += increment;
        }
    }

    if (!delta_y) 
    {
        j = d_x + increment;
        while (j != f_x)
        {
            if (echiquier[j][d_y] != NULL)
                return false;
            j += increment;
        }
    }

    int multiplier = ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0) ? 1 : -1);

	if (delta_x < 0 && delta_y != 0) 
		for (int i = -1; i != delta_x; --i)
			if (echiquier[d_x + i][d_y + (i * multiplier)] != NULL)
				return false;

	if (delta_x > 0 && delta_y != 0)
    	for (int i = 1; i != delta_x; ++i)
			if (echiquier[d_x + i][d_y + (i * multiplier)] != NULL)
				return false;
                
	return true; 
}