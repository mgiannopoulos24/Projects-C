# A python program to run a game of cooperation with two players (programs)
# for a number of rounds. The programs are launched on the first round and
# the referee is reading the output of each program line by line and forwarding
# it to the other program. The referee will subtract points from a program if
# it outputs something other than C or D. The referee calculates the score of
# first player in the argument list based on responses observed as the game goes
# on across rounds and will print it out at the end of the game.

import sys
import subprocess


def run(program1: str, program2: str, rounds: int) -> int:
    """Main routine for running the game. Forwards the output of each program
    to the other program and calculates the score of the first program based
    on the responses observed as the game goes on across rounds.

    Args:
        program1 (str): Program representing player 1
        program2 (str): Program representing player 2
        rounds (int): Number of rounds to play

    Returns:
        int: Score of player 1 at the end of the game
    """
    p1 = subprocess.Popen(program1, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    p2 = subprocess.Popen(program2, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    score = 0

    for i in range(rounds):
        p1_out = p1.stdout.readline().decode('utf-8').strip()
        p2_out = p2.stdout.readline().decode('utf-8').strip()

        if p1_out not in 'CD':
            score -= 1
            continue
        if p2_out not in 'CD':
            score += 1
            continue

        p1.stdin.write(p2_out.encode('utf-8'))
        p1.stdin.flush()
        p2.stdin.write(p1_out.encode('utf-8'))
        p2.stdin.flush()

        if p1_out == 'C' and p2_out == 'C':
            score += 3
        elif p1_out == 'C' and p2_out == 'D':
            score += 0
        elif p1_out == 'D' and p2_out == 'C':
            score += 5
        else:
            score += 1

    p1.stdin.close()
    p2.stdin.close()
    return score


def main():
    """Pass command line arguments to run() and print the score of player 1"""
    if len(sys.argv) != 4:
        print("Usage: python3 referee.py <program1> <program2> <rounds>")
        sys.exit(1)

    program1 = sys.argv[1]
    program2 = sys.argv[2]
    rounds = int(sys.argv[3])

    print(run(program1, program2, rounds))


if __name__ == '__main__':
    main()