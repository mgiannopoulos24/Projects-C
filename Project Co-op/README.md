# Project Co-op

This program simulates an Iterated Prisoner's Dilemma game where two players make decisions over multiple rounds. The program starts by cooperating and then mimics the opponent's last move.

## How It Works

- **Player Strategy**: The player uses a "Tit for Tat" strategy, cooperating initially and then mimicking the opponent's previous move.
- **Opponent Strategy**: The opponent's move is read from standard input.

## Compilation

To compile the program, use the provided Makefile:

```sh
make
```

This will produce an executable named `coop`.

## Running the Program
To run the game, provide the opponent's moves via standard input. For example:

```console
echo -e "C\nD\nC\n" | ./coop
```
This will simulate a game with moves "C", "D", and "C" from the opponent. The program will print its responses ("C" or "D") to standard output.

## Example Usage
To test the program with a sequence of moves:
```console
# Test with 1000 rounds of cooperation
echo > input; for i in `seq 1 1000`; do echo C >> input; done
./coop < input | head -n -1 > output
grep -c D output  # Check number of 'D's
grep -c C output  # Check number of 'C's

# Test with 1000 rounds of defection
echo > input; for i in `seq 1 1000`; do echo D >> input; done
./coop < input | head -n -1 > output
grep -c D output  # Check number of 'D's
grep -c C output  # Check number of 'C's
```
## Clean Up
To clean up the compiled files, use:
```console
make clean
```
**Note:** This project is the 3rd exercise of 2nd assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.