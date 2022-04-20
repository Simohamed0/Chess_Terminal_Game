#pragma once

#include "Piece.hpp"


class Pawn : public Piece {
    
    private:

        bool En_passant   = false;
        bool sest_deplace = false;
        
        int piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        /**
         * @brief trait the pawn movement when he take down an ennemy piece
         *
         * @param d_pos departure position
         * @param f_pos final position
         * @return true if the pawn can move
         */
        bool AdjacentV(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        bool obstacle_detection(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

    public:

        Pawn(Color couleur);

        void has_been_moved();
        bool already_moved() const;

        bool is_enPassant() const;
        void enPassant();
        void not_enPassant();


};
