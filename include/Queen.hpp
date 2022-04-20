#pragma once
#include "Piece.hpp"

class Queen : public Piece {

    private:

        int piece_movement(const char* d_pos, const char* f_pos, Piece* Board[][8]) const;

        bool obstacle_detection(const char* d_pos, const char* f_pos, Piece* Board[][8]) const;
        
    public:

        Queen(Color color);
};