#pragma once
#include "Piece.hpp"


class Knight : public Piece {

    private:

        int piece_movement(const char* d_pos, const char* f_pos, Piece* Board[][8]) const;

        /**
         * @brief Fonction Spécial pour le Cavalier vu que ces déplacements se font sous forme d'un L
         *
         * @param d_pos position de départ
         * @param f_pos position d'arrivé/finale
         * @return true si le mouvmement est sous forme d'un L
         */

        bool Mouvement_L(const char* d_pos, const char* f_pos) const;
        
    public:

        Knight(Color color);
};