/*
 * A simple program that takes string input from two players, and then
 * determines how many points those words are worth in scrabble.
 *
 * The program ends by printing which player had the highest scoring
 * word.
 *
 * Note! The program only takes ASCII input. UTF8 characters are not
 * supported.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 64         /* 64 character long words should be OK. */
#define NR_PLAYERS   2          /* The number of players. */

int  get_score    (char *);
void get_word     (char []);
void print_winner (int []);

int main(void)
{
    /* The word that the player enters. The same array is used for all
     * players' words.
     */
    char word[MAX_WORD_LEN] = {};

    /* The players' scores. */
    int scores[NR_PLAYERS];

    for (int i = 0; i < NR_PLAYERS; ++i) {
        get_word(word);
        scores[i] = get_score(word);
    }

    print_winner(scores);

    return 0;
}

void print_winner(int scores[])
{
    if (scores[0] > scores[1])
        printf("Congratulations Player 1!\n");
    else if (scores[0] < scores[1])
        printf("Congratulations Player 2!\n");
    else
        printf("It's a tie!\n");
}

void get_word(char word[])
{
    printf("Please enter a word: ");

    fgets(word, MAX_WORD_LEN, stdin);
    word[strcspn(word, "\n")] = 0;

    for (int i = 0; word[i]; ++i)
        word[i] = tolower(word[i]);
}

int get_score(char *word)
{
    /* The point for each letter in the alphabet, according to the
     * standard scrabble rules.
     */
    int points[] = {
        1,                      /* a */
        3,                      /* b */
        3,                      /* c */
        2,                      /* d */
        1,                      /* e */
        4,                      /* f */
        2,                      /* g */
        4,                      /* h */
        1,                      /* i */
        8,                      /* j */
        5,                      /* k */
        1,                      /* l */
        3,                      /* m */
        1,                      /* n */
        1,                      /* o */
        3,                      /* p */
        10,                     /* q */
        1,                      /* r */
        1,                      /* s */
        1,                      /* t */
        1,                      /* u */
        4,                      /* v */
        4,                      /* w */
        8,                      /* x */
        4,                      /* y */
        10                      /* z */
    };
    
    /* The sum of a word's points. */
    int score = 0;

    for (int i = 0; i < strlen(word); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == word[i]) {
                score += points[c - 'a'];
                continue;
            }
        }
    }

    return score;
}
