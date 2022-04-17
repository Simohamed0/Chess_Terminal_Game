#pragma once

#include "Piece.hpp"

class King : public Piece {

    private:

        // Fonctionnalité Roque
        bool sest_deplace = false;

        int Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

    public:

        King(Couleur couleur);

        void deplace();
        bool sestDeplace() const;
};
