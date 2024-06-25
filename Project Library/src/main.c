#include "library.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    initialize();
    int choice;
    int book_id; // Variable to store book_id for delete operation
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Add Book\n");
        printf("4. Display Books\n");
        printf("5. Search Book\n");
        printf("6. Borrow Book\n");
        printf("7. Return Book\n");
        printf("8. Delete Book\n");
        printf("9. Logout\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                login();
                break;
            case 3:
                if (is_user_logged_in()) {
                    add_book();
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 4:
                display_books();
                break;
            case 5:
                search_book();
                break;
            case 6:
                if (is_user_logged_in()) {
                    borrow_book(get_logged_in_user_id());
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 7:
                if (is_user_logged_in()) {
                    return_book(get_logged_in_user_id());
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 8:
                if (is_user_logged_in()) {
                    printf("Enter the ID of the book you want to delete: ");
                    if (scanf("%d", &book_id) == 1) {
                        delete_book(book_id);
                    } else {
                        printf("Invalid input for book ID.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 9:
                logout();
                break;
            case 10:
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
