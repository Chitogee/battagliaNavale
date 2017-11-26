#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h> //sleep

#define righe 10
#define colonne 10
#define slotVuoto '-'
#define slotPieno '@'
#define slotCoperto '#'
#define slotAffondato 'O'
#define Mancato 'X'
#define maxGiocatori 2
#define totNavi 20

void mappa (char matrix [righe][colonne][maxGiocatori], int giocatore, char matrixCoperta [righe][colonne][maxGiocatori], int fase);
void deployNavi (char tipoNave [], int rNave, int cNave, int numNave, int maxNave, char matrix [righe][colonne][maxGiocatori], int giocatore, char matrixCoperta [righe][colonne][maxGiocatori], int fase); // prototipo funzione
void player (int giocatore);

void main()
{
    int i, j, k, controlloInput, giocatore, fase;
    int numRiga, numColonna, rNave, cNave, numNave, maxNave;
    char mat [righe][colonne][maxGiocatori], matCoperta [righe][colonne][maxGiocatori], colonna, tipoNave [15];

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            for(k = 0; k < maxGiocatori; k++)
            {
                mat[i][j][k] = slotVuoto;
                matCoperta[i][j][k] = slotCoperto;
            }
        }

    }
    fase = 0;
    for (i = 0; i < maxGiocatori; i++)
    {
        player (i);
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del portaerei", 1, 4, 1, 1, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del primo incrociatore", 1, 3, 1, 2, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del secondo incrociatore", 3, 1, 2, 2, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del primo torpediniere", 2, 1, 1, 3, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del secondo torpediniere", 1, 2, 2, 3, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del terzo torpediniere", 2, 1, 3, 3, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del primo sommergibile", 1, 1, 1, 4, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del secondo sommergibile", 1, 1, 2, 4, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del terzo sommergibile", 1, 1, 3, 4, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
        deployNavi ("del quarto sommergibile", 1, 1, 4, 4, mat, i, matCoperta, fase);
        system("cls");
        mappa (mat, i, matCoperta, fase);
    }
    fase = 1;
    deployNavi ("del quarto sommergibile", 1, 1, 4, 4, mat, i, matCoperta, fase);

}

