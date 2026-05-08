# Map Validation Plan for cub3D Mandatory

## Strategy: two-pass parsing

Validation runs in two phases. **Pass 1** confirms the file is structurally shaped right and *stores* the raw values into the struct. **Pass 2** validates the meaning of those stored values. After Pass 1, no further file I/O for header content — everything is read back from the struct.

```
Pass 1 (file → struct):  structural parse + store
Pass 2 (struct → check): semantic validation
```

---

## Status

| Step | What | File | Status |
|---|---|---|---|
| 0 | File access (`.cub` ext, regular file, openable, non-empty) | [srcs/parsing/permission.c](srcs/parsing/permission.c) | ✅ done |
| 1a | Read full file into `data->file[]` | [srcs/parsing/map_copy.c](srcs/parsing/map_copy.c) | ✅ done |
| 1b | Classify lines, store header values, build `data->map[][]` | [srcs/parsing/extract_data.c](srcs/parsing/extract_data.c) + [helps_to_extract.c](srcs/parsing/helps_to_extract.c) | ✅ done |
| 2a | Texture paths (.png, file exists) | [srcs/parsing/check_textures.c](srcs/parsing/check_textures.c) | ✅ done |
| 2b | F/C RGB validation + hex packing | [srcs/parsing/check_textures.c](srcs/parsing/check_textures.c) | ✅ done |
| 2c | Map: char set, player count, closure (flood fill) | [srcs/parsing/check_map.c](srcs/parsing/check_map.c) | ⏳ **next** |
| 3 | `init_player` — direction/plane vectors, replace player char with `'0'` | (new) | ⏳ pending |
| 4 | Free everything on every error path | [srcs/utils/free_data.c](srcs/utils/free_data.c) | ⏳ ongoing |

