#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

void make_person(person *people, int index, char *name, int sex, int age)
{
    people[index].name = malloc(strlen(name) * sizeof(char));
    if (people[index].name == NULL) {
        perror("failed to malloc people[index].name");
        exit(1);
    }

    strncpy(people[index].name, name, strlen(name));

    people[index].sex  = sex;
    people[index].age  = age;
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

    tmp = realloc(*people, (*nr_people - 1) * sizeof(person));
    if (tmp == NULL) {
        perror("realloc in grow_people() failed");
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
    for (int i = 0; i < nr_people; ++i) {
        printf("My name is %s, I am a %s, and I am %d years old\n",
               people[i].name, people[i].sex ? "boy" : "girl",
               people[i].age);
    }
    printf("\n");
}

void destroy_people(person *people, int nr_people)
{
    for (int i = 0; i < nr_people; ++i)
        kill_person(people, i, nr_people);
}

void rename_person(person *people, int index)
{
    char name[MAX_STR_LENGTH];
    printf("Please enter %s's new name: ", people[index].name);
    if (fgets(name, MAX_STR_LENGTH, stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
        strncpy(people[index].name, name, strlen(name));
    } else {
        fprintf(stderr, "fgets could not write to name");
        exit(1);
    }
}

void save_people(person *people, int nr_people)
{
    FILE *savefile;
    char filepath[MAX_STR_LENGTH];

    /* Determine which directory to place the save file in, depending
     * on the type of operating system that the user has. If they're
     * not on Windows, then we assume they are using a Unix system.
     */
    #ifdef _WIN32
        strcpy(filepath, "\%userprofile\%\\AppData\\Local\\Temp\\people");
    #else
        strcpy(filepath, "/tmp/people");
    #endif

    savefile = fopen(filepath, "w+");

    fprintf(savefile, "%d\n", nr_people);

    for (int i = 0; i < nr_people; ++i) {
        fprintf(savefile, "%s\n", people[i].name);
        fprintf(savefile, "%d\n", people[i].sex);
        fprintf(savefile, "%d\n", people[i].age);
    }

    fclose(savefile);
}

void load_people(person **people, int *nr_people)
{
    FILE *savefile;

    char filepath[MAX_STR_LENGTH];

    /* Determine which directory to place the save file in, depending
     * on the type of operating system that the user has. If they're
     * not on Windows, then we assume they are using a Unix system.
     */
    #ifdef _WIN32
        strcpy(filepath, "\%userprofile\%\\AppData\\Local\\Temp\\people");
    #else
        strcpy(filepath, "/tmp/people");
    #endif

    savefile = fopen(filepath, "r");
    fscanf(savefile, "%d", nr_people);

    person *tmp;

    tmp = realloc(*people, (*nr_people) * sizeof(person));
    if (tmp == NULL) {
        perror("realloc in grow_people() failed");
        exit(1);
    } else {
        *people = tmp;
    }

    char name[MAX_STR_LENGTH];
    unsigned int sex;
    unsigned int age;

    for (int i = 0; i < *nr_people; ++i) {
        fscanf(savefile, "%s", &name);
        fscanf(savefile, "%d", &sex);
        fscanf(savefile, "%d", &age);
        make_person(*people, i, name, sex, age);
    }
    
    fclose(savefile);
}

void birthday(person *people, int index)
{
    ++(people[index].age);
}

void get_name(char *name)
{
    printf("Please enter the person's name: ");
    if (fgets(name, MAX_STR_LENGTH, stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
    } else {
        perror("fgets could not write to name");
        exit(1);
    }
}

void get_sex(unsigned int *sex)
{
    printf("Please enter the person's sex (0 for female or 1 for male): ");

    while (get_int(sex) != 0) {
        printf("error: Expected integer input.\n");
        printf("Please enter a valid age: ");
    }

    while (!(0 <= *sex && *sex <= 1)) {
        get_int(sex);
    }
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
     * most. This is a simple function that should be somewhat more
     * safer than the default methods.
     */

	char *buffer;

    buffer = malloc(MAX_STR_LENGTH * sizeof(char));
    if (buffer == NULL) {
        perror("failed to malloc buffer");
        exit(1);
    }

	fgets(buffer, MAX_STR_LENGTH, stdin);
	buffer[strcspn(buffer, "\n")] = 0;


    /* Check if the characters are digits or not. If the characters
	 * are not within the ASCII range for digits, this function
	 * returns a non-zero value.
	 */
	int is_digit = 1;

	for (int i = 0; i < strlen(buffer); ++i)
		if (!(48 <= buffer[i] && buffer[i] <= 58))
			is_digit = 0;

	if (is_digit) {
		*a = atoi(buffer);
        free(buffer);
		return 0;
	} else {
        free(buffer);
		return 1;
	}
}
