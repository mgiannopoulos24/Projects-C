#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>

#define MAX_BOOKS 500
#define MAX_USERS 50
#define MAX_FILENAME_LENGTH 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Structures
typedef struct {
    int book_id;
    char title[100];
    char author[100];
    int available;
} Book;

typedef struct {
    int user_id;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Function prototypes
void initialize();  // Initialize the library system
void add_book();    // Add a new book to the library
void display_books();  // Display all books in the library
void search_book();   // Search for a book by title or author
void borrow_book(int user_id);  // Borrow a book
void return_book(int user_id);  // Return a borrowed book
void delete_book(int book_id);  // Delete a book from the library
void login();  // User login function
void register_user();  // Register a new user
bool is_user_registered(char *username, char *password);  // Check if a user is registered
int is_user_logged_in();
int get_logged_in_user_id();

void logout();

#endif // LIBRARY_H