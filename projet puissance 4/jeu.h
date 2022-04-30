#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void initialize(char tableau[7][7]) {
    int i, j;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            tableau[i][j] = ' ';
        }
    }
}

void print_tableau(char tableau[7][7]) {
    int i, j;
    printf("\n=======\n");
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            printf("|%c|", tableau[i][j]);
        }
        printf("\n");
    }
    printf("=======\n");
}

int insert_jeton (char tableau[7][7], int colonne, char jeton) {
    int i;
    for(i = 6; i >= 0; i--){
        if(tableau[i][colonne] == ' '){
            tableau[i][colonne] = jeton;
            return 0;
        }
    }
    printf("ERREUR: colonne pleine..\n");
    return 1;
}

void tournergauche(char tableau[7][7]){
    int i, j, a = 0, b = 0;
    char nouveau_tableau[7][7];
    initialize(nouveau_tableau);

    for (j = 0; j < 7; j++){
        for (i = 0; i < 7; i++){
            if(tableau[i][j] != ' '){
                a = 6;
                while(nouveau_tableau[a][i] != ' ' && a > 0){
                    a--;
                }
                nouveau_tableau[a][i] = tableau[i][j];
            }
        }
    }

    for(i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            tableau[i][j] = nouveau_tableau[i][j];
        }
    }
}

void tournerdroite(char tableau[7][7]){
    int i, j, a = 0, b = 0;
    char nouveau_tableau[7][7];
    initialize(nouveau_tableau);

    for (j = 6; j >= 0; j--){
        for (i = 0; i < 7; i++){
            if(tableau[i][j] != ' '){
                a = 6;
                while(nouveau_tableau[a][6-i] != ' ' && a > 0){
                    a--;
                }
                //printf("\n%c %d %d\n", nouveau_tableau[a][6-i], a, 6-i);
                nouveau_tableau[a][6-i] = tableau[i][j];
            }
        }
    }

    for(i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            tableau[i][j] = nouveau_tableau[i][j];
        }
    }
}

void retourner(char tableau[7][7]){
    int i, j, a = 0, b = 0;
    char nouveau_tableau[7][7];
    initialize(nouveau_tableau);

    for (j = 6; j >= 0; j--){
        for (i = 0; i < 7; i++){
            if(tableau[i][j] != ' '){
                a = 6;
                while(nouveau_tableau[a][j] != ' ' && a > 0){
                    a--;
                }
                //printf("\n%c %d %d\n", nouveau_tableau[a][6-i], a, 6-i);
                nouveau_tableau[a][j] = tableau[i][j];
            }
        }
    }

    for(i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            tableau[i][j] = nouveau_tableau[i][j];
        }
    }
}

int check_winner(char tableau[7][7], char symbole){
    int i, j, slice, z, n;
    int score;
    int winner = 0;


    //check horizontal
    for( i = 0; i < 7; i++){
        score = 0;
        for( j = 0; j < 7; j++){
            if(tableau[i][j] == symbole){
                score++;
                if(score == 4){
                    return 1;
                }
            } else {
                score = 0;
            }
        }
    }
    //check vertical
    for( j = 0; j < 7; j++){
        score = 0;
        for(i = 0; i < 7; i++){
            if(tableau[i][j] == symbole){
                score++;
                if(score == 4){
                    return 1;
                }
            } else {
                score = 0;
            }
        }
    }

    //check diagonal
    for (slice = 0; slice < 2 * 7 - 1; ++slice) {
        score = 0;
        z = (slice < 7) ? 0 : slice - 7 + 1;
        for (j = z; j <= slice - z; ++j) {
            if(tableau[j][slice - j] == symbole){
                score++;
                if(score == 4){
                    return 1;
                }
            } else {
                score = 0;
            }
        }
    }

    //check reverse diagonal
    for (slice = 0; slice < 2 * 7 - 1; ++slice) {
        score = 0;
        z = (slice < 7) ? 0 : slice - 7 + 1;
        for (j = z; j <= slice - z; ++j) {
            if(tableau[j][6 - slice - j] == symbole){
                score++;
                if(score == 4){
                    return 1;
                }
            } else {
                score = 0;
            }
        }
    }

    return 0;
}

int check_full(char tableau[7][7]){
    int i, j;

    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            if (tableau[i][j] == ' '){
                return 0;
            }
        }
    }

    return 1;
}


