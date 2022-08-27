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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

int  menu         (person **, int *);
int  get_menu_ans ();
void get_index    (int, int *);

int main()
{
    /* The number of people that exists in the list. */
    int nr_people = 0;

    /* The list of people to manage. */
    person *people;
    people = calloc(nr_people, sizeof(person));
    if (people == NULL) {
        perror("malloc in main() failed");
        exit(1);
    }

    /* If we have a save file, then read the contents. */
    if (load_people(&people, &nr_people) != 0)
        ;

    int is_running = 1;
    while (is_running)
        is_running = menu(&people, &nr_people);

    save_people(people, nr_people);
    destroy_people(people, nr_people);
    free(people);

    return 0;
}

int menu(person **people, int *nr_people)
{
    /* Stores the index of the person that the user wishes to edit. */
    int index;

    /* Stores the user's menu choice. */
    int ans = get_menu_ans();

    switch (ans) {
    case 1:
        grow_people(people, nr_people);
        make_person(*people, (*nr_people - 1));
        save_people(*people, *nr_people);
        break;
        
    case 2:
        get_index(*nr_people, &index);
        edit_person(*people, index);
        save_people(*people, *nr_people);
        break;

    case 3:
        get_index(*nr_people, &index);
        kill_person(*people, index, *nr_people);
        shrink_people(people, nr_people);
        save_people(*people, *nr_people);
        break;
        
    case 4:
        sort_people(*people, *nr_people);
        list_people(*people, *nr_people);
        break;

    case 0:
        return 0;
    }
    return 1;
}

int get_menu_ans()
{
    int ans = 0;
    
    do {
        printf("\n");
        printf("1. Add person\n");
        printf("2. Edit person\n");
        printf("3. Delete a person\n");
        printf("4. List people\n");
        printf("0. Exit\n");

        printf("i: ");
        if (get_int(&ans) != 0)
            printf("error: Expected an integer.\n");
    } while (!(0 <= ans && ans <= 4));
    printf("\n");

    return ans;
}

void get_index(int nr_people, int *index)
{
    printf("Enter the index of the person to delete: ");
    do {
        if (get_int(index) != 0) {
            printf("error: Invalid input.\n");
            printf("Please enter an index between 0 and %d: ", nr_people - 1);
        }
    } while (!(0 <= *index && *index < nr_people));
}
