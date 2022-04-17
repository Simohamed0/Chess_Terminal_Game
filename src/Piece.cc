#include "Piece.hpp"


Piece::Piece(Couleur couleur) : couleur(couleur) {}


Piece::~Piece(){}


Couleur Piece::getCouleur() const {
    return this->couleur;
}


 Type Piece::getType() const {
    return this->type;
}


int Piece::Mouvement_EstValide(const char* d_pos, const char* f_pos, Piece* echiquier[][8], Couleur j_tour) const {

        
    if (j_tour != this->couleur)
        return WRONG_PLAYER;
    
    const int col = f_pos[0] - 'a';
    const int ligne = f_pos[1] - '1';
    if (echiquier[col][ligne] != NULL) {
        if (echiquier[col][ligne]->getCouleur() == this->couleur)
            return OCCUPIED_CASE;
    }


    int erreur = this->Mouvement_Piece(d_pos, f_pos, echiquier);
    if (erreur)
        return erreur;
    return OK;
}


bool Piece::M_Diagonal(const char* d_pos, const char* f_pos) const {
    int delta_x = abs(f_pos[0] - d_pos[0]);
    int delta_y = abs(f_pos[1] - d_pos[1]);

    if (delta_x == delta_y) {
        if (delta_x)
            return true;
    }
    return false;
}


bool Piece::M_Ligne(const char* d_pos, const char* f_pos) const {
    if (d_pos != f_pos) {
        if ((d_pos[0] == f_pos[0] || d_pos[1] == f_pos[1]))
                return true;
    }
    return false;
}


bool Piece::AdjacentVH(const char* d_pos, const char* f_pos) const {
    int delta_x = abs(f_pos[0] - d_pos[0]);
    int delta_y = abs(f_pos[1] - d_pos[1]);

    if (delta_x == 1 || delta_y == 1)
        if (delta_x + delta_y <= 2)
            return true;

    return false;
}

//------------------------------------------------ROI--------------------------------------------------------------------------//


//------------------------------------------------DAME--------------------------------------------------------------------------//



//------------------------------------------------FOU--------------------------------------------------------------------------//


//------------------------------------------------CAVALIER--------------------------------------------------------------------------//

//------------------------------------------------PION--------------------------------------------------------------------------//

//------------------------------------------------TOUR--------------------------------------------------------------------------//

