#ifndef FUNCTIONS
#define FUNCTIONS

int plantSeeds(Position* position, int cell);
void takeSeeds(Position* position, int cell, int seeds);
void merge(Position* position);
bool isOpponentStarved(Position position, bool typeOfPlayer);
void takeAllSeeds(Position* position);
bool gameOver(Position position);

#endif