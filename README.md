*This project has been created as part of the 42 curriculum by nkuydin, matnusko.*

# cub3D

## Installation Insctructions

### macOS prerequisite

GLFW is required to build MLX42. On macOS, install it through Homebrew:

```sh
brew install glfw
```

### MLX42

This project depends on [MLX42](https://github.com/codam-coding-college/MLX42), a simple cross-platform graphics library built on top of GLFW. Follow the official installation guide to set it up:

[MLX42 — Installation](https://github.com/codam-coding-college/MLX42#installation-%EF%B8%8F)

 - git clone https://github.com/codam-coding-college/MLX42.git
 - cd MLX42
 - cmake -B build # build here refers to the outputfolder.
 - cmake --build build -j4 # or do make -C build -j4

### Build

Once GLFW is installed and MLX42 is in place, build the project with:

```sh
make
```

### Usage

```sh
./cub3d <path/to/map.cub>
```

---

## Description

**cub3D** is a 42 school project inspired by the legendary *Wolfenstein 3D* — the game that pioneered the first-person shooter genre back in 1992. The goal is to build a small graphical engine in C that renders a 3D-looking maze from a 2D map description, using the **raycasting** technique.

Starting from a plain text file describing walls, floor, ceiling, textures and the player's spawn position, the program opens a window and immerses the player inside the maze. From there you can walk around, look at the textured walls, and explore — all rendered one vertical strip of pixels at a time, the same way id Software did it more than thirty years ago.

### Features

- Parsing of `.cub` map files with validation of map shape, characters, textures and colors
- Raycasting renderer producing a 3D perspective from a 2D grid
- Differently textured walls depending on their orientation (North, South, East, West)
- Configurable floor and ceiling colors
- Smooth player movement (`W`, `A`, `S`, `D`) and camera rotation (arrow keys)
- Clean window management — closing via the cross or `ESC` exits gracefully

### The `.cub` map format

A map file describes the scene through a small set of identifiers followed by the map grid itself:

```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 220,100,0
C 225,30,0

        1111111111111111
        1000000000000001
        1011000001110001
        1001000000000001
1111111111011000001110001
100000000011000000010001
101111111111111111110000001
1011000000000000000000001N1
1011000111111111111111111111
11111111
```

- `NO`, `SO`, `WE`, `EA` — paths to the wall textures for each cardinal direction
- `F` and `C` — floor and ceiling colors as RGB triplets
- `0` walkable space, `1` wall, `N`/`S`/`E`/`W` player spawn and starting orientation

### Controls

| Key       | Action          |
|-----------|-----------------|
| `W`       | Move forward    |
| `S`       | Move backward   |
| `A`       | Strafe left     |
| `D`       | Strafe right    |
| `←` / `→` | Rotate camera   |
| `ESC`     | Quit            |


## Resources

- [RayCasting in Cub3D Medium Tutorial](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a)
- [Someone's Readme - Good for Concepts & Ideas](https://mintlify.wiki/ibon-ira/Cub3d/introduction)
- [Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-1/#INTRODUCTION)
- [Lode's Computer Graphics Tutorial - RayCasting](https://lodev.org/cgtutor/raycasting.html)
- [Someone's Cub3D Explanation](https://hackmd.io/@nszl/H1LXByIE2#Map-parsing-and-validating)