# cub3D — progress checklist

## Parsing

- [x] File access checks (`.cub` ext, regular file, openable, non-empty) — `srcs/parsing/permission.c`
- [x] Read full file into `data->file[]` — `srcs/parsing/map_copy.c`
- [x] Classify lines, store header values, build `data->map[][]` — `srcs/parsing/extract_data.c` + `helps_to_extract.c`
- [x] Texture path validation (`.png` + file exists) — `srcs/parsing/check_textures.c`
- [x] F/C RGB validation + hex packing (with 0xFF alpha byte) — `srcs/parsing/check_textures.c`
- [x] Reject tab characters in map (subject only allows the 6 chars + spaces)

## Map validation (`check_map`)

- [x] Char-set + player walk (fixed whitespace overrun bug in `check_elements`)
- [x] Single-player check (`MULTIPLE_PLAYER`)
- [x] Missing-player check (`NO_PLAYER`)
- [x] Map-too-small check (`MAP_TOO_SMALL`)
- [x] Missing-map check (`MISSING_MAP`)
- [x] Per-cell closure check — `check_closure` with `is_open` + `check_neighbors`, ragged-row safe via `ft_strlen`
- [x] Direction-specific wall-hole errors (`WALL_HOLE_NORTH/SOUTH/WEST/EAST`)
- [x] Player must have at least one `0` neighbor (`TRAPPED_PLAYER`) — `check_player_can_move`
- [x] Disconnected regions allowed (no reachability check)

## Error output

- [x] Fixed libft `ft_putstr_fd` (was writing `\n` to hardcoded fd 1, dropped extra newline)
- [x] `print_err_msg` writes to stdout (fd 1) for tester compatibility
- [x] `main` returns 0 on parse failures; `ft_error(data, 0)` for file/copy errors

## Memory

- [x] Zero-init `t_data` via `ft_calloc` to fix uninitialized reads in `extract_data`
- [x] Fixed gnl `ft_read_file` leak (old `storage` abandoned on every `ft_strjoin`)
- [x] `free(data)` in main on parse-failure path
- [x] Valgrind clean on parser tests (Ubuntu VM)

## MLX setup

- [x] Typed `data->mlx` as `mlx_t *` and `data->image` as `mlx_image_t *` (was `void *`)
- [x] Removed premature `mlx_delete_image` from `draw_game`
- [x] Moved `mlx_loop` out of `init_mlx` into `main`, added `mlx_terminate` cleanup
- [x] Registered `mlx_loop_hook` for per-frame rendering
- [x] Floor/ceiling color rendering working

## Test fixtures

- [x] Normalized texture paths in `maps/invalid/bad/` to `textures/yellow/yellow{0..3}.png`
- [x] Kept intentionally-bad texture paths in `textures_dir.cub`, `textures_forbidden.cub`, `textures_invalid.cub`, `textures_not_xpm.cub`

## Rendering — pending (mandatory game logic)

- [ ] Load wall textures into `mlx_texture_t` from the parsed PNG paths (NO/SO/WE/EA)
- [ ] DDA ray-casting per screen column — find first wall hit, capture side (N/S/W/E) + distance
- [ ] Per-column wall stripe height from perpendicular distance
- [ ] Texture-x sampling from wall hit position; texture-y sampling per pixel of stripe
- [ ] Draw wall stripes into the image between ceiling and floor (replaces current solid colors in the wall band)
- [ ] Player init from map (`data->player.pos_x/y`, direction vector, camera plane) based on N/S/E/W spawn

## Input — pending

- [ ] Movement: W/A/S/D translate `pos_x/pos_y` along/perpendicular to direction vector, with wall collision
- [ ] Rotation: left/right arrows rotate direction vector + camera plane
- [ ] ESC and window-close button → clean exit (`mlx_close_window` + `mlx_terminate`)

 - (1) Calculating distance
    find horizontal intersection
    find vertical intersection
    find the nearest intersection
(it does mean intersection of the ray/line with the wall)
 - (2) Render based on the distance