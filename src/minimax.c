#include <stdbool.h>
#include "position.h"
#include "functions.h"

int minimax(Position position, int depth) {
	if (depth == 0 || gameOver(position)) {
		return evaluation(position)
	}

	Position nextPosition;
	int values[12];
	int cell;

	// On récupère l'évaluation de toutes les positions possibles à partir de la position courante
	for (int i = 0; i < 12; i++) {
		if (position.computer_play) {
			cell = i * 2; // Si c'est à l'ordinateur de jouer, on joue les cases impaires (indices pairs), donc 0 <= i <= 22
		}
		else {
			cell = i * 2 + 1; // Autrement, on joue les cases paires (indices impairs)
		}

		if (position.board[cell] != 0) { // Si la cellule n'est pas vide, i.e. le coup est valide
			nextPosition = playMove(position, cell);
			values[i] = minimax(nextPosition, depth - 1);
		}
		// Si le coup n'est pas valide, la valeur est la plus petite possible pour l'ordinateur, sinon la plus grande
		else {
			if (position.computer_play) {
				values[i] = -96;
			}
			else {
				values[i] = 96
			}
		}
	}

	if (position.computer_play) {
		int maxEval = -96;
		// Pour chaque fils de la position
		for (int i = 0; i < 12; i++) {
			maxEval = max(maxEval, values[i]);
		}
		return maxEval;
	}

	else {
		int minEval = 96;
		// Pour chaque fils de la position
		for (int i = 0; i < 12; i++) {
			minEval = min(maxEval, values[i]);
		}
		return minEval;
	}
}

int evaluation(Position* position) {
	return position.seeds_computer - position.seeds_player;
}

Position playMove(Position position, int cell) {
    int seeds;

    // On récupère le nombre de graines à la case choisie et on egrène
    seeds = plantSeeds(&position, cell);

    // On regarde s'il y a une prise
    takeSeeds(&position, cell, seeds);

	// On regarde si le joueur qui n'était pas en train de jouer est affamé suite au coup
	if (isOpponentStarved(position)) {
		// On ajoute les graines restantes au total du joueur qui vient de jouer le coup
		takeAllSeeds(&position);
	}

	// S'il reste moins de 48 graines, on fusionne les cellules
	if (position.seeds_total < 48 && !position.merged) {
		merge(&position);
	}

	return position;
}

int max(a, b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int min(a, b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}