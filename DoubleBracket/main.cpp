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

struct Participants
{
    int numero;
    string nameLast;
    string nameFirst;
    int roundResult;
    int position;
};


vector<Participants> JoueurTab;
void Inscriptions()
{
    for(int i = 0; i <64; i++)
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

//tableaux utilisés pour trouver qui fais face à qui
vector<int> BracketGagnants(0);
vector<int> BracketPerdants(0);
void Repartition()
{
    //selon le résultat du round précédent, déterminer la position du joueur (1=winner bracket, 0=loser bracket, -1=éliminé)
    for(int i = 0; i <64; i++)
    {
        if (JoueurTab[i].roundResult==0)
        {
            if (JoueurTab[i].position==1)
            {
                JoueurTab[i].position=0;
            }
            else
            {
                JoueurTab[i].position=-1;
            }
        }

        //prépare tous les joueurs pour leurs round imminent (voir fonction Round() )
        JoueurTab[i].roundResult=1;
    }

    //mettre les joueurs dans leurs bracket respectifs
    BracketGagnants.clear();
    BracketPerdants.clear();
    for(unsigned i = 0; i <64; i++)
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

void RoundGagnants()
{
    if (BracketGagnants.size() > 1)
    {
        for(unsigned i = 0; i < BracketGagnants.size(); i+=2)
        {
            PileOuFace(BracketGagnants[i],BracketGagnants[i+1]);
            cout << endl << "Gagnant" << endl << BracketGagnants[i] << endl << BracketGagnants[i+1] <<endl ;

            //JoueurTab[aaa].roundResult=

            /*if(PileOuFace())
            {
                JoueurTab[BracketGagnants[i]].roundResult=0;
            }
            else
            {
                JoueurTab[BracketGagnants[i+1]].roundResult=0;
            }*/

            JoueurTab[BracketGagnants[i]].roundResult=0;
            JoueurTab[BracketGagnants[i+1]].roundResult=1;
        }
    }
}

void RoundPerdants()
{
    if (BracketPerdants.size() > 1)
    {
        for(unsigned i = 0; i < BracketGagnants.size(); i+=2)
        {
            for(unsigned i = 0; i < BracketPerdants.size(); i+=2)
            {
                PileOuFace(BracketPerdants[i],BracketPerdants[i+1]);
                cout << endl << "Perdant" << endl << BracketPerdants[i] << endl << BracketPerdants[i+1] <<endl ;
            }

            JoueurTab[BracketPerdants[i]].roundResult=0;
            JoueurTab[BracketPerdants[i+1]].roundResult=1;
        }
    }
}


void TestListe() //TEST écrire participants 1 par 1
{
    cout << endl <<endl << "#### PARTICIPANTS ####" << endl;
    for(int i = 0; i <64; i++){
        cout << endl << i << " - ";
        cout << "J" << JoueurTab[i].numero;
        cout << " " << JoueurTab[i].nameLast;
        cout << " " << JoueurTab[i].nameFirst;
        cout << " r" << JoueurTab[i].roundResult;
        cout << " p" << JoueurTab[i].position;
    }
}

void TestGagnants() //TEST écrire participants 1 par 1
{
    cout << endl <<endl << "## BRACKET GAGNANTS ##" << endl;
    if (BracketGagnants.size() > 1)
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

void TestPerdants() //TEST écrire participants 1 par 1
{

    cout << endl <<endl << "## BRACKET PERDANTS ##" << endl;
    if (BracketPerdants.size() > 1)
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
    Inscriptions();

    for (unsigned i=0; i < 10; i++)
    {
        cout << endl << endl << "###### ROUND " << i+1 << " ######";

        //TEST
        //TestListe();

        Repartition();
        RoundGagnants();

        Repartition();
        RoundPerdants();

        // TEST
        //TestGagnants();
        //TestPerdants();
    }


    return 0;
}
