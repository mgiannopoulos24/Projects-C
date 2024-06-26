# Snake and Ladders Game
This project is an implementation of the classic Snake and Ladders board game using C and SDL (Simple DirectMedia Layer) for graphics rendering.

## Features
- Two Players: Play against a friend locally.
- Random Dice Roll: Dice rolls are simulated for movement.
- Snakes and Ladders: The board includes randomly placed snakes that move you down and ladders that move you up.
- Winning Condition: The first player to reach position 100 wins the game.
- Graphical Interface: Uses SDL for rendering the game board, players, and text.
## Requirements
- C compiler (GCC recommended)
- [SDL2 library](https://www.libsdl.org/)
- [SDL2_ttf library](https://www.libsdl.org/projects/SDL_ttf/)
Installation and Usage

## Installation of libraries

To install the libraries please run:
```bash
sudo apt-get update && sudo apt-get install -y libsdl2-dev
sudo apt-get update && sudo apt-get install -y libsdl2-ttf-dev
```

## Compilation

To compile the files run:
```bash
make
```

This will compile the code and produce the executable on the `build/` directory.

## Game Controls:

- Use the spacebar to roll the dice and move your player.
- The game alternates turns between Player 1 (Blue) and Player 2 (Red).
## Gameplay:
- Players move forward according to the number rolled on the dice.
- Snakes move you backward, and ladders move you forward.
- The game ends when a player reaches or exceeds position 100.
## Exiting the game:
- Close the game window to exit cleanly.

## Cleanup
To remove the game run:
```bash
make clean
```
## Contributing
Contributions are welcome! If you'd like to add new features, fix bugs, or improve the code, please feel free to fork the repository and submit a pull request.