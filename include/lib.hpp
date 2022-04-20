#include <cstring>

   
enum Possible_cases{GOOD, DEPLACEMENT_ECHEC, WRONG_PLAYER, OCCUPIED_CASE, INVALIDE_MOVEMENT, OBSTACLE};

enum Color {WHITE, BLACK};
const char color_display[][6] = {"white", "black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};

const char Type_Piece[][10] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
const char BlackPiece_code[][7] = {"  ", "\u265F", "\u265E", "\u265D", "\u265C", "\u265B", "\u265A"};
const char WhitePiece_code[][7] = {"  ", "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654"};
