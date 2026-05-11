# cub3D — progress checklist

## Parsing

- [x] File access checks (`.cub` ext, regular file, openable, non-empty) — `srcs/parsing/permission.c`
- [x] Read full file into `data->file[]` — `srcs/parsing/map_copy.c`
- [x] Classify lines, store header values, build `data->map[][]` — `srcs/parsing/extract_data.c` + `helps_to_extract.c`
- [x] Texture path validation (`.png` + file exists) — `srcs/parsing/check_textures.c`
- [x] F/C RGB validation + hex packing — `srcs/parsing/check_textures.c`

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

## Test fixtures

- [x] Normalized texture paths in `maps/invalid/bad/` to `textures/yellow/yellow{0..3}.png`
- [x] Kept intentionally-bad texture paths in `textures_dir.cub`, `textures_forbidden.cub`, `textures_invalid.cub`, `textures_not_xpm.cub`

## Pending

- [ ] Memory leak testing (waiting on Ubuntu VM install)
- [ ] Rendering / DDA / MLX hooks (mandatory game logic)