void deployNavi (char tipoNave [], int rNave, int cNave, int numNave, int maxNave, char matrix [righe][colonne][maxGiocatori], int giocatore, char matrixCoperta [righe][colonne][maxGiocatori], int fase)
{

    int i, j, controlloInput, numRiga, numColonna, slotOccupato, contaNavi [1] = {0, 0};
    char colonna;

    switch (fase)
    {
    case 0:
        printf("\n\n    _______");
        for (i = 1; i < cNave; i++)
        {
            printf("______");
        }
        printf("\n    |     |");
        for (i = 1; i < cNave; i++)
        {
            printf("     |");
        }
        printf("\n    |  X  |");
        for (i = 1; i < cNave; i++)
        {
            printf("     |");
        }
        printf("\n    |_____|");
        for (i = 1; i < cNave; i++)
        {
            printf("_____|");
        }

        for (i = 1; i < rNave; i++)
        {
            printf("\n    |     |");
            printf("\n    |     |");
            printf("\n    |_____|");
        }
        printf("\n\n");
        do
        {
            printf("\n> Seleziona la riga in cui porre il punto 'X' %s (%d/%d)", tipoNave, numNave, maxNave);
            do
            {
                fflush(stdin);
                printf("\n> ");
                controlloInput = scanf("%d", &numRiga);
                if (controlloInput != 1 || numRiga < 1 || numRiga > 10)
                {
                    printf("[!] Errore, inserisci un valore valido\n");
                }
            }
            while (controlloInput != 1 || numRiga < 1 || numRiga > 10);
            numRiga--;

            printf("\n");
            printf("> Seleziona la colonna in cui porre %s", tipoNave);
            do
            {
                fflush(stdin);
                printf("\n> ");
                scanf("%c", &colonna);
                colonna = toupper(colonna);
                if (colonna != 'A' && colonna != 'B' && colonna != 'C' && colonna != 'D' && colonna != 'E' && colonna != 'F' && colonna != 'G' && colonna != 'H' && colonna != 'I' && colonna != 'J')
                {
                    printf("[!] Errore, inserisci un valore valido\n");
                }
            }
            while (colonna != 'A' && colonna != 'B' && colonna != 'C' && colonna != 'D' && colonna != 'E' && colonna != 'F' && colonna != 'G' && colonna != 'H' && colonna != 'I' && colonna != 'J');
            numColonna = colonna - 65; //Dato il valore 65 di A, sottraendo 65 si ha 0 = valore colonna matrix desiderato. B = 66; 66 - 65 = 1 colonna matrix

            slotOccupato = 0;

            for (i = 0; i < rNave; i++)
            {
                if (matrix [numRiga + i][numColonna][giocatore] == slotPieno)
                {
                    slotOccupato = 1;
                }
            }
            for (i = 1; i < cNave; i++)
            {
                if (matrix [numRiga][numColonna + i][giocatore] == slotPieno)
                {
                    slotOccupato = 1;
                }
            }
            if (slotOccupato == 1 || numRiga + rNave >= 11 || numColonna + cNave >= 11)
            {
                printf("\n[!] Errore, inserisci la nave in spazi validi\n\n");
            }
        }
        while (slotOccupato == 1 || numRiga + rNave >= 11 || numColonna + cNave >= 11);
        for (i = 0; i < rNave; i++)
        {
            matrix [numRiga + i][numColonna][giocatore] = slotPieno;
        }
        for (i = 1; i < cNave; i++)
        {
            matrix [numRiga][numColonna + i][giocatore] = slotPieno;
        }
        break;
    case 1:
        do
        {
            for (i = 1; i < maxGiocatori + 1; i++)
            {
                player (i);
                mappa(matrix, i, matrixCoperta, fase);
                printf("\n> Seleziona la riga da attaccare");
                do
                {
                    fflush(stdin);
                    printf("\n> ");
                    controlloInput = scanf("%d", &numRiga);
                    if (controlloInput != 1 || numRiga < 1 || numRiga > 10)
                    {
                        printf("[!] Errore, inserisci un valore valido\n");
                    }
                }
                while (controlloInput != 1 || numRiga < 1 || numRiga > 10);
                numRiga--;

                printf("\n");
                printf("> Seleziona la colonna da attaccare");
                do
                {
                    fflush(stdin);
                    printf("\n> ");
                    scanf("%c", &colonna);
                    colonna = toupper(colonna);
                    if (colonna != 'A' && colonna != 'B' && colonna != 'C' && colonna != 'D' && colonna != 'E' && colonna != 'F' && colonna != 'G' && colonna != 'H' && colonna != 'I' && colonna != 'J')
                    {
                        printf("[!] Errore, inserisci un valore valido\n");
                    }
                }
                while (colonna != 'A' && colonna != 'B' && colonna != 'C' && colonna != 'D' && colonna != 'E' && colonna != 'F' && colonna != 'G' && colonna != 'H' && colonna != 'I' && colonna != 'J');
                numColonna = colonna - 65;
                if (matrix [numRiga][numColonna][i] == '@')
                {
                    printf("\n\n> Hai colpito una nave nemica!");
                    matrixCoperta [numRiga][numColonna][i] = 'O';
                    contaNavi[i]++;
                }
                else
                {
                    printf("\n\n> Hai mancato il nemico");
                    matrixCoperta [numRiga][numColonna][i] = 'X';
                }
                Sleep(3000);
            }
        }
        while (contaNavi[0] < totNavi && contaNavi[1] < totNavi);
        if (contaNavi[0] > contaNavi[1])
        {
            printf("> Ha vinto il giocatore 1!");
        }
        else
        {
            printf("> Ha vinto il giocatore 2!");
        }
        break;
    }

}

