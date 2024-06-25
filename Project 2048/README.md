# 2048 Game

This project is a simple implementation of the classic 2048 game using SDL2 for graphics and TTF (TrueType Font) for rendering text. The game involves sliding numbered tiles on a grid to combine them, with the goal of creating a tile with the number 2048.

## Features
- Graphical user interface using SDL2.
- Score tracking and display.
- Responsive keyboard controls.
- Color-coded tiles based on their numeric value.
- Simple and intuitive gameplay.

## Requirements
- C compiler (gcc recommended)
- [SDL2 library](https://www.libsdl.org/)
- [SDL2_ttf library](https://www.libsdl.org/projects/SDL_ttf/)


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

## Usage
- Run the compiled executable to start the game.
- Use arrow keys (WASD keys are also supported) to move tiles on the board and combine them.
- The game ends when no more moves are possible.

## Controls
- Up: Move tiles upwards.
- Down: Move tiles downwards.
- Left: Move tiles to the left.
- Right: Move tiles to the right.
- WASD keys are alternative controls for moving tiles.

## Cleanup
To remove the game run:
```bash
make clean
```
## Credits
This game is based on the original 2048 game by [Gabriele Cirulli](https://github.com/gabrielecirulli).

