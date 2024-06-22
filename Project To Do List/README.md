# To-Do List Program
This is a simple command-line to-do list application written in C. It allows users to add tasks, view tasks, remove tasks, and persists tasks in a text file between sessions.

## Features
- Add tasks with descriptions.
- View all tasks currently in the list.
- Remove tasks by specifying their index.
- Tasks are saved to tasks.txt on exit and loaded from it on startup.

## Compilation
Compile the program using `make`.

This will compile the source files and generate the executable in the build directory (build/todo_list).


## Running the Program
To run the program, execute the compiled executable:

```bash
./build/todo_list
```

## Usage
- Choose options from the menu to add tasks, view tasks, remove tasks, or exit the program.
- Tasks are automatically saved to tasks.txt when exiting and loaded from it on startup.
## Cleaning Up
To clean up generated files (object files and executable), run:

```bash
make clean
```

## Example 
```bash
User@Github:~$ ./build/todo_list 

===== To-Do List Menu =====
1. Add Task
2. View Tasks
3. Remove Task
4. Exit
Enter your choice: 1
Enter task to add: Finish Homework
Task added successfully.

===== To-Do List Menu =====
1. Add Task
2. View Tasks
3. Remove Task
4. Exit
Enter your choice: 2
===== Tasks =====
1. Finish Homework

===== To-Do List Menu =====
1. Add Task
2. View Tasks
3. Remove Task
4. Exit
Enter your choice: 3
Enter index of task to remove: 1
Task removed successfully.

===== To-Do List Menu =====
1. Add Task
2. View Tasks
3. Remove Task
4. Exit
Enter your choice: 4
Saving tasks and exiting program.
```

## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your suggested changes.