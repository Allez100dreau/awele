#include "position.h"
#include "functions.h"

int minimax(Position position, int depth, bool maximizingPlayer) {
	if (depth == 0 || gameOver(position)) {
		return evaluation(position)
	}

	Position nextPosition;

	if (maximizingPlayer) {
		int maxEval = -96;
		// Pour chaque fils de la position
		return maxEval;
	}

	else {
		int minEval = 96;
		// Pour chaque fils de la position
		return minEval;
	}

	return 0;
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
	if (isOpponentStarved(position, typeDeCase)) {
		// On ajoute les graines restantes au total du joueur qui vient de jouer le coup
		takeAllSeeds(&position);
	}

	// S'il reste moins de 48 graines, on fusionne les cellules
	if (position.seeds_total < 48 && !position.merged) {
		merge(&position);
	}

	return position;
}