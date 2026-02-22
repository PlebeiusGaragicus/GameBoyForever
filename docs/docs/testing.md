# Testing with Emulicious

## Running a ROM

After building with `make gb`, open the ROM in Emulicious:

```bash
java -jar /path/to/Emulicious.jar build/gb/mygame.gb
```

Or drag-and-drop the `.gb` file onto the Emulicious window.

## Debug Output

GBDK-2020 provides `EMU_printf` for printing to the Emulicious console:

```c
#include <gbdk/emu_debug.h>

EMU_printf("Player x=%d y=%d\n", player_x, player_y);
```

These calls are stripped from release builds automatically and have zero overhead when not running in Emulicious.

## Emulicious Debugging Tools

| Tool | Access | Purpose |
|------|--------|---------|
| Debugger | Tools > Debugger | Step through code, set breakpoints |
| Tile Viewer | Tools > Tile Viewer | Inspect loaded tile data |
| Tilemap Viewer | Tools > Tilemap Viewer | See background/window map |
| Sprite Viewer | Tools > Sprite Viewer | Inspect OAM sprite table |
| Memory Editor | Tools > Memory Editor | Read/write memory live |
| Profiler | Tools > Profiler | Find performance bottlenecks |

## VS Code Remote Debugging

1. Install the "Emulicious Debugger" VS Code extension.
2. In Emulicious: Tools > Remote Debugging > Enable.
3. Add a launch configuration to `.vscode/launch.json`:

    ```json
    {
        "type": "emulicious-debugger",
        "request": "launch",
        "name": "Debug GB ROM",
        "program": "${workspaceFolder}/build/gb/mygame.gb",
        "port": 58870
    }
    ```

4. Press F5 in VS Code to attach.

## Common Issues

**ROM won't load**: Verify the ROM was built successfully. Check that `build/gb/*.gb` exists and is not 0 bytes.

**Garbled graphics**: Tile data may not be loaded before `DISPLAY_ON`. Always call `set_bkg_data()` and `set_bkg_tiles()` before enabling the display.

**No input response**: Ensure `joypad()` is called inside the main loop after `wait_vbl_done()`.
