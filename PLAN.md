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

**Bug to fix in your existing `check_elements`**: the inner whitespace skip needs the null guard:

```c
while (map[i][j] && map[i][j] <= 32)
    j++;
```

Without `map[i][j] &&`, the loop walks past `\0` if the row ends in whitespace.

Also: the outer `while (map[i][j])` only handles the first call, then the inner while modifies `j`. After the inner skip, you need to re-check `if (!map[i][j]) break;` or the same guard pattern. The cleanest is one loop with all the conditions in the right order:

```c
while (map[r][c])
{
    if (map[r][c] == '\n' || map[r][c] == '\r')
        break ;                          // end of row
    if (map[r][c] == '\t' || map[r][c] == ' ')
    {
        c++;
        continue ;
    }
    if (!ft_strchr("01NSEW", map[r][c]))
        return (print_err_msg(WRONG_CHAR));
    if (ft_strchr("NSEW", map[r][c]))
    {
        if (data->player.orientation != '0')
            return (print_err_msg(MULTIPLE_PLAYER));
        data->player.orientation = map[r][c];
        data->player.x = c;
        data->player.y = r;
    }
    c++;
}
```

Add `int x; int y;` to the `t_player` struct in [includes/cub3d.h:81-85](includes/cub3d.h#L81-L85). Initialize `data->player.orientation = '0';` at the start of `check_map`.

---

## Step 2: closure check (per-cell adjacency)

Your insight is right: **every walkable cell** (`0`, `N`, `S`, `E`, `W`) must have its 4 neighbors all be walls (`1`) or other walkable cells (`0`/`N`/`S`/`E`/`W`). If any neighbor is a space, a tab, out-of-bounds, or anything else → the map is open.

This is equivalent to flood fill in terms of what it catches, but simpler:
- No recursion, no stack overflow risk.
- No visited array needed.
- One double loop, ~25 lines.

### Why your example fails this check

```
111111
100001
100001
101111
1  1111
```

Cell `(3, 1)` is `0`. Its neighbor `(4, 1)` is `' '` (space). Neighbor is not in `{0, 1, N, S, E, W}` → leak → `MAP_NOT_CLOSED`. Caught.

The case `check_borders` fails on (`0` adjacent to space when neither is on the outer border) is exactly what this check handles.

### Pseudocode

```c
static int  is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int  is_wall_or_walkable(char c)
{
    return (c == '1' || is_walkable(c));
}

static int  row_real_len(char *row)
{
    int  i;

    i = 0;
    while (row[i] && row[i] != '\n' && row[i] != '\r')
        i++;
    return (i);
}

static int  neighbor_ok(char **map, int height, int r, int c)
{
    if (r < 0 || r >= height)
        return (0);
    if (c < 0 || c >= row_real_len(map[r]))
        return (0);
    return (is_wall_or_walkable(map[r][c]));
}

static int  check_closure(t_data *data)
{
    int  r;
    int  c;
    int  h;

    h = data->mapinfo.row_count;
    r = 0;
    while (r < h)
    {
        c = 0;
        while (c < row_real_len(data->map[r]))
        {
            if (is_walkable(data->map[r][c]))
            {
                if (!neighbor_ok(data->map, h, r - 1, c)
                    || !neighbor_ok(data->map, h, r + 1, c)
                    || !neighbor_ok(data->map, h, r, c - 1)
                    || !neighbor_ok(data->map, h, r, c + 1))
                    return (print_err_msg(MAP_NOT_CLOSED));
            }
            c++;
        }
        r++;
    }
    return (0);
}
```

Five small functions, all under Norm. `row_real_len` exists so trailing `\n` doesn't make the row look one cell wider than it really is.

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

## Player position: just record it

You said "save position and direction (a char), don't worry about init_player." Agreed — drop the whole `init_player` discussion from the plan.

What you save:
- `data->player.x` (int, the column where `N`/`S`/`E`/`W` was found)
- `data->player.y` (int, the row)
- `data->player.orientation` (the char itself: `'N'`, `'S'`, `'E'`, or `'W'`)

That's it. Convert to floats and direction vectors when the raycaster needs them, not now. `check_map`'s job is done once these three are set.

### About "+0.5" — why it's there, and whether you need it

The reason raycasters spawn at `(x + 0.5, y + 0.5)` instead of `(x, y)`:

- Map cells are 1×1 squares in world coordinates. Cell `(col, row)` occupies the square from `(col, row)` to `(col+1, row+1)`.
- The point `(col, row)` is the top-left **corner** of that cell — sitting exactly on the boundary between four cells.
- Spawning at a corner means: the player's position is on the edge of four cells simultaneously. Wall-collision checks (which test "is the cell at `(int)x, (int)y` a wall?") become ambiguous at boundaries — depending on floating-point rounding, you might be "in" the wall to your upper-left.
- `+0.5` puts the player at the **center** of the cell. The player has 0.5 units of clearance to every wall. No ambiguity.

Can you spawn at the corner for stylistic effect? Technically yes, if you also handle the boundary collision correctly. But:
- Visually you'd start clipping into one of the four neighboring walls.
- If any of the four cells around `(x, y)` is a wall (e.g. the cell up-left at `(x-1, y-1)`), you spawn touching it.
- It doesn't add gameplay uniqueness — it just makes the first frame look broken.

If you want the player to spawn somewhere other than the cell center for character, pick `(x + 0.3, y + 0.7)` or whatever — anywhere strictly inside the cell. Don't pick exactly `(x, y)` — that's the corner.

This is all raycaster concern, not validation concern. `check_map` just records integer coordinates; the raycaster picks the spawn offset later.

---

## Recommended call order (final)

```
correct_permission     ← Pass 0 ✅
map_copy_into_file     ← Pass 1a ✅
extract_data_from_file ← Pass 1b ✅
check_textures         ← Pass 2a/2b ✅
check_map              ← Pass 2c ⏳
                        - check_elements  (char set + player record)
                        - check_closure   (per-cell adjacency)
```

---

## Files to modify

- [includes/cub3d.h](includes/cub3d.h) — add `int x;` and `int y;` to `t_player`. Add `MAP_NOT_CLOSED` error macro.
- [srcs/parsing/check_map.c](srcs/parsing/check_map.c) — delete `check_borders` and `check_top_or_btm` (replaced by closure). Fix bug in `check_elements`. Add `check_closure` and helpers. Drop empty `check_player_start_position`.

Adding `MAP_NOT_CLOSED`:

```c
# define MAP_NOT_CLOSED  "Map is not closed; walkable cell adjacent to space or out of bounds"
```

---

## Verification

```sh
for f in maps/invalid/bad/*.cub maps/invalid/map_tests/*.cub \
         maps/invalid/texture_tests/*.cub maps/invalid/color_tests/*.cub; do
    if ./cub3D "$f" >/dev/null 2>&1; then
        echo "FAIL: $f should have errored"
    fi
done

for f in maps/valid/*.cub; do
    ./cub3D "$f"
done
```

After implementing `check_closure`, your example map (the `1  1111` case) should produce `MAP_NOT_CLOSED`, and so should every `bad/wall_hole_*.cub` file in the invalid suite.

---

## What's deliberately out of scope here

- `init_player` — direction/plane vector setup. Live with `data->player.orientation` as a char until the raycaster needs it.
- `normalize_row` / tab translation. Each Pass 2c check handles `\t`/`\n`/`\r` inline.
- Padding rows to uniform width. Jagged rows are handled by `row_real_len` per row.
