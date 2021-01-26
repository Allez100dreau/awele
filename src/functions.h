#ifndef FUNCTIONS
#define FUNCTIONS

int plantSeeds(Position* position, int cell);
void takeSeeds(Position* position, int cell, int seeds);
void merge(Position* position);
bool isOpponentHungry(Position position, bool typeOfPlayer);
bool gameOver(Position position);

#endif