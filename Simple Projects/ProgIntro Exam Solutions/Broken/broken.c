#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value[128];
    struct node * next;
} Elem;

int listdelete(char value[], Elem ** head) {
    Elem * tmp;

    while (*head && strcmp((*head)->value, value)) {
        head = &((*head)->next);
    }

    if (*head) {
        tmp=*head;
        *head = tmp->next;
        free(tmp);
        return 1;
    }
    return -1;
}

int listadd(char value[], Elem ** head) {
    Elem * new = malloc(sizeof(Elem));
    if (new == NULL) {
        return 0;
    }
    Elem * tmp;
    tmp=*head;
    *head=new;
    new->next=tmp;
    strncpy(new->value, value, 127);
    return 1;
}

void listprint(Elem * list) {
  while(list) {
    printf("%s -> ", list->value);
    list = list->next;
  }
  printf("NULL\n");
}

int main() {

    Elem elem1 = {"bruh", NULL};
    Elem * head = &elem1;

    listadd("yee", &head);
    listadd("yesss!", &head);
    listprint(head);
    printf("listdelete: %d\n", listdelete("bruh", &head));
    listprint(head);
    return 0;
}

// Το λάθος είναι στη συνάρτηση listdelete, η γραμμή:
// while (*head && strcmp((*head)->value, value)) {
//     head = &((*head)->next);
// }
//
// Εδώ, ο δείκτης head είναι τύπου Elem **. Όταν χρησιμοποιείς head για να εξετάσεις ή να τροποποιήσεις τη λίστα, το head τροποποιείται έτσι ώστε να δείχνει στον επόμενο κόμβο. Αυτό σημαίνει ότι κατά τη διάρκεια της επανάληψης της while, τροποποιείς τον δείκτη head, ο οποίος τελικά δεν δείχνει στην αρχή της λίστας. Αυτό δημιουργεί πρόβλημα όταν προσπαθείς να διαγράψεις έναν κόμβο.
// Ειδικότερα, η τροποποίηση του head κατά τη διάρκεια της επανάληψης επηρεάζει τη σύνδεση με την υπόλοιπη λίστα, και έτσι μπορεί να χαθεί η αναφορά στην αρχή της λίστας ή να προκύψει σφάλμα όταν προσπαθείς να ελευθερώσεις τη μνήμη.
//
// Θα πρέπει να χρησιμοποιήσεις ένα δεύτερο δείκτη για να διατηρήσεις την αρχή της λίστας και να τροποποιήσεις μόνο τον επόμενο δείκτη του τρέχοντος κόμβου, χωρίς να αλλάξεις τον δείκτη προς την αρχή της λίστας. Αυτό επιτρέπει τη διατήρηση της σωστής αναφοράς στην αρχή της λίστας και την σωστή διαγραφή του κόμβου.
// Για την επίλυση, θα πρέπει να αναθεωρήσεις τη λογική του while loop και να διαχειριστείς την αλλαγή των δεικτών σωστά ώστε να διατηρείς τη σύνδεση με την υπόλοιπη λίστα ενώ διαγράφεις τον κόμβο.