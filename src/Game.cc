#include "Game.hpp"


Game::Game() {
    
    Game_status = "Chess game starts.\n\n";

    // all the empty cases are initialized at nullptr
    for (int ligne = 2; ligne < 6; ++ligne) 
    {
        for (int col = 0; col < 8; ++col) 
        {
            Board[col][ligne] = nullptr;
        }
    }

    // Creation des pièces + allocation

    Board[0][0] = new Rook    (WHITE);
    Board[1][0] = new Knight  (WHITE);
    Board[2][0] = new Bishop  (WHITE);
    Board[3][0] = new Queen   (WHITE);
    Board[4][0] = new King    (WHITE);
    Board[5][0] = new Bishop  (WHITE);
    Board[6][0] = new Knight  (WHITE);
    Board[7][0] = new Rook    (WHITE);

    for(int col = 0; col < 8; ++col) {
        Board[col][1] = new Pawn(WHITE);
    }
    Board[0][7] = new Rook    (BLACK);
    Board[1][7] = new Knight  (BLACK);
    Board[2][7] = new Bishop  (BLACK);
    Board[3][7] = new Queen   (BLACK);
    Board[4][7] = new King    (BLACK);
    Board[5][7] = new Bishop  (BLACK);
    Board[6][7] = new Knight  (BLACK);
    Board[7][7] = new Rook    (BLACK);

    for(int col = 0; col < 8; ++col) {
        Board[col][6] = new Pawn(BLACK);
    }

    strcpy(king_position[WHITE],"e1");
    strcpy(king_position[BLACK],"e8");

    player_turn = WHITE;
    resultat = ongoing;
}

Game::~Game() {
     
    string output;

    for (size_t row(0); row<=7; row++){
            for (char col('a');col<='h';col++) {
                if(Board[col - 'a'][row] != NULL)
                {
                    if (Board[col - 'a'][row]->getCouleur() == WHITE)
                        // get pieces with theit PGN names, 
                        // true -> with P for pawns, true -> w/b for colors.
                        output += pgn_piece_name(string(CodePiece_Blanche[Board[col - 'a'][row]->getType()]),true,true);  
                    else
                        output += pgn_piece_name(string(CodePiece_Blanche[Board[col - 'a'][row]->getType()]),true,true);
                }
                output += ",";
            }
    }
    cout << "\n\n" << output << "\n" ;
    for (int ligne = 0; ligne < 8; ++ligne) 
        for (int col = 0; col < 8; ++col)
            if (Board[col][ligne] != NULL)
                delete Board[col][ligne];
}


Couleur Game::get_Jactuel()
{
    return player_turn;
}

bool Game::enCours() {
    return resultat ? false : true;
}


