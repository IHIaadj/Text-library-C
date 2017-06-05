
/** Ce .c regroupe toutes fonctions gerant le menu Affichage.
  * Ces fonctions concernent principalement :
  * L'affichage du texte ou d'une partie du texte.
  */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include "Headers.h"

//////////////////////////******************************** Affichage *************************************///////////////////////////////

/***********************************************************************************************************/

void Affichtexte(Mot* tete) /* Rôle : Affiche un texte (liste de mot). */
{
    Mot* P;
    P = tete ;
	printf("\n");
	int y = wherey();
	while (P != NULL)
    {
         y = wherey();
		printf("%s", Valeur(P)) ;  // On parcout la liste et on ecrit à chaque fois le mot suivie de la ponctuation.
		printf("%s", Ponct(P));
		if ((Suivant(P)!=NULL)&&(Nligne(P)!=Nligne(Suivant(P)))) // Si on change de ligne alors on ecrit un retour à la ligne.
            {printf("\n");
             y = wherey();
            }
        if (y > 30){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
		P = Suivant(P);
	}


}
/***************************************************************************************************************/
void Affichtext(texte* tete) /* Rôle : Choisit le texte à ecrire et l'écrit on utilisant la procedure Affichtexte. */
{
    texte * t;
    t = Choixtexte(tete);
    if (t == NULL ) { return 0; }
    else {
        Affichtexte(TeteMo(t));
    }
    fflush(stdin);
    getchar();
    ClearScreen();
}

/*****************************************************************************************************/
void Rech_nbrlet(texte *tete)    /*Rôle :Procédure qui affiche tous les mots qui ont un nombre de caractères précis */
{
    Mot *P=NULL;
    texte *t=NULL;
    int nb=0,trouv=0;

    t=Choixtexte(tete);  //On choisit le texte à manipuler
    if (t == NULL ) { return 0; }
    else {
    P=TeteMo(t);      //On rrécupère sa tete

    printf("Donnez un entier (<20) : ");     //On récupère le nombre de caractères
    scanf("%d",&nb);
    printf("Les mots qui contiennent %d caracteres sont : \n",nb);

   int y;
    while (P!=NULL)
        {
            if (strlen(Valeur(P))==nb)
            {
                printf("%s ,",Valeur(P));  //On écrit les mots qui ont une taille égale au nombre choisi
                y = wherey();
                 if (y > 30){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
                trouv=1;
            }
            P=Suivant(P);
        }
        if(!trouv)
            printf("Il n'existe aucaun mot dans ce texte qui a %d caracteres ! \n");


    fflush(stdin);
    getchar();
    ClearScreen();
    }

}

/****************************************************************************************/
void Affich_lignes(texte *TETE)    /* Rôle : Procédure qui affiche un nombre quelconque de lignes */
   {
       int nbr,*tab=NULL,i=0;
       texte *P;
       Mot *Q,*t;
       P=TETE;
       char Nomfichier[255]={0};
       int y;
       P=Choixtexte(TETE);       // On choisit le texte à manipuler
       if (P == NULL){ return 0;}
       else {

        t=TeteMo(P);         // On récupère la tete du texte choisi

       printf("Combien de lignes voulez vous afficher ? ");    //On récupère le nombre de lignes à afficher
       scanf("%d",&nbr);

       tab=malloc(nbr*sizeof(int));     //On alloue dynamiquement le tableau qui va contenir les numéros de lignes à afficher

         for (i=0;i<nbr;i++)        //On récupère les numéros de lignes à afficher dans notre tableau
         {
             printf("La ligne %d ", (i+1));
             scanf("%d",&tab[i]);
             y = wherey();
             if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
         }


         /*-----------La boucle principale : On parcourt le tableau de données -----------*/
        for(i=0;i<nbr;i++)
             {
                 //Pour chaque numéro de ligne récuperé :
                 y = wherey();
                 if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

                    while ((tab[i]!=Nligne(t))&&(Suivant(t)!=NULL))     //Tant qu'on avait pas atteint la ligne recherché on avance dans la LLC
                         {
                             t=Suivant(t);
                         }
                   printf(" La ligne %d est :   ", tab[i]);
                   while ((tab[i]==Nligne(t))&&(Suivant(t)!=NULL))   //Tant qu'On est dans la bonne ligne ,On affiche les mots
                      {
                        printf("%s ",Valeur(t));
                        t=Suivant(t);
                        y = wherey();
                        if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

                      }
                    if ((t!=NULL)&& (tab[i]==Nligne(t)))    //Une vérification ajoutée pour traiter le dernier maillon a part , pour qu'il n' y est pas d'erreur
                        printf("%s ",Valeur(t));

                    if(tab[i] != Nligne(t)){ printf("Le texte ne contient pas ce nombre de ligne. "); }
                 printf("\n\n");
            }
fflush(stdin);
getchar();
ClearScreen();}
   }

/*****************************************************************************************************/
void TaillFich(texte *tete)  /*Rôle : Procédure qui calcule est affiche le nombre de mots et de lignes d'un texte choisi*/

      {
          texte *t;
          Mot *P;
          int m=0,l=1;

          t=Choixtexte(tete);     //On choisit le texte à manipuler
          if ( t== NULL) {return 0; }
          else {
          P=TeteMo(t);   //on récupère la tete du texte choisi

            while (P!=NULL)
            {
                if ((Suivant(P)!=NULL)&&(Nligne(P)!=Nligne(Suivant(P)))) //Si on a changé de ligne
                {
                    l++; //On incrémente le npmbre de lignes
                }
                m++; //on incrémente la variable qui contient le nombre de mots
                P=Suivant(P);
            }


        printf("Ce texte contient %d lignes et %d mots .",l,m);  //On affiche le nombre de lignes et de mots du texte
fflush(stdin);
getchar();
ClearScreen();
          }
      }

/*********************************************************************************************/
void AffichageApartir(texte *tete)  /*Rôle :Procédure qui affiche un nombre de lignes à partir d'une ligne précise */
  {
      texte *t;
      Mot *P;
      int nbrli,deb, y ;

      t=Choixtexte(tete);  //On choisit le texte à manipuler
      if (t== NULL){ return 0; }
      else {

      printf("Combien de lignes voulez vous afficher ? ");
      scanf("%d",&nbrli); //On récupère le nombre de lignes à afficher

      printf("A partir : ");
      scanf("%d",&deb);   //on récupère la 1ere ligne à afficher

      P=TeteMo(t);  //On récupère la tete du texte choisi auparavant
      y = wherey();
      if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
      while((Nligne(P)!=deb)&&(Suivant(P)!=NULL))   //on avance dans la liste tant qu'on est pas dans la bonne postion
      P=Suivant(P);

      if(Suivant(P)!=NULL)
      {
          while((Nligne(P)!=(deb+nbrli))&&(Suivant(P)!=NULL)) //on affiche les mots tant
              {                                               // qu'ils sont dans les lignes
                  printf("%s ",Valeur(P));                    //à afficher
                  if(Nligne(P)!=Nligne(Suivant(P)))
                    printf("\n");
                  P=Suivant(P);

                 y = wherey();
                 if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }


              }
              if (Nligne(P)!=(deb+nbrli))   //cas particulier : le ddernier mot est à afficher !
                printf("%s",Valeur(P));
      }
      else
        printf("Erreur !");

fflush(stdin);
getchar();
ClearScreen();
      }
  }
/************************************************************************************************/
void Inverse_Lignes(texte *tete)  /*Rôle : Procédure qui inverse les lignes du texte et offre la possibilité de sauvegarder le résultat dans un fichier */
 {
     texte *t=NULL;
     FILE *F=NULL;
     Mot *P=NULL,*Q=NULL;
     char O;
     int y;
     t=Choixtexte(tete);   //On choisit le texte à manipuler
     if (t == NULL){return 0;   }
     else {
     P=TeteMo(t);  //On récupère la tete du texte choisi

     F=fopen("texte_inversé.txt","w");  //On ouvre le fichier ou on veux sauvegarder le texte inversé

     while(P!=NULL)
     {
          while((Suivant(P)!=NULL)&&(Nligne(P)==Nligne(Suivant(P))))   //tant qu'on est dans la même ligne
            P=Suivant(P);

            Q=P;  //On récupère P dans Q afin d'éviter la perte du pointeur

            while((Precedant(Q)!=NULL)&&(Nligne(Q)==Nligne(Precedant(Q))))  //tant qu'on est dans la même ligne
            {
                printf("%s ",Valeur(Q));  //On écrit le mot pointé dans la console...
                fprintf(F,"%s ",Valeur(Q));   //...et dans le fichier
                Q=Precedant(Q);
                y = wherey();
                if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
            }
            printf("%s ",Valeur(Q));
            fprintf(F,"%s",Valeur(Q));
            printf("\n");   //on fait un sautt de ligne dans la console
           fprintf(F,"%s","\n");  // et dans le fichier
          P=Suivant(P);
          y = wherey();
          if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
    }
    fclose(F);  //on ferme le fichier
    printf("\nVoulez vous sauvegarder le resultat dans un fichier ? ");
    scanf("%s",&O);
    if (O!='O')  //si l'utilisateur ne veux pase sauvegarder le fichier , on le supprime !!!
        unlink("texte_inversé.txt");

        fflush(stdin);
        getchar();
        ClearScreen();
     }
 }

/**************************************************************************************************/
void inverstexte(texte* P) /* Rôle : inverse tout le texte en commençant par le dernier mot. */
{


    texte* E;
    int y;
    E = Choixtexte(P);
    if (E == NULL) { return 0; }
    else {
       printf("%s", E->nomfich);
               Mot* Q, *D;
               Q = QueuMo(E);
               char v, nomfile[255];
               int i = Nligne(Q);
              printf("\nVoulez vous sauvegarder le resultat ? (O/N)");
               scanf("%c", &v);
               v = getchar();
               if ( toupper(v) == 'O')
                {
                    printf("\nDonner le nom du fichier : ");
                    scanf("%s", &nomfile);
                    FILE * F;
                    F = fopen(nomfile, "w");
               while (Q != NULL)
               {
                   if ( i > Nligne(Q)){ printf("\n"); i = Nligne(Q); fprintf(F, "\n"); }
                   printf("%s ", Valeur(Q));
                   fputs(Valeur(Q), F);
                   fputs(" ", F);
                   Q = Precedant(Q);
                   y = wherey();
                   if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

               }
               }
               else {
                 while (Q != NULL)
               {
                   if ( i > Nligne(Q)){ printf("\n"); i = Nligne(Q);  }
                   printf("%s ", Valeur(Q));
                   Q = Precedant(Q);
                   y = wherey();
                   if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

               }
               }
fflush(stdin);
getchar();
ClearScreen();
    }
}
/**************************************************************************************************/
void permut(Mot *A,  Mot *B)  /* Rôle : permute entre les valeurs des mots des deux Mot A et B. */
{
    Mot *C;
    C = allouer(); // Mot de sauvegarde.
    strcpy(C->mot , A->mot);
    strcpy(A->mot , B->mot);
    strcpy(B->mot , C->mot);
    free(C);


}
/**************************************************************************************************/
char* UpperCase(char mot[]) /* Rôle : Rend toute une chaine de caractères en majuscule. */
{
   char* mot2;
    int i;
   mot2 = malloc(255*sizeof(char));
    for (i=0;i<= strlen(mot); i++){
       mot2[i] = toupper(mot[i]);
    }


   return mot2;

}
/**************************************************************************************************/
Mot* Copytexte(texte* P)  /* Rôle : Crée une copie du texte (LLC). */
{
        texte* Q = NULL, *D = TeteMo(P), *E, *F;

        while  (D != NULL)
        {

            E= allouer();
            Aff_AdrG(E, NULL);
            Aff_AdrD(E, NULL);
            Aff_Val(E, D);
            Aff_pos(E, D);
            Aff_Nligne(E, D);
            if (Q != NULL){ Aff_AdrD(F, E); }
            else { Q = E; }
            F=E;
            D = Suivant(D);
        }

        return Q;
}

/**************************************************************************************************/
void TriAlpha(texte* P) /* Rôle : Tri un texte choisit par ordre alphabetique. */
{
    int y;

    texte* E;
    E = Choixtexte(P);
    if (E == NULL) { return 0; }
    else {
    printf("\n Voulez vous enregistrer le texte dans un fichier ? (O/N) ");
    char v, nomfile[255], mot1[255], mot2[255];
    scanf("%c", &v);
    v = getchar();
    Mot* Q , *D, *A;
    int cpt,i=0;
    Q= Copytexte(E);

    if (toupper(v) == 'O')
    {
        printf("Donner le nom du fichier : ");
        scanf("%s", &nomfile);

        FILE* F;
        F = fopen(nomfile, "w");
        do {

		D = Q;

		cpt = 0 ;

		while (Suivant(D) != NULL) {
		if (strcmp(UpperCase(Valeur(D)), UpperCase(Valeur(Suivant(D)))) > 0) {
            A = Suivant(D);
			permut(D,A) ;
			cpt++;

                }
        D = Suivant(D) ;

        }

        } while (cpt != 0) ;
        D = Q;
        while (D != NULL)
               {
                   if ( i > Nligne(D)){
                    printf("\n");
                    fputc(F, "\n"); i = Nligne(D);  }
                   printf("%s", Valeur(D));
                   printf("%s", Ponct(D));
                   fprintf(F, "%s ", Valeur(D));
                   fprintf(F, "%s ", Ponct(D));
                   D = Suivant(D);
                   y = wherey();
                   if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

               }




    } else {

         do {

		D = Q;

		cpt = 0 ;

		while (Suivant(D) != NULL) {
		if (strcmp(UpperCase(Valeur(D)), UpperCase(Valeur(Suivant(D)))) > 0) {
            A = Suivant(D);
			permut(D,A) ;
			cpt++;

                }
        D = Suivant(D) ;

        }

        } while (cpt != 0) ;
        D = Q;
        while (D != NULL)
               {
                   if ( i > Nligne(D)){ printf("\n"); i = Nligne(D);  }
                   printf("%s ", Valeur(D));
                   printf("%s", Ponct(D));
                   D = Suivant(D);
                   y = wherey();
                   if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }

               }



        }
fflush(stdin);
getchar();
ClearScreen();}
}
