
/** Ce .c regroupe toutes fonctions gerant le menu EDITER.
  * Ces fonctions concernent principalement :
  * La recherche, l'insertion et la suppression.
  */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <unistd.h>
#include "Headers.h"




/////////////////////////////////////////////************************ EDITER ********************************/////////////////////////////////////

/***************************************************************************************************************/
  void Rech_lettr(texte *tete)   /*Rôle : Procédure qui recherche tous les mots d'un texte choisi qui contiennent
                                        une chaine de caractères données à une position précise */
  {
      Mot *P=NULL;
      texte *t;
      char rech[255]={0},Mo[255]={0},chaine[255]={0};
      int po=0,i=0,j=0;

      t=Choixtexte(tete);    //on choisit le texte à manipuler
      if (t == NULL ) { return 0; }
      else {
      P=TeteMo(t);      //on récupère la tete du texte choisi

      printf("Rechercher les mots qui contiennent : ");
      scanf("%s",&rech);   //on récupère la chaineà rechercher

      printf("A la position : ");
      scanf("%d",&po);   //On récupère la position ou on va rechercher

      while(P!=NULL)
      {
          strcpy(Mo,Valeur(P));  //On fait une copie du mot dans une  autre variable

          for(i=0;i<strlen(rech);i++)
             chaine[i]=Mo[po+i-1];   //On récupère la partie à traiter dans la variable chaine

             if (!strcmp(chaine,rech))   //on compare la partie recupèré et la chaine recherchée
             {
                  j=0;
                  for(i=0;i<strlen(Valeur(P));i++)   //On écrit le mot parce qu'il contient la chaine recherchée dans la bonne position
                  {
                      if(Mo[i] == rech[j])   //si le caractère appartient à la chaine recherchée :
                      {
                          j++;
                          color(3,1);  //On l'affiche en vert
                          printf("%c",Mo[i]);
                      }
                      else
                      {
                          color(15,1);   //si ce n'est pas le cas , on l'affiche en blanc
                          printf("%c",Mo[i]);
                      }

                  }
                  printf(",");  //Un séparateur entre les mots trouvés

             }

             P=Suivant(P);  //ON passe au maillon suivant !

        }
        color(15,1);
      }
      fflush(stdin);
      getchar();
      ClearScreen();
}

/******************************************************************************************************/
void Rech_Color(texte *tete)     /*Rôle :Procédure qui recherche un nombre fixé de mots , et affiche le résultat avec des couleurs diffirents.*/
  {
      typedef struct  Info Info;    //la structure qui aide à creer un LLC qui contient les mots du texte avec leurs couleurs
      struct Info
      {
          char mo[255];
          Info *sui;
          char motrech[255];
          int couleur;     //un entier entre 0 et 14 inclus qui représente une couleur précise

      };
      texte *t=NULL;
      Mot *P=NULL;
      char chaine[255]={0};
      Info *Q=NULL,*S=NULL,*te=NULL;
      int nb=0,i=0,clr=0;

      t=Choixtexte(tete);   //On choisit le texte à manipuler
      if (t == NULL ) { return 0; }
      else {
      P=TeteMo(t);      //On récupère la tete du texte choisi

  //-----------------------------------------------------------------------------------------------------------
        while(P!=NULL)        //Une boucle qui sert à copier le texte choisi dans notre structure Info
              {
                  Q=malloc(sizeof(Info));  //On alloue dynamiquement le maillon
                  Q->sui=NULL;
                  if (te==NULL)       //On cree la tete de la nouvelle liste
                  te=Q;
                  else if(S!=NULL)
                  S->sui=Q;
                  Q->couleur=15;    //On initialise tous les mots du texte à blanc (n°15)
                  strcpy(Q->mo,Valeur(P)); //On copie le mot
                  S=Q;
                  S->sui=NULL;
                  P=Suivant(P);
              }
//------------------------------------------------------------------------------------------------------------
printf("Combien de mots voulez vous rechercher ? ");
      scanf("%d",&nb);                //ON récupère le nombre de mots à rechercher
      int y;
      for (i=0;i<nb;i++)
      {
          Q=te;      //On se positionne dans la tete
          rand();
          srand(time(NULL));
          clr = rand()% 14 ;   //On récupère un nombre aleatoire entre 1 et 14
          if (clr == 1) { clr++; }
          printf("le mot %d : ",i+1);
          color(clr,1);        /* On récupère le mot à rechercher
                                        avec la couleur représenté par le nombre choisi aleatoirement */
          scanf("%s",&chaine);
          color(15,1);   //On remmet la console à ses couleurs
          y = wherey();
          if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
          while (Q!=NULL)
          {
              if (!strcmp(Q->mo,chaine))   //On cherche le mot dans notre texte, et on lui donne la couleur choisi  aleatoirement
                  {
                      Q->couleur=clr;
                  }
                Q=Q->sui;
          }
      }

      Q=te;
      P=TeteMo(t);

      while(Q!=NULL)   //On parcourt la structure
      {
          color(Q->couleur,1); //on donne la couleur corrependante à chaque mot
          printf("%s ",Q->mo); //et on l'affiche
          if ((Suivant(P)!=NULL)&&(Nligne(P)!=Nligne(Suivant(P))))
              printf("\n");
          Q=Q->sui;
          P=Suivant(P);
          y = wherey();
          if (y > 20){ fflush(stdin); getchar(); ClearScreen(); gotoxy(0,7); }
      }
      color(15,1);  //ecriture blanche et fond noir !


      fflush(stdin);
      getchar();
      ClearScreen();
  }

  }
