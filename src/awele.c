#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "position.h"
#include "functions.h"

void showBoard(Position position, int turn) {
    printf("### TURN %d ###\n", turn);
    int nb_cells = position.nb_cells;
    for (int i = 0; i < nb_cells; i++) {
        printf("%d ", position.board[i]);
        if (i == (nb_cells / 2 - 1)) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int findBestMove(Position position) {
    int values[12];

    for (int i = 0; i < 12; i++) {
        values[i] = minimax(position, 3);
    }

    int bestScore = -96;
    int bestIndex;

    for (int i = 0; i < 12; i++) {
        if (values[i] > bestScore) {
            bestScore = values[i];
            bestIndex = i;
        }
    }

    int cell = bestIndex * 2;

    return cell;
}

int main() {

    srand(time(NULL));

    // Position initiale du jeu
    // Mettre à true pour faire commencer l'ordi en 1er, aussi dans cette configuration il devra forcément jouer impair
    // Quand on est à false, l'ordi joue en 2nd et doit jouer pair
    
    Position position = { {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                   24, 96, false, 1, 0, 0, false };  

    // Configuration pour tester si le joueur est affamé, il faut jouer 22 et l'ordi est affamé ensuite
    
    /*
    Position position = { {0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4,
                   0, 4, 0, 4, 0, 4, 0, 4, 0, 1, 1, 4},
                   24, 96, false, 1, 0, 0, false };
    */

    // On récupère un pointeur pour la position
    Position* ptr = &position;

    // À propos du jeu
    int turn = 1;

    // Utilisées pour la boucle de jeu
    int cell;
    int seeds;
    int computer_rand = 12;

    // Boucle de jeu
    while (!gameOver(position)) {
        showBoard(position, turn);

        // S'il reste moins de 48 graines, on fusionne les cellules
        if (position.seeds_total < 48 && !position.merged) {
            merge(ptr);

            printf("### BOARD CELLS HAVE BEEN MERGED ###\n");
            
            computer_rand = 6;
            showBoard(position, turn);
        }

        if (position.computer_play) {
            // Joue uniquement les cases impaires
            position.cellType = 1; // L'ordinateur joue les cases impaires

            /*do cell = rand() % computer_rand * 2;
            while (position.board[cell] == 0);*/

            cell = findBestMove(position);

            printf("Computer plays cell %d\n", cell + 1);
        }

        else {
            // Joue uniquement les cases paires
            printf("Choose an even cell : \n");
            position.cellType = 0; // Le joueur joue les cases paires
            do {
                scanf_s("%d", &cell);
                cell--;
            } while (position.board[cell] == 0 || (cell % 2 == 0) || cell > position.nb_cells || cell < 1);
        }

        // On egrène on on récupère le nombre de graines à la case choisie
        seeds = plantSeeds(ptr, cell);

        // On regarde s'il y a une prise
        takeSeeds(ptr, cell, seeds);

        int last_cell = (cell + seeds) % position.nb_cells;
        printf("We reach cell %d\n\n", last_cell + 1);
        printf("Computer's seeds : %d\nPlayer's seeds : %d\n\n", position.seeds_computer, position.seeds_player);

        // On regarde si le joueur qui n'était pas en train de jouer est affamé suite au coup
        if (isOpponentStarved(position)) {
            // On ajoute les graines restantes au total du joueur qui vient de jouer le coup
            printf("Opponent is starved, taking all remaining seeds...\n");
            takeAllSeeds(ptr);
        }

        turn++;

        position.computer_play = !position.computer_play;
    }
    printf("Game is over, players' number of seeds : \nComputer's seeds : %d\nPlayer's seeds : %d\n", ptr->seeds_computer, ptr->seeds_player);

    return 0;
}