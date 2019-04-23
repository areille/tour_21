#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_PAQUET_COMPLET 52

typedef struct une_carte *Carte;
/*
* Définit une carte à jouer par sa valeur (de 1 à 13) et par son signe (pique, trèfle, coeur, carreau)
*/
struct une_carte
{
    int valeur;
    char *signe;
};

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

Carte *construirePaquet()
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

void afficherPaquet(Carte *paquet, int taille_paquet)
{
    for (int i = 0; i < taille_paquet; i++)
    {
        afficherCarte(paquet[i]);
    }
}

void detruireCarte(Carte carte)
{
    if (carte != NULL)
    {
        free(carte->signe);
        free(carte);
    }
}

void detruirePaquet(Carte *paquet)
{
    if (paquet != NULL)
    {
        for (int i = 0; i < TAILLE_PAQUET_COMPLET; i++)
        {
            detruireCarte(*(paquet + i));
        }
        free(paquet);
    }
}

int main()
{
    Carte *paquetComplet = construirePaquet();
    afficherPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);
    detruirePaquet(paquetComplet);
}