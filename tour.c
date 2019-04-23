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
    printf("%s de %s \n", carte->valeur, carte->signe);
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
    // Prendre un paquet de cartes
    Carte *paquetComplet = construirePaquetComplet();
    Carte *paquetTour = malloc((sizeof(struct une_carte) * TAILLE_PAQUET_TOUR) + 1);

    // Mélanger le paquet
    melangerPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Garder 21 cartes
    for (int i = 0; i < TAILLE_PAQUET_TOUR; i++)
        paquetTour[i] = construireCarte(paquetComplet[i]->valeur, paquetComplet[i]->signe);
    detruirePaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Faire choisir une carte au hasard
    printf("Choisir une carte parmi celles ci-dessous :\n");
    for (int j = 0; j < 21; j++)
    {
        if (strcmp(paquetTour[j]->signe, "♥") == 0 || strcmp(paquetTour[j]->signe, "♦") == 0)
            printf(ANSI_COLOR_RED "%5s de %1s" ANSI_COLOR_RESET "\n", paquetTour[j]->valeur, paquetTour[j]->signe);
        else
            printf(ANSI_COLOR_BLUE "%5s de %1s" ANSI_COLOR_RESET "\n", paquetTour[j]->valeur, paquetTour[j]->signe);
    }
    char checkEntree;
    printf("Appuie sur Entrée quand tu as choisi.\n");
    while (1)
    {
        checkEntree = fgetc(stdin);
        if (checkEntree == '\n')
            break;
        checkEntree = getchar();
    }
    printf("la suite\n");
    // ...
    detruirePaquet(paquetTour, TAILLE_PAQUET_TOUR);
}