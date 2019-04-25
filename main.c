#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Carte
{
    char valeur[8]; // As, 2, ... , dame, roi
    char signe[8];  // Pique, trèfle, coeur, carreau
};

void afficherCarte(struct Carte carte)
{
    printf("%s de %s\n", carte.valeur, carte.signe);
}

void afficherPaquet(struct Carte *paquet, int taillePaquet)
{
    for (int i = 0; i < taillePaquet; i++)
        afficherCarte(paquet[i]);
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
void melangerPaquet(struct Carte *paquet, int taille_paquet)
{
    int i, j;
    struct Carte temp;
    for (i = taille_paquet - 1; i > 0; i--)
    {
        j = nombreAleatoire(i + 1);
        temp = paquet[j];
        paquet[j] = paquet[i];
        paquet[i] = temp;
    }
}

int main()
{
    int i, j, k, numeroPaquet;
    struct Carte paquetTour[21];
    struct Carte petitsPaquets[3][7];

    // Construction d'un paquet de 52 cartes
    struct Carte paquetComplet[52];
    for (i = 0; i < 4; i++)
    {
        char signe[8];
        switch (i)
        {
        case 0:
            strcpy(signe, "pique");
            break;
        case 1:
            strcpy(signe, "trèfle");
            break;
        case 2:
            strcpy(signe, "carreau");
            break;
        case 3:
            strcpy(signe, "coeur");
            break;
        default:
            break;
        }
        for (j = 0; j < 13; j++) // 52 cartes / 4 signes = 13 valeurs
        {
            strcpy(paquetComplet[i * 13 + j].signe, signe);
            switch (j)
            {
            case 0:
                strcpy(paquetComplet[i * 13 + j].valeur, "As");
                break;
            case 10:
                strcpy(paquetComplet[i * 13 + j].valeur, "Valet");
                break;
            case 11:
                strcpy(paquetComplet[i * 13 + j].valeur, "Dame");
                break;
            case 12:
                strcpy(paquetComplet[i * 13 + j].valeur, "Roi");
                break;
            default:
                sprintf(paquetComplet[i * 13 + j].valeur, "%d", j);
                break;
            }
        }
    }

    // Mélanger le paquet
    melangerPaquet(paquetComplet, 52);

    // Garder 21 cartes
    for (i = 0; i < 21; i++)
    {
        strcpy(paquetTour[i].signe, paquetComplet[i].signe);
        strcpy(paquetTour[i].valeur, paquetComplet[i].valeur);
    }

    printf("Choisir une carte et la retenir :\n");

    afficherPaquet(paquetTour, 21);

    printf("\nAppuyer sur Entree une fois que vous avez choisi\n");
    getchar();

    // Faire 3 paquets, 3 fois
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            // on distribue dans chaque petit paquet
            petitsPaquets[0][j] = paquetTour[3 * j];
            petitsPaquets[1][j] = paquetTour[3 * j + 1];
            petitsPaquets[2][j] = paquetTour[3 * j + 2];
        }
        printf("Paquet 1 :\n");
        afficherPaquet(petitsPaquets[0], 7);
        printf("\n");
        printf("Paquet 2 :\n");
        afficherPaquet(petitsPaquets[1], 7);
        printf("\n");
        printf("Paquet 3 :\n");
        afficherPaquet(petitsPaquets[2], 7);
        printf("\n");

        printf("Dans quel paquet se trouve ta carte?\n");
        scanf("%d", &numeroPaquet);
        if (numeroPaquet < 1 || numeroPaquet > 3)
        {
            printf("Valeur invalide.\n");
            exit(-1);
        }
        else
        {
            // Déplacer le paquet choisi entre les deux autres
            // Si le paquet est déjà entre les deux autres, pas besoin de le déplacer
            if (numeroPaquet != 2)
            {
                struct Carte tmp[7];
                for (j = 0; j < 7; j++)
                {
                    tmp[j] = petitsPaquets[1][j];
                    petitsPaquets[1][j] = petitsPaquets[numeroPaquet - 1][j];
                    petitsPaquets[numeroPaquet - 1][j] = tmp[j];
                }
            }
        }
        // On rempile les petits paquets
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 7; k++)
            {
                paquetTour[j * 7 + k] = petitsPaquets[j][k];
            }
        }
        printf("\n");
    }

    printf("Ta carte est ...\n");
    afficherCarte(paquetTour[10]);

    return 0;
}
