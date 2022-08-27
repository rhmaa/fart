/*
 * This is a simple tic-tac-toe game written as an exercise in the use
 * of two-dimensional arrays and conditional operators.
 */

#include <stdio.h>
#include <stdlib.h>

#define NR_ROWS 3
#define NR_COLS 3

void go_bananas(int [][NR_COLS]);
void print_board(int [][NR_COLS]);
void get_move(int *, char *);
int  check_move(int [][NR_COLS], int, int);
int  check_win(int [][NR_COLS], int);

int main(void)
{
    /* This is the board on which the game will be played. We
     * initialise each cell of the board with a value of 0. A cell
     * containing 0 means that the player has not yet put down a
     * symbol.
     *
     * 1 means that the player has put down a cross (printed to the
     * user as X).
     *
     * 2 means that the player has put down a circle (printed to the
     * user as O).
     */
    int board[NR_ROWS][NR_COLS] = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    go_bananas(board);

    return 0;
}

void go_bananas(int board[][NR_COLS])
{
    /* player_to_move determines which player's turn it is. 0 means
     * that it's player 1's turn, 1 means that it's player 2's turn.
     */
    int player_to_move = 0;

    for (int i = 0; i < (NR_ROWS * NR_COLS); ++i) {
        print_board(board);

        printf("\nPlayer %d, your move!\n\n", player_to_move ? 2 : 1);

        int is_legal = 0;
        int row, col;
   
        /* Get the player's move, and make sure that it's legal. */
        do {
            get_move(&row, "row");
            get_move(&col, "column");
            is_legal = check_move(board, row, col);
            if (!is_legal)
                printf("\n--- Illegal move! Shame on you!!! ---\n\n");
        } while (!is_legal);

        /* Place the player's symbol on the board. */
        board[row-1][col-1] = (player_to_move ? 2 : 1);

        /* Check if the player has won. */
        int has_won = check_win(board, player_to_move);
        
        if (has_won) {
            print_board(board);
            printf("\n--- Congratulations player %d, you have won! ---\n\n", player_to_move ? 2 : 1);
            break;
        } else if (i == (NR_ROWS * NR_COLS - 1)) {
            print_board(board);
            printf("\n--- It's a draw! ---\n\n");
            break;
        } else {
            player_to_move = player_to_move ? 0 : 1;
        }
    }
}

void print_board(int board[][NR_COLS])
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("    1   2   3 \n");
    printf("  +---+---+---+\n");
    for (int i = 0; i < NR_ROWS; ++i) {
        printf("%d |", i + 1);

        for (int j = 0; j < NR_COLS; ++j)
            printf(" %c |", (board[i][j] ? (board[i][j] == 1 ? 'X' : 'O') : ' '));

        printf("\n  +---+---+---+\n");
    }
}

void get_move(int *move, char *prompt)
{
    printf("Enter the %s number: ", prompt);
    do {
        scanf("%d", move);
        if (!(1 <= *move && *move <= 3))
            printf("Enter a valid number: ");
    } while (!(1 <= *move && *move <= 3));
}

int check_move(int board[][NR_COLS], int row, int col)
{
    /* If the cell contains a 0, i.e. if no player has placed a symbol
     * in the cell previously, then it is a legal move.
     */
    if (board[row-1][col-1] == 0)
        return 1;
    else
        return 0;
}

int check_win(int board[][NR_COLS], int player)
{
    int symbol = player ? 2 : 1;

    /* There are a total of eight win conditions in tic-tac-toe. We
     * check for each one of them.
     */
    if (/* Symbols are horizontally aligned. */
        (board[0][0] == symbol && board[0][1] == symbol && board[0][2] == symbol) ||
        (board[1][0] == symbol && board[1][1] == symbol && board[1][2] == symbol) ||
        (board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol) ||
        /* Symbols are vertically aligned. */
        (board[0][0] == symbol && board[1][0] == symbol && board[2][0] == symbol) ||
        (board[0][1] == symbol && board[1][1] == symbol && board[2][1] == symbol) ||
        (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol) ||
        /* Symbols are diagonally aligned. */
        (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol))
        return 1;
    else
        return 0;
}
