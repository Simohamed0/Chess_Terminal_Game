#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lib.hpp"


using namespace std;



/**
 * @brief Cette classe a pour vocation de manipuler les pièces
 *        Elle a pour rôle de connaitre les mouvements possible des pieces.
 * 
 **/
class Piece {

    protected:

        Couleur couleur;
        Type type = null;


        /**
         * @brief virtal method that define the authorized piece mouvement of each piece
         *
         * @param src departure position
         * @param dst destination position
         * @param echiquier[][8] 
         * @return 0 if the movement is authorized
         */
        virtual int Mouvement_Piece(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
            (void)d_pos;
            (void)f_pos;
            (void)echiquier;
            return OK;};
        
        /**
         * @brief verify if there is any obstacle for the piece mouvement
         *
         * @param src departure position
         * @param dst destination position
         * @param echiquier pointer to echiquier[][8]
         * @return 0 if there is no obstacle
         */
        virtual bool DetectionObstacle(const char* d_pos, const char* f_pos, Piece* echiquier[][8]) const {
            (void) d_pos;
            (void) f_pos;
            (void)echiquier;
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

        Piece(Couleur couleur);

        virtual ~Piece();

        /**
         * @brief Permet de vérifier si le mouvement est valide ou pas de la piece
         *
         * @param d_pos position de départ
         * @param f_pos position d'arrivé/finale
         * @param echiquier[][8] pointeur vers la piece.
         * @param j_tour couleur du joueur actuel
         * @return 0 si le mouvement est valide.
         */
        int Mouvement_EstValide(const char* d_pos, const char* f_pos, Piece* echiquier[][8], Couleur j_tour) const;

        /**
         * @brief Permet de vérifier si la pièce à bouger
         *        ça sera utile pour coder le mouvement Roque.
         * @return true si la pièce à bouger.
         */

        virtual bool sestDeplace() const {return 0;};

        /**
         * @brief Permet de mettre sest_deplace en true si la pièce bouge.
         */
        virtual void deplace() {return;};

        virtual bool Est_En_Passant() const {return 0;}
        virtual void En_Passant(){return;};
        virtual void Pas_En_Passant(){return;};

        Couleur getCouleur() const;
        Type   getType() const;


};

