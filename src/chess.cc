#include "Game.hpp"
#include <regex>


bool saisie_correcte(string const & cmd) {
regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);

}

bool saisie_correcte_petitroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

bool saisie_correcte_grandroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}


int main() {
        
    Game m_Game;
    string input;
    char start_pos[] = "00\0";
    char end_pos  [] = "AA\0";

    while (input != "quit") 
    {    
        
        m_Game.afficher();

        if (m_Game.enCours())
            cout << "Coup (eg. a1a8) ? ";
        else
            break;
        cin >> input;
        
        if(saisie_correcte(input))
        {
            start_pos[0] = input[0];
            start_pos[1] = input[1];
            end_pos  [0] = input[2];
            end_pos  [1] = input[3];
            if (start_pos != NULL) 
            {
                if (end_pos != NULL)
                {	
                    m_Game.deplacer(start_pos, end_pos);
                }
            }
        }

        else if (saisie_correcte_petitroque(input))
        {
            if(m_Game.get_Jactuel() == WHITE)
            {
                m_Game.deplacer("e1", "g1",true);
            }
            else
            {
                m_Game.deplacer("e8", "g8",true);
            }
        }
        else if (saisie_correcte_grandroque(input))
        {
            if(m_Game.get_Jactuel() == WHITE)
            {
                m_Game.deplacer("e1", "c1",true);
            }
            else
            {
                m_Game.deplacer("e8", "c8",true);
            }
        }
        if (input != "quit")
        {
            cerr << "\tLes Coordonées " << input << " sont invalides.\n";
        }
        
    }
	return 0;
}