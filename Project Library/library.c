#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
Book books[MAX_BOOKS];
User users[MAX_USERS];
int num_books = 0;
int num_users = 0;

// Function prototypes for internal use
void load_books_from_file();
void save_books_to_file();
void load_users_from_file();
void save_users_to_file();

void initialize() {
    num_books = 0;
    num_users = 0;
    load_books_from_file();  // Load books from file on initialization
    load_users_from_file();  // Load users from file on initialization
}

void add_book() {
    if (num_books < MAX_BOOKS) {
        Book new_book;
        printf("Enter book title: ");
        if (scanf(" %[^\n]", new_book.title) != 1) {
            printf("Error reading book title.\n");
            return;
        }
        printf("Enter author name: ");
        if (scanf(" %[^\n]", new_book.author) != 1) {
            printf("Error reading author name.\n");
            return;
        }
        new_book.book_id = num_books + 1;
        new_book.available = 1;  // Assume initially available
        books[num_books++] = new_book;
        printf("Book added successfully!\n");
        save_books_to_file();  // Save books to file after adding
    } else {
        printf("Maximum book limit reached!\n");
    }
}

void display_books() {
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| ID |       Title                               |             Author             |  Availability        |\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("| %-3d | %-40s | %-30s | %-20s |\n", 
               books[i].book_id, 
               books[i].title, 
               books[i].author,
               books[i].available ? "Available" : "Not Available");
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
}

void search_book() {
    char search_term[100];
    printf("Enter search term (title or author): ");
    if (scanf(" %[^\n]", search_term) != 1) {
        printf("Error reading search term.\n");
        return;
    }

    printf("Search results:\n");
    printf("ID,Title,Author,Availability\n");
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (strstr(books[i].title, search_term) || strstr(books[i].author, search_term)) {
            printf("%d,%s,%s,%s\n", books[i].book_id, books[i].title, books[i].author,
                   books[i].available ? "Available" : "Not Available");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the search term.\n");
    }
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    if (scanf(" %[^\n]", username) != 1) {
        printf("Error reading username.\n");
        return;
    }
    printf("Enter password: ");
    if (scanf(" %[^\n]", password) != 1) {
        printf("Error reading password.\n");
        return;
    }

    if (is_user_registered(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void register_user() {
    if (num_users < MAX_USERS) {
        User new_user;
        printf("Enter username: ");
        if (scanf(" %[^\n]", new_user.username) != 1) {
            printf("Error reading username.\n");
            return;
        }
        printf("Enter password: ");
        if (scanf(" %[^\n]", new_user.password) != 1) {
            printf("Error reading password.\n");
            return;
        }
        new_user.user_id = num_users + 1;  // Assign user_id incrementally
        users[num_users++] = new_user;
        save_users_to_file();  // Save users to file after registration
        printf("User registered successfully!\n");
    } else {
        printf("Maximum user limit reached!\n");
    }
}

bool is_user_registered(char *username, char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

void load_books_from_file() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int book_id, available;
        char title[100], author[100];

        if (sscanf(line, "%d|%[^|]|%[^|]|%d", &book_id, title, author, &available) != 4) {
            printf("Error reading data from file.\n");
            continue;
        }

        if (num_books < MAX_BOOKS) {
            Book new_book = {book_id, "", "", 0};  // Initialize a new book structure
            strcpy(new_book.title, title);
            strcpy(new_book.author, author);
            new_book.available = available;

            books[num_books++] = new_book;  // Add the book to the array
        } else {
            printf("Maximum book limit reached.\n");
            break;
        }
    }

    fclose(fp);
}

void save_books_to_file() {
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < num_books; i++) {
        fprintf(fp, "%d|%s|%s|%d\n", books[i].book_id, books[i].title, books[i].author, books[i].available);
    }

    fclose(fp);
}

void load_users_from_file() {
    FILE *fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int user_id;
        char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

        if (sscanf(line, "%d|%[^|]|%s", &user_id, username, password) != 3) {
            printf("Error reading data from file.\n");
            continue;
        }

        if (num_users < MAX_USERS) {
            User new_user = {user_id, "", ""};  // Initialize a new user structure
            strcpy(new_user.username, username);
            strcpy(new_user.password, password);

            users[num_users++] = new_user;  // Add the user to the array
        } else {
            printf("Maximum user limit reached.\n");
            break;
        }
    }

    fclose(fp);
}

void save_users_to_file() {
    FILE *fp = fopen("customers.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%d|%s|%s\n", users[i].user_id, users[i].username, users[i].password);
    }

    fclose(fp);
}

void delete_book(int book_id) {
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (books[i].book_id == book_id) {
            // Shift remaining books to the left to fill the gap
            for (int j = i; j < num_books - 1; j++) {
                books[j] = books[j + 1];
            }
            num_books--;
            found = 1;
            printf("Book deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
    save_books_to_file();  // Save books to file after deletion
}

void edit_book(int book_id) {
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (books[i].book_id == book_id) {
            printf("Enter new title (Enter to keep current): ");
            if (scanf(" %[^\n]", books[i].title) != 1) {
                printf("Error reading title.\n");
                return;
            }
            printf("Enter new author (Enter to keep current): ");
            if (scanf(" %[^\n]", books[i].author) != 1) {
                printf("Error reading author.\n");
                return;
            }
            printf("Enter new availability (0 for not available, 1 for available, Enter to keep current): ");
            if (scanf("%d", &books[i].available) != 1) {
                printf("Error reading availability.\n");
                return;
            }
            found = 1;
            printf("Book information updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
    save_books_to_file();  // Save books to file after editing
}

User *get_logged_in_user() {
    static User logged_in_user;  // Static variable to hold logged in user (persistent across function calls)
    return &logged_in_user;
}

int is_user_logged_in() {
    User *logged_in_user = get_logged_in_user();
    return logged_in_user->user_id != 0;
}

int get_logged_in_user_id() {
    User *logged_in_user = get_logged_in_user();
    return logged_in_user->user_id;
}

void logout() {
    User *logged_in_user = get_logged_in_user();
    logged_in_user->user_id = 0;  // Set user_id to 0 to indicate no user is logged in
    printf("Logged out successfully.\n");
}

void borrow_book(int user_id) {
    if (!is_user_logged_in()) {
        printf("Please login first.\n");
        return;
    }

    int book_id;
    printf("Enter the ID of the book you want to borrow: ");
    if (scanf("%d", &book_id) != 1) {
        printf("Invalid input for book ID.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (books[i].book_id == book_id && books[i].available) {
            books[i].available = 0;  // Mark as not available
            printf("Book '%s' borrowed successfully!\n", books[i].title);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found or not available for borrowing.\n");
    }
    save_books_to_file();  // Save books to file after borrowing
}

void return_book(int user_id) {
    if (!is_user_logged_in()) {
        printf("Please login first.\n");
        return;
    }

    int book_id;
    printf("Enter the ID of the book you want to return: ");
    if (scanf("%d", &book_id) != 1) {
        printf("Invalid input for book ID.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (books[i].book_id == book_id && !books[i].available) {
            books[i].available = 1;  // Mark as available
            printf("Book '%s' returned successfully!\n", books[i].title);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found or not borrowed by you.\n");
    }
    save_books_to_file();  // Save books to file after returning
}

