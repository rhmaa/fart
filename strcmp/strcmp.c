/*
    A simple program which takes two strings from the command line,
    and compares them. If the strings are equal to each other, then
    this program returns a zero value. Note that you must use an
    external program to actually print the results of this comparison.
*/

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;

    /* Count the number of chars in each string. */
    int nr_chars[] = { 0, 0 };
    for (int i = 0; i < 2; ++i)
        for (int j = 0; argv[i + 1][j] != '\0'; ++j)
            ++nr_chars[i];

    /* Check that the strings are of equal length. */
    if (nr_chars[0] != nr_chars[1])
        return 1;

    /* Check that the chars are the same. */
    for (int i = 0; i < nr_chars[0]; ++i)
        if (argv[1][i] != argv[2][i])
            return 1;

    return 0;
}
