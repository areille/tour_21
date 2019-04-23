#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TAILLE_PAQUET_COMPLET = 52;

struct Carte
{
    int valeur;
    char signe[1];
} carte_struct;

struct Carte construireCarte(int valeur, char *signe)
{
    struct Carte carte;
    carte.valeur = valeur;
    strcpy(carte.signe, signe);
    afficherCarte(&carte);
    return carte;
}

void afficherCarte(struct Carte *carte)
{
    printf("%d de %s \n", carte->valeur, carte->signe);
}

struct Carte *construirePaquet()
{
    struct Carte *paquetComplet = malloc(sizeof(carte_struct));
    int signe;
    for (signe = 1; signe <= 4; signe++)
    {
        if (signe == 1)
        {
            for (int i = 0; i < 13; i++)
            {
                paquetComplet[i] = construireCarte(i + 1, "♠");
                afficherCarte(&paquetComplet[i]);
            }
        }
        if (signe == 2)
        {
            for (int i = 0; i < 13; i++)
            {
                paquetComplet[13 + i] = construireCarte(i + 1, "♣");
            }
        }
        if (signe == 3)
        {
            for (int i = 0; i < 13; i++)
            {
                paquetComplet[26 + i] = construireCarte(i + 1, "♥");
            }
        }
        if (signe == 4)
        {
            for (int i = 0; i < 13; i++)
            {
                paquetComplet[39 + i] = construireCarte(i + 1, "♦");
            }
        }
    }
    return paquetComplet;
}

void afficherPaquet(struct Carte *paquet, int taille_paquet)
{
    for (int i = 0; i < taille_paquet; i++)
    {
        afficherCarte(&paquet[i]);
    }
}

void detruirePaquet(struct Carte *paquet)
{
    free(paquet);
}

int main()
{
    struct Carte *paquetComplet = construirePaquet();
    afficherPaquet(paquetComplet, TAILLE_PAQUET_COMPLET);
    detruirePaquet(paquetComplet);
}