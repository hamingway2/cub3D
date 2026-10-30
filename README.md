_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D

## Description

cub3D is a 42 project inspired by the classic Wolfenstein 3D raycasting engine.
The project loads a `.cub` map, validates the map data, and renders a first-person
3D maze using raycasting in a MiniLibX window. The player can move, rotate, and
explore the level while the game continuously draws textured walls, a ceiling,
a floor, and a minimap overlay.

### Requirements

The project is developed for Linux and requires:

- GCC or another compatible C compiler
- GNU Make
- MiniLibX
- X11 development libraries

### Project structure

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

This creates the `cub3D` executable.

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
./cub3D <map.cub>
```

Example:

```bash
./cub3D maps/valid/map00.cub
```

The `--help` flag displays usage information:

```bash
./cub3D --help
```

If the program is executed without arguments or with more than one argument, the usage information is displayed:

```bash
./cub3D
./cub3D map1.cub map2.cub
```

#### Map format

A `.cub` file contains texture paths, floor and ceiling colors, and the map layout.

Example:

```text
NO ./texture/north.xpm
SO ./texture/south.xpm
WE ./texture/west.xpm
EA ./texture/east.xpm

F 220,100,0
C 225,30,0

111111111
100000001
100N00001
100000001
111111111
```
| Element | Meaning |
|:-------:|---------|
| `NO` | North wall texture |
| `SO` | South wall texture |
| `WE` | West wall texture |
| `EA` | East wall texture |
| `F` | Floor RGB color |
| `C` | Ceiling RGB color |
| `1` | Wall |
| `0` | Empty space |
| `N` | Player spawn facing north |
| `S` | Player spawn facing south |
| `E` | Player spawn facing east |
| `W` | Player spawn facing west |

## Technical implementation

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

### Raycasting

The rendering engine uses raycasting with the Digital Differential Analyzer (DDA) algorithm.

For each vertical screen column:

1. A ray is calculated based on the player's viewing direction.
2. DDA traverses the map grid until a wall is hit.
3. The perpendicular distance to the wall is calculated.
4. The projected wall height is determined.
5. The corresponding wall texture is sampled and drawn.

The wall texture is selected based on the side and direction from which the ray hits the wall.

### Texture rendering

- Loads and uses separate textures for north, south, east, and west-facing walls.
- Selects the appropriate wall texture based on the direction of the ray intersection.
- Calculates texture coordinates to render the correct part of each wall texture.
- Uses perspective projection to determine wall height and render textured vertical columns.

### Player movement and collision

- Supports forward and backward movement using `W` and `S`.
- Supports strafing left and right using `A` and `D`.
- Allows player rotation using the left and right arrow keys.
- Implements collision detection to prevent the player from walking through walls.
- Updates the player's position and viewing direction in real time.

### Minimap

- Displays a top-down view of the map, including walls and the player's position.
- Shows the player's facing direction and field of view.
- Uses a player-centered viewport with a fixed tile size.
- Maintains the viewport's aspect ratio when the game window is resized.
- Scales the minimap viewport to one quarter of the game window's width and height.

### Get next line changes

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

## Controls and exit

- Press `Esc` to quit the program.
- Press `F11` to toggle between the screen-sized view and a smaller window.
- Use `W`/`S` to move forward/backward, `A`/`D` to strafe, and the left/right
  arrow keys to turn.
- Closing the window also ends the session.
- The program frees allocated map, texture-path, image, and MiniLibX resources
  during shutdown.

## Error handling

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