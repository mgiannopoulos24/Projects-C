# Rock Paper Scissors Game

This is a simple command-line implementation of the classic Rock Paper Scissors game in C.

## How to Play

1. **Compilation**:

- Compile the game using the provided `Makefile`:
```console
make
```
- This will create an executable named `rock_paper_scissors`.

2. **Running the Game**:
- Execute the compiled program:
```console
User@Github:~$ ./rock_paper_scissors 
```

3. **Game Instructions**:
- You will be prompted to choose whether to play against the computer (`C`) or against another player (`P`).
- If playing against the computer, enter your choice (0 for Rock, 1 for Paper, 2 for Scissors).
- If playing against another player, each player will take turns entering their choices.
- After each round, the game will display the result (who wins or if it's a draw).
- You can choose to play again after each round.

4. **Input Validation**:
- The program validates user inputs to ensure they are within the valid range (0 to 2) for choices.

5. **Cleanup**:
- To remove the executable and object files, run:
```console
make clean
```