string Game::pgn_piece_name(string const name, bool view_pawn, bool view_color) const 
{
    string psymb;
    if      (name=="\u2656") psymb="R";  // Rook W
    else if (name=="\u2658") psymb="N";  // Knight W
    else if (name=="\u2657") psymb="B";  // Bishop W
    else if (name=="\u2655") psymb="Q";  // Queen W
    else if (name=="\u2654") psymb="K";  // King W
    else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) { // one of the white piece has been found
            if (view_color)
                return "w"+psymb;
            else
                return psymb;
    } 
    if      (name=="\u265C") psymb= "R";  // Rook B
    else if (name=="\u265E") psymb= "N";  // Knight B
    else if (name=="\u265D") psymb= "B";  // Bishop B
    else if (name=="\u265B")  psymb= "Q"; // Queen B
    else if (name=="\u265A")  psymb= "K"; // King B
    else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
    if (psymb.size()>0) { // one of the black piece has been found
            if (view_color)
                return "b"+psymb;
            else
                return psymb;
    } 
    else return "";
}
void Game::deplacer(const char* d_pos, const char* f_pos, bool roque) {

    Game_status.clear();

    Couleur other_player = player_turn;
    swap_players(other_player);

    if(!Piece_Exist(d_pos)) {
        return;
    }
    // Fonctionalité Prise en Passant
    if(enpassant_move(d_pos,f_pos))
    {
        swap_players(player_turn);
        return;
    }
    // Fonctionalité Roque
    if (roque)
    {
        castling_move(d_pos, f_pos);
        return;
    }
    const int col = d_pos[0] - 'a';
    const int ligne = d_pos[1] - '1';

    int erreur = Board[col][ligne]->Mouvement_EstValide(d_pos, f_pos, Board, player_turn);

    switch (erreur) {
        case WRONG_PLAYER :
            invalide = true;
            if (Board[col][ligne]->getCouleur() == WHITE)
                Game_status += "Vous ne pouvez pas déplacer " + string(CodePiece_Blanche[Board[col][ligne]->getType()]) 
                            + " .Ce n'est pas votre pièce.\n\n";
            else
                Game_status += "Vous ne pouvez pas déplacer " + string(CodePiece_Noir[Board[col][ligne]->getType()]) 
                            + " .Ce n'est pas votre pièce.\n\n";
            return;
        case OCCUPIED_CASE :
            invalide = true;
            Game_status += f_pos;
            if (Board[col][ligne]->getCouleur() == WHITE)
                Game_status += " est occupée par votre " + string(CodePiece_Blanche[Board[f_pos[0] - 'a'][f_pos[1] - '1']->getType()]) + " .\n\n";
            else
                Game_status += " est occupée par votre " + string(CodePiece_Noir[Board[f_pos[0] - 'a'][f_pos[1] - '1']->getType()])    + " .\n\n";
            return;
        case MOUVEMENT_INVALIDE :
            invalide = true;
            if (Board[col][ligne]->getCouleur() == WHITE)
            {
                Game_status += "Votre " + string(CodePiece_Blanche[Board[col][ligne]->getType()]);
                Game_status += " ne peut pas se déplacer de ";
                Game_status += d_pos;
                Game_status += " vers ";
                Game_status += f_pos;
                Game_status += ".\n\n";
            }
            else
            {
                Game_status += "Votre " + string(CodePiece_Noir[Board[col][ligne]->getType()]);
                Game_status += " ne peut pas se déplacer de ";
                Game_status += d_pos;
                Game_status += " vers ";
                Game_status += f_pos;
                Game_status += ".\n\n";
            }
            return;
        case OBSTACLE :
            invalide = true;
            if (Board[col][ligne]->getCouleur() == WHITE)
                Game_status += "Votre " + string(CodePiece_Blanche[Board[col][ligne]->getType()]);
            else
                Game_status += "Votre " + string(CodePiece_Noir[Board[col][ligne]->getType()]);
        
            Game_status += " ne peut pas se déplacer de ";
            Game_status += d_pos;
            Game_status += " vers ";
            Game_status += f_pos;
            Game_status += " car il y a une pièce sur le chemin.\n\n";
            return;
    }
    
    if (if_checkmate(d_pos, f_pos) == DEPLACEMENT_ECHEC) {
        invalide = true;
        if (est_enEchec[player_turn]) {
            if (Board[col][ligne]->getCouleur() == WHITE)
                Game_status += "Vous ne pouvez pas déplacer votre " + string(CodePiece_Blanche[Board[col][ligne]->getType()]);
            else
                Game_status += "Vous ne pouvez pas déplacer votre " + string(CodePiece_Noir[Board[col][ligne]->getType()]);

            Game_status += " de ";
            Game_status += d_pos;
            Game_status += " vers ";
            Game_status += f_pos;
            Game_status += " car votre Roi est en echec.\n\n";
        }
        else {
            if (Board[col][ligne]->getCouleur() == WHITE)

                Game_status += "Vous ne pouvez pas déplacer votre " + string(CodePiece_Blanche[Board[col][ligne]->getType()]);
            else
                Game_status += "Vous ne pouvez pas déplacer votre " + string(CodePiece_Noir[Board[col][ligne]->getType()]);

            Game_status += " de ";
            Game_status += d_pos;
            Game_status += " vers ";
            Game_status += f_pos;
            Game_status += " car cela va mettre votre Roi en echec.\n\n";
        }
        return;

    }
    // Deplacement de la pièce
    invalide = false;
    const int& d_x = col;
    const int& d_y = ligne;
    const int f_x = f_pos[0] - 'a';
    const int f_y = f_pos[1] - '1';

    if (Board[col][ligne]->getCouleur() == WHITE)
        Game_status += string(CodePiece_Blanche[Board[col][ligne]->getType()]);
    else
        Game_status += string(CodePiece_Noir[Board[col][ligne]->getType()]);

    Game_status += " moved from ";
    Game_status += d_pos;
    Game_status += " to ";
    Game_status += f_pos;

    Board[d_x][d_y]->deplace();    // Utile pour le mouvement Roque

    if (Board[d_x][d_y]->getType() == king)
        strcpy(king_position[player_turn], f_pos);    


    if (Board[f_x][f_y] != NULL) {
        Game_status += " en mangeant ";
        if (Board[f_x][f_y]->getCouleur() == WHITE)
            Game_status += string(CodePiece_Blanche[Board[f_x][f_y]->getType()]);
        else
            Game_status += string(CodePiece_Noir[Board[f_x][f_y]->getType()]);
        Game_status += ".\n";
        compteur = 0;
        // deallocate taken piece    
        delete Board[f_x][f_y];
    }

    else
    {
        Game_status += ".\n";
    }

    if (Board[d_x][d_y]->getType() == pawn)     // handy for the promotion
    {
        if (f_y == 7 || f_y == 0)
            promotion(d_pos);
    }
    else
    {
        compteur ++;
    }
    Board[f_x][f_y] = Board[d_x][d_y];
    Board[d_x][d_y] = NULL;
    if (checkmate(other_player, king_position[other_player])) 
    {
        est_enEchec[other_player] = true;
        
        Game_status += "\n\t checkmate " + string(color_display[player_turn]);
        Game_status += " player win";
    }
    else 
        est_enEchec[other_player] = false;

    swap_players(player_turn);
    resultat = Check_result();
    if (resultat == ongoing && est_enEchec[other_player])
        Game_status += ".\n";

    Game_status += "\n";
}


