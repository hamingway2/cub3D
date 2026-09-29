_This project has been created as part of the 42 curriculum by azielnic, gkhavari._

# cub3D
## Description


## Instructions
### Compilation
Compile the project using
```
make
```
This creates the `cube3D` executable.


For a build with debugging information, use:
```
make debug
```
This compiles the project with the `-g` flag, allowing the program to be inspected with a debugger such as `gdb`.

To remove the compuled object files:
```
make clean
```

To remove all compiled files and the executables:
```
make fclean
```

To recompile the project from scratch
```
make re
```


### Execution

The program expects a single `.cub` map file:
```
./cub3D <map.cub>
```

The `--help` flag displays information about the correct usage:
```
./cube3D --help
```

If the program is executed without arguments or with more than one argument, the usage information is displayed
```
./cube3D
./cube3D map1.cub map2.cub
```

#### Argument validation
Before parsing the map, the program validates the command-line arguments:
1. Exactly one argument must be provided.
2. The argument must have the `.cub` extension.

## Resources


### AI Usage
AI tools (such as ChatGPT) were used as a support resource during the project. 

Specifically:
- Clarifying concepts
- Assisting with debugging and error interpretation
- Suggesting improvements in code structure and organisation
- Helping with the creation of this README

AI was not used to produce complete solutions but rather as a learning aid and debugging assistant.