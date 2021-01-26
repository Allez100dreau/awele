#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "position.h"

bool isOpponentHungry(bool merged, Position position, int nb_cells, bool typeOfPlayer) {
    // Si le joueur aux cases impaires vient de jouer, on vérifie les cases paires (indices impairs), et vice versa
    for (int i = typeOfPlayer; i < nb_cells; i+=2) {
        if (position.board[i] != 0) {
            return false;
        }
    }
    return true;
}

void merge(Position* position) {
    int sum_seeds = 0;
    int merged_cell = 0;
    for (int i = 1; i < 24; i += 2) {
        sum_seeds = position->board[i] + position->board[i - 1];
        position->board[merged_cell] = sum_seeds;
        merged_cell++;
    }
    printf("### BOARD CELLS HAVE BEEN MERGED ###\n");
}

int plantSeeds(Position* position, int cell, int nb_cells) {
    int start_cell = cell;
    // Le nombre de graines présentes dans la case choisie
    int seeds = position->board[cell];
    position->board[cell] = 0;
    for (int i = 1; i <= seeds; i++) {
        if ((cell + i) % nb_cells != start_cell) {
            position->board[(cell + i) % nb_cells] += 1;
        }
        else seeds++;
    }
    return seeds;
}

void takeSeeds(Position* position, int cell, int seeds, int nb_cells) {
    // La cellule sur laquelle on atterrit
    int last_cell = (cell + seeds) % nb_cells;
    printf("We reach cell %d\n\n", last_cell + 1);
    while (position->board[last_cell] == 2 || position->board[last_cell] == 3) {
        if (position->computer_play) {
            position->seeds_computer += position->board[last_cell];
            position->seeds_total -= position->board[last_cell];
        }
        else {
            position->seeds_player += position->board[last_cell];
            position->seeds_total -= position->board[last_cell];
        }
        position->board[last_cell] = 0;
        if (last_cell == 0) {
            last_cell = nb_cells;
        }
        last_cell--;
    }
    printf("Computer's seeds : %d\nPlayer's seeds : %d\n\n", position->seeds_computer, position->seeds_player);
}

void showBoard(Position position, int turn, int nb_cells) {
    printf("### TURN %d ###\n", turn);
    for (int i = 0; i < nb_cells; i++) {
        printf("%d ", position.board[i]);
        if (i == (nb_cells / 2 - 1)) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int main() {

    srand(time(NULL));

    // Position initiale du jeu
    // Mettre à true pour faire commencer l'ordi en 1er, aussi dans cette configuration il devra forcément jouer impair
    // Quand on est à false, l'ordi joue en 2nd et doit jouer pair

    /*
    Position position = { {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                   96, false, 0, 0 };
    */
    

    // Configuration pour tester si le joueur est affamé, il faut jouer 22 et l'ordi est affamé ensuite
    
    Position position = { {0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4,
                   0, 4, 0, 4, 0, 4, 0, 4, 0, 1, 1, 4},
                   96, false, 0, 0 };
    

    Position* ptr = &position;

    // À propos du jeu
    int turn = 1;
    int nb_cells = 24;
    bool merged = false;

    // Utilisées pour la boucle de jeu
    int cell;
    int seeds;
    int computer_rand = 12;
    int typeDeCase;

    showBoard(position, turn, nb_cells);

    // Boucle de jeu
    while (!gameOver(ptr)) {
        // S'il reste moins de 48 graines, on fusionne les cellules
        if (position.seeds_total < 48 && !merged) {
            merge(ptr);
            merged = true;

            nb_cells = 12;
            computer_rand = 6;
            showBoard(position, turn, nb_cells);
        }

        if (position.computer_play) {
            // Joue uniquement les cases impaires
            typeDeCase = 1; // L'ordinateur joue les cases impaires
            do cell = rand() % computer_rand * 2;
            while (position.board[cell] == 0);
            printf("Computer plays cell %d\n", cell + 1);
        }

        else {
            // Joue uniquement les cases paires
            printf("Choose an even cell : \n");
            typeDeCase = 0; // Le joueur joue les cases paires
            do {
                scanf_s("%d", &cell);
                cell--;
            } while (position.board[cell] == 0 || (cell % 2 == 0) || cell > nb_cells || cell < 1);
        }

        // On egrène on on récupère le nombre de graines à la case choisie
        seeds = plantSeeds(ptr, cell, nb_cells);

        // On regarde s'il y a une prise
        takeSeeds(ptr, cell, seeds, nb_cells);

        // On regarde si le joueur qui n'était pas en train de jouer est affamé suite au coup
        if (isOpponentHungry(merged, position, nb_cells, typeDeCase)) {
            // On ajoute les graines restantes au total du joueur qui vient de jouer le coup
            if (position.computer_play) {
                ptr->seeds_computer += ptr->seeds_total;
                ptr->seeds_total = 0;
            }
            else {
                ptr->seeds_player += ptr->seeds_total;
                ptr->seeds_total = 0;
            }
        }

        turn++;
        showBoard(position, turn, nb_cells);

        position.computer_play = !position.computer_play;
    }
    printf("Position is over, players' number of seeds : \nComputer's seeds : %d\nPlayer's seeds : %d\n", ptr->seeds_computer, ptr->seeds_player);

    return 0;
}