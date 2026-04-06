# Online Voting System

This project provides a secure online voting system implemented in C. It includes functionality to manage candidates and voters, authenticate voters with passwords, cast votes, and persist election data across sessions.

## Files
The project consists of the following files and directories:

- `src/main.c`: Contains the main function with an interactive CLI menu for managing the election lifecycle and user interactions.

- `src/voting.c`: Implementation file that defines all voting logic, including candidate/voter management, authentication, vote casting, persistence, and election state transitions.

- `include/voting.h`: Header file that declares the data structures (`Candidate`, `Voter`, `Election`, `ElectionState`) and all function prototypes used throughout the project.

- `Makefile`: Makefile for compiling the project, organizing object files into the `obj/` directory, outputting the binary to `bin/`, and cleaning up build artifacts.

## Functionality
`add_candidate(Election *election, const char *name)`
- Adds a new candidate to the election with a unique ID.
- Validates that the election is not running and the candidate name is unique.

`add_voter(Election *election, const char *name, const char *password)`
- Registers a new voter with a unique ID and password.
- Validates name uniqueness and password length constraints.

`authenticate_voter(const Election *election, int voter_id, const char *password)`
- Verifies voter credentials before allowing them to cast a vote.
- Returns authentication success or failure.

`cast_vote(Election *election, int voter_id, int candidate_id)`
- Records a vote for the specified candidate after successful authentication.
- Prevents double voting and validates election state.

`start_election(Election *election)` / `end_election(Election *election)`
- Manages the election lifecycle states (`NOT_STARTED`, `RUNNING`, `ENDED`).
- Enforces rules like requiring at least 2 candidates to start.

`save_election(const Election *election)` / `load_election(Election *election)`
- Persists the entire election state to a binary file (`election.dat`).
- Automatically loads saved data on startup.

## Usage
To use the online voting system:

1. Compile the program: Use the provided Makefile to compile the program.
```bash
make
```
2. Run the program: Execute the compiled binary `voting`.
```bash
make run
```
or
```bash
./bin/voting
```

## Examples
- Adding a Candidate:
```bash
User@Github:~$ ./bin/voting
State: Not Started
1. Add Candidate
...
Enter choice: 1
Enter candidate name: Alice
Candidate 'Alice' added with ID 1.
```
- Adding a Voter:
```bash
Enter choice: 2
Enter voter name: Bob
Enter password: secret123
Voter 'Bob' added with ID 1.
```
- Casting a Vote:
```bash
Enter choice: 3
Election started! Voting is now open.

Enter choice: 4
Enter voter ID: 1
Enter password: secret123

--- Candidates ---
ID: 1 | Name: Alice
ID: 2 | Name: Charlie
------------------

Enter candidate ID: 1
Vote cast successfully: 'Bob' voted for 'Alice'.
```
- Viewing Results:
```bash
Enter choice: 7

=== Election Results ===
Candidate: Alice                | Votes: 1
Candidate: Charlie              | Votes: 0

Total voters: 1 | Voted: 1 | Remaining: 0

Winner: Alice with 1 votes!
========================
```
- Saving and Exiting:
```bash
Enter choice: 10
Save before exit? (yes/no): yes
Election data saved to election.dat.
Exiting. Goodbye!
```

## Cleaning Up
To clean up the build artifacts (object files and executable), use:
```bash
make clean
```
