#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_PAQUET_COMPLET 52
#define TAILLE_PAQUET_TOUR 21

typedef struct une_carte *Carte;
/*
* Définit une carte à jouer par sa valeur (de 1 à 13) et par son signe (pique, trèfle, coeur, carreau)
*/
struct une_carte
{
    int valeur;
    char *signe;
};

/*
* Construit dynamiquement une carte à partir d'une valeur et d'un signe.
*/
Carte construireCarte(int valeur, char *signe)
{
    Carte carte = malloc(sizeof(struct une_carte));
    carte->signe = (char *)malloc((sizeof(char)) * (strlen(signe) + 1));
    if (carte->signe == NULL)
    {
        perror("Allocation memoire");
        exit(1);
    }
    carte->valeur = valeur;
    strncpy(carte->signe, signe, strlen(signe) + 1);
    return carte;
}

void afficherCarte(Carte carte)
{
    printf("%d de %s \n", carte->valeur, carte->signe);
}

void detruireCarte(Carte carte)
{
    if (carte != NULL)
    {
        free(carte->signe);
        free(carte);
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
            *(paquetComplet + (signeIndex * NB_CARTES_PAR_SIGNE) + i) = construireCarte(i + 1, signe);
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
    {
        aleatoire = rand();
    } while (aleatoire >= limite);
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
    {
        afficherCarte(paquet[i]);
    }
}

void detruirePaquet(Carte *paquet, int taille_paquet)
{
    if (paquet != NULL)
    {
        for (int i = 0; i < taille_paquet; i++)
        {
            detruireCarte(*(paquet + i));
        }
        free(paquet);
    }
}

int main()
{
    // Prendre un paquet de cartes
    Carte *paquetComplet = construirePaquetComplet();
    Carte *paquetTour = malloc((sizeof(struct une_carte) * TAILLE_PAQUET_TOUR) + 1);
    Carte carteChoisie;
    // printf("PAQUET COMPLET :\n");
    // afficherPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Mélanger le paquet
    melangerPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);
    // printf("PAQUET MÉLANGÉ :\n");
    // afficherPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Garder 21 cartes
    for (int i = 0; i < TAILLE_PAQUET_TOUR; i++)
    {
        paquetTour[i] = construireCarte(paquetComplet[i]->valeur, paquetComplet[i]->signe);
    }
    // printf("PAQUET DU TOUR :\n");
    // afficherPaquet(paquetTour, TAILLE_PAQUET_TOUR);
    detruirePaquet(paquetComplet, TAILLE_PAQUET_COMPLET);

    // Faire choisir une carte au hasard
    printf("Choisir une carte parmi celles ci-dessous :\n");
    for (int j = 0; j < 7; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            int index = 7 * k + j;
            printf("[%-2d] : %2d de %1s        ", index + 1, paquetTour[index]->valeur, paquetTour[index]->signe);
        }
        printf("\n");
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