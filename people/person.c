#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

void make_person(person *people, int index)
{
    people[index].name = calloc(MAX_STR_LEN, sizeof(char));
    if (people[index].name == NULL) {
        perror("calloc in make_person() failed");
        exit(1);
    }
    edit_person(people, index);
}

void edit_person(person *people, int index)
{
    char name[MAX_STR_LEN];
    int  sex;
    int  age;

    get_name(name);
    get_sex(&sex);
    get_age(&age);

    memset(people[index].name, 0, strlen(people[index].name));
    char *tmp = realloc(people[index].name, strlen(name));
    if (tmp == NULL) {
        perror("realloc in edit_person failed");
        exit(1);
    }
    people[index].name = tmp;
    strncpy(people[index].name, name, strlen(name));
    people[index].sex = sex;
    people[index].age = age;
}

void load_person(person *people, int index, char *name, int sex, int age)
{
    people[index].name = calloc(strlen(name), sizeof(char));
    if (people[index].name == NULL) {
        perror("calloc in load_person() failed");
        exit(1);
    }

    strncpy(people[index].name, name, strlen(name));
    people[index].sex = sex;
    people[index].age = age;
}

void kill_person(person *people, int index, int nr_people)
{
    /* If the deleted person is not the last person in the list of
     * people, then we need to move all the other people one step left
     * in memory.
     */
    if (!(index == nr_people - 1)) {
        for (int i = index; i < nr_people - 1; ++i) {
            people[i].name = people[i+1].name;
            people[i].sex  = people[i+1].sex;
            people[i].age  = people[i+1].age;
        }
    }

    /* Regardless of if we had to move people or not, we need to
     * nullify the last element in the arrray.
     */
    people[nr_people-1].name = NULL;
    people[nr_people-1].sex  = 0;
    people[nr_people-1].age  = 0;

    /* And then we have to free the memory that the person's name
     * held.
     */
    free(people[nr_people-1].name);
}

void grow_people(person **people, int *nr_people)
{
    person *tmp;

    tmp = realloc(*people, (*nr_people + 1) * sizeof(person));

    if (tmp == NULL) {
        perror("realloc in grow_people() failed");
        exit(1);
    } else {
        *people = tmp;
        ++(*nr_people);
    }
}

void shrink_people(person **people, int *nr_people)
{
    person *tmp;

    if (*nr_people > 1)
        tmp = realloc(*people, (*nr_people - 1) * sizeof(person));

    if (tmp == NULL) {
        perror("realloc in shrink_people() failed");
        exit(1);
    } else {
        *people = tmp;
        --(*nr_people);
    }
}

void sort_people(person *people, int nr_people)
{
    person tmp;

    /* Sort the list of people alphabetically. Use bubble sort. */
    for (int i = 0; i < nr_people - 1; ++i) {
        for (int j = 0; j < nr_people - 1; ++j) {
            if (strcmp(people[j].name, people[j+1].name) > 0) {
                tmp = people[j+1];
                people[j+1] = people[j];
                people[j] = tmp;
            }
        }
    }
}

void list_people(person *people, int nr_people)
{
    if (nr_people != 0) {
        for (int i = 0; i < nr_people; ++i)
            printf("%d\t%s\t%s\t%d\n", i, people[i].name, people[i].sex ? "M" : "F", people[i].age);
    } else {
        printf("No people to print.\n");
    }
}

void destroy_people(person *people, int nr_people)
{
    for (int i = 0; i < nr_people; ++i)
        kill_person(people, i, nr_people);
}

void rename_person(person *people, int index)
{
    char name[MAX_STR_LEN];
    printf("Please enter %s's new name: ", people[index].name);
    if (fgets(name, MAX_STR_LEN, stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;

        /* When we enter a name that is shorter than the original
         * name, the last letters of the first name will still be
         * present in the person's name.
         */
        memset(people[index].name, 0, strlen(people[index].name));
        char *tmp = realloc(people[index].name, strlen(name));
        if (tmp == NULL) {
            perror("realloc in rename_person failed");
            exit(1);
        }
        people[index].name = tmp;
        strncpy(people[index].name, name, strlen(name));
    } else {
        perror("fgets in rename_person could not write to name");
        exit(1);
    }
}

void save_people(person *people, int nr_people)
{
    FILE *savefile;

    char filepath[MAX_STR_LEN];
    strcpy(filepath, SAVEFILE);

    savefile = fopen(filepath, "w+");

    fprintf(savefile, "%d\n", nr_people);

    for (int i = 0; i < nr_people; ++i) {
        fprintf(savefile, "%s\n", people[i].name);
        fprintf(savefile, "%d\n", people[i].sex);
        fprintf(savefile, "%d\n", people[i].age);
    }

    fclose(savefile);
}

int load_people(person **people, int *nr_people)
{
    FILE *savefile;

    char filepath[MAX_STR_LEN];
    strcpy(filepath, SAVEFILE);

    if (savefile = fopen(filepath, "r"))
        fscanf(savefile, "%d", nr_people);

    if (*nr_people > 0) {
        person *tmp;

        tmp = realloc(*people, (*nr_people) * sizeof(person));
        if (tmp == NULL) {
            perror("realloc in grow_people() failed");
            exit(1);
        } else {
            *people = tmp;
        }

        char name[MAX_STR_LEN];
        unsigned int sex;
        unsigned int age;

        for (int i = 0; i < *nr_people; ++i) {
            fscanf(savefile, "%s", &name);
            fscanf(savefile, "%d", &sex);
            fscanf(savefile, "%d", &age);
            load_person(*people, i, name, sex, age);
        }
    
        fclose(savefile);

        return 0;
    } else {
        return 1;
    }
}

void birthday(person *people, int index)
{
    ++(people[index].age);
}

void get_name(char *name)
{
    printf("Please enter the person's name: ");
    if (fgets(name, MAX_STR_LEN, stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
    } else {
        perror("fgets in get_name could not write to name");
        exit(1);
    }
}

void get_sex(unsigned int *sex)
{
    printf("Please enter the person's sex (0 for female or 1 for male): ");
    do {
        if (get_int(sex) != 0) {
            printf("error: Expected an integer input.\n");
            printf("Please enter a valid sex: ");
        } else if (!(0 <= *sex && *sex <= 1)) {
            printf("error: Expected 0 for female or 1 for male.\n");
            printf("Please enter a valid sex: ");
        }
    } while (!(0 <= *sex && *sex <= 1));
}

void get_age(unsigned int *age)
{
    printf("Please enter the person's age: ");
    while (get_int(age) != 0) {
        printf("error: Expected integer input.\n");
        printf("Please enter a valid age: ");
    }
}

int get_int(int *a)
{
    /* Taking integer input from the user in C is unreliable at
     * most. This is a simple function that should be somewhat safer
     * than the default methods.
     */
    char buffer[MAX_STR_LEN];

    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    /* Check if the characters are digits or not. If the characters
     * are not within the ASCII range for digits, this function
     * returns a non-zero value.
     */
    for (int i = 0, n = strlen(buffer); i < n; ++i)
        if (!(48 <= buffer[i] && buffer[i] <= 58))
            return 1;

    *a = atoi(buffer);
    return 0;
}
