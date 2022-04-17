#pragma once
#include "Piece.hpp"


class Rook : public Piece {

    private:

        bool sest_deplace = false;

        int Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        bool DetectionObstacle(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;
        
    public:

        Rook(Couleur couleur);

        void deplace();
        bool sestDeplace() const;
};