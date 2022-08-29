/*
 * A simple game of rock, paper, scissors -- with cheat mode of
 * course.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NR_MOVES     3
#define MAX_STR_LEN  1024

void get_player_move (int *, char *[]);
void get_cpu_move    (int *);

int main(int argc, char **argv)
{
    /* We do a little cheating here. */
    int cheat_mode = 0;
    if (argc == 2 && strcmp(argv[1], "--cheat") == 0) {
        cheat_mode = 1;
        printf("\n🚨 CHEAT MODE ACTIVATED 🚨\n\n");
    }
    
    /* A list of all legal moves. */
    char *moves[NR_MOVES] = { "rock", "paper", "scissors" };

    /* The player's move, read through user input. */
    int player_move = -1;

    /* The computer's move, randomly generated. */
    int cpu_move;

    do {
        get_player_move(&player_move, moves);
        
        if (!(0 <= player_move && player_move < NR_MOVES))
            printf("Illegal move!\n");

    } while (!(0 <= player_move && player_move < NR_MOVES));

    if (!cheat_mode) {
        get_cpu_move(&cpu_move);
    } else {
        /* If cheat mode is activated, the computer picks whatever the
         * player beats.
         */
        switch (player_move) {
        case 0:
            cpu_move = 2;
            break;
        case 1:
            cpu_move = 0;
            break;
        case 2:
            cpu_move = 1;
            break;
        }
    }

    printf("The computer chose %s.\n", moves[cpu_move]);

    if (player_move == cpu_move)
        printf("It's a draw!\n\n");
    else if (player_move == 0 && cpu_move == 2 || /* rock beats scissors  */
             player_move == 1 && cpu_move == 0 || /* paper beats rock     */
             player_move == 2 && cpu_move == 1    /* scissors beats paper */)
        printf("The player won!\n\n");
    else
        printf("The computer won!\n\n");

    return 0;
}

void get_player_move(int *player_move, char *moves[])
{
    char buffer[MAX_STR_LEN];
    
    printf("Enter your move: ");

    if (fgets(buffer, MAX_STR_LEN, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    } else {
        perror("fgets in main() could not write to buffer");
        exit(1);
    }

    /* Make sure that the move is matched, no matter how the player
     * entered it. It should not matter if the person wrote "ROCK"
     * instead of "rock".
     */
    for (int i = 0; buffer[i]; ++i)
        buffer[i] = tolower(buffer[i]);

    for (int i = 0; i < NR_MOVES; ++i) {
        if (strcmp(buffer, moves[i]) == 0) {
            *player_move = i;
            break;
        }
    }
}

void get_cpu_move(int *cpu_move)
{
    srand(time(0));
    *cpu_move = rand() % NR_MOVES;
}
