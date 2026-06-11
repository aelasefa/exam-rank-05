# exam-rank-05

This workspace contains two small C projects:

- `BSQ`: finds the biggest square on a map and marks it with the full character.
- `life`: simulates a simple grid-based cellular automaton controlled from the keyboard.

## BSQ

`BSQ` reads a map from standard input or from files passed on the command line. The program parses the header, loads the grid, runs a dynamic-programming search, and prints the map with the largest empty square replaced by the `full` character.

### Build

```sh
cd BSQ
cc -Wall -Wextra -Werror -o bsq main.c b.c
```

### Run

```sh
./bsq maps/valid_map.txt
cat maps/valid_map.txt | ./bsq
```

### Map format

The first line is the header:

```text
<number_of_rows><empty><obstacle><full>
```

Example:

```text
4.ox
....
..o.
....
....
```

Rules:

- The row count must be a positive integer.
- The three header symbols must be printable and different from each other.
- Every map row must have the same length.
- Only the `empty` and `obstacle` characters are allowed in the input grid.

## Life

`life` is an interactive board simulation. It takes the board width, height, and number of iterations as arguments. The program then reads keyboard input to draw cells, runs the simulation for the requested number of generations, and prints the final board.

### Build

```sh
cd life
cc -Wall -Wextra -Werror -o life life.c
```

### Run

```sh
./life 20 10 5
```

### Controls

- `w`, `a`, `s`, `d` move the cursor.
- `x` toggles drawing mode.
- When drawing mode is on, the current cell is filled.

### Arguments

- `width`: board width, must be greater than 0.
- `height`: board height, must be greater than 0.
- `iterations`: number of generations to simulate, must be 0 or greater.

## Repository Layout

```text
BSQ/
  main.c
  b.c
  b.h
  maps/
life/
  life.c
  subject/
```
