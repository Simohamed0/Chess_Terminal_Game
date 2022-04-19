#pragma once
#include "Piece.hpp"


class Rook : public Piece {

    private:

        bool sest_deplace = false;

        int piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        bool obstacle_detection(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;
        
    public:

        Rook(Color couleur);

        void has_been_moved();
        bool already_moved() const;
};