/***************************************************************************************/
  void Rech_Remp(texte *TETE)   /*Rôle : procédure qui recherche un mot lu , et le remplacer pzr un autre .*/
   {
       Mot *P;
       texte *Q;
       char old[255]={0} ,ne[255]={0};
       int trouv=0;

           Q=Choixtexte(TETE);        //On choisit le texte à manipuler
           if (Q == NULL){return 0;}
           else
           {

                   P=TeteMo(Q);     // On récupère la tete du texte choisi

                   trouv=0;

                   printf("Quel est le mot a remplacer  ? ");   // On récupere le mot à remplacer
                   scanf("%s",&old);
                   printf("Remplacer par : ");
                   scanf("%s",&ne);                     //On récupère avec quoi le remplacer


                   while (P!=NULL)         //On parcourt toute la LLC des mots
                       {
                           if (!strcmp(old,Valeur(P)))     //Si le mot est égale à celui recherché
                           {
                               Aff_Val(P,ne);              //On remplace le mot trouvé pour le nouveau
                               trouv=1;
                           }
                           P=Suivant(P);

                       }
                       if (!trouv)
                        printf("Le mot %s n'existe pas ! ",old);    // Si le mot introduit n'existe pas dans  le texte on affiche un simple message

            fflush(stdin);
            getchar();
            ClearScreen();
           }
}
/*****************************************************************************************/
void Reinitial_Lig_pos(Mot *S)  /*Rôle : Procédure qui réinitialise les coordonnée des mots du texte*/
{
    int ligne=1,i=1;
    Mot *P;
    P=S;   //On récupère la tete dans P

     while (P!=NULL)  //Avant qu'on atteint la fin de la liste :
         {
                if (Nligne(P)==ligne)
                {
                    Aff_Nligne(P,ligne);  //on adjuste le nombre de ligne
                    Aff_pos(P,i);   //On adjuste la postion
                    P=Suivant(P);  //On avance dans la liste
                    i++;  //on incrémente la position
                }
                 else   //Une autre ligne
                 {
                     i=1;  //On met le compteur à pos 1

                     ligne++;   //on incrémente le nombre de lignes
                 }

         }

}
/***********************************************************************************************************************/
void Insertion_Mots(texte *tete)   /* Rôle : procédure qui permet d'insérer un ou plusieurs mots à des positions données.*/

 {
     typedef struct MotPos      //La structure qui permet de sauvegarder les informations nécessaires sur les mots à insérer
     {
         char mot[255];
         int pos;
         int ligne;
     }MotPos;
//---------------------------------------------------------------------------
    MotPos *tab=NULL;
    Mot *P,*S,*SAU;
    texte *Q;
    int nbr,i,trouv,ligne;
    char Nomfichier[255]={0};
//---------------------------------------------------------------------------

  Q=Choixtexte(tete);   //On choisit le texte à manipuler
  if (Q == NULL){return 0; }

  else {
    printf("Combien de mots voulez vous inserer? ");  // on récupère le nombre du mots à insérer
    scanf("%d",&nbr);

    tab=malloc(nbr *sizeof(MotPos));  // On alloue dynamiquement l'éspace en mémoire pour la structure des données

    for (i=0;i<nbr;i++)
    {
        printf("Le mot a inserer : ");   //On récupère les mots à insérer et leurs coordonées
        scanf("%s",&tab[i].mot);
        printf("Dans la ligne : ");
        scanf("%d",&tab[i].ligne);
        printf("A la postion : ");
        scanf("%d",&tab[i].pos);

    }



/*LA BOUCLE PRINCIPALE : On parcourt le tableau des données */

     for (i=0;i<nbr;i++)
     {
        S=allouer();          /** On prépare le maillon qui contient le mot à insérer avec tout ses coordonnées **/
        Aff_Val(S,tab[i].mot);
        Aff_pos(S,tab[i].pos);
        Aff_Nligne(S,tab[i].ligne);
        Aff_Ponct(S, " ");
  //---------------------------------------------------------//
         trouv=0;  // On initialise la variable qui indique
         P=TeteMo(Q);   //On récupère la tete du txete choisi auparavant
         Reinitial_Lig_pos(P);  //Et on fait l'adjustement des nombre de lignes et de positions

         if ((tab[i].ligne ==1)&&(tab[i].pos==1))  // Cas particulier : Insertion au début
            {
                Aff_AdrD(S,P);    //Chainage  necéssaire entre le debut du texte et le nouveau maillon
                Aff_AdrG(P,S);
                Aff_AdrG(S,NULL);
                Aff_Tete(Q,S);   // Changement de la tete
                trouv=1;   //Insertion éffectué

             }
         else   //Cas général : Insertion au milieu
         {

            while ((P!=NULL)&&(Nligne(P)<=tab[i].ligne)&&(!trouv))     /*Tant que le nbr de lignes du maillon actuel est inférieur ou égale à la ligne recherchée
                                                                     ,et tant qu'on n'a ni trouvé la postion ni terminé la liste on fait ce que va suivre */
             {
                if ((Position(P)==tab[i].pos)&&(Nligne(P)==tab[i].ligne))  //Si on est dans la bonne position
                   {
                       trouv=1;
                                                                 //on fait le chainage nécéssaire
                       Aff_AdrG(S,Precedant(P));
                       Aff_AdrD(Precedant(P),S);
                       Aff_AdrD(S,P);
                       Aff_AdrG(P,S);
                   }
                   SAU=P;            //On sauvegarde toujours le pointeur P en cas au il s'annule
                   P=Suivant(P);    // on avance dans la liste
             }

             if((!trouv)&&(Nligne(SAU)==tab[i].ligne)&&(tab[i].pos >Position(SAU))&&(P!=NULL))    //On résumé , Si la ligne éxiste dans le texte mais la position est trés grande
             {

                     Aff_AdrD(SAU,S);
                     Aff_AdrG(S,SAU);    //On fait le chainage entre le maillon S qui contient le mot à insérer et le dernier maillon de la ligne
                     Aff_AdrD(S,P);
                     Aff_AdrG(P,S);
                     trouv=1;
             }

            if ((!trouv)&&(P==NULL)) //Si la position et la ligne sont les deux inéxistant

             {
                   Aff_AdrG(S,SAU);
                   Aff_AdrD(SAU,S);    //On fait le chainage à la fin du texte
                   Aff_AdrD(S,NULL);
             }
         }
     }

     P=TeteMo(Q);   //On récupère la tete du texte dans P
     Reinitial_Lig_pos(P);  //Et on fait l'adjustement des nombre de lignes et de positions

     Affichtexte(TeteMo(Q));

fflush(stdin);
getchar();
ClearScreen();
  }
 }
