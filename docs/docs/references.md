# Reference Projects

The `references/` folder contains cloned repositories that serve as learning material and code references. These are git-ignored and not part of this repo's history.

## BlackCastle

**Path:** `references/BlackCastle/`
**Source:** [github.com/untoxa/BlackCastle](https://github.com/untoxa/BlackCastle)

A complete multi-platform game built with GBDK-2020. Builds for Game Boy, NES, Game Gear, SMS, Mega Duck, and Analogue Pocket.

**What to study:**

- `Makefile` / `Makefile.targets` -- multi-platform build system
- `src/main.c` -- game initialization, interrupt handlers, main loop
- `include/global.h` -- shared state and constants
- `src/` -- game state machine, entity management, scrolling, collision
- `res/` -- tile and map data formats
- `.github/workflows/` -- CI/CD for automated ROM builds

## gb-studio

**Path:** `references/gb-studio/`
**Source:** [github.com/chrismaltby/gb-studio](https://github.com/chrismaltby/gb-studio)

GB Studio is an Electron-based drag-and-drop Game Boy game creator. Its C engine (under `appData/`) is useful reference material.

**What to study:**

- `appData/engine/` -- the C game engine that GB Studio compiles
- `appData/engine/gbvm/` -- the GB Studio virtual machine (submodule)
- `appData/src/` -- scene types, actors, triggers, UI, music drivers
- `buildTools/` -- asset pipeline tools

## gbdk-2020

**Path:** `references/gbdk-2020/`
**Source:** [github.com/gbdk-2020/gbdk-2020](https://github.com/gbdk-2020/gbdk-2020)

The GBDK-2020 toolchain itself -- compiler, linker, libraries, and examples.

**What to study:**

- `gbdk-lib/examples/` -- official examples covering sprites, tiles, sound, banking, and more
- `gbdk-lib/include/` -- all header files documenting the public API
- `gbdk-lib/libc/` -- C runtime library source
- `docs/` -- toolchain documentation source

## VWF (Variable Width Font)

**Path:** `references/VWF/`
**Source:** [github.com/PlebeiusGaragicus/VWF](https://github.com/PlebeiusGaragicus/VWF)

A variable-width font rendering library for GBDK-2020. Supports up to 4 fonts simultaneously with configurable foreground/background colors.

**What to study:**

- `src/` -- VWF rendering implementation
- `include/` -- public API headers (`vwf.h`)
- `Makefile` -- build integration example for a GBDK library
- Font format in `vwf_font.c` -- 1-bit font tile definitions

**Features:**

- Variable-width font rendering (proportional text instead of fixed 8px grid)
- Up to 4 fonts at once
- Foreground/background color control
- Render to background or window layer
- Control characters for inverse text, gotoxy, font switching
