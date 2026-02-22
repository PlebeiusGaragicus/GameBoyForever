# Game Structure

Every game in `games/` follows this directory layout, modeled after BlackCastle:

```
games/MyGame/
├── Makefile            Build configuration
├── Makefile.targets    Platform target definitions
├── README.md           Game description and design notes
├── src/                C source files
│   └── main.c          Entry point
├── include/            Header files (.h)
├── res/                Game resources (tiles, maps, palettes)
├── build/              Compiled ROMs (per platform)
└── obj/                Intermediate object files
```

## Makefile

The Makefile drives compilation via GBDK's `lcc` compiler driver. Key variables:

| Variable | Purpose |
|----------|---------|
| `GBDK_HOME` | Path to GBDK-2020 installation |
| `PROJECTNAME` | Output ROM filename (no extension) |
| `TARGETS` | Space-separated list of platforms to build (e.g. `gb gg sms`) |
| `LCCFLAGS` | Linker and compiler flags |
| `CFLAGS` | C compiler flags (include paths, etc.) |

Common build commands:

```bash
make gb          # Build Game Boy Color ROM
make clean       # Remove all build artifacts
```

The template uses `-Wm-yC` in `LCCFLAGS_gb` to mark the ROM as CGB-only, enabling Game Boy Color features (color palettes, double-speed CPU, extra VRAM bank).

## Source Code (`src/`)

The entry point is `src/main.c` with a `void main(void)` function. A minimal Game Boy Color program:

```c
#include <gbdk/platform.h>
#include <stdio.h>

void main(void) {
    printf("Hello World!");
    SHOW_BKG;
    DISPLAY_ON;
    while (1) {
        wait_vbl_done();
    }
}
```

Platform-specific code goes in subdirectories like `src/sm83/` (Game Boy / GBC).

## Resources (`res/`)

Graphics, tilemaps, and other binary assets live in `res/`. These are typically converted from PNG to C arrays using tools like:

- **png2asset** (included in GBDK-2020) -- converts PNG images to C source
- **GBTD/GBMB** -- Game Boy Tile Designer / Map Builder

The converted `.c` and `.h` files are compiled alongside game source code.

## Headers (`include/`)

Shared declarations, constants, and data structures. Keep game state, entity definitions, and resource externs here.
