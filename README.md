![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

# GeeseSpotter 

**Author:** Insaf Lashari  
**Date:** November 10, 2023

A command-line logic game inspired by Minesweeper — but with geese instead of mines! The objective is to reveal all safe fields on the board without disturbing a goose.

## 🕹 Gameplay Overview

- The player is presented with a board where all fields are initially hidden (`*`).
- Each turn, the player can choose one of the following actions:
  - **[S]how**: Reveal a field
  - **[M]ark**: Mark or unmark a field suspected of containing a goose
  - **[R]estart**: Start a new game with fresh parameters
  - **[Q]uit**: Exit the game

## Game Rules

- If the player **reveals a goose**, the game ends in defeat.
- If the player **reveals a safe field**:
  - The field is shown.
  - If the field and its neighbors contain no geese, neighboring fields are also automatically revealed.
  - Each revealed field displays a number from 0–8 representing how many adjacent geese are nearby.
- **Marking/Unmarking**:
  - A hidden field can be marked as suspected of containing a goose.
  - A marked field can be unmarked to return it to the hidden state.
  - Only hidden fields can be revealed or marked.
- The game is **won** when all non-goose fields are successfully revealed.

## Sample Output

```
Welcome to GeeseSpotter!
Please enter the x dimension (max 60): 5
Please enter the y dimension (max 20): 5
Please enter the number of geese: 3
*****
*****
*****
*****
*****
Please enter the action ([S]how, [M]ark, [R]estart, [Q]uit): s
Please enter the x location to show: 1
Please enter the y location to show: 1
*****
*1***
*****
*****
*****
```


📁 File Structure

----main.cpp: Entry point and main game loop

----geesespotter_lib.cpp/h: Game setup, masks, and utility logic

----geesespotter.cpp/h: Game mechanics such as board creation, revealing, marking, etc.

## How to Compile & Run
Make sure you have a C++ compiler like `g++` installed. Then, from your terminal:

```bash
g++ -o geesespotter main.cpp geesespotter_lib.cpp geesespotter.cpp
./geesespotter