void mappa (char matrix [righe][colonne][maxGiocatori], int giocatore, char matrixCoperta [righe][colonne][maxGiocatori], int fase)
{
    int i;

    if (fase == 0)
    {
        printf("\n       A     B     C     D     E     F     G     H     I     J\n");
        printf("    _____________________________________________________________\n");
        for (i = 0; i < 10; i++)
        {
            printf("    |     |     |     |     |     |     |     |     |     |     |\n");
            if (i < 9)
            {
                printf("  %d", i + 1);
            }
            else
            {
                printf(" %d", i + 1);
            }
            printf(" |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |\n", matrix [i][0][giocatore], matrix [i][1][giocatore], matrix [i][2][giocatore], matrix [i][3][giocatore], matrix [i][4][giocatore], matrix [i][5][giocatore], matrix [i][6][giocatore], matrix [i][7][giocatore], matrix [i][8][giocatore], matrix [i][9][giocatore]);
            printf("    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
        }
    }
    else
    {
        printf("\n       A     B     C     D     E     F     G     H     I     J\n");
        printf("    _____________________________________________________________\n");
        for (i = 0; i < 10; i++)
        {
            printf("    |     |     |     |     |     |     |     |     |     |     |\n");
            if (i < 9)
            {
                printf("  %d", i + 1);
            }
            else
            {
                printf(" %d", i + 1);
            }
            printf(" |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |\n", matrixCoperta [i][0][giocatore], matrixCoperta [i][1][giocatore], matrixCoperta [i][2][giocatore], matrixCoperta [i][3][giocatore], matrixCoperta [i][4][giocatore], matrixCoperta [i][5][giocatore], matrixCoperta [i][6][giocatore], matrixCoperta [i][7][giocatore], matrixCoperta [i][8][giocatore], matrixCoperta [i][9][giocatore]);
            printf("    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
        }
    }
}

void player (int giocatore)
{
    system("cls");
    if (giocatore == 1)
    {        printf("     _______ _________ _______  _______  _______ _________ _______  _______  _______      _______\n");
        printf("    (  ____ \\\\__   __/(  ___  )(  ____ \\(  ___  )\\__   __/(  ___  )(  ____ )(  ____ \\    /____   )\n");
        printf("    | (    \\/   ) (   | (   ) || (    \\/| (   ) |   ) (   | (   ) || (    )|| (    \\/    \\/   )   |\n");
        printf("    | |         | |   | |   | || |      | (___) |   | |   | |   | || (____)|| (__            /   )\n");
        printf("    | | ____    | |   | |   | || |      |  ___  |   | |   | |   | ||     __)|  __)         _/   /\n");
        printf("    | | \\_  )   | |   | |   | || |      | (   ) |   | |   | |   | || (\\ (   | (           /   _/\n");
        printf("    | (___) |___) (___| (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__| (____/\\    (   (__/\\\n");
        printf("    (_______)\\_______/(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/(_______/    \\_______/\n");

    }
    else
    {
        printf("     _______ _________ _______  _______  _______ _________ _______  _______  _______      ___\n");
        printf("    (  ____ \\\\__   __/(  ___  )(  ____ \\(  ___  )\\__   __/(  ___  )(  ____ )(  ____ \\    /   \\\n");
        printf("    | (    \\/   ) (   | (   ) || (    \\/| (   ) |   ) (   | (   ) || (    )|| (    \\/    \\/) )\n");
        printf("    | |         | |   | |   | || |      | (___) |   | |   | |   | || (____)|| (__          | |\n");
        printf("    | | ____    | |   | |   | || |      |  ___  |   | |   | |   | ||     __)|  __)         | |\n");
        printf("    | | \\_  )   | |   | |   | || |      | (   ) |   | |   | |   | || (\\ (   | (            | |\n");
        printf("    | (___) |___) (___| (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__| (____/\\    __) (_\n");
        printf("    (_______)\\_______/(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/(_______/    \\____/\n");
    }
    Sleep(3000);
    system("cls");
}


/*
       A     B     C     D     E     F     G     H     I     L
    _____________________________________________________________
    |     |     |     |     |     |     |     |     |     |     |
  1 |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
*/