/******************************************************************************************************************/

void CreationStructLigne(Lignes tab[])  /*Rôle :Une procédure qui cré Une LLC pour chaque ligne lue à partir du fichier
                                           de travail de la procédure Insertion_Lignes*/
  {
      int i=0,pos=1,ligne=1;
      FILE *F=NULL;
      char mot[255]={0};
      Mot *P=NULL,*Q=NULL;

//-----------------------------------------------------------------------------------------

     F=fopen("fich.txt","r");   //On ouvre le fichier de travail qui contient les lignes à inserer

     if (F != NULL)  //Si il est ouvert :
        {
            do {
                        fseek(F,-2, SEEK_CUR);  //On se déplace dans le fichier de 2 positions vers l'arrière
                        fscanf(F, "%s",mot);  //On récupère le mot
                        P = allouer() ;  //On alloue P (ptr vers un maillon de type mot)
                        Aff_Val(P,mot);   //On affecte le mot dedans
                        Aff_Nligne(P, ligne); //On récuoère la ligne...
                        Aff_pos(P, pos);  //...et la position du mot
                        Aff_Ponct(P, " ");
                        Aff_AdrD(P,NULL) ;
                        Aff_AdrG(P,NULL);

                        if (tab[i].Debutligne != NULL)
                            {
                                Aff_AdrD(Q,P) ;      //On fait le chainage entre les mots de la meme ligne
                                Aff_AdrG(P,Q);
                             }

                        else
                        tab[i].Debutligne=P;  //On récupère la tete de chaque ligne

                        Q = P ;  //On récupère P dans Q

                        if (fgetc(F) == '\n')
                        {
                            Aff_AdrD(P,NULL);
                            tab[i].Finligne=P;

                            i++;
                            ligne++;
                            pos = 0;
                        }

                        pos++;
                    }
                while(fgetc(F)!= EOF);



    }else { printf("\n Fichier inexistant \n"); }


      fclose(F);

  }

