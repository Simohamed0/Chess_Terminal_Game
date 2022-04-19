#pragma once

#include "Piece.hpp"


class Pawn : public Piece {
    
    private:

        bool En_passant   = false;
        bool sest_deplace = false;
        
        int piece_movement(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        /**
         * @brief Fonction Spécial pour le pion pour traiter la manière de deplacement du pion
         *        quand il mange une pièce énnemie
         *
         * @param d_pos position de départ
         * @param f_pos position d'arrivé/finale
         * @return true s'il peut faire se deplacement.
         */
        bool AdjacentV(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

        bool obstacle_detection(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const;

    public:

        Pawn(Color couleur);

        void has_been_moved();
        bool already_moved() const;

        bool Est_En_Passant() const;
        void En_Passant();
        void Pas_En_Passant();


};
