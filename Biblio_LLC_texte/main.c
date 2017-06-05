
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include <../ModeleLLC/ModeleLLC.h>
#include <unistd.h>
#include "Headers.h"


char chemin[255] = {0},
     ponctuation[255] =",?! ;:-.(){}";


//////////////////////////////////////*****************************AUTRES****************************************//////////////////////////////////////

/*****************************************************************************************/
void imprim(texte* P) /*Rôle : Imprime un fichier .txt . (testée sur Windows 8 et 7 ) */
{
     texte* t = Choixtexte(P);
     if (t == NULL) { return 0 ; }
     else {

        ShellExecute(NULL, TEXT("print"), TEXT(Nom_fich(t)), NULL, NULL, SW_HIDE); // Appele le systeme d'exploitation à realiser l'impression (car c'est le sys qui gere ça ).
        fflush(stdin);
        getchar();
        ClearScreen();
        }
}
/*******************************************************************************************/
int ponctu(char o) /* Rôle : Indique si le caractère donné est un signe de ponctuation. */
{
    int v=0, i;
    for (i = 0; i <strlen(ponctuation); i++)
    {
        if (ponctuation[i] == o) {v = 1; }
    }
    return v;

}

/**************************************************************************************/
texte* Choixtexte(texte* P) /* Rôle : Choisit le texte à manipuler. */
{

    texte* E= P;

     if (E == NULL) { printf("Il n'y a aucun texte a charger");      // Dans le cas ou l'utilisateur n'a pas
                      getchar();                                     // encore ouvert de texte.
                      ClearScreen();
                      return NULL;
                     }
     else {
            if (Suivant_T(P) == NULL){ E= P; }
            else {
        printf("Quel texte voulez vous manipuler (Donner l'indice du texte) :  ");

        int k = 0, c;

        while (E != NULL)
        {
            printf("  \n%d. %s", (k+1), E->nomfich);                      // On liste la liste des textes
            k++;                                                  // Pour que l'utilisateur choisit le texte à manipuler.
            E = Suivant_T(E);
        }
        printf("\n");
        E = P;
        scanf("%d", &c);
        c--;
        for (k=0; k<c; k++)
        {
            E= Suivant_T(E);
        }}
        return E;             // Elle retourne le texte choisit.
        }

}

///////////////////////////////////////*************************** FICHIER ******************************//////////////////////////////////////////


/*****************************************************************************************/
void Configuration()  /* Rôle : Change le chemin du fichier utilisé. */
{

    printf("Par default le chemin des fichiers utilises est le repertoire du projet.\n ");
    printf("Definir un autre chemin : ");
    scanf("%s", &chemin);
    ClearScreen();
}

/*****************************************************************************************/
void Sauv_FichS(texte* tete) /* Rôle : Enregistre le texte sous un fichier donné. */
{

        FILE* F;

        Mot* P = NULL;
        texte *t=NULL;
        char mot[255] ={0}, nom[255]= {0};
        int i = 1;

        t=Choixtexte(tete);                             // On choisit le texte à enregistrer.
        if (t == NULL ) { return 0; }

        else{

        P=TeteMo(t);
        char nomfile[255];

        printf("Donner un nom de fichier : ");
        scanf("%s", &nomfile);                            // On lit le nom du fichier.
        strcat(nom, chemin);                              // on concatene avec le chemin, dans le cas ou l'utilisateur à changer le chemin.
        strcat(nom, nomfile);
        F= fopen(nom, "w");

        if (F!=NULL)
        {
            while (P != NULL)
            {
                if (Nligne(P) > i){ fprintf(F, "\n"); i++; }  // Si on est à une autre ligne, on ecrit un saut de ligne dans le fichier.
                strcat(mot, Valeur(P));
                strcat(mot, Ponct(P));
                fputs(mot, F);                                // On ecrit le mot avec la ponctuation qu'il y a après.
                P = Suivant(P);
                strncpy(mot, "", sizeof(mot));

            }

        }fclose(F);

        getchar();
        ClearScreen();
        }
}
/*****************************************************************************************/
void Sauv_Fich(texte* tete)  /* Rôle : Enregistre le fichier en ecrasant le premier fichier chargé. */
{

        FILE* F;

        Mot* P = NULL;
        texte *t=NULL;
        char mot[255] ={0}, nom[255]= {0};
        int i = 1;

        t=Choixtexte(tete);                              // On choisit le texte à enregistrer.
        if (t == NULL ) { return 0; }                    // Si l'utilisateur n'a chargé aucun texte en revient au menu.

        else{

        P=TeteMo(t);                                    // On affecte à P la tete de mon texte t.

        strcat(nom, chemin);
        strcat(nom, Nom_fich(t));                      // On concatene le nom du fichier avec le chemin.

        F= fopen(nom, "w");

        if (F!=NULL)
        {
            while (P != NULL)
            {
                if (Nligne(P) > i){ fprintf(F, "\n"); i++; } //Si on est à une autre ligne, on ecrit un saut de ligne dans le fichier.
                strcat(mot, Valeur(P));
                strcat(mot, Ponct(P));
                fputs(mot, F);                             // On ecrit le mot avec la ponctuation qu'il y a après.
                P = Suivant(P);
                strncpy(mot, "", sizeof(mot));

            }

        }fclose(F);

        fflush(stdin);                                  // On vide le buffer.
        getchar();                                      // On attend jusqu'a ce que l'utilisateur appuie sur entrée.
        ClearScreen();                                  // On efface la zone d'interaction avec l'utilisateur.
        }
}

