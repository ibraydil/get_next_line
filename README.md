*This project has been created as part of the 42 curriculum by dibrayev.*

# get_next_line

## Description

`get_next_line` is a C function that reads from a file descriptor and returns **one line per call**. Calling it repeatedly (for example in a loop) walks through a file, the standard input, a pipe or any other readable descriptor line by line.

```c
char *get_next_line(int fd);
```

- **Returns** the next line, including its terminating `\n` (the last line of a file has no `\n` if the file does not end with one).
- **Returns `NULL`** when there is nothing left to read or when an error occurs (invalid fd, `read()` failure, allocation failure).
- The returned line is heap-allocated; **the caller must `free()` it**.

The goal of the project is to learn how **static variables** work in C: a static variable keeps its value between function calls, which lets the function remember data that was already read from the descriptor but not yet returned.

Only `read`, `malloc` and `free` are allowed. `libft`, `lseek()` and global variables are forbidden.

### Files

| File | Content |
|---|---|
| `get_next_line.c` | `get_next_line()` and its core helpers: `read_to_leftover()`, `get_line()`, `cut_leftover()`, `index_position()` |
| `get_next_line_utils.c` | String helpers: `ft_strlen()`, `ft_strjoin()`, `ft_strchr()` |
| `get_next_line.h` | Prototypes, includes and the default `BUFFER_SIZE` |

## Instructions

### Compilation

The function is meant to be compiled together with your own program. The buffer size used by `read()` is set with `-D BUFFER_SIZE=n`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

The flag is optional: without it, `BUFFER_SIZE` defaults to **66** (defined in `get_next_line.h`). A `BUFFER_SIZE` of 0 or less makes the function return `NULL`.

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = 0;                          /* standard input by default */
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
```

```sh
printf 'hello\nworld\nlast' > file.txt
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl file.txt          # read a file
cat file.txt | ./gnl    # read from standard input
```

### Testing tips

- Try very different buffer sizes: `1`, `42`, `9999`, `10000000`.
- Try empty files, files without a final `\n`, files made only of `\n`, and very long lines.
- Read from stdin and pipes, not only regular files.
- Check for leaks with `valgrind --leak-check=full ./gnl file.txt`.

## Algorithm

### Overview

The function keeps one static pointer, `leftover`, which stores the bytes that were read from the descriptor but not returned yet. Each call works in three steps:

1. **Fill** – `read_to_leftover()` calls `read()` into a temporary buffer of `BUFFER_SIZE + 1` bytes and appends the buffer to `leftover` (with `ft_strjoin`) **until `leftover` contains a `\n`** or `read()` returns 0 (end of file).
2. **Extract** – `get_line()` copies everything up to and including the first `\n` (or up to the end of the string if there is no `\n`) into a new string. This is the line returned to the caller.
3. **Keep the rest** – `cut_leftover()` copies whatever comes after that `\n` into a new string, which becomes the new `leftover`. If nothing is left, `leftover` becomes `NULL`. The old `leftover` is freed.

`index_position()` is the shared helper that finds the length of the current line (position of the first `\n` + 1, or the string length if there is no `\n`), so `get_line()` and `cut_leftover()` always split at the same place.

### Edge cases

- **Invalid fd or `BUFFER_SIZE <= 0`**: returns `NULL` immediately, before allocating anything.
- **`read()` error**: `leftover` is freed and set to `NULL`, so no memory is leaked and the function returns `NULL`.
- **End of file**: when `read()` returns 0, whatever is left in `leftover` is returned as the last line; the next call returns `NULL`.
- **Large `BUFFER_SIZE`**: the read buffer is allocated on the heap (not on the stack), so values such as `10000000` do not overflow the stack.

### Why this approach

- **Reads as little as possible.** The loop stops as soon as a `\n` is in `leftover`, so the function never reads the whole file at once, as the subject requires. It also works for streams that never "end" in advance, such as stdin or a pipe.
- **Works with any buffer size.** Lines longer than `BUFFER_SIZE` are built by joining several reads; a buffer that contains several lines leaves the extra lines in `leftover` for the next calls.
- **One static variable.** Only the unreturned bytes need to survive between calls, so a single `static char *` is enough. Everything else is local and freed before returning.
- **Simple ownership.** Every string is either returned to the caller or freed inside the function, which makes it easy to prove there are no leaks.
- **Trade-off.** `ft_strjoin` copies `leftover` on every read, so with a very small `BUFFER_SIZE` and very long lines the cost grows roughly quadratically with the line length. For a learning project this simplicity was preferred over a more complex buffer structure (for example a linked list of chunks).

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C – GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- The 42 Norm (`norminette`)

### AI usage

AI (Claude) was used to help write and structure this `README.md` from the project subject and the existing code. The implementation of `get_next_line` and its helper functions was written with Learn mode in Claude.
