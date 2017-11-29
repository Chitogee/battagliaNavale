#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define righe 10
#define colonne 10
#define slotVuoto '-'
#define slotPieno '@'
#define slotCoperto '#'
#define slotAffondato 'O'
#define slotMancato 'X'
#define numGiocatori 2
#define totNavi 20

void grafica(int imgASCII);
void mappaDeploy (int i, char matDeploy [][colonne][numGiocatori]);
void mappaCoperta (int i, char matCoperta [][colonne][numGiocatori]);
int deployNavi (int i, char descNave [], int rNave, int cNave, int ordineNave, int maxNave, char matDeploy [][colonne][numGiocatori], int sommaNavi);
int inputRiga ();
int inputColonna ();

int main()
{
    char matDeploy[righe][colonne][numGiocatori], matCoperta[righe][colonne][numGiocatori], sceltaRiavvia;
    int i, j, k, sommaNavi, contaNavi[2], numRiga, numColonna;

    do
    {
        sommaNavi = 0;
        contaNavi[0] = 0;
        contaNavi[1] = 0;
        for(i = 0; i < righe; i++)
        {
            for(j = 0; j < colonne; j++)
            {
                for(k = 0; k < numGiocatori; k++)
                {
                    matDeploy[i][j][k] = slotVuoto;
                    matCoperta[i][j][k] = slotCoperto;
                }
            }

        }
        grafica(10);

        for (i = 0; i < numGiocatori; i++)
        {
            system("cls");
            grafica(i);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi(i, "portaerei", 1, 4, 1, 1, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "primo incrociatore", 1, 3, 1, 2, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "secondo incrociatore", 3, 1, 2, 2, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "primo torpediniere", 2, 1, 1, 3, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "secondo torpediniere", 1, 2, 2, 3, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "terzo torpediniere", 2, 1, 3, 3, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "primo sommergibile", 1, 1, 1, 4, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "secondo sommergibile", 1, 1, 2, 4, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "terzo sommergibile", 1, 1, 3, 4, matDeploy, sommaNavi);
            mappaDeploy(i, matDeploy);
            sommaNavi = deployNavi (i, "quarto sommergibile", 1, 1, 4, 4, matDeploy, sommaNavi);
            system("cls");
        }
        sommaNavi /= 2;
        do
        {
            for (j = 1; j >= 0; j--)
            {
                grafica(!j);
                mappaCoperta (j, matCoperta);
                do
                {
                    printf("\n> Seleziona la riga da attaccare");
                    numRiga = inputRiga();

                    printf("\n> Seleziona la colonna da attaccare");
                    numColonna = inputColonna();

                    if (matCoperta [numRiga][numColonna][j] == slotAffondato || matCoperta [numRiga][numColonna][j] == slotMancato)
                    {
                        fflush(stdin);
                        printf("[!] Errore, non puoi colpire nuovamente questo slot\n");
                    }
                }
                while (matCoperta [numRiga][numColonna][j] == slotAffondato || matCoperta [numRiga][numColonna][j] == slotMancato);
                if (matDeploy [numRiga][numColonna][j] == slotPieno)
                {
                    printf("\n> Hai colpito una nave nemica!");
                    matCoperta [numRiga][numColonna][j] = slotAffondato;
                    contaNavi[j]++;
                }
                else
                {
                    printf("\n> Hai mancato il nemico");
                    matCoperta [numRiga][numColonna][j] = slotMancato;
                }
                Sleep(3000);
                system("cls");

            }
        }
        while (contaNavi[0] < sommaNavi && contaNavi[1] < sommaNavi);
        if (contaNavi[0] > contaNavi [1])
        {
            grafica(2);
            printf("> Ha vinto il giocatore 2!");
        }
        else
        {
            if (contaNavi[0] < contaNavi [1])
            {
                grafica(2);
                printf("\n\n> Ha vinto il giocatore 1!");
            }
            else
            {
                printf("\n\n> I giocatori hanno pareggiato!");
            }
        }
        Sleep(3000);
        printf("\n\n> Vuoi riavviare il programma? (S/N)");
        do
        {
            fflush(stdin);
            printf("\n> ");
            scanf("%c", &sceltaRiavvia);
            sceltaRiavvia = toupper(sceltaRiavvia);
            if (sceltaRiavvia != 'S' && sceltaRiavvia != 'N')
            {
                printf("[!] Errore, inserisci un valore valido\n");
            }

        }
        while (sceltaRiavvia != 'S' && sceltaRiavvia != 'N');
    }
    while (sceltaRiavvia != 'N');
    return 0;
}

