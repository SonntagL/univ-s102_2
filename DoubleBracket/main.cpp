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

bool PileOuFace(unsigned indexJ1, unsigned indexJ2)
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

//obligé de le mettre au-dessus des initialisations de variables/tableaux. Est utilisé pour les faire.
struct Participants
{
    int numero;
    string nameLast;
    string nameFirst;
    int roundResult;
    int position;
};

//-----------------------------VARIABLES GLOBALES--------------------------------------------
//a garder
    const unsigned nmbParticipantsTotal=64;

//----------------------------------FONCTIONS------------------------------------------------

void Inscriptions(vector<Participants> JoueurTab)
{
    for(int i = 0; i <nmbParticipantsTotal; i++)
    {
        //définir nom/prénom des participants (temporaire, utiliser entrée standard + tard)
        string tmpnom = "nom" + to_string(i);
        string tmpprenom = "prenom" + to_string(i);

        //ajouter participant dans JoueurTab
        Participants tmpjoueur = {i, tmpnom, tmpprenom, 1, 1};
        JoueurTab.push_back(tmpjoueur);

        cout << endl << i << " - J";
        cout << JoueurTab[i].numero << " ";
        cout << JoueurTab[i].nameLast << " ";
        cout << JoueurTab[i].nameFirst;
    }


}

void Repartition(vector<Participants> & JoueurTab, vector<int> &BracketGagnants, vector<int> &BracketPerdants, vector<int> &ParticipantsElimine)
{
    //selon le résultat du round précédent, déterminer la position du joueur (1=winner bracket, 0=loser bracket, -1=éliminé)
    for(int i = 0; i <nmbParticipantsTotal; i++)
    {
        if (JoueurTab[i].roundResult==0)
        {
            if (JoueurTab[i].position==1)
            {
                JoueurTab[i].position=0;
            }
            else
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
    for(unsigned i = 0; i <nmbParticipantsTotal; i++)
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

void RoundGagnants(vector<Participants> & JoueurTab, const vector<int> &BracketGagnants, bool &FinalisteGagnant)
{
    if (BracketGagnants.size() > 1)
    {
        for(unsigned i = 0; i < BracketGagnants.size(); i+=2)
        {
            unsigned tmp_numero_participant;
            tmp_numero_participant=PileOuFace(BracketGagnants[i],BracketGagnants[i+1]);

            //JoueurTab[tmp_numero_participant].roundResult=0;

            //pour truquer les résultats
            JoueurTab[BracketGagnants[i]].roundResult=1;
            JoueurTab[BracketGagnants[i+1]].roundResult=0;
        }
    }
    else
        FinalisteGagnant=true;

}

void RoundPerdants(vector<Participants> & JoueurTab, vector<int> &BracketPerdants, bool & FinalistePerdant)
{
    if (BracketPerdants.size() > 1)
    {
        for(unsigned i = 0; i < BracketPerdants.size(); i+=2)
        {
            unsigned tmp_numero_participant;
            tmp_numero_participant=PileOuFace(BracketPerdants[i],BracketPerdants[i+1]);

            //JoueurTab[tmp_numero_participant].roundResult=0;

            //pour truquer les résultats
            JoueurTab[BracketPerdants[i]].roundResult=1;
            JoueurTab[BracketPerdants[i+1]].roundResult=0;
        }
    }
    else
        FinalistePerdant=true;
}

void RoundFinalistes(vector<Participants> & JoueurTab, const vector<int> &BracketGagnants, const vector<int> &BracketPerdants)
{
    JoueurTab[BracketPerdants[0]].position=1;

    unsigned tmp_numero_participant;
    tmp_numero_participant=PileOuFace(BracketGagnants[0],BracketGagnants[1]);

    //JoueurTab[tmp_numero_participant].roundResult=0;

    //pour truquer les résultats
    JoueurTab[BracketGagnants[0]].roundResult=1;
    JoueurTab[BracketGagnants[1]].roundResult=0;
}


void TestGagnants(const vector<Participants> & JoueurTab, const vector<int> &BracketGagnants) //TEST écrire participants 1 par 1
{
    cout << endl <<endl << "## BRACKET GAGNANTS ##" << endl;
    if (BracketGagnants.size() > 0)
    {

        for(unsigned i = 0; i < BracketGagnants.size(); i++)
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
        for(unsigned i = 0; i < BracketPerdants.size(); i++)
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

int main()
{

    //voir fonction INSCRIPTIONS()
    //tableau qui liste les participants
    vector<Participants> JoueurTab;

    //voir fonction REPARTITION()
    //tableaux utilisés pour trouver qui fait face à qui
    vector<int> BracketGagnants(0);
    vector<int> BracketPerdants(0);
    vector<int> ParticipantsElimine(0);

    //voir fonctions ROUNDGAGNANTS() et ROUNDPERDANTS()
    //quand il ne reste qu'un joueur dans un tableau, il est mis à TRUE, si les deux sont TRUE, lance le round de finalistes
    bool FinalisteGagnant=false;
    bool FinalistePerdant=false;

    //--------------------------------------------------------------------------//

    Inscriptions(JoueurTab);

    unsigned roundCounter=0;
    while (true)
    {
        roundCounter++;
        cout << endl << endl << "###### ROUND " << roundCounter << " ######";

        Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);
        RoundGagnants(JoueurTab, BracketGagnants, FinalisteGagnant);

        Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);
        RoundPerdants(JoueurTab, BracketPerdants, FinalistePerdant);

        // TEST
        cout << endl ;
        cout << "J" << JoueurTab[32].numero;
        cout << " " << JoueurTab[32].nameLast;
        cout << " " << JoueurTab[32].nameFirst;
        cout << " r" << JoueurTab[32].roundResult;
        cout << " p" << JoueurTab[32].position;
        //TestGagnants(JoueurTab, BracketGagnants);
        //TestPerdants(JoueurTab, BracketPerdants);
        // TEST

        if(FinalisteGagnant && FinalistePerdant)
            break;
    }
    cout << endl << endl << endl << endl << "###### ROUND FINALISTES ######";
    RoundFinalistes(JoueurTab, BracketGagnants, BracketPerdants);
    Repartition(JoueurTab, BracketGagnants, BracketPerdants, ParticipantsElimine);

    // TEST
    TestGagnants(JoueurTab, BracketGagnants);
    TestPerdants(JoueurTab, BracketPerdants);
    // TEST


    cout << endl << endl << endl << endl << endl << endl << "####### RESULTATS #######";
    unsigned cmpt=0;
    ParticipantsElimine.push_back(JoueurTab[BracketPerdants[0]].numero);
    ParticipantsElimine.push_back(JoueurTab[BracketGagnants[0]].numero);

    for(unsigned i=65; i>0; --i)
    {
        cmpt++;
        cout << endl ;
        cout << cmpt << ". " ;
        cout << JoueurTab[ParticipantsElimine[i]].nameFirst << " " << JoueurTab[ParticipantsElimine[i]].nameLast;
    }


    return 0;
}
