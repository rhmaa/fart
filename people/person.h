#ifndef PERSON_H_
#define PERSON_H_

/* It's very unlikely that we'll have strings longer than 1024 in this
 * program.
 */
#define MAX_STR_LENGTH 1024

typedef struct {
    char *name;          /* The name of the person */
    unsigned int sex;    /* 0 = female, 1 = male   */
    unsigned int age;    /* The age of the person  */
} person;

void make_person    (person *,  int);
void edit_person    (person *,  int);
void load_person    (person *,  int, char *, int, int);
void kill_person    (person *,  int, int);
void grow_people    (person **, int *);
void shrink_people  (person **, int *);
void sort_people    (person *,  int);
void list_people    (person *,  int);
void rename_person  (person *,  int);
void save_people    (person *,  int);
int  load_people    (person **, int *);
void destroy_people (person *,  int);
void birthday       (person *,  int);

void get_name (char *);
void get_sex  (unsigned int *);
void get_age  (unsigned int *);

int  get_int  (int *);

#endif /* PERSON_H_ */
