//les bibliothèques du C++ ici
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//les bibliothèques du C ici

//les bibliothèques maison ici
#include "myvect.h"
#include "mystring.h"

using namespace std;

//fonctions
string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

int PileOuFace(unsigned indexJ1, unsigned indexJ2)
{
    //système de pile ou face aléatoire
    if (rand()%2==0)
    {
        return indexJ1;
    }
    else
    {
        return indexJ2;
    }
}


int PierreFeuilleCiseaux(unsigned indexJ1, unsigned indexJ2)
{
    /*système de pierre feuille ciseaux automatique
     * 0=pierre     L1  W1             L2  W2
     * 1=feuille    W2      L1         W1      L2
     * 2=ciseaux        L2  W2            L1  W1
    */
    while(true)
    {
        int choixJ1=rand()%3; //résultat entre 0 et 2 inclus
        int choixJ2=rand()%3;

        if((choixJ1 == choixJ2+1) || (choixJ1 == choixJ2-2))
        {
            return indexJ1;
            break;
        }
        else if((choixJ2 == choixJ1+1) || (choixJ2 == choixJ1-2))
        {
            return indexJ2;
            break;
        }
    }
}

int JeuDeDes(unsigned indexJ1, unsigned indexJ2)
{
    //système de jeu de dés aléatoire ("Jet de sauvegarde DnD" : 1d20 chacun, le plus haut gagne)
    while(true)
    {
        int choixJ1=rand()%21; //résultat entre 0 et 20 inclus
        int choixJ2=rand()%21;

        if(choixJ1 > choixJ2)
        {
            return indexJ1;
            break;
        }
        else if(choixJ2 > choixJ1)
        {
            return indexJ2;
            break;
        }
    }
}


//-----------------------------VARIABLES GLOBALES--------------------------------------------

const unsigned nmbParticipantsTotal=64;

//----------------------------------FONCTIONS------------------------------------------------

struct Participants
{
    unsigned int numero;
    string nameLast;
    string nameFirst;
    int roundResult;
    int position;
};

void Inscriptions(vector<Participants> &JoueurTab)
{
    for(unsigned int i = 0; i <nmbParticipantsTotal; ++i)
    {
        //définir nom/prénom des participants (temporaire, utiliser entrée standard + tard)
        string tmpnom = "nom" + to_string(i);
        string tmpprenom = "prenom" + to_string(i);

        //ajouter participant dans JoueurTab
        Participants tmpjoueur = {i, tmpnom, tmpprenom, 1, 1};
        JoueurTab.push_back(tmpjoueur);

        //cout << endl << i << " - J";
        //cout << JoueurTab[i].numero << " ";
        //cout << JoueurTab[i].nameLast << " ";
        //cout << JoueurTab[i].nameFirst;
    }

}

void Repartition(vector<Participants> &JoueurTab, vector<int> &BracketGagnants, vector<int> &BracketPerdants, vector<int> &ParticipantsElimine)
{
    //selon le résultat du round précédent, déterminer la position du joueur (1=winner bracket, 0=loser bracket, -1=éliminé)
    for(unsigned int i = 0; i <nmbParticipantsTotal; ++i)
    {
        if (JoueurTab[i].roundResult==0)
        {
            if (JoueurTab[i].position==1)
            {
                JoueurTab[i].position=0;
            }
            else if(JoueurTab[i].position==0)
            {
                ParticipantsElimine.push_back(JoueurTab[i].numero);
                JoueurTab[i].position=-1;
            }
        }
        //prépare tous les joueurs pour leurs round imminent (voir fonction Round() )
        JoueurTab[i].roundResult=1;
    }
    //mettre les joueurs dans leurs bracket respectifs
    BracketGagnants.clear();
    BracketPerdants.clear();
    for(unsigned i = 0; i <nmbParticipantsTotal; ++i)
    {
        if (JoueurTab[i].position==1)
        {
            BracketGagnants.push_back(JoueurTab[i].numero);
        }
        if (JoueurTab[i].position==0)
        {
            BracketPerdants.push_back(JoueurTab[i].numero);
        }
    }
}

