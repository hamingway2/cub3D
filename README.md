_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D

## Description

cub3D is a 42 project inspired by the classic Wolfenstein 3D raycasting engine.
The current implementation focuses on parsing and validating `.cub` map files,
initializing a MiniLibX window, and preparing the game state for a future
raycasting renderer.

## Current functionality

The project now includes the following features:

- Command-line argument validation for a single `.cub` file
- Parsing of config lines such as:
  - `NO ...`, `SO ...`, `WE ...`, `EA ...`
  - `F ...`, `C ...`
- Loading the map grid from the input file
- Detection of the player's starting position (`N`, `S`, `E`, `W`)
- Basic wall and character validation for the map
- MiniLibX window initialization and clean shutdown with `Esc`

The project already stores the texture paths and color values in the game
structure, and it enforces basic validation rules before continuing the game
setup.

## Instructions

### Compilation

Compile the project using:

```bash
make
```

This creates the `cub3d` executable.

For a build with debugging information:

```bash
make debug
```

To remove object files:

```bash
make clean
```

To remove all generated files:

```bash
make fclean
```

To rebuild everything from scratch:

```bash
make re
```

### Execution

The program expects a single `.cub` map file:

```bash
./cub3d <map.cub>
```

Example:

```bash
./cub3d maps/map00.cub
```

The `--help` flag displays usage information:

```bash
./cub3d --help
```

If the program is executed without arguments or with more than one argument, the
usage information is displayed:

```bash
./cub3d
./cub3d map1.cub map2.cub
```

### Parsing and validation

After the input file is checked, the parser reads the file and identifies:

1. configuration lines
2. the beginning of the map
3. the player's spawn point

The map is then validated to ensure it is bounded by walls and that only valid
characters are used.

### Controls and exit

- Press `Esc` to quit the program.
- Closing the window also ends the session.
- On shutdown, the program frees the allocated map and MiniLibX resources.

### Error handling

The program reports errors for cases such as:

- invalid argument count
- invalid filename or extension
- failed file opening
- invalid configuration lines
- duplicate texture or color definitions
- invalid map walls
- invalid map characters
- missing player start position

## Resources

The project includes the MiniLibX and `libft` source code. MiniLibX uses the X11
window system on Linux.

## AI usage

AI tools were used as a support resource during the project for:

- clarifying concepts
- debugging and interpreting errors
- suggesting code organization improvements
- helping draft project documentation

AI was not used to generate complete solutions; it was used as a learning aid and
support tool during development.