Wired into the pipeline in [srcs/main.c:59-72](srcs/main.c#L59-L72) — `parsing()` calls Pass 0 → 1a → 1b → 2a/2b → 2c (stub) → return.

---

## Pass 2c: `check_map` — the plan

This is what you're writing now. It only reads from `data->map[][]` (already populated by Pass 1b). No file I/O.

### Stance on whitespace in the map

The 42 subject says: *"the map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle."*

Your interpretation, agreed:

- **Spaces** in the map are valid. They represent void / outside-the-map. The closure check decides whether a given space is acceptable (no walkable cell adjacent to it) or not (adjacent to a `0` cell → leak).
- **Tabs** are treated as **equivalent to spaces** — both before, inside, and after map content. Authors often use tabs for indentation; they're visually whitespace, so accept them.
- **Trailing `\r` / `\n`** on each row are stripped at storage time.
- Any other character → reject.

After normalization, `data->map[i]` contains only `{ '0', '1', ' ', 'N', 'S', 'E', 'W' }`.

### Step 0 — normalize rows (do this in `extract_data`'s `store_data`, not in `check_map`)

Replace `data->map[data->map_idx] = ft_strdup(line);` with a helper:

```c
static char  *normalize_row(char *line)
{
    int   len;
    int   i;
    char  *res;

    len = 0;
    while (line[len])
        len++;
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        len--;
    res = ft_calloc(len + 1, sizeof(char));
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        if (line[i] == '\t')
            res[i] = ' ';
        else
            res[i] = line[i];
        i++;
    }
    return (res);
}
```

Now `data->map[i]` is "clean" — no `\r`, no `\n`, no `\t`. This makes every subsequent check trivial.

### Step 1 — character set + player position + walkable count (single walk)

Three checks in one loop. For each cell `(r, c)` in `data->map`:

- If char is in `{ '0', '1', ' ' }` → accept, increment walkable count if it's `'0'`.
- If char is in `{ 'N', 'S', 'E', 'W' }` → record `(c, r, char)` as the player triple, increment player count, increment walkable count.
- Else → error (`INVALID_MAP_CHAR`).

After the loop:

- `player_count == 0` → error (`MISSING_PLAYER`).
- `player_count > 1` → error (`MULTIPLE_PLAYERS`).
- `walkable_count == 0` → error (`MAP_NO_WALKABLE`). Catches `bad/map_too_small.cub` (3×3 of `1`s).

Store the player triple on `t_data` (add `int player_x; int player_y; char player_dir;` to the struct, or nest in a `t_player`). `init_player` will consume it later.

### Step 2 — flood fill for closure

This is the killer check. Recursive DFS from the player's position over `'0'` and player cells, marking visited cells. The map is **closed** iff during the flood:

1. No cell index ever goes out of bounds (negative row/col, row ≥ height, or col ≥ length of *that specific row*).
2. No reached cell is 4-adjacent (up/down/left/right) to a `' '` (space).

If either fails → not closed → error.

The standard pattern: copy `data->map` (or use a parallel "visited" 2D array), recurse from `(player_x, player_y)`. On entry to each cell:

- If out of bounds → set "leak" flag, return.
- If cell is `' '` → set "leak" flag, return.
- If cell is `'1'` → return (wall, stop).
- If already visited → return.
- Mark visited. Recurse into four neighbors.

Pseudocode:

```
flood(map, r, c, height, leak):
    if r < 0 or r >= height:
        *leak = true; return
    if c < 0 or c >= row_len(map[r]):
        *leak = true; return
    if map[r][c] == ' ':
        *leak = true; return
    if map[r][c] == '1' or map[r][c] == 'V':   // V = visited marker
        return
    map[r][c] = 'V'
    flood(map, r - 1, c, height, leak)
    flood(map, r + 1, c, height, leak)
    flood(map, r, c - 1, height, leak)
    flood(map, r, c + 1, height, leak)
```

The map is closed iff `leak` is still `false` after the recursion returns. The `'V'` marker stops re-recursion and lets you scan the map afterward to confirm every reachable `'0'` got visited (sanity, optional).

Either:
- **Mutate `data->map` directly.** Cheap. Player char is overwritten with `'V'` then later replaced by `init_player` with `'0'`. Save the player position before flood so you don't lose it.
- **Allocate a separate `char **visited`** to keep `data->map` pristine. Cleaner but extra alloc + free. Use this if you want `init_player` to read the original char.

Either works. Mutating is one fewer allocation — go with that unless you need the original map untouched.

### Jagged-row reminder

Rows may legally have different lengths. **The flood fill must use the actual length of *each row*** when checking out-of-bounds, not a global "max width":

```c
int  row_len(char **map, int r)
{
    int  i;

    i = 0;
    while (map[r][i])
        i++;
    return (i);
}
```

Then `if (c >= row_len(map, r))` → out of bounds. Treating it as "wall" or "space" instead is the classic bug — `bad/wall_hole_*.cub` files exploit this.

### What `check_map` catches, by failure mode

| Test file | Failure mode | Caught by |
|---|---|---|
| `bad/map_missing.cub`, `bad/empty.cub`, `map_tests/test17`, `test18`, `test20` | no map at all | Pass 1b's `MISSING_MAP` (already done) |
| `bad/map_first.cub`, `map_middle.cub`, `file_letter_end.cub`, `map_tests/test8`, `test12`, `test13`, `test14` | header/blank after map starts | Pass 1b's `MAP_NOT_LAST` (already done) |
| `map_tests/test10` (`Q` char) | invalid character | char-set check |
| `bad/player_none.cub`, `map_tests/test2` | no player | player count == 0 |
| `bad/player_multiple.cub`, `map_tests/test11`, `test19` (`1NW1`) | multiple players | player count > 1 |
| `bad/map_too_small.cub` | no walkable | walkable count == 0 |
| `bad/wall_hole_north/south/east/west.cub` | open boundary | flood fill OOB neighbor |
| `bad/wall_none.cub` | all 0s | flood OOB on every edge |
| `bad/player_on_edge.cub` | player at row 0 | flood looks past row -1 → OOB |
| `bad/forbidden.cub`, `map_tests/test1`, `test5`–`test9` | 0 adjacent to space | flood reaches space cell |

That's the full Pass 2c coverage.

---

## Step 3 — `init_player`

Once `check_map` returns success:

1. Read the recorded player triple `(player_x, player_y, player_dir)` from `t_data`.
2. Set `data->player.x = player_x + 0.5; data->player.y = player_y + 0.5;` (cell-center spawn).
3. Set initial direction vector + camera plane based on `player_dir`:
   - `'N'` → dir `(0, -1)`, plane `(0.66, 0)`
   - `'S'` → dir `(0,  1)`, plane `(-0.66, 0)`
   - `'E'` → dir `(1,  0)`, plane `(0,  0.66)`
   - `'W'` → dir `(-1, 0)`, plane `(0, -0.66)`
4. Replace the player char in `data->map[player_y][player_x]` with `'0'` so the raycaster only sees `0`/`1`/space.

This is also where you add the player struct to `t_data`:

```c
typedef struct s_player {
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;
```

`check_map` finishes with the player at integer coordinates; `init_player` upgrades to doubles for ray math.

---

## Recommended call order (no change from before)

```
correct_permission     ← O(1) syscalls, fastest
map_copy_into_file     ← Pass 1a: file → data->file[] raw copy ✅
extract_data_from_file ← Pass 1b: classify, store, build data->map[][] ✅
check_textures         ← Pass 2a/2b: texture paths + RGB ✅
check_map              ← Pass 2c: char set + player + flood fill ⏳
init_player            ← consume player triple, prep runtime state ⏳
```

---

## Files to modify for `check_map`

- [includes/cub3d.h](includes/cub3d.h) — add `int player_x;`, `int player_y;`, `char player_dir;` to `t_data` (or nest in a `t_player`). Add error macros: `INVALID_MAP_CHAR`, `MISSING_PLAYER`, `MULTIPLE_PLAYERS`, `MAP_NO_WALKABLE`, `MAP_NOT_CLOSED`.
- [srcs/parsing/check_map.c](srcs/parsing/check_map.c) — implement char-set + player + walkable scan, plus flood fill driver. Probably split into 2–3 helpers across one or two files (Norm 5-funcs-per-file limit).
- [srcs/parsing/extract_data.c](srcs/parsing/extract_data.c) — apply the `normalize_row` helper inside `store_data` so `\t` becomes `' '` and `\r\n` is stripped before storing.
- [srcs/utils/free_data.c](srcs/utils/free_data.c) — make sure `data->map[]` is freed on every error path.

---

## Verification

Test suite at `maps/invalid/`:

- `bad/` — single-failure-mode files.
- `map_tests/test1.cub` … `test20.cub` — map-content failures.
- `texture_tests/` — texture path failures (already passing).
- `color_tests/` — RGB failures (already passing).

```sh
# Every invalid file must exit non-zero with "Error\n..."
for f in maps/invalid/bad/*.cub maps/invalid/map_tests/*.cub \
         maps/invalid/texture_tests/*.cub maps/invalid/color_tests/*.cub; do
    if ./cub3D "$f" >/dev/null 2>&1; then
        echo "FAIL: $f should have errored"
    fi
done

# Every valid file must open the window
for f in maps/valid/*.cub; do
    ./cub3D "$f"
done
```

**Reclassifications expected under the new tab stance:**

- `map_tests/test4.cub` — has `1P1` (the `P` is the failure, not the tabs). Move to `valid/` if you fix the typo to `1N1`; otherwise it stays invalid because `P` isn't in the allowed set. ❓ pending decision.
- `map_tests/test15.cub` — leading tabs only, otherwise a closed `1N1` 3×3 room. Under the tab-as-space rule, this is **valid**. Move to `maps/valid/`.

**Leak check on error paths** (macOS):

```sh
for f in maps/invalid/bad/*.cub; do
    leaks --atExit -- ./cub3D "$f" 2>&1 | grep -E "leaks for|Error"
done
```

Every error path must free everything stored up to that point. The leakiest area is Pass 1b's partial stores; Pass 2c only adds the player-triple integers (no allocs), so failures inside `check_map` should free the same set as `extract_data`'s success path.

**Worth adding to the suite:**
- `valid/jagged_rows.cub` — irregular row lengths that pass closure (positive test).
- `valid/non_standard_order.cub` — `F` before `NO`, etc., still valid.
- `crlf_endings.cub` — `\r\n` line endings (the `normalize_row` helper should make this work transparently).
