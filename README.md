# 42 - PIPEX

### SUMMARY
Pipex is a project that replicates the behavior of the Unix pipeline (|). It takes input and output files along with two shell commands, executing them in sequence while redirecting the output of the first command to the input of the second.

Simulates shell piping:
```
< file1 cmd1 | cmd2 > file2
```

### REPOSITORY STRUCTURE
- `srcs`: Contains the source code for the program.
- `libft`: Custom library for utility functions.
- `pipex.h`: Header file containing the functions prototypes and including the used external libraries.
- `Makefile`: Compiles the project.

### KEY FEATURES
- Uses **forks**, **pipes**, and **file descriptors** for inter-process communication.
- Handles edge cases like invalid commands and file errors.
- Implements error handling and memory management.

### USAGE
1. **Compile the program:**
```
make
```

2. **Run the program with an existing `infile` and a `outfile` that is created by the program if it does not already exist.**
```
./pipex infile cmd1 cmd2 outfile
```
`cmd1` and `cmd2` are shell commands that are executed in sequence, with `cmd1`'s output being used as `cmd2`'s input, just like in a Unix pipeline.

3. **Example:**
```
./pipex infile "cat" "wc -l" outfile
```

It is equivalent to:
```
< infile cat | wc -l > outfile
```

Breakdown:
- `cat < infile`: Reads the contents of `infile`.
- `| wc -l`: Passes the output of `cat` to `wc -l`, which counts the number of lines.
- `> outfile`: Redirects the final output to `outfile`.

----
🐸 Feel free to fork, clone, or contact me for questions or feedback. 