bool Game::if_checkmate(const char* d_pos, const char* f_pos) {
    const int d_x = d_pos[0] - 'a';
    const int d_y = d_pos[1] - '1';
    const int f_x = f_pos[0] - 'a';
    const int f_y = f_pos[1] - '1';

    // On va simuler le mouvement de la pièce
    Piece* piece_tmp = Board[f_x][f_y];
    Board[f_x][f_y] = Board[d_x][d_y];
    Board[d_x][d_y] = NULL;

    char king_position_tmp[3]; // saving the king position
    strcpy(king_position_tmp, king_position[player_turn]);

    if (Board[f_x][f_y]->getType() == king)
        strcpy(king_position[player_turn], f_pos);

    if (checkmate(player_turn, king_position[player_turn])) 
    {
        Board[d_x][d_y] = Board[f_x][f_y];
        Board[f_x][f_y] = piece_tmp;
        strcpy(king_position[player_turn], king_position_tmp);
        return DEPLACEMENT_ECHEC;
    }

    Board[d_x][d_y] = Board[f_x][f_y];
    Board[f_x][f_y] = piece_tmp;
    strcpy(king_position[player_turn], king_position_tmp);
    return OK;
}





bool Game::Piece_Exist(const char* d_pos) {

    
    const int col = d_pos[0] - 'a';
    const int ligne = d_pos[1] - '1';
    if (Board[col][ligne] == NULL) {
        invalide = true;
        Game_status += "no piece exists at ";
        Game_status += d_pos;
        Game_status += ".\n\n";
        return false;
    }
    return true;
}


void Game::afficher() const {
    {
        // Displays a unicode chess board as well as material advantage.
        string space5 = string(5,' ');
        cout << endl;
        cout << "     a     b     c     d     e     f     g     h    "<< endl;
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        for (int i(7);i>=0;i--) 
        {
                    cout << i+1 << " "; // numérotation ligne dans affichage
                    for (int j(0);j<8;j++) {
                            cout << "|" ;
                            if (Board[j][i]) { 
                            cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                            if (Board[j][i]->getCouleur() == WHITE)
                                cout << CodePiece_Blanche[Board[j][i]->getType()];
                            else if (Board[j][i]->getCouleur() == BLACK)
                                cout << CodePiece_Noir[Board[j][i]->getType()];
                            cout << "\u0020" << " ";
                            }
                            else 
                                    cout << space5;  // 2 ascii spaces
                    }
                    cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
                    cout << endl;
        }
        cout << "\t" << Game_status;
    }
}


bool Game::checkmate(Couleur joueur_actuel, const char* king_position) {
    // Vérifier si une des pièces du joueur adverse peuvent attacker le roi du joueur actuel.
    Couleur autre_joueur = joueur_actuel;
    swap_players(autre_joueur);
    char test_pos[2];
    for (int col = 0; col < 8; ++col) {
        for (int ligne = 0; ligne < 8; ++ligne) {
            if (Board[col][ligne] != NULL) {
                test_pos[0] = col + 'a';
                test_pos[1] = ligne + '1';
                if (Board[col][ligne]->Mouvement_EstValide(test_pos, king_position, Board, autre_joueur) == OK) {
                    return true;
                }
            }
        }
    }
    return false;
}





