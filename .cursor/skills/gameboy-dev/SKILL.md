---
name: gameboy-dev
description: Scaffold and build Game Boy Color games using GBDK-2020. Use when the user asks to create a new game, add features to a game, work with sprites/tiles/palettes/input, build ROMs, or debug with Emulicious.
---

# Game Boy Color Development with GBDK-2020

All games in this repo target Game Boy Color (CGB-only, `-Wm-yC` flag).

## Toolchain

- GBDK-2020 v4.5.0 is installed at `gbdk/` in the repo root
- Emulicious emulator is at `Emulicious/Emulicious.jar` (requires Java)
- Each game Makefile defaults to `GBDK_HOME = ../../gbdk/`

## Scaffold a New Game

1. `cp -r games/_template games/GameName`
2. Edit `games/GameName/Makefile` -- set `PROJECTNAME = gamename`
3. Write game logic in `src/main.c`
4. Build: `make gb`
5. Launch: `java -jar ../../Emulicious/Emulicious.jar build/gb/gamename.gb`
6. User tests and provides screenshot feedback

## Development Loop

After every feature change, follow this cycle:

1. Edit source files
2. `make gb` -- fix any compile errors
3. Launch the ROM in Emulicious for the user to test
4. User provides screenshots from Emulicious as visual feedback
5. Iterate based on the screenshots

## Project Structure

```
games/GameName/
├── Makefile            # Build config (set PROJECTNAME here)
├── Makefile.targets    # Platform targets
├── src/main.c          # Entry point: void main(void)
├── include/            # Headers
├── res/                # Graphics and map data
├── build/gb/           # Output ROM
└── obj/gb/             # Intermediate objects
```

## Key APIs

### Display Setup
```c
#include <gbdk/platform.h>
DISPLAY_ON;
SHOW_BKG;
SHOW_SPRITES;
SPRITES_8x16;
```

### GBC Color Palettes
```c
const palette_color_t bg_pal[] = {
    RGB_WHITE, RGB(10, 20, 10), RGB(5, 10, 5), RGB_BLACK,
};
set_bkg_palette(0, 1, bg_pal);
set_sprite_palette(0, 1, sprite_pal);
```

### Main Loop
```c
while (1) {
    wait_vbl_done();
    uint8_t keys = joypad();
    // update game state, update sprites
}
```

### Background
```c
set_bkg_data(first_tile, num_tiles, tile_data);
set_bkg_tiles(x, y, width, height, map_data);
set_bkg_attributes(x, y, width, height, attr_map);
scroll_bkg(dx, dy);
move_bkg(x, y);
```

### Sprites
```c
set_sprite_data(first_tile, num_tiles, tile_data);
set_sprite_tile(sprite_id, tile_num);
set_sprite_prop(sprite_id, props);  // palette, flip, priority
move_sprite(sprite_id, x, y);
```

### Input
```c
uint8_t keys = joypad();
// J_UP, J_DOWN, J_LEFT, J_RIGHT, J_A, J_B, J_START, J_SELECT
```

### Debug
```c
#include <gbdk/emu_debug.h>
EMU_printf("x=%d y=%d\n", px, py);
```

### GBC Extras
```c
cpu_fast();             // double-speed mode (CGB)
VBK_REG = 1;           // switch to VRAM bank 1
VBK_REG = 0;           // back to VRAM bank 0
```

## Asset Pipeline

Convert PNGs to C arrays using png2asset (in `gbdk/bin/`):
```bash
../../gbdk/bin/png2asset sprite.png -o res/sprite.c -sw 16 -sh 16
```

Flags: `-sw`/`-sh` set sprite width/height. Output is a `.c` and `.h` pair.

## Reference Code

Before implementing features, check these reference projects in `references/`:

| Feature | Where to Look |
|---------|--------------|
| Multi-platform Makefile | `references/BlackCastle/Makefile` |
| Game state machine | `references/BlackCastle/src/main.c` |
| Scrolling | `references/BlackCastle/src/level.c` |
| Sprites and animation | `references/BlackCastle/src/player.c` |
| GBDK API examples | `references/gbdk-2020/gbdk-lib/examples/` |
| Scene/actor system | `references/gb-studio/appData/engine/` |

## Hardware Constraints (Game Boy Color)

| Resource | Limit |
|----------|-------|
| VRAM tiles | 384 per bank, 2 banks (768 total) |
| OAM sprites | 40 (max 10 per scanline) |
| Sprite size | 8x8 or 8x16 pixels |
| Screen | 160x144 pixels |
| WRAM | 32 KB (8 banks of 4 KB) |
| ROM bank | 16 KB each |
| CPU | ~1 MHz normal, ~2 MHz double-speed |
| BG palettes | 8 palettes of 4 colors each |
| Sprite palettes | 8 palettes of 4 colors each |
| Colors | 15-bit RGB (32768 possible colors) |
