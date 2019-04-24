#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_PAQUET_COMPLET 52
#define TAILLE_PAQUET_TOUR 21
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct une_carte *Carte;
/*
* Définit une carte à jouer par sa valeur (de 1 à 13) et par son signe (pique, trèfle, coeur, carreau)
*/
struct une_carte
{
    char *valeur;
    char *signe;
};

/*
* Construit dynamiquement une carte à partir d'une valeur et d'un signe.
*/
Carte construireCarte(char *valeur, char *signe)
{
    Carte carte = malloc(sizeof(struct une_carte));
    carte->valeur = (char *)malloc((sizeof(char)) * (strlen(valeur) + 1));
    carte->signe = (char *)malloc((sizeof(char)) * (strlen(signe) + 1));
    if (carte->valeur == NULL || carte->signe == NULL)
    {
        perror("Allocation memoire");
        exit(1);
    }
    strncpy(carte->valeur, valeur, strlen(valeur) + 1);
    strncpy(carte->signe, signe, strlen(signe) + 1);
    return carte;
}

void afficherCarte(Carte carte)
{
    if (strcmp(carte->signe, "♥") == 0 || strcmp(carte->signe, "♦") == 0)
        printf(ANSI_COLOR_RED "%5s de %1s" ANSI_COLOR_RESET "\n", carte->valeur, carte->signe);
    else
        printf(ANSI_COLOR_BLUE "%5s de %1s" ANSI_COLOR_RESET "\n", carte->valeur, carte->signe);
}

void detruireCarte(Carte carte)
{
    if (carte != NULL)
    {
        free(carte->valeur);
        free(carte->signe);
        free(carte);
    }
}

char *retourneValeur(int valeurIndex)
{
    char *str = malloc(sizeof(char) * 2);
    switch (valeurIndex)
    {
    case 1:
        return "As";
    case 11:
        return "Valet";
    case 12:
        return "Dame";
    case 13:
        return "Roi";
    default:
        sprintf(str, "%d", valeurIndex);
        return str;
    }
}

char *retourneSigne(int signeIndex)
{
    switch (signeIndex)
    {
    case 0:
        return "♠";
        break;
    case 1:
        return "♣";
        break;
    case 2:
        return "♥";
        break;
    case 3:
        return "♦";
        break;
    default:
        break;
    }
}

Carte *construirePaquetComplet()
{
    Carte *paquetComplet = malloc((sizeof(struct une_carte) * TAILLE_PAQUET_COMPLET) + 1);
    int signeIndex;
    int NB_CARTES_PAR_SIGNE = TAILLE_PAQUET_COMPLET / 4;
    for (signeIndex = 0; signeIndex < 4; signeIndex++)
    {
        char *signe;
        signe = retourneSigne(signeIndex);
        for (int i = 0; i < NB_CARTES_PAR_SIGNE; i++)
        {
            char *valeur;
            valeur = retourneValeur(i + 1);
            *(paquetComplet + (signeIndex * NB_CARTES_PAR_SIGNE) + i) = construireCarte(valeur, signe);
        }
    }
    return paquetComplet;
}

static int nombreAleatoire(int maximum)
{
    srand(time(NULL)); // Réinitialise rand()
    int limite = RAND_MAX - RAND_MAX % maximum;
    int aleatoire;
    do
        aleatoire = rand();
    while (aleatoire >= limite);
    return aleatoire % maximum;
}

// Basé sur l'algorithme de fisher-yates
void melangerPaquet(Carte *paquet, int taille_paquet)
{
    int i, j;
    Carte temp;
    for (i = taille_paquet - 1; i > 0; i--)
    {
        j = nombreAleatoire(i + 1);
        temp = paquet[j];
        paquet[j] = paquet[i];
        paquet[i] = temp;
    }
}

void afficherPaquet(Carte *paquet, int taille_paquet)
{
    for (int i = 0; i < taille_paquet; i++)
        afficherCarte(paquet[i]);
}

void detruirePaquet(Carte *paquet, int taille_paquet)
{
    if (paquet != NULL)
    {
        for (int i = 0; i < taille_paquet; i++)
            detruireCarte(*(paquet + i));
        free(paquet);
    }
}

