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
        
        Couleur rook_player = WHITE;
       
        /**
         * @brief Permet de vérifier si il y a une pièce à la position de départ
         * 
         * @param d_pos position de départ
         * @return true s'il y a une pièce à la position de départ.
         */
        bool Piece_Existe(const char* d_pos);

        /**
         * @brief Permet de vérifier si le deplacement de la piece va provoquer un échec
         * 
         * @param d_pos position de départ
         * @param f_pos position d'arrivée/finale
         * @return true si le deplacement va provoquer un échec
         */
        bool VersEchec(const char* d_pos, const char* f_pos);

        /**
         * @brief Permet d'échanger le tour entre les joueurs
         * 
         * @param j_tour la couleur du joueur actuel
         */
        void swap_players(Couleur& j_tour);

        /**
         * @brief Permet de connaitre l'état de la partie(en cours ou fini)
         * 
         * @return Le resultat de la partie en cours.
         */

        Result Check_result();

        /**
         * @brief Permet de réaliser le mouvement roque(petit roque ou grande roque)
         * 
         * @param d_pos position de départ
         * @param f_pos position d'arrivée/finale
         */
        void mouvement_roque(const char* d_pos, const char* f_pos);

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
         * @brief Permet la promotion du pion
         * 
         * @param pion_pos les coordonnées du pion
         */
        void promotion(const char* pion_pos);

        

    public:
    
        /** @brief Constructor of a chess game
         * 
         * */
        Game();

        /** @brief destructor 
         * */
        ~Game();

        /**
         * @brief Permet de déplacer la pièce sur l'échiquier
         * 
         * @param d_pos position de départ de la pièce
         * @param f_pos position d'arrivée/finale de la pièce
         * @param roque permet de dire s'il s'agit d'un mouvement roque
         **/
        void deplacer(const char* d_pos, const char* f_pos,bool roque = false);

        /**
         * @brief Permet de vérifier si le jeu est en cours
         * 
         * @return true si le jeu est en cours
         **/
        bool enCours();

        /**
         * @brief Permet de vérifier si le roi du joueur actuel est en échec
         * 
         * @param joueur_actuel couleur du joueur actuel (Blanc/Noir)
         * @param position_roi  la position du roi du joueur actuel
         * @return true si le roi du joueur actuel est en échec
         **/
        bool est_En_Echec(Couleur joueur_actuel, const char* position_roi);

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


