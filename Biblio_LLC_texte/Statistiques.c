
/** Ce .c regroupe toutes fonctions gerant le menu Statistiques.
  * Ces fonctions concernent principalement :
  * La frequence d'apparition, l'histogramme.
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <unistd.h>
#include "Headers.h"


//////////////////////////////////////************************** STATISTIQUES **************************///////////////////////////

/**************************************************************************************************/
int freqApp( char mot[], texte* P) /* Rôle : Calcule la frequence d'apparition de mot dans le texte. */
{
    Mot *Q = TeteMo(P);
    int i = 0;

    while (Q != NULL)
    {
            if( strcmp(Valeur(Q), mot)== 0 ) // strcmp renvoi 0 dans le cas ou les mots sont identiques.
            {
                i++;
            }

            Q = Suivant(Q);
    }
    return i;
}
/**************************************************************************************************/
void Frequence(texte** tete)/* Rôle : Affiche la frequence d'un mot donné dans un texte choisit. */
{
    texte* t;
    t = Choixtexte(tete);
    if (t== NULL) { return 0; }       // Si l'utilisateur n'a pas encore ouvert de texte.
    else
    {
        char mot[255];
        printf("Donner le mot : \n");
        scanf("%s", &mot);
        printf("Sa frequence d'apparition est : %d ", freqApp(mot, t)); // On appelle la fonction precedante.
        fflush(stdin);
        getchar();
        ClearScreen();

    }
}


