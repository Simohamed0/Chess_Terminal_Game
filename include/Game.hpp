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


/**
 * @brief This Class manages and mantains the chess game .
 * 
 **/
class Game {

    protected:
        
        Piece* Board[8][8];  // 8x8 Board
        
        bool invalide = false;

        int counter = 0; // for stalemate

        string Game_status = "";

        char king_position[2][3];

        bool est_enEchec[2] = {false, false};
        
        Color player_turn = WHITE;  // white start the game

        bool game_over = false;
       
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
        void swap_players(Color& player_turn);

       
        /** 
         *  @brief verify if the game is over or not
         * 
         * @return the game result
         **/
        bool Check_result();

        /**
         * @brief execute the castling mouvement
         * 
         * @param d_pos departure position
         * @param f_pos final position
         */
        void castling_move(const char* d_pos, const char* f_pos);

        /**
         * @brief Initialise en_passant movement
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
        void deplacer(const char* d_pos, const char* f_pos,bool castling = false);

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
        bool toward_checkmate(Color joueur_actuel, const char* position_roi);

        /**
         * @brief verify if the instant player is able to move a piece
         * 
         * @param joueur instant player
         * @return true if he can move a piece false otherwise
         **/
        bool can_move(Color joueur);
        
        /**
         * @brief display the board in the terminal
         *        
         **/
        void display() const;

        /**
         * @brief get the instant player
         *        
         **/
        Color instant_player() const;

        /** @brief check if the game is over
         * 
         **/
        bool is_over() const;

        string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;
};


