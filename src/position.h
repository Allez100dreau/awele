typedef struct {
    int cell;
    int score;
}CellScore;

typedef struct {
    int board[24];
    int nb_cells;
    int seeds_total;
    bool computer_play;
    int cellType;
    int seeds_player;
    int seeds_computer;
    bool merged;
} Position;