void RoundGagnants(vector<Participants> & JoueurTab, const vector<int> &BracketGagnants, bool &FinalisteGagnant, unsigned int &aQuoiOnJoue)
{
    if (BracketGagnants.size() > 1)
    {
        for(unsigned i = 0; i < BracketGagnants.size(); i+=2)
        {
            unsigned tmp_numero_participant;
            switch(aQuoiOnJoue)
            {
            case 1:
            {
                tmp_numero_participant = PileOuFace(BracketGagnants[i],BracketGagnants[i+1]);
                break;
            }
            case 2:
            {
                tmp_numero_participant = PierreFeuilleCiseaux(BracketGagnants[i],BracketGagnants[i+1]);
                break;
            }
            case 3:
            {
                tmp_numero_participant = JeuDeDes(BracketGagnants[i],BracketGagnants[i+1]);
                break;
            }
            default:
                cout << endl << "Erreur selection de jeu." << endl;
            }
            JoueurTab[tmp_numero_participant].roundResult=0;
        }
    }
    else
        FinalisteGagnant=true;

}

void RoundPerdants(vector<Participants> & JoueurTab, vector<int> &BracketPerdants, bool & FinalistePerdant, unsigned int &aQuoiOnJoue)
{
    if (BracketPerdants.size() > 1)
    {
        for(unsigned i = 0; i < BracketPerdants.size(); i+=2)
        {
            unsigned tmp_numero_participant;
            switch(aQuoiOnJoue)
            {
            case 1:
            {
                tmp_numero_participant = PileOuFace(BracketPerdants[i],BracketPerdants[i+1]);
                break;
            }
            case 2:
            {
                tmp_numero_participant = PierreFeuilleCiseaux(BracketPerdants[i],BracketPerdants[i+1]);
                break;
            }
            case 3:
            {
                tmp_numero_participant = JeuDeDes(BracketPerdants[i],BracketPerdants[i+1]);
                break;
            }
            default:
                cout << endl << "Erreur selection de jeu." << endl;
            }
            JoueurTab[tmp_numero_participant].roundResult=0;

        }
    }
    else
        FinalistePerdant=true;
}

void RoundFinalistes(vector<Participants> & JoueurTab, const vector<int> &BracketGagnants, const vector<int> &BracketPerdants, unsigned int &aQuoiOnJoue)
{
    JoueurTab[BracketPerdants[0]].position=1;

    unsigned tmp_numero_participant;
    switch(aQuoiOnJoue)
    {
    case 1:
    {
        tmp_numero_participant = PileOuFace(BracketGagnants[0],BracketGagnants[1]);
        break;
    }
    case 2:
    {
        tmp_numero_participant = PierreFeuilleCiseaux(BracketGagnants[0],BracketGagnants[1]);
        break;
    }
    case 3:
    {
        tmp_numero_participant = JeuDeDes(BracketGagnants[0],BracketGagnants[1]);
        break;
    }
    default:
        cout << endl << "Erreur selection de jeu." << endl;
    }
    JoueurTab[tmp_numero_participant].roundResult=0;
}


void TestGagnants(const vector<Participants> & JoueurTab, const vector<int> &BracketGagnants) //TEST écrire participants 1 par 1
{
    cout << endl <<endl << "## BRACKET GAGNANTS ##" << endl;
    if (BracketGagnants.size() > 0)
    {
        for(unsigned i = 0; i < BracketGagnants.size(); ++i)
        {
            cout << endl << i << " - ";
            cout << "J" << JoueurTab[BracketGagnants[i]].numero;
            cout << " " << JoueurTab[BracketGagnants[i]].nameLast;
            cout << " " << JoueurTab[BracketGagnants[i]].nameFirst;
            cout << " r" << JoueurTab[BracketGagnants[i]].roundResult;
            cout << " p" << JoueurTab[BracketGagnants[i]].position;
        }
    }
}

void TestPerdants(const vector<Participants> & JoueurTab, const vector<int> &BracketPerdants) //TEST écrire participants 1 par 1
{

    cout << endl <<endl << "## BRACKET PERDANTS ##" << endl;
    if (BracketPerdants.size() > 0)
    {
        for(unsigned i = 0; i < BracketPerdants.size(); ++i)
        {
            cout << endl << i << " - ";
            cout << "J" << JoueurTab[BracketPerdants[i]].numero;
            cout << " " << JoueurTab[BracketPerdants[i]].nameLast;
            cout << " " << JoueurTab[BracketPerdants[i]].nameFirst;
            cout << " r" << JoueurTab[BracketPerdants[i]].roundResult;
            cout << " p" << JoueurTab[BracketPerdants[i]].position;
        }
    }
}

