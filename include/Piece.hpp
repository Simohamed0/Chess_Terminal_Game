#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lib.hpp"


using namespace std;



/**
 * @brief This class implements and deals with chess pieces 
 *        and their legal mouvements in the game.
 * 
 **/
class Piece {

    protected:

        Color m_color;
        Type m_type = null;

        /**
         * @brief virtal method that define the authorized piece mouvement of each piece
         *
         * @param src departure position
         * @param dst destination position
         * @param Board[][8] 
         * @return 0 if the movement is authorized
         */
        virtual int piece_movement(const char* d_pos, const char* f_pos, Piece* Board[][8]) const {
            (void)d_pos;
            (void)f_pos;
            (void)Board;
            return OK;};
        
        /**
         * @brief verify if there is any obstacle for the piece mouvement
         *
         * @param src departure position
         * @param dst destination position
         * @param Board pointer to Board[][8]
         * @return 0 if there is no obstacle
         */
        virtual bool obstacle_detection(const char* d_pos, const char* f_pos, Piece* Board[][8]) const {
            (void) d_pos;
            (void) f_pos;
            (void)Board;
            return OK;}; 

        /**
         * @brief verify if the mouvement is diagonal
         * 
         * @param src departure position
         * @param dst destination position
         * @return true is it is false otherwise
         */
        bool M_Diagonal(const char* d_pos, const char* f_pos) const;

        /**
         * @brief verify if the mouvement is straight 
         * 
         * @param src departure position
         * @param dst destination position
         * @return true is it is false otherwise
         */
        bool M_Ligne(const char* d_pos, const char* f_pos) const;

        /**
         * @brief verify if the mouvement is adjacent
         * 
         * @param src departure position
         * @param dst destination position
         * @return true is it is false otherwise
         */
        bool AdjacentVH(const char* d_pos, const char* f_pos) const;

    public:

        Piece(Color couleur);

        virtual ~Piece();

        /**
         * @brief verify if the mouvement is legal or not
         *
         * @param d_pos departure position
         * @param f_pos final position
         * @param Board
         * @param actual_player 
         * @return 0 is it's legal
         */
        int Mouvement_EstValide(const char* d_pos, const char* f_pos, Piece* Board[][8], Color actual_player) const;

        /**
         * @brief Permet de vérifier si la pièce à bouger
         *        ça sera utile pour coder le mouvement Roque.
         * @return true si la pièce à bouger.
         */
        virtual bool already_moved() const {return 0;};

        /**
         * @brief change has_already_moved variable to true.
         */
        virtual void has_been_moved() {return;};

        virtual bool Est_En_Passant() const {return 0;}
        virtual void En_Passant(){return;};
        virtual void Pas_En_Passant(){return;};

        Color getColor() const;
        Type   getType() const;


};