/**********************************************************************************************/
void Insertion_Lignes(texte *tete)   /*Rôle :Une procédure qui effectue l'insertion d'une ou plusieurs ligens à des positions données */
   {

//-------------------------------------------------------------------------------------------------------------------------
       Lignes *tab=NULL;
       int nbr=0,i=0;
       texte *t=NULL;
       Mot *P;
       FILE *F;


       t=Choixtexte(tete);   //On choisit le texte à manipuler

       printf("Combien de lignes voulez vous inserer ? ");  //On demande le nombre de lignes à insérer
       scanf("%d",&nbr);
       rewind(stdin);
       tab = malloc(nbr*sizeof(Lignes));    //On alloue dynamiquement un tableau de Lignes (structure de données)

//-----------------------Récupèration des coordonnées de chaque ligne à insérer----------------------------------------------------------------------------------
     F=fopen("fich.txt","w");   //On ouvre un fichier de travail, et on sauvegarde dedans les lignes à insérer

       for (i=0;i<nbr;i++)

           {
               printf("Quelle est la ligne a inserer ");
               gets(tab[i].phrase);          //On récupère la ligne à insérer à partir du clavier
               fprintf(F,"%s\n",tab[i].phrase); //On sauvegarde cette ligne dans notre fichier de travail
               printf("A la postion : ");
               scanf("%d",&tab[i].pos);   //On récupère la position ou on doit insérer la ligne
               rewind(stdin);
           }

      rewind(F);  //on revient au dèbut de fichier

    fclose(F);   //on ferme le fichier de travail
//----------------------------------------------------------------------------------------------------------
           for(i=0;i<nbr;i++)  //on initialise les poiteurs de la structure à NULL
           {
               tab[i].Debutligne=NULL;
               tab[i].Finligne=NULL;
            }

   CreationStructLigne(tab); //On remplit les champs Debutligne et finligne de chaque ligne

/* La boucle principale :Insertion de lignes à leurs positions */

            i=0;
            P=TeteMo(t);   //On récupère la tete du texte choisi

         while((P!=NULL)&&(i<nbr))  //Tant qu'on a pas inséré toutes les lignes et le texte n'est pas terminé :
         {

             P=TeteMo(t);   //On récupère la tete du texte .
            Reinitial_Ligne(P);  //on met à jour les coordonnées des mots du texte

            if(tab[i].pos==1)  //Si on doit insérer cette ligne au début
              {
                  Aff_AdrD(tab[i].Finligne,P);   //On fait le chainage nécéssaire
                  Aff_AdrG(P,tab[i].Finligne);
                  Aff_Tete(t,tab[i].Debutligne);  // et on change la tete
              }

            else
             {
                 while((Suivant(P)!=NULL)&&(Nligne(P)!=tab[i].pos))  //Tant qu'on est pas à la bonne position
                 {
                     P=Suivant(P);
                 }
                    if (Suivant(P)!=NULL)    //cad, si la position est au milieu
                    {
                            Aff_AdrD(Precedant(P),tab[i].Debutligne);  //On fait le chainage avec le début de la ligne à insérer...
                            Aff_AdrG(tab[i].Debutligne,Precedant(P));
                            Aff_AdrD(tab[i].Finligne,P);    //...Puis avec sa fin .
                            Aff_AdrG(P,tab[i].Finligne);
                     }
                     else   //Si la posititon est à la fin ou n'existe pas
                     {
                         Aff_AdrD(P,tab[i].Debutligne);    //On insère la ligne à la fin du texte
                         Aff_AdrG(tab[i].Debutligne,P);
                     }
             }
             i++;

         }

         P=TeteMo(t);
         Reinitial_Ligne(P);   //On réctifie  le nombre de lignes aprés les insertions effectués

unlink("fich.txt");
fflush(stdin);
getchar();
ClearScreen();
}
/**************************************************************************************************************************/
void Supp_Mot(texte *tete)   /* Rôle : Supprime un mot ainsi que toute ses occurences. */
  {
      texte *t;
      Mot *P;
      int trouv=0;
      char old[255];
      t=Choixtexte(tete);
      P=TeteMo(t);

                   printf("Quel est le mot a supprimer  ? ");
                   scanf("%s",&old);

                   while (P!=NULL)
                       {

                           if (!strcmp(old,Valeur(P)))
                           {
                               if ((Nligne(P)==1)&&(Position(P)==1))
                               {
                                   Aff_Tete(t,Suivant(P));
                                   trouv=1;
                               }

                               else if(Suivant(P)!=NULL)
                                {
                                   Aff_AdrD(Precedant(P),Suivant(P));
                                   Aff_AdrG(Suivant(P),Precedant(P));
                                   trouv=1;
                                   free(P);
                                }
                                else
                                {
                                    Aff_AdrD(Precedant(P),NULL);
                                    free(P);
                                }
                           }
                           P=Suivant(P);

                       }
                       if (!trouv)
                        printf("Le mot %s n'existe pas ! ",old);
            P=TeteMo(t);
            Reinitial_Lig_pos(P);
fflush(stdin);
getchar();
ClearScreen();

  }

