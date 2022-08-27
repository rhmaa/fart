/*
 * This program is an exercise in the use of pointers and references.
 *
 * We have a struct called person, which contains a C-string, and two
 * integers. The C-string denotes the person's name, the integers
 * denote the person's sex and age.
 *
 * This program lets the user grow and shrink a list of people. It
 * lets the user modify the list, without ever having to pass and
 * return the actual values of the list between functions.
 *
 * The user is able to save the list, and load the list. The list is
 * automatically saved when the program exits.
 * 
 * At some point I will experiment with adding some actual menu driven
 * interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

int main()
{
    person *people;
    int nr_people = 3;

    people = malloc(nr_people * sizeof(person));
    if (people == NULL) {
        perror("malloc failed");
        exit(1);
    }

    printf("--- We have made three people ---\n");
    make_person(people, 0, "John", 1, 26);
    make_person(people, 1, "Jennifer", 0, 24);
    make_person(people, 2, "Kate", 0, 32);

    list_people(people, nr_people);

    printf("--- Now we are adding one more ---\n");
    grow_people(&people, &nr_people);
    make_person(people, (nr_people - 1), "Bill", 1, 45);
    list_people(people, nr_people);

    printf("--- And add one more again ---\n");
    grow_people(&people, &nr_people);
    make_person(people, (nr_people - 1), "Jill", 0, 20);
    list_people(people, nr_people);

    printf("--- Now we kill one person ---\n");
    kill_person(people, 0, nr_people);
    shrink_people(&people, &nr_people);
    list_people(people, nr_people);

    printf("--- Now we rename another one ---\n");
    rename_person(people, 3);
    sort_people(people, nr_people);
    list_people(people, nr_people);

    printf("--- We are now killing everyone :o ---\n\n");
    save_people(people, nr_people);
    destroy_people(people, nr_people);
    free(people);

    nr_people = 1;
    people = malloc(nr_people * sizeof(person));
    if (people == NULL) {
        perror("malloc failed");
        exit(1);
    }

    load_people(&people, &nr_people);

    printf("--- But that's ok, because we saved them earlier :D ---\n\n");
    list_people(people, nr_people);

    destroy_people(people, nr_people);
    free(people);

    return 0;

}
