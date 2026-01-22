*This project has been created as part of the 42 curriculum by bbastos-*

# get_next_line

## Description

**get_next_line** is a function that reads and returns a single line from a file descriptor, handling any buffer size efficiently. The project challenges students to manage static variables, dynamic memory allocation, and file I/O operations in C.

**Goal (high level)**
- Return one line per call (including the trailing `\n` when present)
- Support any `BUFFER_SIZE` value (compile-time macro)
- Keep state between calls so reading continues correctly
- Be memory-safe (no leaks / invalid frees)

## Instructions

### Compile

This project is meant to be compiled together with a tester (your own `main.c` or a provided one):

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

To try different buffer sizes:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
```

### Run

```bash
./a.out
```

## Algorithm (explanation + justification)

`read()` gives you arbitrary chunks of bytes, not lines. A line can be split across multiple reads, and a
single read can contain multiple lines. The simplest correct strategy is to keep a persistent “remainder”
of unread bytes between calls.

**Step-by-step**
1. Maintain a remainder string that stores data already read from the FD but not yet returned.
2. While the remainder does not contain a `\n`:
	- `read()` up to `BUFFER_SIZE` bytes into a temporary buffer.
	- if `read()` returns 0 (EOF): stop reading.
	- if `read()` returns -1 (error): free what is needed and return `NULL`.
	- append the new bytes to the remainder.
3. If the remainder contains a `\n`, split at the first newline:
	- return the prefix (including `\n`).
	- keep the suffix as the new remainder for the next call.
4. If there is no `\n` and EOF was reached:
	- if remainder is non-empty, return it as the last line.
	- otherwise return `NULL`.

**Why this works well**
- Correct by construction: each call returns exactly one line, and leftover bytes are preserved.
- Efficient: reading in blocks reduces syscalls; total work is proportional to the amount of input (overall O(n)).
- Safe ownership: the caller frees the returned line; the remainder is managed internally.

## Resources

**Classic references**
- `man 2 read`
- `man 2 open`, `man 2 close`
- `man 3 malloc`, `man 3 free`
- 42 subject for `get_next_line`

**Links used**
- https://labex.io/pt/tutorials/c-how-to-use-static-variables-safely-464765
- https://en.wikipedia.org/wiki/Static_variable
- https://www.youtube.com/watch?v=ji1dq8cklyU&t=123s
- https://www.youtube.com/watch?v=BqRN9jfmULo&t=399s
- https://www.youtube.com/watch?v=zPy12AKhYIg&t=11s
- https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line
- https://www.geeksforgeeks.org/c/memory-layout-of-c-program/
- https://www.inf.ufpr.br/hexsel/ci067/10_aloc.html
- https://folivetti.github.io/courses/AEDI/PDF/aedi02_ponteiros_revisao.pdf

**AI usage**
- AI was used only to rewrite/structure `README.md` (formatting + wording to match the required sections).
