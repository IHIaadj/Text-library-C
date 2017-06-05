#include "../ModeleLLC/LLC_modele.h"



typedef struct Lignes Lignes ;  //La structure qui permet de récuperer les lignes à insérer et leurs coordonnées
       struct Lignes
       {
           char *phrase[255];
           Mot *Debutligne;
           Mot *Finligne;
           int pos;
       };


void imprim(texte* P); /*Rôle : Imprime un fichier .txt . (Marche que sur Windows) */

int ponctu(char o); /* Rôle : Verifie si o est un signe de ponctuation. */

texte* Choixtexte(texte* P); /* Rôle : Affiche la liste de texte ouvert, et demande à l'utilisateur de choisir un. */

void Configuration(); /* Rôle : Gère la fonction "CONFIGURATION" du menu "FICHIER". */

void Sauv_FichS(texte* tete); /*Rôle : Enregistre un texte (depuis la LLC) vers un fichier nouveau. */

void Sauv_Fich(texte* tete); /* Rôle : Enregistre un texte et ecrase le fichier original. */

int lecttexte(texte** text ); /* Rôle : lit un texte depuis un fichier et crée la liste correspondante. */

void CreateListText(texte ** tete); /* Rôle : Cree la liste de texte. */


/////////////////////////////////////////// EDITER //////////////////////////////////////////////////

void Rech_lettr(texte *tete);  /*Rôle : Procédure qui recherche tous les mots d'un texte choisi qui contiennent
                                        une chaine de caractères données à une position précise */

void Rech_Color(texte *tete); /*Rôle :Procédure qui recherche un nombre fixé de mots , et affiche le résultat avec des couleurs diffirents.*/

void Rech_Remp(texte *TETE); /*Rôle : procédure qui recherche un mot lu , et le remplacer par un autre .*/

void Insertion_Mots(texte *tete); /* Rôle : procédure qui permet d'insérer un ou plusieurs mots à des positions données.*/

void CreationStructLigne(Lignes tab[]); /*Rôle :Une procédure qui cré Une LLC pour chaque ligne lue à partir du fichier
                                           de travail de la procédure Insertion_Lignes*/

void Insertion_Lignes(texte *tete);  /*Rôle :Une procédure qui effectue l'insertion d'une ou plusieurs ligens à des positions données */

void Supp_Pos(texte *tete); /* Rôle : Supprime un mot donné par sa position et sa ligne. */

void Supp_Mot(texte *tete); /* Rôle : Supprime toutes les occurences d'un mot donnée. */

void Reinitial_Lig_pos(Mot *S);  /*Rôle : Procédure qui réinitialise les coordonnée des mots du texte*/

void Reinitial_Ligne(Mot *P);  /*Rôle :Une procédure qui réinitialise le nombre de lignes en fonction des positions */

void Supp_lignes(texte *tete); /* Rôle : Supprime plusieurs ligne donnée. */


////////////////////////////////////////////////////// AFFICHAGE ///////////////////////////////////////////////

void Affichtexte(Mot* tete); /* Rôle : Affiche un texte (liste de mot). */

void Affichtext(texte* tete); /* Rôle : Choisit le texte à ecrire et l'écrit on utilisant la procedure Affichtexte. */

void Rech_nbrlet(texte *tete);    /*Rôle :Procédure qui affiche tous les mots qui ont un nombre de caractères précis */

void Affich_lignes(texte *TETE); /* Rôle : Procédure qui affiche un nombre quelconque de lignes */

void TaillFich(texte *tete);  /*Rôle : Procédure qui calcule est affiche le nombre de mots et de lignes d'un texte choisi*/

void AffichageApartir(texte *tete); /* Rôle : Affiche un nombre de ligne donné à partir d'une ligne donnée. */

void Inverse_Lignes(texte *tete);  /*Rôle : Procédure qui inverse les lignes du texte et offre la possibilité de sauvegarder le résultat dans un fichier */

void inverstexte(texte* P); /* Rôle : inverse tout le texte en commençant par le dernier mot. */

void permut(Mot *A,  Mot *B); /* Rôle : permute entre les valeurs des mots des deux Mot A et B. */

char* UpperCase(char mot[]); /* Rôle : Rend toute une chaine de caractères en majuscule. */

Mot* Copytexte(texte* P); /* Rôle : Crée une copie du texte (LLC). */

void TriAlpha(texte* P); /* Rôle : Tri un texte choisit par ordre alphabetique. */

////////////////////////////////////////////////////////////// STATISTIQUE ////////////////////////////////////////////////////
int freqApp( char mot[], texte* P); /* Rôle : Calcule la frequence d'apparition de mot dans le texte. */

void Frequence(texte** tete); /* Rôle : Affiche la frequence d'un mot donné dans un texte choisit. */

void histo(texte* P); /* Rôle : Affiche un histogramme comparant la frequence de plusieurs mot. */

int longueur(Mot* tete);  /* Rôle : Donne la longueur du texte en nombre de mot. */

void DonnerPoslig(texte* P, char mot[]); /* Rôle : Affiche la position et la ligne de chaque occurance de mot. */

void Npremierfreq(texte* P); /* Rôle : Affiche les N premiers mots, en fonction de leur frequence. */

