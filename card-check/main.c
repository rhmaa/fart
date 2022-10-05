/***********************************************************************
  A simple program that checks the validity of a credit card number.

  The user enters a credit card number as a command line argument. The
  user must enter a number that is between 13 and 19 digits long.

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
int check_card  (unsigned long);

int main(int argc, char **argv)
{
    if (check_input(argv[1]) == 1) {
        printf("usage: %s [%d-%d digits]\n", argv[0], MIN_CARD_LEN, MAX_CARD_LEN);
        return 1;
    }

    unsigned long card_num = strtol(argv[1], NULL, 10);

    if (check_card(card_num) == 1)
        printf("The credit card number is invalid.\n");
    else
        printf("The credit card number is valid.\n");

    return 0;
}

int check_input(char *input)
{
    /* Check if the input is long enough to be a valid number.
     */
    if (!(MIN_CARD_LEN <= strlen(input) && strlen(input) <= MAX_CARD_LEN))
        return 1;

    /* Check if the input contains anything other than digits. If any
     * of the characters in the input are not within the ASCII range
     * for digits, the input is not a number.
     */
    for (int i = 0; i < strlen(input); ++i)
        if (!(48 <= input[i] && input[i] <= 58))
            return 1;

    return 0;
}

int check_card(unsigned long card_num)
{
    int sum = 0;
    
    /* Check the validity of the number according to Luhn's algorithm:
     * https://en.wikipedia.org/wiki/Luhn_algorithm
     */
    while (card_num > 0) {
        /* Add the digits that we'll not be multiplying to sum. */
        sum += card_num % 10;
        card_num = card_num / 10;
        
        /* Multiply every other digit by 2, starting with the number's
         * second-to-last digit. Add the digits of the product to sum.
         */
        int product = (card_num % 10) * 2;
        card_num = card_num / 10;
        while (product > 0) {
            sum += product % 10;
            product /= 10;
        }
    }

    /* If the sum is divisible by 10, the number is valid. */
    return (sum % 10 == 0) ? 0 : 1;
}
