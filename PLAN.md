# Map Validation Plan for cub3D Mandatory

## Strategy: two-pass parsing

Validation runs in two distinct phases. **Pass 1** confirms the file is structurally shaped right and *stores* the raw values into the struct. **Pass 2** validates the meaning of those stored values. After Pass 1, no further file I/O for header content — everything is read back from the struct.

```
Pass 1 (file → struct):  structural parse + store
Pass 2 (struct → check): semantic validation
```

This keeps each function single-purpose, decouples I/O from semantics, makes errors easier to localize, and means the raycaster/init step also reads from the struct rather than re-parsing.

---

## Pass 0: file access

`correct_permission(t_data *data, char **argv)` — already implemented in [srcs/parsing/permission.c](srcs/parsing/permission.c).

- `argv[1]` not NULL.
- Filename ends in `.cub` (exactly — `map.cub.bak` fails; `.cub` alone fails).
- `stat()` succeeds and `S_ISREG` (reject directories — opening a dir succeeds on some systems and gives garbage).
- `open(O_RDONLY)` succeeds.
- File is not empty.

---

## Storage: extend `t_data`

Pass 1 needs somewhere to write to. Replace the empty `t_texrgbinfo` placeholder in [includes/cub3d.h:43-46](includes/cub3d.h#L43-L46) with concrete fields:

- Four texture path strings: `no_path`, `so_path`, `we_path`, `ea_path` (NULL until set; duplicates detected by "already non-NULL").
- Two RGB raw strings (or two `int[3]` triples, decided in Pass 2): `f_rgb`, `c_rgb`.
- Map line array: `char **map_lines`, `int map_height`.
- Player triple `(x, y, orient)` — populated during Pass 2 map validation, consumed by `init_player`.

Either nest a `t_scene` inside `t_data`, or flatten — your call. Just commit to the shape before writing parser code.

---

## Pass 1: structural parse + store

Pass 1 is split into two sub-steps that already have files on disk:

### 1a. `map_copy_into_file` — raw file copy ✅ done

[srcs/parsing/map_copy.c](srcs/parsing/map_copy.c) reads the whole `.cub` into `data->file` (a `char **` of every line, NULL-terminated) plus `data->line_count` and `data->path`. No interpretation — just an in-memory mirror of the file so subsequent steps don't re-open the FD.

### 1b. `extract_data` — structural parse + store (today's task)

[srcs/parsing/extract_data.c](srcs/parsing/extract_data.c) walks `data->file[]` once and dispatches each non-blank line. **No value validation at this step** — just identify, store, and enforce structural rules.

For each line:

- **Header line** — first token is `NO`/`SO`/`WE`/`EA`/`F`/`C` followed by whitespace:
  - Take the remainder of the line (trimmed) and assign it to the matching field on `data->texrgbinfo`:
    - `NO` → `texrgbinfo.north`
    - `SO` → `texrgbinfo.south`
    - `WE` → `texrgbinfo.west`
    - `EA` → `texrgbinfo.east`
    - `F`  → `texrgbinfo.floor` (raw string for now; parse to ints in Pass 2)
    - `C`  → `texrgbinfo.ceiling` (same)
  - **If that field is already non-NULL → duplicate identifier → error.** This is the only "validation" Pass 1b does on header values.
  - Do **not** check that the path ends in `.png`, that the file exists, that RGB is 3 ints, or anything else about the value itself. That's Pass 2's job.

- **Map line** — line consists only of `0`/`1`/space/`N`/`S`/`E`/`W`:
  - Flip a `map_started` flag and append the line to a real 2D map buffer `data->map[][]` (a separate `char **` from `data->file`, owned by Pass 1b — `data->file` stays as the raw source-of-truth copy).
  - Track `data->map_height`.

- **Blank line**:
  - Allowed *before* the map starts (acts as separator between header and map, or between header lines).
  - **Forbidden once the map has started** — terminates the map; any further content is structurally illegal.

- **Anything else** (unknown identifier, garbage line, header line appearing after `map_started`): error.

### Pass 1b structural invariants — enforced here, not later

- **Each of the six identifiers appears at most once** (duplicate detection during store; see above).
- **Map lives at the end of the file.** Once `map_started` flips true, no header line and no blank line is allowed after it. This rejects:
  - Map at the start (followed by headers).
  - Map in the middle (headers after map lines).
  - Maps split by a blank line in the middle.
- **All six header fields end up non-NULL** (else: missing element — checked once at the end of Pass 1b).
- **`data->map` has at least one row** (else: missing map).

The header *order* among NO/SO/WE/EA/F/C is **not** restricted — subject allows any order, only requires all six precede the map.

### Storage shape after Pass 1b

- `data->file[]` — raw line copy (already populated by 1a).
- `data->texrgbinfo.north / .south / .west / .east` — raw path strings (no `.png` check yet).
- `data->texrgbinfo.floor / .ceiling` — raw RGB strings (no parse-to-int yet).
- `data->map[][]` — clean 2D char array of just the map rows (no header/blank lines).
- `data->map_height` — row count.

### Gotchas

- **CRLF endings** — strip trailing `\r` defensively before tokenizing.
- **Trailing whitespace on header lines** — trim before storing.
- **Leading BOM** (`\xEF\xBB\xBF`) — rare; strip or reject.
- **Partial-store leaks** — every error exit must free whatever has been stored so far on `data` (texture path strings, partial `data->map` rows). Pass 1b is the leakiest area.

---

## Pass 2: semantic validation (struct → check)

Each validator reads from `t_data` only. No FD, no cursor, no re-parsing.

### 2a. `textures_path_valid(t_data *data)`

For each of the four stored paths:

- Path is non-empty.
- Path ends in `.png` (MLX42 only loads PNG) — already have `wrong_png` helper in [srcs/parsing/permission.c:33-43](srcs/parsing/permission.c#L33-L43).
- File at that path opens for reading (reuse `check_file(path, false)`).
- Reject trailing garbage on the original line — actually catch this in Pass 1 when tokenizing (a header line should have exactly identifier + path, no third token).

### 2b. `floor_ceil_rgb_valid(t_data *data)`

For each of the two stored RGB strings:

- Exactly three comma-separated tokens (count commas; reject 2 or 4).
- Each token is purely digits (no `+`, no `.`, no letters).
- Each parses to an integer in **[0, 255]**.
- **Whitespace around commas**: subject doesn't explicitly allow it. Pick a stance — strict (reject `220, 100, 0`) is safer for evaluators, but most accept it. Document the choice in code.
- Store parsed `int[3]` back into the struct (or a separate field) so the renderer reads ints, not strings.

### 2c. `map_valid(t_data *data)`

Operates on `map_lines[]` only.

**Character set.** Only `0`, `1`, ` `, `N`, `S`, `E`, `W` allowed. **Tabs rejected** — confirmed by `map_tests/test4.cub` and `map_tests/test15.cub`. Anything else → error.

**Player count.** Exactly **one** of `{N, S, E, W}` across all cells. Zero → error. Two or more → error (note `1NW1` row from `test19.cub` — N at col 1, W at col 2, two players).

**Walkable region exists.** Total `0` + player cells ≥ 1. A 3×3 of all `1`s is invalid (`bad/map_too_small.cub`).

**Closure via flood fill** — the killer check. BFS/DFS from the player position over `0` cells. Map is closed iff:
1. No cell index ever goes out of array bounds (negative row/col, row ≥ height, or col ≥ length of *that specific row*).
2. No `0` cell is 4-adjacent to a space character.

If either fails → not closed → error.

**Jagged rows reminder.** Rows may legally have different lengths. When checking neighbours, treat `col ≥ len(this_row)` as out-of-bounds, not as space:
```
11111
10001
10001
1001    <- 4 wide; cell (3,1)'s right neighbour at col 4 doesn't exist → OOB → leak
11111
```

This single flood fill catches:
- All `bad/wall_hole_*.cub` (boundary cells with no wall → OOB neighbour).
- `bad/wall_none.cub` (all 0s).
- `bad/player_on_edge.cub` (BFS step looks past row 0).
- `bad/forbidden.cub` (0s adjacent to space).
- `map_tests/test1.cub`, `test5.cub`–`test9.cub` — interior leaks and short-row gaps.

**Note: `map_valid` only validates.** It records the player triple `(x, y, orient)` into the struct but does **not** rewrite the map or set up direction vectors. That's `init_player`'s job (next section).

---

## After validation: `init_player`

Once Pass 2 returns success:

1. Read the recorded player triple from `t_data`.
2. Set `data->player.x`, `data->player.y` (typically + 0.5 for cell-center spawn).
3. Set initial direction vector + camera plane based on N/S/E/W:
   - `N` → dir `(0, -1)`, plane `(0.66, 0)`
   - `S` → dir `(0, 1)`, plane `(-0.66, 0)`
   - `E` → dir `(1, 0)`, plane `(0, 0.66)`
   - `W` → dir `(-1, 0)`, plane `(0, -0.66)`
4. Replace the player char in `map_lines` with `'0'` so the raycaster only sees `0`/`1`/space.

Validation answers *"is this map structurally OK?"* — init answers *"set up runtime state from it."*

---

## Recommended call order

```
correct_permission     <- O(1) syscalls, fastest
map_copy_into_file     <- Pass 1a: file → data->file[] raw copy (done)
extract_data           <- Pass 1b: classify lines, store header values,
                          build data->map[][], enforce map-at-end + uniqueness
textures_path_valid    <- Pass 2: validate stored texture paths
floor_ceil_rgb_valid   <- Pass 2: parse + range-check stored RGB strings
map_valid              <- Pass 2: char set + player count + flood fill
init_player            <- consume player triple, prep runtime state
```

---

## Files to modify

- [includes/cub3d.h](includes/cub3d.h) — flesh out `t_texrgbinfo` (or rename to `t_scene`) with texture paths, RGB triples, map lines, player triple. Add prototypes for new parser functions.
- [srcs/parsing/validate.c](srcs/parsing/validate.c) — currently stubbed. Implement Pass 2 validators here.
- [srcs/parsing/textures.c](srcs/parsing/textures.c) — currently a one-line stub. Implement texture path checks here.
- New `srcs/parsing/parse_store.c` (or similar) — Pass 1 driver.
- New `srcs/parsing/map.c` — flood fill + player count + char set checks (separate to keep `validate.c` under Norm function/file limits).
- [srcs/main.c:38-46](srcs/main.c#L38-L46) — wire `parsing()` to call the new pipeline; currently only calls `check_file`.
- [srcs/utils/error.c](srcs/utils/error.c) — extend `ft_error` to free the new struct fields once they're added.

---

## Verification

Test suite at `42Cub3d/maps/invalid/`:

- `bad/` — 28 single-failure-mode files.
- `map_tests/` — `test1.cub` through `test20.cub`, focused on map content.
- `texture_tests/` — texture path failures.
- `color_tests/` — RGB failures.

```sh
# All invalid maps must exit non-zero with "Error\n..."
for f in maps/invalid/bad/*.cub maps/invalid/map_tests/*.cub; do
    ./cub3D "$f" >/dev/null 2>&1
    if [ $? -eq 0 ]; then echo "FAIL: $f should have errored"; fi
done

# All valid maps must open the window
for f in maps/valid/*.cub; do
    ./cub3D "$f"
done
```

**Leak check on error paths** (macOS):

```sh
for f in maps/invalid/bad/*.cub; do
    leaks --atExit -- ./cub3D "$f" 2>&1 | grep -E "leaks for|Error"
done
```

Every error path must free everything stored up to that point — Pass 1 partial stores are the leakiest area.

**Worth adding to the suite:**
- `crlf_endings.cub` — `\r\n` line endings.
- `valid/jagged_rows.cub` — irregular row lengths that should pass.
- `valid/non_standard_order.cub` — F before NO, etc., still valid (confirms order independence).
- `not_dot_cub.cub`, `something.txt` — wrong extension.
