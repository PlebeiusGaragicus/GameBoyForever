# Getting Started

## Install GBDK-2020

1. Download the latest release for your platform from [github.com/gbdk-2020/gbdk-2020/releases](https://github.com/gbdk-2020/gbdk-2020/releases).
2. Unzip to a known location (e.g. `/opt/gbdk/` or `~/gbdk/`).
3. On macOS, unquarantine the binaries:

    ```bash
    cd /path/to/gbdk/bin
    xattr -d com.apple.quarantine *
    ```

4. Set the `GBDK_HOME` environment variable:

    ```bash
    export GBDK_HOME=/path/to/gbdk/
    ```

5. Verify by running:

    ```bash
    ${GBDK_HOME}bin/lcc --version
    ```

## Install Emulicious

Emulicious is a free multi-system emulator with powerful debugging tools. It is **not** included in GBDK-2020 and must be installed separately.

1. Download from [emulicious.net/downloads](https://emulicious.net/downloads/).
2. Extract the archive. No installation required.
3. Emulicious requires Java SE 1.6+. On macOS, install via `brew install --cask temurin` if needed.
4. Run `Emulicious.jar` to launch.

!!! tip "VS Code Integration"
    Emulicious supports remote debugging via VS Code. Install the "Emulicious Debugger" extension for breakpoint and step-through debugging of your Game Boy ROMs.

## Build Your First ROM

Use the template in `games/_template/`:

```bash
cd games/_template
make gb
```

This produces `build/gb/<projectname>.gb` -- a Game Boy Color ROM. Open it in Emulicious to test.

!!! note "Game Boy Color Target"
    All games in this repo target Game Boy Color (CGB-only). The template Makefile includes the `-Wm-yC` flag which sets the CGB-only header. The ROM will run on GBC hardware and GBC-compatible emulators but not on original DMG Game Boy.

## Clone Reference Repos

If the `references/` folder is empty, clone the reference projects:

```bash
cd references/
git clone --recurse-submodules git@github.com:PlebeiusGaragicus/gb-studio.git
git clone https://github.com/gbdk-2020/gbdk-2020.git
```

BlackCastle should already be present. If not:

```bash
git clone git@github.com:PlebeiusGaragicus/BlackCastle.git
```
