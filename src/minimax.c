#include <stdbool.h>
#include <limits.h>
#include "position.h"
#include "functions.h"

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

	position.computer_play = !position.computer_play;
	position.cellType = !position.cellType;

	return position;
}

int evaluation(Position position) {
	return position.seeds_computer - position.seeds_player;
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

int minimax(Position position, int depth, int alpha, int beta, int* bestCell) {
	if (gameOver(position)) {
		if (position.seeds_computer > position.seeds_player) {
			return INT_MAX;
		}
		else {
			return INT_MIN;
		}
	}

	if (depth == 0) {
		return evaluation(position);
	}

	Position nextPosition;
	int cell;
	int eval;

	if (position.computer_play) {
		int maxEval = INT_MIN;
		// Pour chaque fils de la position
		for (int i = 0; i < 12; i++) {
			cell = i * 2 + !position.cellType;

			if (position.board[cell] != 0) { // Si la cellule n'est pas vide, i.e. le coup est valide
				nextPosition = playMove(position, cell);
				eval = minimax(nextPosition, depth - 1, alpha, beta, bestCell);
				if (eval > maxEval) {
					maxEval = eval;
					*bestCell = i;
				}
			}

			alpha = max(alpha, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return maxEval;
	}

	else {
		int minEval = INT_MAX;
		// Pour chaque fils de la position
		for (int i = 0; i < 12; i++) {
			cell = i * 2 + position.cellType;

			if (position.board[cell] != 0) { // Si la cellule n'est pas vide, i.e. le coup est valide
				nextPosition = playMove(position, cell);
				eval = minimax(nextPosition, depth - 1, alpha, beta, bestCell);
				minEval = min(minEval, eval);
			}

			beta = min(beta, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return minEval;
	}
}