bool Game::Peut_Deplacer(Couleur joueur) {
    char d_pos[2];
    char f_pos[2];
    for (int i = 'a'; i < 'i'; ++i) 
        for (int j = '1'; j < '9'; ++j) 
            for (int k = 'a'; k < 'i'; ++k) 
                for (int l = '1'; l < '9'; ++l) 
                    if (Board[i - 'a'][j - '1'] != NULL) {
                        d_pos[0] = i;
                        d_pos[1] = j;
                        f_pos[0] = k;
                        f_pos[1] = l;
                        if (Board[i - 'a'][j - '1']->Mouvement_EstValide(d_pos, f_pos, Board, joueur) == OK)
                            if (if_checkmate(d_pos, f_pos) != DEPLACEMENT_ECHEC) 
                                return true;
                    }
    return false;
}


void Game::swap_players(Couleur &player_turn) {
    
    if (player_turn == WHITE)
    {
        player_turn = BLACK;
    }
    else
    {
        player_turn = WHITE;
    }
}

void Game::castling_move(const char* d_pos, const char* f_pos) {

    if (strcmp(king_position[player_turn], d_pos))
        return;
    
    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';
    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';
    int delta_x = f_x - d_x;

    if (delta_x != -2 && delta_x != 2)
        return;

    // Initialement Cas Grand-Roque
    int Tour_d_x = 0;
    int increment = -1;

    // Cas Petit-Roque
    if (delta_x == 2) 
    {
        Tour_d_x = 7;
        increment = 1;
    }

    if (Board[Tour_d_x][d_y] == NULL) 
        return;

    if (Board[Tour_d_x][d_y]->getCouleur() != player_turn)
        return;   
    
    if (Board[Tour_d_x][d_y]->getType() != rook)
        return; 

    if (Board[Tour_d_x][d_y]->sestDeplace()) {
        invalide = true;
        Game_status += "Le mouvement roque est impossible car ";
        if (Board[Tour_d_x][d_y]->getCouleur() == WHITE)
            Game_status += string(CodePiece_Blanche[Board[Tour_d_x][d_y]->getType()]);
        else
            Game_status += string(CodePiece_Noir[Board[Tour_d_x][d_y]->getType()]);
        Game_status += " a déjà bougé.\n\n";
        return;
    }

    if (Board[d_x][d_y]->sestDeplace()) {
        invalide = true;
        Game_status += "Le mouvement roque est impossible car ";
        if (Board[Tour_d_x][d_y]->getCouleur() == WHITE)
            Game_status += string(CodePiece_Blanche[Board[d_x][d_y]->getType()]);
        else
            Game_status += string(CodePiece_Noir[Board[d_x][d_y]->getType()]);
        Game_status += " a déjà bougé.\n\n";
        return;
    }

    if (checkmate(player_turn, king_position[player_turn])) {
        invalide = true;
        Game_status += "Castling is impossible because of ";
        if (Board[Tour_d_x][d_y]->getCouleur() == WHITE)
            Game_status += string(CodePiece_Blanche[Board[d_x][d_y]->getType()]);
        else
            Game_status += string(CodePiece_Noir[Board[d_x][d_y]->getType()]);
        Game_status += " est en echec.\n\n";
        return;
    }
    
    for (int i = d_x + increment; i != Tour_d_x; i += increment) {
        invalide = true;
        if (Board[i][d_y] != NULL) {
            Game_status += "Castling is impossible because of obstacle.\n\n";
            return;
        }
    }

    invalide = false;
    
    strcpy(king_position[player_turn], f_pos);
    Board[f_x][f_y] = Board[d_x][d_y];  // king mouvement
    Board[d_x][d_y] = NULL;
    
    Board[d_x + increment][d_y] = Board[Tour_d_x][d_y]; // rook mouvement
    Board[Tour_d_x][d_y] = NULL;

    Game_status += std::string(color_display[player_turn]);
    Game_status += " player ";
    Game_status += " has executed";
    if (increment == -1) Game_status += " queenside- ";
    else Game_status += " kingside- ";
    Game_status += "castling.\n\n";
    compteur ++;
    swap_players(player_turn);

    return;
}


