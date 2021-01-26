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

	int eval;

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

void playMove(Position* nextPosition, Position* position, int cell) {
    int seeds;

    // On récupère le nombre de graines à la case choisie et on egrène
    seeds = plantSeeds(ptr, cell);

    // On regarde s'il y a une prise
    takeSeeds(ptr, cell, seeds);
}