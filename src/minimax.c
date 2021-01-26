int minimax(Position* position, int depth, bool maximizingPlayer) {
	if (depth == 0 || gameOver(position)) {
		return evaluation(position)
	}

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

bool gameOver(Position* position) {
	return position.seeds_total < 8;
}