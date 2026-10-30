_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D

## Description

cub3D is a 42 project inspired by the classic Wolfenstein 3D raycasting engine.
The project loads a `.cub` map, validates the map data, and renders a first-person
3D maze using raycasting in a MiniLibX window. The player can move, rotate, and
explore the level while the game continuously draws textured walls, a ceiling,
a floor, and a minimap overlay.

## Current functionality

The project currently includes the following features:

- Command-line argument validation for a single `.cub` file
- Parser for texture (`NO`, `SO`, `WE`, `EA`) and floor/ceiling color (`F`, `C`)
  configuration lines
- RGB color validation and duplicate/missing configuration detection
- Map loading, allowed-character validation, wall-enclosure checks, and player
  start detection
- 3D raycasting engine with DDA wall traversal and perspective projection
- Textured wall rendering with dedicated north, south, east, and west textures
- Floor and ceiling background fill using the configured colors
- MiniLibX window and image initialization
- Player movement with `W`/`S`/`A`/`D`, rotation with the left/right arrow keys,
  and collision checks
- Top-down minimap showing walls, the player, and facing direction
- Clean shutdown with resource freeing for the map, textures, image, and MiniLibX
  allocations
- Exit handling with `Esc` or by closing the window

## Project structure

- `src/` contains the main game loop, parser, renderer, raycasting logic, and
  player movement code
- `includes/` holds the project headers and shared type definitions
- `libft/` contains the custom C utility library used across the project
- `maps/valid/` and `maps/invalid/` provide valid and invalid `.cub` test maps
- `texture/` stores the wall textures used by the renderer
- `Makefile` builds the project and links MiniLibX and `libft`

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
color values, and verifies map characters, wall enclosure, and player count.
The map filename must have a non-empty basename and end in `.cub`. Texture
paths must have a non-empty basename and end in `.xpm`; each wall direction
must be mapped correctly before the game can start.
Configuration lines may have leading and trailing spaces or tabs, and one or
more spaces or tabs may separate an identifier from its value. Whitespace is
also allowed around RGB components and commas in floor and ceiling colors.
Maps with walkable tiles or regions that cannot be reached from the player's
starting position are accepted as valid, provided the map passes the other
validation checks.

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
- file read errors while parsing the map

## Get next line changes

The only change in the custom get_next_line implementation is that it now treats
`read_error` separately from end-of-file handling. In practice, a `read()` return
value of `0` is interpreted as normal end-of-file, while a negative value is
reported through the `read_error` flag so the caller can stop and report a real
file-read failure without confusing it with a valid end-of-file condition. This
is why the function now takes two arguments: `fd` and a pointer to an `int` that
stores whether the last read failed. The parser can then distinguish between:

- `line == NULL` and `read_error == false` : normal EOF
- `line == NULL` and `read_error == true` : actual read failure

The rest of the logic remains the same: it reads one line at a time, keeps any
remaining characters in a static buffer, and continues cleanly from the next call.

## Resources

The project includes `libft` for utility functions and relies on MiniLibX with the
Linux X11 dependencies available on the system linker path.

## AI usage

AI tools were used as a support resource during the project for:

- clarifying concepts
- debugging and interpreting errors
- suggesting code organization improvements
- helping draft project documentation

AI was not used to generate complete solutions; it was used as a learning aid and
support tool during development.