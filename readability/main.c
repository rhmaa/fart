/*************************************************************************
  A simple program that calculates the reading level for any text.

  TODO: Rewrite this program so that we no longer read the entire file
  into memory. The current implementation creates more limitations
  than is needed.
 *************************************************************************/

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_text          (char *, char **);
void count_sentences   (char *, int *);
void count_words       (char *, int *);
void count_letters     (char *, int *);
void get_reading_level (int, int, int, double *);

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s [FILEPATH]\n", argv[0]);
        return 1;
    }

    /* The text that we will determine the readability score of. */
    char *text;

    /* The number of sentences in the text. */
    int nr_sentences = 0;

    /* The number of words in the text. */
    int nr_words = 0;

    /* The number of characters in the text (excluding whitespace and
     * punctuation).
     */
    int nr_letters = 0;

    /* The reading level of the text. */
    double reading_level;

    get_text(argv[1], &text);

    count_sentences(text, &nr_sentences);
    count_words(text, &nr_words);
    count_letters(text, &nr_letters);

    get_reading_level(nr_sentences, nr_words, nr_letters, &reading_level);
    printf("Reading Level: %.f\n", reading_level);

    free(text);

    return 0;
}

void get_reading_level(int nr_sentences, int nr_words, int nr_letters, double *reading_level)
{
    double l = (double)nr_letters / nr_words * 100;
    double s = (double)nr_sentences / nr_words * 100;
    *reading_level = 0.0588 * l - 0.296 * s - 15.8;
}

void count_letters(char *text, int *nr_letters)
{
    for (int i = 0; text[i]; ++i)
        if (!(isspace(text[i]) || ispunct(text[i])) && (text[i] & 0xc0) != 0x80)
            ++(*nr_letters);
}

void count_words(char *text, int *nr_words)
{
    for (int i = 0; text[i]; ++i)
        if (isspace(text[i]) && !(isspace(text[i + 1])))
            ++(*nr_words);
}

void count_sentences(char *text, int *nr_sentences)
{
    for (int i = 0; text[i]; ++i)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            ++(*nr_sentences);
}

void get_text(char *filepath, char **text)
{
    /* The file from which we read our text. */
    FILE *stream;

    stream = fopen(filepath, "r");
    if (stream == NULL) {
        fprintf(stderr, "failed to open %s\n", filepath);
        exit(1);
    }

    char *tmp;
    tmp = calloc(sizeof(char), INT_MAX);
    if (tmp == NULL) {
        perror("tmp calloc in get_text failed");
        exit(1);
    }
    
    fread(tmp, INT_MAX, sizeof(char), stream);

    *text = malloc(strlen(tmp));
    if (*text == NULL) {
        perror("text malloc in get_text failed");
        exit(1);
    }
    
    strncpy(*text, tmp, strlen(tmp));

    free(tmp);
    fclose(stream);
}
