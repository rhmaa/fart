#include <stdio.h>

int get_str_len(const char *);

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    else
        printf("%d\n", get_str_len(argv[1]));

    return 0;
}

int get_str_len(const char *s)
{
    register const char *tmp;
    for (tmp = s; *tmp; ++tmp);
    return tmp - s;
}
