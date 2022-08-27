/*
 * This is a simple tic-tac-toe game written as an exercise in the use
 * of two-dimensional arrays and conditional operators.
 */

#include <stdio.h>
#include <stdlib.h>

#define NR_ROWS 3
#define NR_COLS 3

int  go_bananas  (int [][NR_COLS]);
void print_board (int [][NR_COLS]);
void get_move    (int *, char *);
int  check_move  (int [][NR_COLS], int, int);
int  check_win   (int [][NR_COLS], int);

int main(void)
{
    /* This is the board on which the game is played.
     *
     * All squares on the board are initialised with a value of 0.
     *
     * A value of 1 means that player 1 has placed their symbol in the
     * square. This is printed to the user as an 'X'.
     *
     * A value of 2 means that player 2 has placed their symbol in the
     * square. This is printed to the user as an 'O'.
     */
    int board[NR_ROWS][NR_COLS] = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    /* Run the game loop and get the winning player. */
    int winner = go_bananas(board);

    print_board(board);

    if (winner != 0)
        printf("Congratulations player %d!\n\n", winner);
    else
        printf("It's a draw!\n\n");

    return 0;
}

int go_bananas(int board[][NR_COLS])
{
    /* player determines which player's turn it is. A value of 0 means
     * player 1, a value of 1 means player 2. Confusing, I know.
     */
    int player = 0;

    /* row and col are the coordinates of the square in which the
     * player would like to place their symbol.
     */
    int row, col;
    
    /* is_legal determines if the player's desired move is legal or
     * not.
     */
    int is_legal = 0;

    /* has_won determines if the current player has won or not. If
     * they have won, then the game is over.
     */
    int has_won = 0;

    for (int i = 0; i < (NR_ROWS * NR_COLS); ++i) {
        print_board(board);
        printf("Player %d, your move!\n\n", player ? 2 : 1);

        do {
            get_move(&row, "row");
            get_move(&col, "column");
            is_legal = check_move(board, row, col);
            if (!is_legal)
                printf("Illegal move! Shame on you!!!\n\n");
        } while (!is_legal);

        board[row-1][col-1] = player ? 2 : 1;

        has_won = check_win(board, player);
        
        if (has_won)
            return player ? 2 : 1;
        else
            player = player ? 0 : 1;
    }

    /* If the loop ended before a player could win, then that means
     * the game ended in a draw.
     */
    return 0;
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
    printf("\n");
}

void get_move(int *move, char *prompt)
{
    printf("Enter the %s number: ", prompt);
    do {
        scanf("%d", move);
        if (!(1 <= *move && *move <= 3))
            printf("Enter a valid %s number: ", prompt);
    } while (!(1 <= *move && *move <= 3));
}

int check_move(int board[][NR_COLS], int row, int col)
{
    if (board[row-1][col-1] == 0)
        return 1;
    else
        return 0;
}

int check_win(int board[][NR_COLS], int player)
{
    int symbol = player ? 2 : 1;

    /* There are a total of eight win conditions in tic-tac-toe. We
     * check for each one of them here.
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
