_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D

## Description

cub3D is a 42 project inspired by the classic Wolfenstein 3D raycasting engine.
The project has progressed from raw map parsing into a working game foundation:
it validates input files, loads the map, initializes the MiniLibX window, places
the player, and prepares the event loop for the next rendering stage.

## Current functionality

The project currently includes the following features:

- Command-line argument validation for a single `.cub` file
- Parsing of configuration lines such as:
  - `NO ...`, `SO ...`, `WE ...`, `EA ...`
  - `F ...`, `C ...`
- Loading the map grid from the input file
- Detection of the player's starting position (`N`, `S`, `E`, `W`)
- Basic map validation for borders and allowed characters
- MiniLibX initialization and window creation
- Player initialization with position and direction values
- Keyboard exit handling with `Esc`
- Clean shutdown of the game resources

The current implementation is a game-state and window foundation for the
raycasting engine; actual raycasting rendering is still the next major step.

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

The map is then validated to confirm it is enclosed by walls and contains only
valid map characters.

### Controls and exit

- Press `Esc` to quit the program.
- Closing the window also ends the session.
- The program frees the allocated map, image, and MiniLibX resources during
  shutdown.

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

## Validation TODO

The following validation work is still needed before the project fully matches a
complete cub3D map parser:

- Check that all required texture identifiers are present exactly once:
  - `NO`, `SO`, `WE`, `EA`
- Check that all required color entries are present exactly once:
  - `F`, `C`
- Validate the floor and ceiling color values as proper RGB triplets
- Ensure texture paths are non-empty and valid
- Reject empty or malformed config lines before the map starts
- Validate that the player start position appears exactly once
- Verify that the map does not contain trailing garbage after the final row

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