void Game::promotion(const char* pawn_pos) {
    char c='N';
    int d_x = pawn_pos[0] - 'a';
    int d_y = pawn_pos[1] - '1';
    delete Board[d_x][d_y];

    debut:
    cout << "You want to promote your pawn to a: Queen(Q),Knight(K),Rook(R) or Bishop(B) ?";
    cin >> c;
    cout << endl ;
    switch(c)
    {
        case 'Q':
            Board[d_x][d_y] = new Queen(player_turn);
            Game_status += string(color_display[player_turn]) + "Pawn " ;
            Game_status += " is promoted to Queen\n\n";
            break;
        case 'K':
            Board[d_x][d_y] = new Knight(player_turn);
            Game_status += string(color_display[player_turn]) + "Pawn " ;
            Game_status += " is promoted to Knight\n\n";;
            break;
        case 'B':
            Board[d_x][d_y] = new Bishop(player_turn);
            Game_status += string(color_display[player_turn]) + "Pawn " ;
            Game_status += " is promoted to Bishop\n\n";;
            break;
        case 'R':
            Board[d_x][d_y] = new Rook(player_turn);
            Game_status += string(color_display[player_turn]) + "Pawn " ;
            Game_status += " is promoted to Rook\n\n";;
            break;
        default:
            cout << "you have to choose between Q-K-R-B  \n";
            goto debut;
    }
}
void Game::init_enpassant()
{
    for(int col = 0 ; col < 8 ; col ++)
    {
        for(int ligne = 0; ligne < 8; ligne ++)
        {
            if(Board[col][ligne] != NULL && Board[col][ligne]->getType() == pawn && Board[col][ligne]->Est_En_Passant())
                Board[col][ligne]->Pas_En_Passant();
        }
    }
}

bool Game::enpassant_move(const char* d_pos, const char* f_pos)
{

    int d_x = d_pos[0] - 'a';
    int d_y = d_pos[1] - '1';

    int f_x = f_pos[0] - 'a';
    int f_y = f_pos[1] - '1';

    if(Board[d_x][d_y]->getType() != pawn)
    {
        init_enpassant();
        return false;
    }
        
    int delta_y = f_y - d_y;

    if (player_turn == BLACK)
        delta_y = delta_y * (-1);
    
    if (Board[f_x][d_y] != NULL && Board[f_x][d_y]->getType() == pawn )
    {
        if(Board[f_x][d_y]->Est_En_Passant())
        {
            if(player_turn == WHITE)
            {
                if(d_y == 4 && f_y == 5)
                {
                    Game_status += string(CodePiece_Blanche[Board[d_x][d_y]->getType()]);
                    Game_status += " a effectué une prise en passant,il s'est deplacé de ";
                    Game_status += d_pos;
                    Game_status += " vers ";
                    Game_status += f_pos;
                    Game_status += " en mangeant ";
                    Game_status += string(CodePiece_Noir[Board[f_x][d_y]->getType()]);
                    Game_status += ".\n\n";
                    
                    Board[f_x][f_y] = Board[d_x][d_y];
                    delete Board[f_x][d_y];
                    Board[d_x][d_y] = NULL;
                    Board[f_x][d_y] = NULL;
                    compteur = 0;
                }
                else if(delta_y == 2)
                {
                    init_enpassant();
                    Board[f_x][d_y]->En_Passant();
                    return false; 
                }
                else
                {
                    init_enpassant();
                    return false;
                }
            }
            else
            {
                if(d_y == 3 && f_y == 2)
                {
                    Game_status += string(CodePiece_Noir[Board[d_x][d_y]->getType()]);
                    Game_status += " a effectué une prise en passant,il s'est deplacé de ";
                    Game_status += d_pos;
                    Game_status += " vers ";
                    Game_status += f_pos;
                    Game_status += " en mangeant ";
                    Game_status += string(CodePiece_Blanche[Board[f_x][d_y]->getType()]);
                    Game_status += ".\n\n";
                    Board[f_x][f_y] = Board[d_x][d_y];
                    delete Board[f_x][d_y];
                    Board[d_x][d_y] = NULL;
                    Board[f_x][d_y] = NULL;
                    compteur = 0;
                }
                else if(delta_y == 2)
                {
                    init_enpassant();
                    Board[f_x][d_y]->En_Passant();
                    return false; 
                }
                else
                {
                    init_enpassant();
                    return false;
                }
            }
            
            return true;
        }
        else if(delta_y == 2)
        {
            init_enpassant();
            Board[f_x][d_y]->En_Passant();
            return false; 
        }
        else
        {
            init_enpassant();
            return false;
        }
    }

    return false;
    
}


Result Game::Check_result() {
    
    if (est_enEchec[player_turn]) 
    {
        if (!Peut_Deplacer(player_turn)) 
        {
            return ended;
        }
    }
    else {
        if (compteur == 50 || !Peut_Deplacer(player_turn)) {
            Game_status += "\tGame ended in stalemate.\n";
            return ended;
        }
    }
    return ongoing;
}