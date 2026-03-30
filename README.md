*This project has been created as part of the 42 curriculum by dgeara.*

# SO_LONG

## Description

so_long is a small 2D game project from the 42 curriculum, built entirely in C using **MiniLibX** — a minimal graphical library based on x11.

You play as a character on a tile-based map. The objective is simple: **collect all collectibles, then reach the exit** — in as few moves as possible. The game renders sprites, handles keyboard input, tracks your move count, and validates the map before anything starts.

The real challenge is making sure the map is actually solvable before the game even begins — which means implementing a **flood fill** algorithm to check that all collectibles and the exit are reachable from the player's starting position.

### Features

**Mandatory**
- Tile-based map rendered with MiniLibX (walls, floor, player, collectibles, exit)
- Keyboard movement (W/A/S/D or arrow keys) with wall collision
- Move counter printed to the terminal on each step
- Map validation: rectangular shape, surrounded by walls, exactly one player, one exit, at least one collectible
- Flood fill reachability check — map must be completable

**Bonus**
- Enemies that kill the player on contact
- Animated sprites (frame-based animation loop)
- Move counter displayed directly on screen (not just terminal)

---

## MiniLibX
 
MiniLibX is a lightweight graphical library  offering a simple way to open windows, draw pixels, load images, and handle keyboard/mouse events — without the complexity of a full graphics framework.
 
It's built on top of **X11** (the windowing system used on Linux) and **AppKit** on macOS. Under the hood, it wraps just enough of those APIs to let you put pixels on a screen and react to input.
 
Here's what it exposes:
 
| Function family | What it does |
|---|---|
| `mlx_init` / `mlx_new_window` | Creates the display connection and opens a window |
| `mlx_xpm_file_to_image` | Loads an XPM sprite from disk into memory |
| `mlx_put_image_to_window` | Draws an image at a given (x, y) position in the window |
| `mlx_hook` | Registers a callback for a specific event (keypress, window close...) |
| `mlx_loop` / `mlx_loop_hook` | Starts the event loop — keeps the window alive and fires hooks each frame |
 
The key mental model: **MiniLibX is event-driven**. You don't write a `while(1)` yourself — you register hooks and let `mlx_loop` call them. Your game logic lives inside those hooks.
 
To find the keycode for a specific key, you can temporarily print it with:
```c
ft_printf("%d\n", keycode);
```
Then press the key in-game and read the value from the terminal.
 
---
## Instructions

### Compilation

```
make
```

This produces the `so_long` binary.

```
make clean    # remove object files
make fclean   # remove object files + binary
make re       # fclean + make
```

For the bonus version:

```
make bonus
```

### Map format

Maps are `.ber` files. Valid characters are:

| Character | Meaning       |
|-----------|---------------|
| `1`       | Wall          |
| `0`       | Empty floor   |
| `P`       | Player start  |
| `E`       | Exit          |
| `C`       | Collectible   |
| `X`       | Enemies       |

Example map:

```
1111111111
10C0000001
1000011101
1P0011E001
1111111111
```

Rules:
- Must be rectangular
- Must be fully surrounded by walls (`1`)
- Exactly **one** `P` and **one** `E`
- At least **one** `C`
- All collectibles and the exit must be reachable from `P`

### Usage

```
./so_long maps/map.ber
```

```
./so_long_bonus maps/map.ber
```

### Error handling

The program prints `Error` to stderr and exits if:
- The map file is missing or unreadable
- The map doesn't meet the format requirements
- The map is not completable (flood fill fails)

### Controls

| Key           | Action     |
|---------------|------------|
| `W` / `↑`    | Move up    |
| `S` / `↓`    | Move down  |
| `A` / `←`    | Move left  |
| `D` / `→`    | Move right |
| `ESC`         | Quit       |

---

## Resources

### MiniLibX
- [Getting started with MiniLibX — Aurélien Brabant](https://aurelienbrabant.fr/blog/getting-started-with-the-minilibx)

### Algorithms
- [Flood fill — Wikipedia](https://en.wikipedia.org/wiki/Flood_fill)
- [Flood fill — GeeksForGeeks](https://www.geeksforgeeks.org/problems/flood-fill-algorithm1856/1)

### XPM format
- [X PixMap — Wikipedia](https://en.wikipedia.org/wiki/X_PixMap)

### More fun 
- [Oscillator (cellular automaton) — Wikipedia](https://en.wikipedia.org/wiki/Oscillator_(cellular_automaton))
- [Conway's Life oscillators reference](https://conwaylife.com/book/oscillators)
---

### AI usage

Claude (Anthropic) was used during this project for:

- **MiniLibX** — understanding how the event loop works, how to hook keyboard events, and how to push images to the window correctly
- **Flood fill** — clarifying the algorithm logic (recursive vs iterative), understanding how to mark visited tiles without corrupting the original map
- **Debugging** — interpreting segfaults and memory errors, understanding when and why to free things in a graphical context

	ft_printf("%d\n", keycode);