/************************************************************************************************/
void Supp_Pos(texte *tete) /* Rôle : Supprime un mot donné par sa position et sa ligne. */

{
    typedef struct MotSup MotSup ;
    struct MotSup
    {
        int ligne;
        int pos;
    };

    MotSup *t=NULL;
    int nbr,i,trouv,ligne;
    Mot *P;
    texte  *S;
    S=Choixtexte(tete);
    printf("Combien de mots voulez vous supprimer ? ");
    scanf("%d",&nbr);
        t=malloc(nbr*sizeof(MotSup));
        for(i=0;i<nbr;i++)
        {
            printf("le mot qui se trouve dans la ligne : ");
            scanf("%d",&t[i].ligne);
            printf("Et a la position : ");
            scanf("%d",&t[i].pos);
        }
        for(i=0;i<nbr;i++)
        {
            P=TeteMo(S);
            trouv=0;
            if((t[i].ligne==1)&&(t[i].pos==1))
            {
                Aff_Tete(S,Suivant(P));
                trouv=1;
            }
            else
            {
                while ((P!=NULL)&&(!trouv))
                {
                    if((Position(P)==t[i].pos)&&(Nligne(P)==t[i].ligne))
                    {
                        if (Suivant(P)!=NULL)
                        {
                        Aff_AdrD(Precedant(P),Suivant(P));
                        Aff_AdrG(Suivant(P),Precedant(P));
                        free(P);

                        }
                        else
                        {
                            Aff_AdrD(Precedant(P),NULL);
                            free(P);
                        }
                        trouv=1;
                    }
                    P=Suivant(P);

                }
                if(!trouv)
                    printf("la position n'existe pas ! ");

            }

        }
    P=TeteMo(S);
    Reinitial_Lig_pos(P);
fflush(stdin);
getchar();
ClearScreen();
}
/*********************************************************************************************************************/
 void Reinitial_Ligne(Mot *P)  /*Rôle :Une procédure qui réinitialise le nombre de lignes en fonction des positions */
   {
        int ligne=1,pos=1;

           while (P!=NULL)
           {
               if (Position(P)>=pos)  //Si on est toujours dans la même ligne :
               {
                   Aff_Nligne(P,ligne);  //On affecte le nombre de la ligne au maillon
                   pos++;  //On incrémente la position
               }
               else  //Si on a changé la ligne
                {
                    pos=1;  //On met la position à 1
                    ligne++;  //On incrémente le nombre de lignes
                    Aff_Nligne(P,ligne);  //On affecte ce nombre au  premier maillon de ligne
                 }
               P=Suivant(P);
            }
   }

