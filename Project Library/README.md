Library Management System
The Library Management System is a command-line application written in C. It allows users to manage books, register/login users, borrow and return books, search for books, and perform administrative tasks such as adding, deleting, and displaying books.

Features
User Management:

Register new users.
Login/logout functionality.
Track currently logged-in users.
Book Management:

Add new books to the library collection.
Display all books with details (title, author, availability).
Search for books by title or author.
Borrow and return books (for logged-in users).
File Handling:

Data persistence using text files (books.txt for books data, customers.txt for user data).
Automatic loading of existing data on program startup.
Saving data to files after each operation (add, delete, borrow, return).

## Compilation

To compile the project run `make`.

This will produce the `library_system` executable in the `build/` directory.

## Usage
1. Run the compiled executable:

```bash
User@Github:~$ ./build/library_system 
```

2. Follow the on-screen menu to navigate through different options:

- Register new users or login with existing credentials.
- Manage books: add, display, search, borrow, return, delete.
- Logout to switch users or exit the program.

## Example Usage
1. Register a new user:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 1
Enter username: james
Enter password: 123456
User registered successfully!
```

2. Login:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 2   
Enter username: james
Enter password: 123456
Login successful!
```

3. Add a new book:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 3
Enter book title: Python Programming Language
Enter author name:  Berajah Jayne    
Book added successfully!
```

4. Display all books:

```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 4
----------------------------------------------------------------------------------------------------------
| ID |       Title                               |             Author             |  Availability        |
----------------------------------------------------------------------------------------------------------
| 1   | The Catcher in the Rye                   | J.D. Salinger                  | Available            |
| 2   | To Kill a Mockingbird                    | Harper Lee                     | Available            |
.
.
.
.
.
| 98  | The Prince                               | Machiavelli                    | Available            |
| 99  | The Art of War                           | Sun Tzu                        | Available            |
| 100 | The Communist Manifesto                  | Karl Marx                      | Available            |
| 101 | Programming Techniques                   | Robert Sedgewick               | Available            |
| 102 | Python Programming Language              | Berajah Jayne                  | Available            |
----------------------------------------------------------------------------------------------------------
```

5. Search for books:

```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 5
Enter search term (title or author): Gatsby
Search results:
ID,Title,Author,Availability
5,The Great Gatsby,F. Scott Fitzgerald,Available
```
6. Borrow a book:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 6
Enter the ID of the book you want to borrow: 5
Book 'The Great Gatsby' borrowed successfully!
```

We can confirm that a user borrowed the book by looking at the availability of the book.

```txt
1|The Catcher in the Rye|J.D. Salinger|1
2|To Kill a Mockingbird|Harper Lee|1
3|1984|George Orwell|1
4|Pride and Prejudice|Jane Austen|1
5|The Great Gatsby|F. Scott Fitzgerald|0
```

7. Return a book:

```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 7
Enter the ID of the book you want to return: 5
Book 'The Great Gatsby' returned successfully!
```
We can confirm that a user returned the book by looking at the availability of the book.

```txt
1|The Catcher in the Rye|J.D. Salinger|1
2|To Kill a Mockingbird|Harper Lee|1
3|1984|George Orwell|1
4|Pride and Prejudice|Jane Austen|1
5|The Great Gatsby|F. Scott Fitzgerald|1
```
8. Delete Book:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 8
Enter the ID of the book you want to delete: 102
Book deleted successfully.
```
We can see the selected book was removed.
```txt
98|The Prince|Machiavelli|1
99|The Art of War|Sun Tzu|1
100|The Communist Manifesto|Karl Marx|1
101|Programming Techniques|Robert Sedgewick|1
```

9. Logout:

```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 9
Logged out successfully.
```
10. Exit:
```console
Library Management System
1. Register
2. Login
3. Add Book
4. Display Books
5. Search Book
6. Borrow Book
7. Return Book
8. Delete Book
9. Logout
10. Exit
Enter your choice: 10
Exiting the program...
```



