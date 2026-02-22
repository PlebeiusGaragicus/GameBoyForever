# Creating a Game

## Step 1: Copy the Template

```bash
cp -r games/_template games/MyGame
```

Edit `games/MyGame/Makefile` and set `PROJECTNAME`:

```makefile
PROJECTNAME = mygame
```

## Step 2: Write Game Logic

Edit `src/main.c`. A basic game loop looks like:

```c
#include <gbdk/platform.h>
#include <stdint.h>

void main(void) {
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    while (1) {
        wait_vbl_done();

        uint8_t keys = joypad();
        if (keys & J_UP)    { /* move up */ }
        if (keys & J_DOWN)  { /* move down */ }
        if (keys & J_LEFT)  { /* move left */ }
        if (keys & J_RIGHT) { /* move right */ }
        if (keys & J_A)     { /* action */ }
    }
}
```

## Step 3: Add Graphics

1. Create a 8x8 or 8x16 pixel PNG for your tiles/sprites.
2. Convert using GBDK's `png2asset`:

    ```bash
    ${GBDK_HOME}bin/png2asset sprite.png -o res/sprite.c
    ```

3. Include the generated header in your source:

    ```c
    #include "res/sprite.h"
    ```

## Step 4: Build and Test

```bash
cd games/MyGame
make gb
```

Open `build/gb/mygame.gb` in Emulicious.

## Step 5: Iterate

Refer to the reference projects for patterns:

- **BlackCastle** (`references/BlackCastle/`) -- multi-platform game with state machines, scrolling, sprites, sound
- **gb-studio** (`references/gb-studio/appData/`) -- GB Studio's C engine showing scene management, scripting, UI
- **gbdk-2020** (`references/gbdk-2020/gbdk-lib/examples/`) -- official GBDK examples covering every API

## Common GBDK APIs

| Function | Purpose |
|----------|---------|
| `set_bkg_tiles()` | Set background tilemap |
| `set_bkg_data()` | Load background tile data |
| `set_sprite_tile()` | Assign tile to sprite |
| `move_sprite()` | Position a sprite on screen |
| `joypad()` | Read button input |
| `wait_vbl_done()` | Wait for vertical blank (frame sync) |
| `DISPLAY_ON` / `DISPLAY_OFF` | Toggle LCD |
| `SHOW_SPRITES` / `HIDE_SPRITES` | Toggle sprite layer |
| `SHOW_BKG` / `HIDE_BKG` | Toggle background layer |

## Game Boy Color APIs

| Function | Purpose |
|----------|---------|
| `set_bkg_palette()` | Set background color palettes (up to 8 palettes of 4 colors) |
| `set_sprite_palette()` | Set sprite color palettes (up to 8 palettes of 4 colors) |
| `set_bkg_palette_entry()` | Set a single color in a BG palette |
| `set_sprite_palette_entry()` | Set a single color in a sprite palette |
| `VBK_REG = 1` | Switch to VRAM bank 1 (extra tile data) |
| `set_bkg_attributes()` | Assign palette and flags per background tile |
| `cpu_fast()` / `cpu_slow()` | Toggle CGB double-speed mode |
| `RGB(r, g, b)` | Create a 15-bit GBC color (0-31 per channel) |