void TestEliminations(const vector<Participants> & JoueurTab, const vector<int> &ParticipantsElimine) //TEST écrire joueurs éliminés 1 par 1
{

    cout << endl <<endl << "# ELIMINATIONS #" << endl;
    if (ParticipantsElimine.size() > 0)
    {
        for(unsigned i = 0; i < ParticipantsElimine.size(); ++i)
        {
            cout << endl << i << " - ";
            cout << "J" << JoueurTab[ParticipantsElimine[i]].numero;
            cout << " " << JoueurTab[ParticipantsElimine[i]].nameLast;
            cout << " " << JoueurTab[ParticipantsElimine[i]].nameFirst;
        }
    }
}

int main()
{
    //graine aléatoire
    srand(time(NULL));

    //voir fonctions ROUNDGAGNANTS(), ROUNDPERDANTS() et ROUNDFINALISTES()
    //sert à déterminer à quel jeu on joue, 1= Pile ou Face, 2= Pierre Feuille Ciseaux, 3= Jeux de Dés
    unsigned int aQuoiOnJoue;

    for (aQuoiOnJoue=1; aQuoiOnJoue<4; ++aQuoiOnJoue)
    {
        //-------------------------PREPARATION DE PARTIE----------------------------//

        //voir fonction INSCRIPTIONS()
        //tableau qui liste les participants
        vector<Participants> JoueurTab;
        JoueurTab.clear();

        //voir fonction REPARTITION()
        //tableaux utilisés pour trouver qui fait face à qui
        vector<int> BracketGagnants(0);
        vector<int> BracketPerdants(0);
        vector<int> ParticipantsElimine(0);
        BracketGagnants.clear();
        BracketPerdants.clear();
        ParticipantsElimine.clear();

        //voir fonctions ROUNDGAGNANTS() et ROUNDPERDANTS()
        //quand il ne reste qu'un joueur dans un tableau, il est mis à TRUE, si les deux sont TRUE, lance le round de finalistes
        bool FinalisteGagnant=false;
        bool FinalistePerdant=false;

        //--------------------LANCEMENT DU JEU SELECTIONE--------------------------//

        Inscriptions(JoueurTab);

        //TEST, utilisé seulement par les commentaires, donc désactivé
        //unsigned roundCounter=0;
        while (true)
        {
            //TEST, utilisé seulement par les commentaires, donc désactivé
            //++roundCounter;

            Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);
            RoundGagnants(JoueurTab, BracketGagnants, FinalisteGagnant, aQuoiOnJoue);

            Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);
            RoundPerdants(JoueurTab, BracketPerdants, FinalistePerdant, aQuoiOnJoue);

            // TEST, retirer les commentaires des lignes suivantes pour affichier dans la sortie standard
            //       le nom de tous les participants et leurs état a chaque round

            /* cout << endl << endl << "###### ROUND " << roundCounter << " ######";
             * TestGagnants(JoueurTab, BracketGagnants);
             * TestPerdants(JoueurTab, BracketPerdants);
             * TestEliminations(JoueurTab, ParticipantsElimine);
            */

            if(FinalisteGagnant && FinalistePerdant)
                break;
        }
        // TEST, bannière du round de finalistes
        // cout << endl << endl << endl << endl << "###### ROUND FINALISTES ######";

        RoundFinalistes(JoueurTab, BracketGagnants, BracketPerdants, aQuoiOnJoue);
        Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);

        //TEST, possibilité de cacher les lignes suivantes, mais c'est plus simple de se retrouver parmis les résultats avec
        cout << endl << endl << "####### RESULTATS " ;
        switch(aQuoiOnJoue)
        {
        case 1:
        {
            cout << "PILE-OU-FACE" ;
            break;
        }
        case 2:
        {
            cout << "PIERRE-FEUILLE-CISEAUX" ;
            break;
        }
        case 3:
        {
            cout << "JEU-DE-DES" ;
            break;
        }
        default:
            cout << "ErrSelecJeu" ;
        }
        cout << " #######" << endl;


        ParticipantsElimine.push_back(JoueurTab[BracketPerdants[0]].numero);
        ParticipantsElimine.push_back(JoueurTab[BracketGagnants[0]].numero);

        unsigned cmpt=0;
        for(unsigned i=4/*nmbParticipantsTotal*/; i>0; --i)
        {
            ++cmpt;
            cout << cmpt << ". " ;
            cout << JoueurTab[ParticipantsElimine[i-1]].nameFirst << " " << JoueurTab[ParticipantsElimine[i-1]].nameLast << endl;
        }
    }


    return 0;
}
