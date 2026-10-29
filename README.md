_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D

## Description

cub3D is a 42 project inspired by the classic Wolfenstein 3D raycasting engine.
The project currently provides map parsing and validation, a MiniLibX window,
player movement, and a minimap. The 3D raycasting renderer and textured walls
have not yet been implemented.

## Current functionality

The project currently includes the following features:

- Command-line argument validation for a single `.cub` file
- Checks for one `.cub` input file and parses texture (`NO`, `SO`, `WE`, `EA`)
  and floor/ceiling color (`F`, `C`) configuration lines
- RGB color validation and detection of missing or duplicate configuration
  entries
- Map loading, allowed-character checks, wall-enclosure checks, and player
  start detection
- MiniLibX window and image initialization
- Player movement with WASD, rotation with the left/right arrow keys, and
  collision checks
- A top-down minimap showing the walls, player, and facing direction
- Exit handling with `Esc` or by closing the window

The window does not yet show a 3D scene. Parsed texture paths are not loaded or
drawn, and the configured floor and ceiling colors are not yet used for
rendering. The program currently prints parsed game state to standard output
for debugging.

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
./cub3d maps/valid/map00.cub
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

The parser checks required and duplicate configuration entries, validates
color values, and checks map characters, wall enclosure, and player count.
Texture paths are required to be non-empty, but the referenced files are not
currently checked or loaded.

### Controls and exit

- Press `Esc` to quit the program.
- Use `W`/`S` to move forward/backward, `A`/`D` to strafe, and the left/right
  arrow keys to turn.
- Closing the window also ends the session.
- The program frees allocated map, texture-path, image, and MiniLibX resources
  during shutdown.

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

The project includes `libft`. On Linux, MiniLibX and its X11 development
dependencies must be available to the system linker;

## AI usage

AI tools were used as a support resource during the project for:

- clarifying concepts
- debugging and interpreting errors
- suggesting code organization improvements
- helping draft project documentation

AI was not used to generate complete solutions; it was used as a learning aid and
support tool during development.