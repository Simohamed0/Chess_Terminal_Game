#pragma once
#include "Piece.hpp"

class Queen : public Piece {

    private:

        int Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        bool DetectionObstacle(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;
        
    public:

        Queen(Color couleur);
};