/*************************************************************/
int lecttexte(texte** text )
{

    FILE* F;
    char mot[255], nom[255] = {0};
    strcat(nom, chemin);
    strcat(nom, Nom_fich(*text));

    F = fopen(nom, "r");      // On ouvre le fichier on mode lecture.
    Mot *P, *Q;
    int ligne= 1, pos = 1, i = 0;
    Aff_Tete(*text, NULL);              // On initialise la tête et la queue à NILL.
    Aff_Queu(*text, NULL);

    int k = 0, l=0;

    if (F != NULL){

            char c = fgetc(F);
            fseek(F, -1, 1);
            while(c != EOF)         // On parcourt le fichier jusqu'à la fin.
            {

                    strncpy(mot, "", sizeof(mot));   // On remet mot à NULL à chaque iteration.
                        if (l){ fseek(F , -1, 1); }

                        c =fgetc(F);
                        k =0;
                        while ( !ponctu(c) && c!= EOF && c!= '\n')   // On extrait le mot.
                        {
                            mot[k] = c;
                            k++;
                            c = fgetc(F);
                        }

                        P = allouer() ;    // On alloue un Mot.
                        Aff_Val(P,mot);    // On lui affecte le mot.
                        Aff_Nligne(P, ligne); // On lui affecte le numero de la ligne et sa position.
                        Aff_pos(P, pos);
                        Aff_AdrD(P,NULL) ;  // Car la liste est biderectionnelle.
                        Aff_AdrG(P,NULL);
                        if (TeteMo(*text) != NULL) {Aff_AdrD(Q,P) ; Aff_AdrG(P,Q); } // Si la tete n'est plus à NILL alors on lie les deux mot(precedant avec le suivant).
                        else { Aff_Tete(*text, P); Aff_AdrG(P, NULL);}
                        Q = P ;
                        if (c == '\n'){  // On verifie si on a atteint la fin de la ligne, si oui on incremente ligne et on remet pos à 1.
                            ligne++;
                            pos = 0;
                            c = fgetc(F); // On avance dans le fichier.


                        } else
                        {   // Si on est au milieu de la ligne.
                            k =0;
                            while (ponctu(c)) // On extrait la ponctuation qui vient après le mot extrait.
                            {
                                P->ponctu[k] = c;
                                k++;
                                c = fgetc(F);
                                l=1;
                            }
                        if (c == '\n'){ // Si après le dernier mot, il y a de la ponctuation.
                            ligne++;
                            pos = 0;
                            c = fgetc(F);

                        }

                        }

                        pos++;

                    }
                    rewind(F); // On remet le curseur au debut du fichier.
                    Aff_Queu(*text, P); // On affecte à la queue le dernier Mot alloué.
                    return 1;
                    //printf("%s", P->ponctu);
                    fclose(F);


    }else { printf("\n Fichier inexistant \n"); return 0;  }


}

/*******************************************************************************************/

