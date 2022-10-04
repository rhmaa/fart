#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A credit card consists of 16 digits. */
#define CARD_NUM_LEN 16

int check_card(unsigned long);

int main(int argc, char **argv)
{
    /* The user must have entered a credit card number, and it must
     * have 16 digits in it.
     */
    if (argc != 2 || strlen(argv[1]) != CARD_NUM_LEN) {
        printf("usage: %s [16 digit number]\n\n", argv[0]);
        return 1;
    }

    unsigned long card_num = strtol(argv[1], NULL, 10);

    /* Check if the credit card is valid. */
    if (check_card(card_num))
        printf("The credit card number is invalid.\n");
    else
        printf("The credit card number is valid.\n");

    return 0;
}

int check_card(unsigned long card_num)
{
    int sum                        = 0;
    int products[CARD_NUM_LEN / 2] = {};

    for (int i = 0; i < CARD_NUM_LEN / 2; ++i) {
        /* Add the digits that we'll not be multiplying by 2 to sum.
         */
        sum += card_num % 10;
        card_num /= 10;
        
        /* Multiply every other digit by 2, starting with the credit
         * card number's second-to-last digit.
         */
        products[i] = (card_num % 10) * 2;
        card_num /= 10;

        /* Add the digits of the calculated products to sum. */
        while (products[i]) {
            sum += products[i] % 10;
            products[i] /= 10;
        }
    }

    /* If the calculated sum is evenly divisible by 10, then the
     * credit card number is valid according to Luhn's algorithm.
     */
    if (sum % 10 == 0)
        return 0;
    else
        return 1;
}
