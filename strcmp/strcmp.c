/*
 * This program takes two strings from the command line, and compares
 * them. If the strings are equal, then this program returns a zero
 * value. Note that you must use an external program to actually print
 * the results of this comparison.
 * 
 * If the strings are equal, return 0. If the strings are not equal,
 * return -1. If the user has entered an incorrect number of strings,
 * return 1.
 */

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;

    const char *s1 = argv[1];
    const char *s2 = argv[2];

    for (; *s1 == *s2; ++s1, ++s2)
        if (*s1 == '\0')
            return 0;

    return -1;
}