/***************************************************************************************************************************/
void Supp_lignes(texte *tete) /* Rôle : Supprime plusieurs lignes du texte. */
 {
     int *t=NULL,nbr,i,trouv,ligne;
     texte *S=NULL;
     Mot *P,*Q,*te;
     S=Choixtexte(tete);
     printf("Combien de lignes voulez vous supprimer ? ");
     scanf("%d",&nbr);
     t=malloc(nbr*sizeof(int));

     printf("Quelles sont les lignes a supprimer ? \n");
     for(i=0;i<nbr;i++)
     {
         printf("La ligne %d : ",i+1);
         scanf("%d",&t[i]);
     }

     P=TeteMo(S);
    for(i=0;i<nbr;i++)
             {
                 trouv=0;
                    while ((t[i]!=Nligne(P))&&(Suivant(P)!=NULL))
                         {
                             P=Suivant(P);
                         }
                         Q=Precedant(P);
                         te=P;
                   while ((t[i]==Nligne(P))&&(Suivant(P)!=NULL))
                      {
                        free(P);
                        P=Suivant(P);
                      }

                      if (te==TeteMo(S))
                      {
                          trouv=1;             // 1ere ligne
                          Aff_Tete(S,P);
                      }

                      else if (Suivant(P)!=NULL)
                        {
                            trouv=1;
                            Aff_AdrD(Q,P);      //milieu
                            Aff_AdrG(P,Q);
                        }
                        else
                        {
                             Aff_AdrD(Q,NULL);//derniere ligne
                             trouv=1;
                        }

                if (!trouv)
                    printf("cette ligne n'existe pas ! (n°%d)",t[i]);

            }
            P=TeteMo(S);
            Reinitial_Ligne(P);
fflush(stdin);
getchar();
ClearScreen();
}

