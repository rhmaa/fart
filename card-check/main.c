/***********************************************************************
  A simple program that checks the validity of a credit card number.

  The user enters a credit card number as a command line argument. The
  user must enter only one number, and it must be 16 digits long.

  The program then checks the validity of the number according to
  Luhn's algorithm. A message is printed to the user, stating if the
  number is valid or invalid.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A credit card number consists of 13 to 19 digits. */
#define MIN_CARD_LEN 13
#define MAX_CARD_LEN 19

int check_input (char *);
int check_card  (unsigned long, int);

int main(int argc, char **argv)
{
    /* Validate the user's input. */
    if (check_input(argv[1]) == 1) {
        printf("usage: %s [%d-%d DIGIT INTEGER]\n",
               MIN_CARD_LEN, MAX_CARD_LEN, argv[0]);
        return 1;
    }

    unsigned long card_num = strtol(argv[1], NULL, 10);

    if (check_card(card_num, strlen(argv[1])) == 1)
        printf("The credit card number is invalid.\n");
    else
        printf("The credit card number is valid.\n");

    return 0;
}

int check_input(char *input)
{
    /* Check if the user's argument is between 13 and 19 characters long. */
    if (!(MIN_CARD_LEN <= strlen(input) && strlen(input) <= MAX_CARD_LEN))
        return 1;

    /* Check if the user's argument contains anything other than
     * digits. If any of the characters in the argument are not within
     * the ASCII range for digits, the user's input is not a number.
     */
    for (int i = 0; i < strlen(input); ++i)
        if (!(48 <= input[i] && input[i] <= 58))
            return 1;

    return 0;
}

int check_card(unsigned long card_num, int card_len)
{
    /* We check the validity of the credit card number according to
     * Luhn's algorithm: https://en.wikipedia.org/wiki/Luhn_algorithm
     */
    int sum = 0;

    int *products = malloc(sizeof(int) * (card_len / 2));
    if (products == NULL) {
        perror("malloc in check_card() failed");
        exit(1);
    }

    for (int i = 0; i < card_len / 2; ++i) {
        /* Add the digits that we'll not be multiplying to sum. */
        sum += card_num % 10;
        card_num /= 10;
        
        /* Multiply every other digit by 2, starting with the credit
         * card number's second-to-last digit. Then add the digits of
         * the products to sum.
         */
        products[i] = (card_num % 10) * 2;
        card_num /= 10;
        while (products[i]) {
            sum += products[i] % 10;
            products[i] /= 10;
        }
    }

    free(products);

    /* If the calculated sum is divisible by 10, then the credit card
     * number is valid according to Luhn's algorithm.
     */
    if (sum % 10 == 0)
        return 0;
    else
        return 1;
}
