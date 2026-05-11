# Map Validation Plan for cub3D Mandatory

## Strategy: two-pass parsing

Pass 1 reads the file and stores raw values into the struct. Pass 2 validates the meaning of those stored values without re-reading the file.

---

## Status

| Step | What | File | Status |
|---|---|---|---|
| 0 | File access (`.cub` ext, regular file, openable, non-empty) | [srcs/parsing/permission.c](srcs/parsing/permission.c) | ✅ done |
| 1a | Read full file into `data->file[]` | [srcs/parsing/map_copy.c](srcs/parsing/map_copy.c) | ✅ done |
| 1b | Classify lines, store header values, build `data->map[][]` | [srcs/parsing/extract_data.c](srcs/parsing/extract_data.c) + [helps_to_extract.c](srcs/parsing/helps_to_extract.c) | ✅ done — leave as-is |
| 2a | Texture paths (.png + file exists) | [srcs/parsing/check_textures.c](srcs/parsing/check_textures.c) | ✅ done |
| 2b | F/C RGB validation + hex packing | [srcs/parsing/check_textures.c](srcs/parsing/check_textures.c) | ✅ done |
| 2c | Map: char set + player + closure | [srcs/parsing/check_map.c](srcs/parsing/check_map.c) | ⏳ **in progress** — needs closure check |
| 3 | Save player position + orientation char | (in `check_map`) | ⏳ pending |

Wired into the pipeline in [srcs/main.c:59-72](srcs/main.c#L59-L72).

**Decision: no `normalize_row`.** `data->map[i]` stays exactly what `gnl` produced — possibly with trailing `\n`, possibly with internal/trailing tabs. Each Pass 2c check handles whitespace explicitly. The current code already does this.

---

## Pass 2c: `check_map` — what it has and what's missing

### What's there now ([srcs/parsing/check_map.c](srcs/parsing/check_map.c))

- `check_borders` — checks the top row is all `1`s, the bottom row is all `1`s, and the last non-whitespace char of each middle row is `1`. **Insufficient.** Fails on the example you gave:

  ```
  111111
  100001
  100001
  101111
  1  1111   ← `0` at row 3 col 1 has a space below it; check_borders only checks "last char is 1"
  ```

  `check_top_or_btm` also has a logic bug: it stops at the first whitespace after some `1`s (`1  1111` → reads `1`, hits space, returns OK — never sees the `1111` after the space).

- `check_elements` — walks the map, builds char-set check, records the player. **Has a real bug**: the inner `while (map[i][j] <= 32) j++;` has no `&& map[i][j]` guard. If a row ends in whitespace, this walks past `\0` into undefined memory.

- `check_player_start_position` — empty stub. Currently does nothing.

### What it should do

Replace `check_borders` (and absorb `check_player_start_position`) with **two** orthogonal passes over `data->map`:

1. **Char-set + player walk** — fix the existing `check_elements`, also save player x/y.
2. **Closure check** — your "every 0 must be surrounded by 1s or NSEW" idea is correct and is simpler than flood fill.

---

## Step 1: char-set + player walk

Walk every cell. For each `data->map[r][c]`:

- If `c` is `'\n'`, `'\r'`, `' '` → skip (allowed; spaces represent void).
- If `c` is `'\t'` → skip (treat as space; you decided not to reject).
- If `c` is in `{'0', '1'}` → fine.
- If `c` is in `{'N', 'S', 'E', 'W'}`:
  - If a player was already recorded → `MULTIPLE_PLAYER`.
  - Else record `data->player.orientation = c; data->player.x = c; data->player.y = r;`.
- Else → `WRONG_CHAR`.

After the walk: if `data->player.orientation == '0'` (sentinel) → `NO_PLAYER`.


## Step 2: closure check (per-cell adjacency)

Your insight is right: **every walkable cell** (`0`, `N`, `S`, `E`, `W`) must have its 4 neighbors all be walls (`1`) or other walkable cells (`0`/`N`/`S`/`E`/`W`). If any neighbor is a space, a tab, out-of-bounds, or anything else → the map is open.

This is equivalent to flood fill in terms of what it catches, but simpler:
- No recursion, no stack overflow risk.
- No visited array needed.
- One double loop, ~25 lines.

### What `check_closure` catches by failure mode

| Test file | Failure mode | How it's caught |
|---|---|---|
| `bad/wall_hole_north.cub` | hole on top edge | `0` at `r=0` looks up to `r=-1` → OOB → `neighbor_ok` returns 0 |
| `bad/wall_hole_south.cub` | hole on bottom edge | `0` at last row looks down → OOB |
| `bad/wall_hole_east.cub` | hole on right edge | `0` at end of row looks right → OOB |
| `bad/wall_hole_west.cub` | hole on left edge | `0` at col 0 looks left → OOB |
| `bad/wall_none.cub` | all `0`s, no walls | every cell on the boundary has OOB neighbor → fail |
| `bad/player_on_edge.cub` | player at row 0 | player looks up → OOB |
| `bad/forbidden.cub` | `0` adjacent to space | `neighbor_ok` returns 0 (space isn't wall or walkable) |
| your example: `1  1111` | space below a `0` | same |
| `map_tests/test1`, `test5`–`test9` | interior leaks | same |

---
