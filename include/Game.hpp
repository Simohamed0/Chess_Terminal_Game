#pragma once

#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

enum Result {ongoing, ended};

/**
 * @brief This Class manages and mantains the chess game .
 * 
 **/
class Game {

    protected:
        
        Piece* Board[8][8];  // 8x8 Board
        
        bool invalide = false;

        int compteur = 0;
        
        Result resultat;

        string Game_status = "";

        char king_position[2][3];

        bool est_enEchec[2] = {false, false};
        
        Couleur player_turn = WHITE;  // white start the game
       
        /**
         * @brief verify if the square is empty or not
         * 
         * @param d_pos departure position
         * @return true if the square is not empty
         */
        bool Piece_Exist(const char* d_pos);

        /**
         * @brief verify if the next mouvement leads to a checkmate 
         * 
         * @param d_pos departure position
         * @param f_pos final position
         * @return true if it is the case false otherwise
         */
        bool if_checkmate(const char* d_pos, const char* f_pos);

        /**
         * @brief swap players turns
         * 
         * @param j_tour color of the actual player
         */
        void swap_players(Couleur& player_turn);

       
        /** 
         *  @brief verify if the game is over or not
         * 
         * @return the game result
         **/
        Result Check_result();

        /**
         * @brief execute the castling mouvement
         * 
         * @param d_pos departure position
         * @param f_pos final position
         */
        void castling_move(const char* d_pos, const char* f_pos);

        /**
         * @brief Initialise le mouvement en_passant
        **/
        void init_enpassant();

        /**
         * @brief playing en_passant mouvement
         * 
         * @param  d_pos departure position
         * @param  f_pos final position
         * @return true if the mouvement is possible
        **/
        bool enpassant_move(const char* d_pos, const char* f_pos);

        /**
         * @brief promote the pawn
         * 
         * @param pawn_pos pawn position
         */
        void promotion(const char* pawn_pos);

        

    public:
    
        /** @brief Constructor of a chess game
        **/
        Game();

        /** @brief destructor 
        **/
        ~Game();

        /**
         * @brief move a piece in the board
         * 
         * @param d_pos departure position
         * @param f_pos final position
         * @param roque bool if it's a castling move
         **/
        void deplacer(const char* d_pos, const char* f_pos,bool roque = false);

        /**
         * @brief verify if the game is ongoing
         * 
         * @return true if it's the case
         **/
        bool enCours();

        /**
         * @brief verify if the instant player is checkmate
         * 
         * @param joueur_actuel color of the instant player
         * @param position_roi  king position of the instant player
         * @return true if the instant player's king is checkmate
         **/
        bool checkmate(Couleur joueur_actuel, const char* position_roi);

        /**
         * @brief Permet de vérifier si le joueur peut déplacer une pièce
         *        Cette fonction est utile pour la fonctionalité PAT et Echec et Mat
         * 
         * @param joueur couleur du joueur (Blanc/Noir)
         * @return true s'il lui reste des pièces qui peuvent se déplacer
         **/
        bool Peut_Deplacer(Couleur joueur);
        
        /**
         * @brief Permet d'afficher l'échiquier
         *        
         **/
        void afficher() const;

        /**
         * @brief Permet de connaitre le joueur actuel
         *        
         **/
        Couleur get_Jactuel();

        /**
         * @brief Fonction auxiliaire permettant à la fin d'obtenir la forme canonique 
         *        des positions finales des pièces de l'échiquier.
         *        
         **/
        string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;

};


