#include <stdbool.h>
#include "position.h"
#include "functions.h"

int plantSeeds(Position* position, int cell) {
    int start_cell = cell;
    int nb_cells = position->nb_cells;
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

void takeSeeds(Position* position, int cell, int seeds) {
    int nb_cells = position->nb_cells;
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

bool isOpponentHungry(Position position, bool typeOfPlayer) {
    // Si le joueur aux cases impaires vient de jouer, on vérifie les cases paires (indices impairs), et vice versa
    int nb_cells = position.nb_cells;
    for (int i = typeOfPlayer; i < nb_cells; i += 2) {
        if (position.board[i] != 0) {
            return false;
        }
    }
    return true;
}

bool gameOver(Position position) {
    return position.seeds_total < 8;
}