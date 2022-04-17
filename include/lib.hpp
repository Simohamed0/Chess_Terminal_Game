#include <cstring>
#include <cmath>

#define OK                 0
#define DEPLACEMENT_ECHEC  1 
#define WRONG_PLAYER       2    
#define OCCUPIED_CASE      3   
#define MOUVEMENT_INVALIDE 4 
#define OBSTACLE           5    

enum Couleur {WHITE, BLACK};
const char color_display[][6] = {"white", "black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};

const char Type_Piece[][10] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
const char CodePiece_Noir[][7] = {"  ", "\u265F", "\u265E", "\u265D", "\u265C", "\u265B", "\u265A"};
const char CodePiece_Blanche[][7] = {"  ", "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654"};
