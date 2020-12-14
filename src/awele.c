#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int board[24];
    int seeds_total;
    bool computer_play;
    int seeds_player;
    int seeds_computer;
} Game;

bool gameOver(Game game) {
    return game.seeds_total < 8;
}

bool isOpponentHungry(bool merged, Game game) {
    int cpt = 24;
    if (merged == true) {
        cpt = 12;
    }
    for (int i = 0; i < cpt; i++) { 
        // Quand computer play est true (= 1), donc l'ordinateur joue, on va vérifier les indices impairs qui correspondent aux cases paires du joueur
        if (i % 2 == game.computer_play) {
            if (game.board[i] != 0) {
                return false;
            }
        }
    }
    return true;
}

void merge(Game * game) {
    int sum_seeds = 0;
    int merged_cell = 0;
    for (int i = 1; i < 24; i += 2) {
        sum_seeds = game->board[i] + game->board[i - 1];
        game->board[merged_cell] = sum_seeds;
        merged_cell++;
    }
    printf("### BOARD CELLS HAVE BEEN MERGED ###\n");
}

int plantSeeds(Game * game, int cell, int nb_cells) {
    int start_cell = cell;
    // Le nombre de graines présentes dans la case choisie
    int seeds = game->board[cell];
    game->board[cell] = 0;
    for (int i = 1; i <= seeds; i++) {
        if ((cell + i) % nb_cells != start_cell) {
            game->board[(cell + i) % nb_cells] += 1;
        }
    }
    return seeds;
}

void takeSeeds(Game * game, int cell, int seeds, int nb_cells) {
    // La cellule sur laquelle on atterrit
    int last_cell = (cell + seeds) % nb_cells;
    printf("We reach cell %d\n\n", last_cell + 1);
    while (game->board[last_cell] == 2 || game->board[last_cell] == 3) {
        if (game->computer_play) {
            game->seeds_computer += game->board[last_cell];
            game->seeds_total -= game->board[last_cell];
        }
        else {
            game->seeds_player += game->board[last_cell];
            game->seeds_total -= game->board[last_cell];
        }
        game->board[last_cell] = 0;
        if (last_cell == 0) {
            last_cell = nb_cells;
        }
        last_cell--;
    }
    printf("Computer's seeds : %d\nPlayer's seeds : %d\n\n", game->seeds_computer, game->seeds_player);
}

void showBoard(Game game, int turn, int nb_cells) {
    printf("### TURN %d ###\n", turn);
    for (int i = 0; i < nb_cells; i++) {
        printf("%d ", game.board[i]);
        if (i == (nb_cells/2 - 1)) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int main() {

    srand(time(NULL));

    // Position initiale du jeu
    Game game = { {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
                   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                   96, false, 0, 0};

    //Configuration pour tester si le joueur est affamé, il faut jouer 22 et l'ordi est affamé ensuite
    //Game game = { {0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4,
    //               0, 4, 0, 4, 0, 4, 0, 4, 0, 1, 1, 4},
    //              96, false, 0, 0 };

    Game* ptr = &game;

    // À propos du jeu
    int turn = 1;
    int nb_cells = 24;
    bool merged = false;

    // Utilisées pour la boucle de jeu
    int cell;
    int seeds;
    int computer_rand = 12;

    showBoard(game, turn, nb_cells);

    // Boucle de jeu
    while (!gameOver(game)) {
        // S'il reste moins de 48 graines, on fusionne les cellules
        if (game.seeds_total < 48 && !merged) {
            merge(ptr);
            merged = true;

            nb_cells = 12;
            computer_rand = 6;
            showBoard(game, turn, nb_cells);
        }

        if (game.computer_play) {
            // Joue uniquement les cases impaires
            do cell = rand() % computer_rand * 2;
            while (game.board[cell] == 0);
            printf("Computer plays cell %d\n", cell + 1);
        }

        else {
            // Joue uniquement les cases paires
            printf("Choose an even cell : \n");
            do {
                scanf("%d", &cell);
                cell--;
            }
            while (game.board[cell] == 0 || (cell % 2 == 0) || cell > nb_cells);
        }

        // On egrène on on récupère le nombre de graines à la case choisie
        seeds = plantSeeds(ptr, cell, nb_cells);

        // On regarde s'il y a une prise
        takeSeeds(ptr, cell, seeds, nb_cells);

        // On regarde si le joueur qui n'était pas en train de jouer est affamé suite au coup
        if (isOpponentHungry(merged, game)) {
            //on ajoute les graines sur le plateau au total du joueur actuel
            if (game.computer_play) {
                ptr->seeds_computer += ptr->seeds_total;
                ptr->seeds_total -= ptr->seeds_total;
            }
            else {
                ptr->seeds_player += ptr->seeds_total;
                ptr->seeds_total -= ptr->seeds_total;
            }
        }
       
        turn++;
        showBoard(game, turn, nb_cells);

        game.computer_play = !game.computer_play;
    }
    printf("Game is over, players' number of seeds : \nComputer's seeds : %d\nPlayer's seeds : %d\n" , ptr->seeds_computer, ptr->seeds_player);


    return 0;
}