int main()
{
    int numeroPaquet, i;
    // Prendre un paquet de cartes
    Carte *paquetComplet = construirePaquetComplet();
    Carte *paquetTour = malloc((sizeof(struct une_carte) * TAILLE_PAQUET_TOUR) + 1);
    Carte petitsPaquets[3][7];

    // Mélanger le paquet
    melangerPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Garder 21 cartes
    for (i = 0; i < TAILLE_PAQUET_TOUR; i++)
        paquetTour[i] = construireCarte(paquetComplet[i]->valeur, paquetComplet[i]->signe);
    detruirePaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Faire choisir une carte au hasard
    printf("Choisir une carte parmi celles ci-dessous :\n");
    afficherPaquet(paquetTour, TAILLE_PAQUET_TOUR);
    char checkEntree;
    printf("Appuie sur Entrée quand tu as choisi.\n");
    while (1)
    {
        checkEntree = fgetc(stdin);
        if (checkEntree == '\n')
            break;
        checkEntree = getchar();
    }

    // Faire 3 paquets

    for (i = 0; i < TAILLE_PAQUET_TOUR / 3; i++)
    {
        petitsPaquets[0][i] = paquetTour[3 * i];
        petitsPaquets[1][i] = paquetTour[3 * i + 1];
        petitsPaquets[2][i] = paquetTour[3 * i + 2];
    }
    printf("Paquet 1 :\n");
    afficherPaquet(petitsPaquets[0], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 2 :\n");
    afficherPaquet(petitsPaquets[1], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 3 :\n");
    afficherPaquet(petitsPaquets[2], TAILLE_PAQUET_TOUR / 3);
    printf("\n");

    printf("Dans quel paquet se trouve ta carte?\n");
    scanf("%d", &numeroPaquet);
    if (numeroPaquet < 1 || numeroPaquet > 3)
        printf("Valeur invalide.");
    else
    {
        if (numeroPaquet != 2)
        {
            Carte tmp[7];
            for (i = 0; i < 7; i++)
            {
                tmp[i] = petitsPaquets[1][i];
                petitsPaquets[1][i] = petitsPaquets[numeroPaquet - 1][i];
                petitsPaquets[numeroPaquet - 1][i] = tmp[i];
            }
        }
    }

    for (i = 0; i < TAILLE_PAQUET_TOUR; i++)
    {
        paquetTour[i] = petitsPaquets[TAILLE_PAQUET_TOUR % 7][i];
    }

    // Re Faire 3 paquets

    for (i = 0; i < TAILLE_PAQUET_TOUR / 3; i++)
    {
        petitsPaquets[0][i] = paquetTour[3 * i];
        petitsPaquets[1][i] = paquetTour[3 * i + 1];
        petitsPaquets[2][i] = paquetTour[3 * i + 2];
    }
    printf("Paquet 1 :\n");
    afficherPaquet(petitsPaquets[0], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 2 :\n");
    afficherPaquet(petitsPaquets[1], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 3 :\n");
    afficherPaquet(petitsPaquets[2], TAILLE_PAQUET_TOUR / 3);
    printf("\n");

    printf("Dans quel paquet se trouve ta carte?\n");
    scanf("%d", &numeroPaquet);
    if (numeroPaquet < 1 || numeroPaquet > 3)
        printf("Valeur invalide.");
    else
    {
        if (numeroPaquet != 2)
        {
            Carte tmp[7];
            for (i = 0; i < 7; i++)
            {
                tmp[i] = petitsPaquets[1][i];
                petitsPaquets[1][i] = petitsPaquets[numeroPaquet - 1][i];
                petitsPaquets[numeroPaquet - 1][i] = tmp[i];
            }
        }
    }

    for (i = 0; i < TAILLE_PAQUET_TOUR; i++)
    {
        paquetTour[i] = petitsPaquets[TAILLE_PAQUET_TOUR % 7][i];
    }

    // Re Re Faire 3 paquets

    for (i = 0; i < TAILLE_PAQUET_TOUR / 3; i++)
    {
        petitsPaquets[0][i] = paquetTour[3 * i];
        petitsPaquets[1][i] = paquetTour[3 * i + 1];
        petitsPaquets[2][i] = paquetTour[3 * i + 2];
    }
    printf("Paquet 1 :\n");
    afficherPaquet(petitsPaquets[0], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 2 :\n");
    afficherPaquet(petitsPaquets[1], TAILLE_PAQUET_TOUR / 3);
    printf("\n");
    printf("Paquet 3 :\n");
    afficherPaquet(petitsPaquets[2], TAILLE_PAQUET_TOUR / 3);
    printf("\n");

    printf("Dans quel paquet se trouve ta carte?\n");
    scanf("%d", &numeroPaquet);
    if (numeroPaquet < 1 || numeroPaquet > 3)
        printf("Valeur invalide.");
    else
    {
        if (numeroPaquet != 2)
        {
            Carte tmp[7];
            for (i = 0; i < 7; i++)
            {
                tmp[i] = petitsPaquets[1][i];
                petitsPaquets[1][i] = petitsPaquets[numeroPaquet - 1][i];
                petitsPaquets[numeroPaquet - 1][i] = tmp[i];
            }
        }
    }

    for (i = 0; i < TAILLE_PAQUET_TOUR; i++)
    {
        paquetTour[i] = petitsPaquets[TAILLE_PAQUET_TOUR % 7][i];
    }

    printf("Ta carte est ...\n");
    afficherCarte(paquetTour[10]);

    // ...
    detruirePaquet(paquetTour, TAILLE_PAQUET_TOUR);
}