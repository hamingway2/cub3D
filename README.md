_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D
## Description


## Instructions
### Compilation
Compile the project using
```
make
```
This creates the `cub3d` executable.


For a build with debugging information, use:
```
make debug
```
This compiles the project with the `-g` flag, allowing the program to be inspected with a debugger such as `gdb`.

To remove the compiled object files:
```
make clean
```

To remove all compiled files and the executables:
```
make fclean
```

To recompile the project from scratch:
```
make re
```


### Execution

The program expects a single `.cub` map file:
```
./cub3d <map.cub>
```

For example, run one of the maps included with the project:
```
./cub3d maps/map00.cub
```

The `--help` flag displays information about the correct usage:
```
./cub3d --help
```

If the program is executed without arguments or with more than one argument, the
usage information is displayed:
```
./cub3d
./cub3d map1.cub map2.cub
```

#### Argument validation
Before parsing the map, the program validates the command-line arguments:
1. Exactly one argument must be provided.
2. The argument must have the `.cub` extension.

#### Initialisation and parsing

After checking the command-line arguments, cub3D initializes MiniLibX and creates
the game window and image buffer. It then reads the supplied `.cub` file and
stores the map as a grid of lines.

The parser skips blank lines and identifies configuration lines and the start of
the map. Configuration parsing is not implemented yet. Once the map is loaded,
the program searches it for the player's starting position (`N`, `S`, `E`, or
`W`) and sets the player's initial coordinates and direction.

Map validation and parsing of texture and floor/ceiling color settings are still
in progress.

#### Exiting the program

Press **Esc** or close the window to exit. The program releases the map, image,
window, and MiniLibX resources during shutdown.

#### Error messages

The program reports errors for an incorrect number of arguments, a filename
without the `.cub` extension, failure to open the map file, an unrecognized line
before the map, or a map without a player starting position. Full map validation
is not yet implemented.

## Resources

The project includes the MiniLibX and libft source code. MiniLibX uses the X11
window system on Linux.

### AI Usage
AI tools (such as ChatGPT) were used as a support resource during the project. 

Specifically:
- Clarifying concepts
- Assisting with debugging and error interpretation
- Suggesting improvements in code structure and organisation
- Helping with the creation of this README

AI was not used to produce complete solutions but rather as a learning aid and debugging assistant.