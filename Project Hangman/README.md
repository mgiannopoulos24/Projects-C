# Hangman Game
This is a simple Hangman game implemented in C. The project is organized into multiple files and directories for better modularity and maintainability. The game randomly selects a word from a predefined list and allows the user to guess letters until they either guess the word correctly or run out of attempts.

## Compilation and Execution

1. Add Words to words.txt:
- Ensure `words.txt` is in the project root directory and contains a list of words, one per line.
2. Build the Project:
```console
make
```
3. Run the Game:
```console
./build/hangman
```
4. Clean the Build Artifacts:
```console
make clean
```
## Gameplay
- The game will randomly select a word from `words.txt`.
- You have a limited number of attempts to guess the word.
- Each incorrect guess decreases the number of remaining attempts.
- If you guess all the letters in the word correctly, you win.
- If you run out of attempts, you lose and the word is revealed.