void save_tableau(char tableau[7][7], int tour){
    FILE *fp;
    int i, j;

    fp = fopen("sauvegarde.txt", "w");

    if(fp == NULL){
        printf("\nSauvegarde échouée!!\n");
        return;
    }

    fprintf(fp, "%d", tour);

    for(i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            fprintf(fp, "%c", tableau[i][j]);
        }
    }
}

void load_tableau(char tableau[7][7], int *tour){
    FILE *fp;
    int i, j;

    fp = fopen("sauvegarde.txt", "r");


    if(fp == NULL){
        printf("\nLecture du fichier échouée!!\n");
        return;
    }

    fscanf(fp, "%d", tour);

    for(i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            fscanf(fp, "%c", &tableau[i][j]);
        }
    }
}


void game(char tableau[7][7]){
    int n_joueurs, choix, colonne, return_status;
    int game_over = 0, winner = 0, autonome = 0;
    int tour = 1;
    char jeton;

    printf("\n\nBonjour. Choisissez le nombre de joueurs. (1 ou 2):");
    scanf("%d", &n_joueurs);

    if(n_joueurs == 1){
        autonome = 1;
        printf("\nJoueur 1: vous jouez les X. Joueur 2 (Ordinateur): vous jouez les O");
    } else if(n_joueurs == 2) {
        printf("\nJoueur 1: vous jouez les X. Joueur 2: vous jouez les O");
    } else {
        printf("\nCHOIX INVALIDE, LE JEU VA QUITTER!!\n");
        return;
    }

    while(game_over == 0){
        if(tour == 1){
           jeton = 'X';
        } else if (tour == 2){
            jeton = 'O';
        }

        CHOIX:

        print_tableau(tableau);
       

        printf("\nJoueur %d: c'est ton tour. Que voulez-vous faire?\n", tour);
        printf("1. inserer jeton.\n");
        printf("2. tourner le tableau a gauche.\n");
        printf("3. tourner le tableau a droite.\n");
        printf("4. retourner le tableau.\n");
        printf("5. sauvegarder la partie.\n");
        printf("6. charger la dernière partie sauvegardée.\n");
        printf("7. abandonner la partie\n");


        if (tour == 2 && autonome == 1){
            choix = (rand() % (4 - 1 + 1) + 1);
            printf("\nl'Ordinateur choisit l'option: %d\n", choix);
        } else {
            scanf("%d", &choix);
        }

        switch(choix){
            case 1: printf("Choisissez une colonne (de 1 a 7):");
                    if (tour == 2 && autonome == 1){
                        colonne = (rand() % (7 - 1 + 1) + 1);
                        printf("\nl'Ordinateur choisit la colonne: %d\n", colonne);
                    } else {
                        scanf("%d", &colonne);
                    }
                    return_status = insert_jeton(tableau, colonne-1, jeton);
                    break;
            case 2: tournergauche(tableau);
                    printf("\ntableau tourné à gauche.\n");
                    break;
            case 3: tournerdroite(tableau);
                    printf("\ntableau tourné a droite.\n");
                    break;
            case 4: retourner(tableau);
                    printf("\ntableau retourne.\n");
                    break;
            case 5: printf("\nSAUVEGARDE EN COURS.\n");
                    save_tableau(tableau, tour);
                    goto CHOIX;
                    break;
            case 6: printf("\nCHARGEMENT DE LA SAUVEGARDE EN COURS\n");
                    load_tableau(tableau, &tour);
                    goto CHOIX;
                    break;
            case 7: printf("\nVous abandonnez la partie, joueur %d. \n", tour);
                    winner = tour == 1 ? 2 : 1;
                    game_over = 1;
                    break;
            default: printf("\nCHOIX INVALIDE!\n");
                     break;
        }

        if(check_winner(tableau, 'X') == 1){
            winner = 1;
            game_over = 1;
        } else if(check_winner(tableau, 'O') == 1){
            winner = 2;
            game_over = 1;
        }

        if(check_full(tableau) == 1){
            game_over = 1;
        }


        tour = tour == 1 ? 2 : 1;
    }

    if(game_over == 1){
        print_tableau(tableau);
        if(winner != 0){
            printf("\nJOUEUR %d GAGNE!!!\n", winner);
        } else {
            printf("\nMATCH NUL");
        }

        printf("\n\n====================\nPARTIE TERMINEE!\n");
    }


