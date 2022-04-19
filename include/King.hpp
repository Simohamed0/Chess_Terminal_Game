#pragma once

#include "Piece.hpp"

class King : public Piece {

    private:

        bool has_already_moved = false; // for castling 

        int piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

    public:

        /**
         * @brief Construct a new King object
         * 
         * @param couleur 
         */
        King(Color couleur);

        void has_been_moved();

        bool already_moved() const;
};
