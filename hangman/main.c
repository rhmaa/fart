/***********************************************************************
  A simple hangman game.
  
  A list of words are read from a file provided by the player. A
  random word is picked, and the player has to guess which word it is.

  The game is over when the player has guessed the correct word, or
  when they've run out of chances.
 ***********************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* According to Google, the longest word in the English language is 45
 * characters long.
 * www.britannica.com/dictionary/eb/qa/The-Longest-Word-in-the-Dictionary
 */
#define MAX_WORD_LEN 45

/* The number of chances that the user has to guess the right word. */
#define NR_CHANCES   8

char ** load_words    (char **, char *);
char *  get_rand_word (char **);
int     go_bananas    (char *);
int     check_guess   (char, char *, char *);
void    print_guesses (char *);
void    get_guess     (char *);

int main(int argc, char **argv)
{
    /* The list of words from which we will pick a random word. */
    char **words;
    
    /* The random word that the player has to guess. */
    char *rand_word;

    /* The full path to the file from which we get our words. */
    char *filepath;

    if (argc != 2) {
        printf("usage: %s [FILE]\n", argv[0]);
        return 1;
    } else {
        filepath = calloc(strlen(argv[1]), sizeof(char));
        if (filepath == NULL) {
            perror("calloc in main failed");
            return 1;
        } else {
            strncpy(filepath, argv[1], strlen(argv[1]));
        }
    }

    /* Load the words from a file and pick one at random. */
    words = load_words(words, filepath);
    if (words == NULL) {
        perror("load_words in main failed");
        return 1;
    }

    rand_word = get_rand_word(words);

    /* Run the game loop. */
    int has_won = go_bananas(rand_word);

    if (has_won)
        printf("Congratulations, you won!\n\n");
    else
        printf("Better luck next time, cunt!\n\n");

    free(filepath);
    free(rand_word);
    free(words);
    
    return 0;
}

int go_bananas(char *word)
{
    /* The number of chances that the player has used. After each
     * wrong guess, increment by one.
     */
    int chances_used = 0;

    /* The player's guess, compared against every character in
     * word.
     */
    char guess;

    /* The player's correct guesses. When guesses == word, the player
     * has won.
     */
    char *guesses;

    guesses = calloc(strlen(word), sizeof(char));
    if (guesses == NULL) {
        perror("calloc in go_bananas failed");
        exit(1);
    } else {
        memset(guesses, '_', strlen(word));
    }

    while (chances_used < NR_CHANCES) {
        printf("\nYou have %d %s left.\n", NR_CHANCES - chances_used,
               (NR_CHANCES - chances_used == 1) ? "chance" : "chances");

        print_guesses(guesses);

        printf("Your guess: ");
        guess = 0;
        get_guess(&guess);

        if (check_guess(guess, guesses, word) == 1)
            ;
        else
            ++chances_used;

        if (strcmp(guesses, word) == 0) {
            print_guesses(guesses);
            free(guesses);
            return 1;
        }
    }

    print_guesses(guesses);
    free(guesses);

    return 0;
}

int check_guess(char guess, char *guesses, char *word)
{
    int is_correct = 0;

    for (int i = 0; i < strlen(word); ++i) {
        if (guess == word[i]) {
            guesses[i] = guess;
            is_correct = 1;
        }
    }

    return is_correct;
}

void get_guess(char *guess)
{
    char buffer[MAX_WORD_LEN];

    fgets(buffer, MAX_WORD_LEN, stdin);

    /* If the player has typed one character, and then pressed enter,
     * the buffer should contain two characters (whatever the player
     * typed and '\n'. If it contains more, then it means the player
     * entered more than just one character before hitting enter. If
     * it contains less, then the player just pressed enter.
     */
    if (strlen(buffer) != 2)
        printf("\nYou must type one letter, you naughty boy.\n");
    else
        *guess = tolower(buffer[0]);
}

void print_guesses(char *guesses)
{
    printf("\n");
    
    for (int i = 0; i < strlen(guesses); ++i)
        printf("%c ", guesses[i]);

    printf("\n\n");
}

char ** load_words(char **words, char *filepath)
{
    /* The file from which we read the list of words. */
    FILE *fp;

    /* The number of lines in the text file. */
    int nr_lines = 0;

    /* A character read from the file. c is compared against '\n',
     * which is how we determine where a line ends.
     */
    int c = 0;

    /* A word read from the file, stored here temporarily before being
     * saved to words.
     */
    char tmp[MAX_WORD_LEN];

    fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "fopen failed to open the file %s", filepath);
        return NULL;
    }

    /* Get the number of lines in the file. Using this method means
     * that the last word in the file has to end with a newline
     * character, otherwise it will not be counted.
     */
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            ++nr_lines;

    words = malloc(sizeof(char *) * nr_lines);
    if (words == NULL) {
        perror("malloc in load_words failed");
        return NULL;
    }

    rewind(fp);

    for (int i = 0; i < nr_lines; ++i) {
        fgets(tmp, MAX_WORD_LEN, fp);
        words[i] = calloc(strlen(tmp) - 1, sizeof(char));
        if (words[i] == NULL) {
            fprintf(stderr, "calloc failed to allocate words[%d]\n", i);
            return NULL;
        } else {
            tmp[strcspn(tmp, "\n")] = 0;
            strncpy(words[i], tmp, strlen(tmp));
        }
    }

    fclose(fp);
    return words;
}

char * get_rand_word(char **words)
{
    srand(time(NULL));

    int nr_words = sizeof(*words) / sizeof(*words[0]);
    int rand_index = rand() % nr_words;

    return words[rand_index];
}