void CreateListText(texte ** tete) /* Rôle : Ouvrir un texte ( ajouter un maillon texte à la liste des textes). La procédure est récursive.  */
{
        char nomfich[255], *text, v ,bo;
        texte* P, *Q, *t = *tete;
        int i, nbfich, cpt, z;


//-------------------------------------------------------------------------------
                     while (t != NULL) { Q = t; t =Suivant_T(t); } // Q reçoit la queu de la liste des textes.
//-------------------------------------------------------------------------------

                    P = allouerT();
                    cpt = 0;
                    v = 0;


//------------------------------------------------------ Affiche un menu pour le choix Console/Fichier -------------------------------------------//

                        COORD debut, fin;
                        char *menu_listV1[2] = { "Depuis la console", "Depuis un fichier externe"  };

                              int j,
                                  xpos1 = 2,                      // la coordonnée x (colonne) à laquel on écrit les lignes du menu.
                                  ypos1[7] = {11,12};             // les coordonnées y (ligne) à laquel on ecrit chaque ligne du menu.

                                  color(15,1);

                               debut.X = xpos1;                   // on enregistre les Coords de début pour supprimer la partie du menu.
                               debut.Y = ypos1[0];

                                for (j=0; j< 2; j++)                 // On ecrit le menu.
                                {
                                    gotoxy(xpos1, ypos1[j] );
                                    printf("%s",menu_listV1[j] );
                                }
                                fin.X = wherex();              // on enregistre les Coords de fin pour supprimer la partie du menu.
                                fin.Y = wherey();
                                //printf(" les pos sont , %d %d    ", fin.X, fin.Y);
                                j=0;


                                int continu = 1;
                                while(continu)
                                {


                                    gotoxy(xpos1, ypos1[j]);                  // On ecrit la ligne qui doit être coloré.
                                    color(1,15 );
                                    printf("%s",menu_listV1[j] );


                                switch( _getch() )
                                {
                                    case 72: if(j>0) {               // Si l'utilisateur appuie sur le bouton UP et on est pas dans la premiere ligne du menu.
                                        gotoxy(xpos1,ypos1[j] );     // On décolore ce qui a été coloré.
                                        color(15,1);
                                        printf("%s", menu_listV1[j] );
                                        --j;                         // On decremente le j (on monte dans le menu).
                                        }
                                        break;

                                    case 80: if(j< 1)           // Si l'utilisateur appuie sur le button DOWN et on est pas dans la dernière ligne du menu.
                                        {
                                            gotoxy(xpos1,ypos1[j] );   // On decolore ce qui a été coloré.
                                            color(15,1);
                                            printf("%s", menu_listV1[j] );
                                            ++j;                // On incremente le j (On descend dans le menu).
                                            }
                                    break;
                                    case 75 : continu = 0; supprdepuis(debut, fin);  break;
                                    case 77 : continu = 0; supprdepuis( debut, fin ); break;

                                    case 13: if(j==0) {  cpt= 0 ;  continu =0;  }   // Si l'utlisateur appuie sur entrée il choisit la ligne selectionnée,
                                             if(j==1) {  cpt = 1;  continu = 0; }   // On sort donc de la boucle(Continu = 0) et on met le cpt par rapport à la ligne.

                                        break;
                                }
                                }

                        supprdepuis(debut, fin); // Supprime la partie comprise entre les COORDs debut et fin.

//---------------------------------------------------------------------------------------------------------------------------------------
                        color(15,1);
                        if (cpt == 1)  // MODE : Fichier externe.
                        {

                        do
                            {

                                printf("Donner le nom d'un fichier : ");  // On demande le nom du fichier.
                                scanf("%s", &nomfich);
                                Sauv_Nom(P, nomfich);                     // On sauvegarde le nom du fichier dans le maillon du texte (déjà allouer).


                              } while(!lecttexte(&P));                   // On lit le fichier et on crée la liste de mot associé.
                        }

             else {         // MODE : En console.


                 do
                            {

                                FILE* F;
                                text = malloc(1000* sizeof(char));
                                printf("Donner le titre du texte : ");   // On demande un titre au texte.
                                scanf("%s", &nomfich);
                                Sauv_Nom(P, nomfich);                    // On sauvegarde le titre dans le maillon.
                                printf("\n");
                                fflush(stdin);
                                F =fopen(nomfich, "w");
                                printf("Entrer votre texte : \n\n");         // On demande le texte.
                                fscanf(stdin, "%[^/]", text);                //On lit jusqu'à ce que l'utilisateur entre un slash /.
                                Sleep(1000);
                                fprintf(F, "%s", text);                      // On ecrit le texte dans un fichier (qui sera supprimer à la fin).
                                fclose(F);


                            }
                         while(!lecttexte(&P));                  // On crée la liste de mot du texte.


                   }

                    Aff_AdrT(P, NULL);
                    if (*tete != NULL){ Aff_AdrT(Q,P);  }                // Si la tête de la liste des textes est null on affecte
                    else { *tete = P; }
                    Q = P;
                    fflush(stdin);

                    printf("Voulez vous charger un autre texte pour la manipulation simultanee ?");
                    scanf("%c",&bo);
                    if(bo == 'O'){   // On appelle la procedure si l'utilisateur veut charger un autre texte.
                    ClearScreen();
                    CreateListText(tete);
                      }

                    ClearScreen();
}

