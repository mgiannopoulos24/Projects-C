#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main() {
    int choice;
    initialize();

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add a new book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Borrow a book\n");
        printf("5. Return a book\n");
        printf("6. Register\n");
        printf("7. Login\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                display_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                if (is_user_logged_in()) {
                    borrow_book(get_logged_in_user_id());
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 5:
                if (is_user_logged_in()) {
                    return_book(get_logged_in_user_id());
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 6:
                register_user();
                break;
            case 7:
                login();
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}
