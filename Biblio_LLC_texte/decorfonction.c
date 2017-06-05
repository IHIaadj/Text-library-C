


/** Ce .c regroupe toutes fonctions gerant les fonctionnalités de couleurs,
  * des fonctions utilisées dans cette bibliothèque.
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <unistd.h>
#include "Headers.h"


void color(int t,int f)/* Rôle : Change la couleur du texte ainsi que la couleur de fond de texte. */
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}