int deployNavi (int i, char descNave [], int rNave, int cNave, int ordineNave, int maxNave, char matDeploy [][colonne][numGiocatori], int sommaNavi)
{

    int j, numRiga, numColonna, slotOccupato;

    printf("\n\n    _______");
    for (j = 1; j < cNave; j++)
    {
        printf("______");
    }
    printf("\n    |     |");
    for (j = 1; j < cNave; j++)
    {
        printf("     |");
    }
    printf("\n    |  X  |");
    for (j = 1; j < cNave; j++)
    {
        printf("     |");
    }
    printf("\n    |_____|");
    for (j = 1; j < cNave; j++)
    {
        printf("_____|");
    }

    for (j = 1; j < rNave; j++)
    {
        printf("\n    |     |");
        printf("\n    |     |");
        printf("\n    |_____|");
    }
    printf("\n\n");
    do
    {
        printf("\n> Seleziona la riga in cui porre il punto 'X' del %s (%d/%d)", descNave, ordineNave, maxNave);
        numRiga = inputRiga();
        printf("\n");
        printf("> Seleziona la colonna in cui porre il %s", descNave);
        numColonna = inputColonna();

        slotOccupato = 0;
        for (j = 0; j < rNave; j++)
        {
            if (matDeploy [numRiga + j][numColonna][i] == slotPieno)
            {
                slotOccupato = 1;
            }
        }
        for (j = 1; j < cNave; j++)
        {
            if (matDeploy [numRiga][numColonna + j][i] == slotPieno)
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
    for (j = 0; j < rNave; j++)
    {
        matDeploy [numRiga + j][numColonna][i] = slotPieno;
    }
    for (j = 1; j < cNave; j++)
    {
        matDeploy [numRiga][numColonna + j][i] = slotPieno;
    }
    sommaNavi += cNave * rNave;
    return sommaNavi;
}

int inputRiga ()
{
    int numRiga, controlloInput = 0;

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
    return numRiga;
}

int inputColonna ()
{
    char colonna;
    int numColonna;

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
    return numColonna;
}

void mappaDeploy (int i, char matDeploy [][colonne][numGiocatori])
{
    int j, k;

    system("cls");
    printf("\n       A     B     C     D     E     F     G     H     I     J\n");
    printf("    _____________________________________________________________\n");
    for (j = 0; j < righe; j++)
    {
        printf("    |     |     |     |     |     |     |     |     |     |     |\n");
        if (j < 9)
        {
            printf("  %d", j + 1);
        }
        else
        {
            printf(" %d", j + 1);
        }
        printf(" |  %c  |", matDeploy [j][0][i]);
        for (k = 1; k < colonne; k++)
        {
            printf("  %c  |", matDeploy [j][k][i]);
        }
        printf("\n    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    }
}

void mappaCoperta (int i, char matCoperta [][colonne][numGiocatori])
{
    int j, k;

    system("cls");
    printf("\n       A     B     C     D     E     F     G     H     I     J\n");
    printf("    _____________________________________________________________\n");
    for (j = 0; j < righe; j++)
    {
        printf("    |     |     |     |     |     |     |     |     |     |     |\n");
        if (j < 9)
        {
            printf("  %d", j + 1);
        }
        else
        {
            printf(" %d", j + 1);
        }
        printf(" |  %c  |", matCoperta [j][0][i]);
        for (k = 1; k < colonne; k++)
        {
            printf("  %c  |", matCoperta [j][k][i]);
        }
        printf("\n    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    }
}

void grafica(int imgASCII)
{
    fflush(stdin);
    switch (imgASCII)
    {
    case 10:
        printf("v2.31 - Falcone Federico - 27/11/2017");
        printf("\n\n                                             |__\n");
        printf("                                             |\\/\n");
        printf("                                             ---\n");
        printf("                                             / | [\n");
        printf("                                      !      | |||\n");
        printf("                                    _/|     _/|-++'\n");
        printf("                                +  +--|    |--|--|_ |-\n");
        printf("                             { /|__|  |/\\__|  |--- |||__/\n");
        printf("                            +---------------___[}-_===_.'____                 /\\\n");
        printf("                        ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _\n");
        printf("         __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7\n");
        printf("        |                                                                     BB-61/\n");
        printf("         \\_________________________________________________________________________|\n\n");
        printf("\n\n     ______   _______ __________________ _        _______  _______          _________ _______\n");
        printf("    (  ___ \\ (  ___  )\\__   __/\\__   __/( \\      (  ____ \\(  ____ \\|\\     /|\\__   __/(  ____ )\n");
        printf("    | (   ) )| (   ) |   ) (      ) (   | (      | (    \\/| (    \\/| )   ( |   ) (   | (    )|\n");
        printf("    | (__/ / | (___) |   | |      | |   | |      | (__    | (_____ | (___) |   | |   | (____)|\n");
        printf("    |  __ (  |  ___  |   | |      | |   | |      |  __)   (_____  )|  ___  |   | |   |  _____)\n");
        printf("    | (  \\ \\ | (   ) |   | |      | |   | |      | (            ) || (   ) |   | |   | ( \n");
        printf("    | )___) )| )   ( |   | |      | |   | (____/\\| (____/\\/\\____) || )   ( |___) (___| )\n");
        printf("    |/ \\___/ |/     \\|   )_(      )_(   (_______/(_______/\\_______)|/     \\|\\_______/|/\n\n\n");
        printf("                                 Premi invio per continuare\n");
        getchar();
        system("cls");
        break;
    case 0:
        printf("     _______ _________ _______  _______  _______ _________ _______  _______  _______      ___\n");
        printf("    (  ____ \\\\__   __/(  ___  )(  ____ \\(  ___  )\\__   __/(  ___  )(  ____ )(  ____ \\    /   \\\n");
        printf("    | (    \\/   ) (   | (   ) || (    \\/| (   ) |   ) (   | (   ) || (    )|| (    \\/    \\/) )\n");
        printf("    | |         | |   | |   | || |      | (___) |   | |   | |   | || (____)|| (__          | |\n");
        printf("    | | ____    | |   | |   | || |      |  ___  |   | |   | |   | ||     __)|  __)         | |\n");
        printf("    | | \\_  )   | |   | |   | || |      | (   ) |   | |   | |   | || (\\ (   | (            | |\n");
        printf("    | (___) |___) (___| (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__| (____/\\    __) (_\n");
        printf("    (_______)\\_______/(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/(_______/    \\____/\n");
        Sleep(3000);
        system("cls");
        break;
    case 1:
        printf("     _______ _________ _______  _______  _______ _________ _______  _______  _______      _______\n");
        printf("    (  ____ \\\\__   __/(  ___  )(  ____ \\(  ___  )\\__   __/(  ___  )(  ____ )(  ____ \\    /____   )\n");
        printf("    | (    \\/   ) (   | (   ) || (    \\/| (   ) |   ) (   | (   ) || (    )|| (    \\/    \\/   )   |\n");
        printf("    | |         | |   | |   | || |      | (___) |   | |   | |   | || (____)|| (__            /   )\n");
        printf("    | | ____    | |   | |   | || |      |  ___  |   | |   | |   | ||     __)|  __)         _/   /\n");
        printf("    | | \\_  )   | |   | |   | || |      | (   ) |   | |   | |   | || (\\ (   | (           /   _/\n");
        printf("    | (___) |___) (___| (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__| (____/\\    (   (__/\\\n");
        printf("    (_______)\\_______/(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/(_______/    \\_______/\n");
        Sleep(3000);
        system("cls");
    case 2:
        printf("       .-=========-.   \n");
        printf("       \\'-=======-'/  \n");
        printf("       _|   .=.   |_   \n");
        printf("      ((|  {{1}}  |))  \n");
        printf("       \\|   /|\\   |/ \n");
        printf("        \\__ '`' __/   \n");
        printf("          _`) (`_      \n");
        printf("        _/_______\\_   \n");
        printf("       /___________\\  \n");
        break;
    }
}

