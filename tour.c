#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_PAQUET_COMPLET 52

typedef struct une_carte *Carte;
struct une_carte
{
    int valeur;
    char signe[1];
};

Carte construireCarte(int valeur, char *signe)
{
    Carte carte = malloc(sizeof(struct une_carte));
    carte->valeur = valeur;
    strcpy(carte->signe, signe);
    return carte;
}

void afficherCarte(Carte carte)
{
    printf("%d de %s \n", carte->valeur, carte->signe);
}

Carte *construirePaquet()
{
    Carte *paquetComplet = malloc((sizeof(struct une_carte) * TAILLE_PAQUET_COMPLET) + 1);
    int signe;
    for (signe = 1; signe <= 4; signe++)
    {
        if (signe == 1)
        {
            for (int i = 0; i < 13; i++)
            {
                *(paquetComplet + i) = construireCarte(i + 1, "♠");
            }
        }
        if (signe == 2)
        {
            for (int i = 0; i < 13; i++)
            {
                *(paquetComplet + 13 + i) = construireCarte(i + 1, "♣");
            }
        }
        if (signe == 3)
        {
            for (int i = 0; i < 13; i++)
            {
                *(paquetComplet + 26 + i) = construireCarte(i + 1, "♥");
            }
        }
        if (signe == 4)
        {
            for (int i = 0; i < 13; i++)
            {
                *(paquetComplet + 39 + i) = construireCarte(i + 1, "♦");
            }
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

void detruirePaquet(Carte *paquet)
{
    free(paquet);
}

int main()
{
    Carte *paquetComplet = construirePaquet();
    afficherPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);
    detruirePaquet(paquetComplet);
}