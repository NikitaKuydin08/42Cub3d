# Map Validation Checks for cub3D Mandatory

## Context

User is implementing map/scene file validation in [42Cub3d/srcs/validate.c](42Cub3d/srcs/validate.c). The five validation functions are stubbed but empty. The subject requires the program to exit with `Error\n` followed by an explicit message on **any** misconfiguration. This plan lists exactly which checks each function needs to perform.

(Side note on the user's earlier question — yes, smooth animated doors are doable for bonus via multi-frame textures cycling on `mlx_get_time()`. Not in scope here.)

## The five validation layers

### 1. `correct_permission(t_data *data, char **argv)` — argument & file access

- `argv[1]` is not NULL (already guarded in main, but defensive check is fine).
- Filename ends in `.cub` (exactly — `map.cub.bak` should fail; `.cub` alone with no name should fail).
- File exists and `open()` succeeds with `O_RDONLY`.
- File is not a directory (`stat()` + `S_ISREG`). Opening a directory succeeds on some systems and gives garbage reads.
- File is not empty.

### 2. `handle_args(t_data *data, char **argv)` — top-level orchestrator

Just calls the others in order, propagates errors. Owns the FD lifecycle (open here, close at the end). On any sub-check failure, print `Error\n<message>\n` to stderr and return non-zero.

### 3. `textures_path_valid(...)` — element parsing for NO/SO/WE/EA

For each of the four texture identifiers:

- Identifier appears **exactly once** (no duplicates, none missing).
- Identifier matches exactly: `NO`, `SO`, `WE`, `EA` (uppercase, two chars).
- Followed by **at least one whitespace** (space or tab — subject allows multiple).
- Path is non-empty and points to a readable file.
- Path ends in `.png` (MLX42 only loads PNG).
- Trailing garbage on the line is rejected (`NO ./tex.png extra` → error).

Store the path in `t_data` for later use by texture loading.

### 4. `floor_ceil_rgb_valid(...)` — element parsing for F and C

For each of `F` and `C`:

- Identifier appears **exactly once** each.
- Matches exactly `F` or `C` followed by whitespace.
- Value is **three** comma-separated integers — count commas, reject 2 or 4.
- Each integer:
  - Is purely digits (no `+`, no leading/trailing letters, no `.`)
  - Parses cleanly and is in **[0, 255]**.
- Whitespace between number and comma is **not** specified as allowed by the subject — being strict is safer (`F 220, 100, 0` → reject). But many evaluators tolerate spaces; pick a stance and document it.
- Trailing garbage rejected.

### 5. `map_valid(...)` — map content

`map_valid` only **validates** — it does not store the player or rewrite the map. Position and orientation tracking moves to the init step (see "After validation" below). Validation reads the lines from the cursor onward and applies these checks, in this order. Each check is tagged with the test files it catches.

**5a. Map exists at all**
- At least one non-blank line remains past the cursor.
- Catches: `bad/map_missing.cub`, `bad/empty.cub`, `map_tests/test17.cub`, `map_tests/test18.cub`, `map_tests/test20.cub`.

**5b. No interleaving — map is the last element**
- Once a line that "looks like map" is seen (starts with `0`, `1`, ` `, or N/S/E/W and contains only those), every following non-blank line must also be map.
- Any header element (`NO`, `SO`, `WE`, `EA`, `F`, `C`) appearing after the first map line → error.
- A blank line *after* map content has started → error (terminates the map; subsequent content is forbidden).
- Catches: `bad/map_first.cub`, `bad/map_middle.cub`, `bad/file_letter_end.cub`, `map_tests/test8.cub`, `map_tests/test12.cub`, `map_tests/test13.cub`, `map_tests/test14.cub`.

**5c. Character set**
- Only allowed: `0`, `1`, ` ` (space), `N`, `S`, `E`, `W`. Plus the implicit `\n` line terminator.
- **Tabs are rejected** — your test files `map_tests/test4.cub` and `map_tests/test15.cub` confirm tabs should fail.
- Anything else (`2`, `Q`, `P`, letters, punctuation) → error.
- Catches: `map_tests/test10.cub` (Q), `map_tests/test4.cub` (tab prefix), `map_tests/test15.cub` (tab prefix).

**5d. Player count**
- Exactly **one** of `{N, S, E, W}` across all map cells.
- Zero → error (`bad/player_none.cub`, `map_tests/test2.cub`).
- Two or more → error (`bad/player_multiple.cub`, `map_tests/test11.cub`, `map_tests/test19.cub` which has `1NW1` — N at col 1 and W at col 2, two players).
- Just record the (x, y, orient) triple in a temporary local — actual storage to `t_data` happens in init.

**5e. Map has at least one walkable region**
- Total count of `0` + player cells ≥ 1.
- A map made entirely of walls is invalid.
- Catches: `bad/wall_none.cub` (all 0s, no walls — flood fill check below catches it), `bad/map_too_small.cub` (3×3 of all 1s, no walkable cells).

**5f. Map closure via flood fill** — the killer check, catches the most failures

Run BFS/DFS from the player's starting position over `0` cells. The map is **closed iff** during the flood:
1. No cell index ever goes out of array bounds (negative row/col, or row ≥ height, or col ≥ row-length-of-current-row).
2. No `0` cell is adjacent (4-direction: up/down/left/right) to a space character.

If either condition fails → map is not closed.

This single check catches **all** of these:
- `bad/wall_hole_north.cub`, `bad/wall_hole_south.cub`, `bad/wall_hole_east.cub`, `bad/wall_hole_west.cub` — flood reaches a boundary cell with no wall there → out-of-bounds neighbour.
- `bad/wall_none.cub` — every cell is `0`, every boundary cell has out-of-bounds neighbours → fail.
- `bad/player_on_edge.cub` — player at row 0 col 1; first BFS step looks up at row -1 → out-of-bounds.
- `bad/forbidden.cub` — `0`s adjacent to space cells in the layout.
- `map_tests/test1.cub` — `1N1` row with only `111` below; player has no wall *above* (out-of-bounds top).
- `map_tests/test5.cub` — spaces inside what should be wall row → adjacent space leak.
- `map_tests/test6.cub` — short row creates implicit "out-of-bounds" beneath cells in the longer row above.
- `map_tests/test7.cub`, `map_tests/test9.cub` — interior leaks via space cells.

**Jagged rows reminder**: rows may have different lengths legally. When checking neighbours, treat "col index ≥ length of *that specific row*" as out-of-bounds, not as a space. Example:
```
11111
10001
10001  <- this row 5 wide
1001   <- this row only 4 wide; cell (3,3) (the '0') has no right neighbour wall
11111
```
The `0` at row 3 col 1 — its neighbour at row 3 col 4 (if you index into a 5-wide assumption) doesn't exist. Treat as out-of-bounds, not as wall. → leak → fail.

## After validation: initialization (separate step)

Once `map_valid` returns success, `init_data` (or a new `init_player`) does:

1. Read the player position and orientation found during validation (pass it back from `map_valid` via `t_data` or out-params).
2. Set `data->player.x`, `data->player.y` (typically + 0.5 for cell-center spawn).
3. Set initial direction vector + camera plane based on N/S/E/W:
   - `N` → dir = (0, -1), plane = (0.66, 0)
   - `S` → dir = (0, 1), plane = (-0.66, 0)
   - `E` → dir = (1, 0), plane = (0, 0.66)
   - `W` → dir = (-1, 0), plane = (0, -0.66)
4. Replace the player char in `data->map` with `'0'` so the raycaster and movement code only see `0`/`1`/space.

This separation matches your instinct: validation says *"is this map structurally OK?"*, init says *"set up runtime state from it."*

## Recommended check order (fail fast, cheap-first)

```
correct_permission   <- O(1) syscalls, fastest
textures_path_valid  <- header pass, advance cursor
floor_ceil_rgb_valid <- header pass, advance cursor
map_valid            <- everything past the cursor is map; char set + flood fill
```

### Reading strategy: single read + position cursor

Read the whole file into one buffer (or use a single `get_next_line` loop), then keep a **cursor** — either a `char *` into the buffer or a line-index — that each validator advances past what it consumed. After header validation finishes, the cursor sits at the first line of the map. `map_valid` reads from that point onward without re-opening the file or re-parsing the header.

Replace `int fd_map` parameter on the validators with something like:

```c
typedef struct s_parse_ctx {
    char  *buf;       // full file contents
    char  *cursor;    // current parse position; advanced by each validator
    char  *end;       // one past last byte
}   t_parse_ctx;
```

Or simpler — track line index:

```c
typedef struct s_parse_ctx {
    char **lines;     // file split into lines, NULL-terminated
    int    cur;       // index into lines[]; first unconsumed line
    int    count;
}   t_parse_ctx;
```

The line-array form is friendlier for the map flood fill (random access by row/col), so prefer it. `handle_args` builds the array once, then each check moves `cur` forward past blank lines and any element it owns.

## Common gotchas

- **CRLF line endings** — files saved on Windows have `\r\n`. Strip `\r` defensively or reject.
- **Trailing whitespace on element lines** — `NO ./tex.png   ` (trailing spaces) — should accept but trim.
- **Empty lines between elements** before the map — explicitly allowed by subject.
- **Map in the middle of the file** — explicitly forbidden.
- **A leading BOM** (`\xEF\xBB\xBF`) on UTF-8 saved files — rare, but reject or strip.
- **Memory leaks on error path** — every `Error\n` exit path must `free()` everything allocated so far. Run with leak checker (`valgrind` on Linux, `leaks` on macOS).

## Files to modify

- [42Cub3d/srcs/validate.c](42Cub3d/srcs/validate.c) — implement all five functions
- [42Cub3d/includes/cub3d.h](42Cub3d/includes/cub3d.h) — extend `t_data` with map storage, player position, texture paths, RGB values
- Likely a new `srcs/parser.c` to host helpers (RGB parser, line tokenizer, flood fill) — `validate.c` shouldn't grow past Norm's function/file limits

## Verification

You already have an extensive test suite at `42Cub3d/maps/invalid/`:

- `bad/` — 28 single-failure-mode files (wall_hole_*, player_*, map_*, color_*, textures_*, forbidden, empty)
- `map_tests/` — `test1.cub` through `test20.cub`, focused on map-content failures
- `texture_tests/` — texture-path failures
- `color_tests/` — RGB failures

**Coverage check** — the tagged test files in section 5 above confirm `map_valid` catches every map-related failure case in the suite.

**Missing test cases worth adding** (your suite doesn't seem to cover these):
- `crlf_endings.cub` — file with `\r\n` line endings
- `valid/jagged_rows.cub` — a map that **passes** despite irregular row lengths (positive test)
- `valid/non_standard_order.cub` — F before NO, etc., still valid
- `not_dot_cub.cub`, `something.txt` — wrong extension (handled by `correct_permission`, but worth a test)
- A `valid_xpm.cub` that has `.xpm` paths — your `bad/textures_not_xpm.cub` exists but the meaning depends on whether you accept `.xpm` (mandatory should reject since you're using MLX42 + PNG; some textures_*.cub tests already check this).

**How to run the suite**:

```sh
# All invalid maps must exit non-zero with "Error\n..."
for f in maps/invalid/bad/*.cub maps/invalid/map_tests/*.cub; do
    ./cub3D "$f" >/dev/null 2>&1
    if [ $? -eq 0 ]; then echo "FAIL: $f should have errored"; fi
done

# All valid maps must open the window
for f in maps/valid/*.cub; do
    ./cub3D "$f"  # spot check by eye
done
```

**Memory leak verification on error paths** (macOS):

```sh
for f in maps/invalid/bad/*.cub; do
    leaks --atExit -- ./cub3D "$f" 2>&1 | grep -E "leaks for|Error"
done
```
Every error path must `free()` allocations made up to that point — partial parses are the most leak-prone area.
