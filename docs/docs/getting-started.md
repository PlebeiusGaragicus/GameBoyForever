# Getting Started

This guide walks through setting up GameBoyForever from a fresh clone.

## Quick Setup

The fastest path is the automated setup script:

```bash
git clone git@github.com:PlebeiusGaragicus/GameBoyForever.git
cd GameBoyForever
./setup.sh
```

This single script handles everything below. If you prefer manual setup, follow the steps in order.

## Prerequisites

You need these tools installed before proceeding:

| Tool | Purpose | Install |
|------|---------|---------|
| **git** | Clone repos | [git-scm.com/downloads](https://git-scm.com/downloads) |
| **make** | Build ROMs | macOS: `xcode-select --install` / Linux: `sudo apt install build-essential` |
| **Java 1.6+** | Run Emulicious | macOS: `brew install --cask temurin` / Linux: `sudo apt install default-jre` |
| **curl** | Download tools | Usually pre-installed on macOS and Linux |

## Step 1: Install GBDK-2020

GBDK-2020 is the C compiler toolchain for Game Boy. Download the prebuilt release for your platform:

| Platform | Download |
|----------|----------|
| macOS ARM (Apple Silicon) | [gbdk-macos-arm64.tar.gz](https://github.com/gbdk-2020/gbdk-2020/releases/latest) |
| macOS Intel | [gbdk-macos-x64.tar.gz](https://github.com/gbdk-2020/gbdk-2020/releases/latest) |
| Linux x64 | [gbdk-linux64.tar.gz](https://github.com/gbdk-2020/gbdk-2020/releases/latest) |
| Linux ARM | [gbdk-linux-arm64.tar.gz](https://github.com/gbdk-2020/gbdk-2020/releases/latest) |
| Windows 64-bit | [gbdk-win64.zip](https://github.com/gbdk-2020/gbdk-2020/releases/latest) |

Extract into the repo root so the directory is named `gbdk/`:

```bash
cd /path/to/GameBoyForever
# Example for macOS ARM:
curl -L -o /tmp/gbdk.tar.gz https://github.com/gbdk-2020/gbdk-2020/releases/download/4.5.0/gbdk-macos-arm64.tar.gz
tar xzf /tmp/gbdk.tar.gz
```

On macOS, remove quarantine flags so the binaries can run:

```bash
xattr -dr com.apple.quarantine gbdk/
```

Verify it works:

```bash
GBDK_HOME=gbdk/ gbdk/bin/lcc -v
```

## Step 2: Install Emulicious

Emulicious is a free Game Boy emulator with debugging tools. It is **not** part of GBDK.

1. Download from [emulicious.net/downloads](https://emulicious.net/downloads/)
2. Extract into the repo root so the directory is named `Emulicious/`:

```bash
curl -L -o /tmp/emulicious.zip "https://emulicious.net/download/emulicious/"
mkdir -p Emulicious
unzip -q -o /tmp/emulicious.zip -d Emulicious/
```

!!! tip "VS Code Integration"
    Install the "Emulicious Debugger" VS Code extension for breakpoint and step-through debugging.

## Step 3: Clone Reference Repos

The `references/` folder holds complete projects that serve as learning material. All three should be cloned:

```bash
mkdir -p references
cd references

# BlackCastle -- complete multi-platform GBDK game
git clone git@github.com:PlebeiusGaragicus/BlackCastle.git

# gb-studio -- drag-and-drop game builder with C engine (has submodules)
git clone --recurse-submodules git@github.com:PlebeiusGaragicus/gb-studio.git

# gbdk-2020 -- GBDK toolchain source, libraries, and examples
git clone https://github.com/gbdk-2020/gbdk-2020.git

# VWF -- Variable Width Font library for GBDK
git clone git@github.com:PlebeiusGaragicus/VWF.git

cd ..
```

## Step 4: Build and Test

Compile the template project to verify everything works:

```bash
cd games/_template
make gb
```

You should see output ending with `Converted build/gb/mygame.noi to build/gb/mygame.sym.`

Launch it in Emulicious:

```bash
java -jar ../../Emulicious/Emulicious.jar build/gb/mygame.gb
```

You should see "Hello GBC!" on a green-tinted Game Boy Color screen.

!!! note "Game Boy Color Target"
    All games in this repo target Game Boy Color (CGB-only). The template Makefile includes the `-Wm-yC` flag which sets the CGB-only header. The ROM will run on GBC hardware and GBC-compatible emulators but not on original DMG Game Boy.

## What's Git-Ignored

The following directories are **not tracked** in version control and must be set up locally:

| Directory | Contents | How to Get |
|-----------|----------|------------|
| `gbdk/` | GBDK-2020 toolchain binaries | `./setup.sh` or Step 1 above |
| `Emulicious/` | Emulicious emulator | `./setup.sh` or Step 2 above |
| `references/` | BlackCastle, gb-studio, gbdk-2020 source | `./setup.sh` or Step 3 above |

## Development Workflow

Once set up, the daily workflow is:

1. Edit source code (add features, fix bugs)
2. `make gb` to compile
3. Launch the ROM in Emulicious
4. Test in the emulator, take screenshots for feedback
5. Iterate
