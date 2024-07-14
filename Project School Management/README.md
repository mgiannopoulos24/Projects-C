# School Management System
The School Management System is a console-based application written in C that allows users to manage student records. It provides functionalities such as adding students, finding students by various criteria, updating and deleting student records, and saving the student data to a file.

## Features
1. Add Student
- Allows the user to input student details including roll number, first name, last name, course, and age. The student is then added to the system.
2. Find Student by Roll Number
- Enables searching for a student by their unique roll number and displays their details if found.
3. Find Student by First Name
- Searches for students by their first name and displays details of all students matching the search criteria.
4. Find Students by Course
- Finds all students enrolled in a specific course and displays their details.
5. Display Student Count
- Shows the total number of students currently stored in the system.
6. Delete Student
- Allows the user to delete a student record by specifying the roll number.
7. Update Student
- Enables updating of student details such as first name, last name, course, and age based on the roll number.
8. Exit
- Terminates the program.
## File Handling
Student records are stored in a text file named `students.txt`. Each student's information is stored in a new line in the format: `rollNumber firstName lastName course age`.
## Usage
1. Compilation
Compile the program using the provided Makefile:
```console
make
```

2. Running the Program

Execute the compiled program:

```console
User@Github:~$ ./build/school_management
```
3. Menu Navigation

Follow the on-screen prompts to navigate through different functionalities
```console
School Management System
1. Add Student
2. Find Student by Roll Number
3. Find Student by First Name
4. Find Students by Course
5. Display Student Count
6. Delete Student
7. Update Student
8. Exit
Enter your choice:
```

4. Input Guidelines

- Follow the instructions for each menu option to input data correctly.
- Ensure to handle spaces in course names appropriately.
5. Saving Changes
Student data is automatically saved to students.txt each time a new student is added or an existing record is updated or deleted.