/**************************************************************************************************/
void histo(texte* P) /* Rôle : Affiche un histogramme comparant la frequence de plusieurs mot. */
{

        texte* E;
        E = Choixtexte(P);
        if ( E == NULL){ return 0;}


        else {

        char** listemots;   // Un tableau de mot pour ecrire les mots en bas de l'histogramme.
        int nbmots, i;

        printf("Combien de mots voulez vous representer ? ");   // On demande le nombre de mots à afficher.
        scanf("%d", &nbmots);

        listemots = malloc(sizeof(*listemots)*nbmots);

        for (i=0; i <nbmots; i++){
        listemots[i] = malloc(sizeof(**listemots)* 255);}


        int y = wherey();      // On recupere la ligne du curseur pour le dessin de l'histogramme.

         for (i = 0; i<nbmots ; i++)
        {
            printf("\n Donner mot :  ");           // On recupere les mots.
            scanf("%s", listemots[i]);
            y = wherey();
            if (y > 30){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

        }


        // Calcule du Maxfreq des mots données :
        int max = freqApp(listemots[0], E);
        for (i =0; i<nbmots ; i++){
          if( freqApp(listemots[i], E) > max ){ max = freqApp(listemots[i], E); }

        }


       int** histo = NULL; // tableau d'entier qui va contenir le code ascii de notre symbole.

        histo = (int**) malloc(sizeof(int*)*max);  // On alloue l'espace memoire pour chaque ligne.
        for (i=0 ; i<max; i++){
            histo[i] = (int*) malloc(sizeof(int)*nbmots );   // On alloue l'espace memoire pour chaque colonne.
         }


       int j =0;

       for (i=0; i < max; i++){
        for(j=0; j <nbmots ; j++){
            histo[i][j] = 0;                      // On initialise notre tableau à 0.
        }
       }
        j=0 ;

    if (max <15)
    {
    do {

    for (i=max - freqApp(listemots[j], E); i < max  ; i++){
        histo[i][j] = 219;                                              // On remplit notre tableau de haut en bas avec notre symbole 219 : █.
    }
    j++;
    } while (j < nbmots  );
    }
    else {

         do {

    for (i=(max - freqApp(listemots[j], E))/2; i < max/2  ; i++){
        histo[i][j] = 219;                                              // On remplit notre tableau de haut en bas avec notre symbole 219 : █.
    }
    j++;
    } while (j < nbmots  );


    }
    ClearScreen();

   // On calcule la longueur maximum des mots données (Pour l'affichage).
   int maxlen= strlen(listemots[0]);
   for (i=0; i< nbmots; i++){ if (strlen(listemots[i]) > maxlen) {maxlen = strlen(listemots[i]); }}


//-------------------------------------------- Tracer de l'encadrer qui va contenir l'histogramme ----------------------------//
   gotoxy(45,y);
   printf("%c", 218 );
   for (i=0; i<50; i++){ printf("%c", 196);}
   printf("%c", 191 );
   for (j=y+1; j< y+15; j++)
   {
       gotoxy(45,j);
       printf("%c", 179);

       gotoxy(96,j);
       printf("%c", 179);

   }
   gotoxy(45,j);
   printf("%c", 192 );
   for (i=0; i<50; i++){ printf("%c", 196);}
   printf("%c", 217 );

//-------------------------------------------- Tracer de l'histogramme -------------------------------------------------------//
        int k, h;

        int clr=2;
        h = 2;
        for( i=0; i < nbmots; i++)
        {
            if (max > 15 ) { k = y + 15 - max/2 ;

            color(clr+i,1);
             for(j=0; j<max/2; j++)
             {
                  gotoxy(47+i+h, k);
                  printf("%c", histo[j][i]);
                  k++;
             }
             color(15,1);
             if (nbmots * maxlen > 40 ){ h += 2; }
            else
            h += maxlen; }
            else {k = y+15 - max;

            color(clr+i,1);
             for(j=0; j<max; j++)
             {
                  gotoxy(47+i+h, k);
                  printf("%c", histo[j][i]);
                  k++;
             }
             color(15,1);
             if (nbmots * maxlen < 40 ){ h += 2; }
            else
            h += maxlen;
            }
        }
     // --------------------- Affiche la légende --------------------- //
     clr = 2;
     gotoxy(2, y);
     printf("\n      Legende :     \n ");
     for (i= 0; i<nbmots; i++)
     {
         gotoxy(2,y+3+i);
         color(clr+i, 1);
         printf(" %c.", 220);
         color(15,1);
         printf("%s, %d", listemots[i], freqApp(listemots[i], E));

     }

     // --------------------- Affiche l'echelle --------------------- //
     int a = (max < 15 ) ? 1 : 2;
     printf("\n\n      Echelle :     \n\n");
     printf("    %c ---->  %d ", 219, a);



    fflush(stdin);
    getchar();
    ClearScreen();
    }
}
/**************************************************************************************************/
int longueur(Mot* tete) /* Rôle : Donne la longueur du texte en nombre de mot. */
{
    int cpt = 0;
     Mot* P;
     P = tete;
     while (P!= NULL)
     {
         cpt++;
         P = Suivant(P);

     }
     return cpt;
}
/**************************************************************************************************/
void DonnerPoslig(texte* P, char mot[]) /* Rôle : Affiche la position et la ligne de chaque occurance de mot. */
{
    Mot *Q = TeteMo(P);
    int y;
    while (Q != NULL)
    {
            if( strcmp(Valeur(Q), mot)== 0 )
            {
               printf(" Ligne : %d | Colonne : %d \n", Nligne(Q), Position(Q));
               y = wherey();
               if (y > 30){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
            }

            Q = Suivant(Q);
    }

    printf("\n");
}
/**************************************************************************************************/
void Npremierfreq(texte* P) /* Rôle : Affiche les N premiers mots, en fonction de leur frequence. */
{

//----------------------------------------------- Definir une nouvelle structure -------------------------------------//
                                 // Cette structure n'est utile que dans cette fonction.
        typedef struct freq
        {
            int freq;
            char mot[255];
            int* pos;
            int* ligne;
        } freq;

//---------------------------------------------------------------------------------------------------------------------

        texte* E;
        E = Choixtexte(P);
        if (E == NULL ){ return 0; }
        else
        {

        printf("Donner le nombre de mots a afficher : ");
        int nbmot;
        scanf("%d", &nbmot);

        Mot* Q = TeteMo(E);
        int i, j, trouv = 0;

        freq * tab = malloc(longueur(TeteMo(E))* sizeof(freq)); // On alloue dynamiquement un tableau de freq.

        for (i=0; i <longueur(TeteMo(E)); i++)
        {
            trouv = 0;
            for (j=0; j<i ; j++){
                if (!strcmp(tab[j].mot, Valeur(Q)))
                {

                    trouv++;
                }
            }

            if(!trouv)
            {
            strcpy(tab[i].mot, Valeur(Q));
            tab[i].freq = freqApp(Valeur(Q), E);
          // printf("La frequence d'apparition de %s est : %d\n ", tab[i].mot, tab[i].freq);
            }

            Q = Suivant(Q);
        }

        int cpt;
        freq c;

             do
             {
             cpt=0;
             for (i=0; i<longueur(TeteMo(E))-1;i++)
             {
                 if (tab[i].freq<tab[i+1].freq)
                 {
                   c=tab[i];
                   tab[i]=tab[i+1];
                   tab[i+1]=c;
                   cpt++;
                 }
             }
           } while (cpt>0);


        int y = wherey();

          for (i=0; i<nbmot; i++)
           {

               printf("Le %d Mot est : %s, sa frequence est %d.\n Ses occurrences :\n", i+1, tab[i].mot, tab[i].freq);
               DonnerPoslig(E, tab[i].mot);
                y = wherey();
                if (y > 30){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

           }



            fflush(stdin);
            getchar();
            ClearScreen();
        }
}
/********************************************************************************************/
