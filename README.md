# GameBoyForever

AI agents building original Game Boy Color games in C using [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020).

## Purpose

This repo is a workspace for AI coding agents to design, implement, and test Game Boy Color games. The `references/` folder contains complete working projects (BlackCastle, gb-studio, gbdk-2020) that agents study to learn GBDK patterns, APIs, and build conventions before writing new games. All ROMs are built as CGB-only (Game Boy Color exclusive).

## Repo Structure

```
GameBoyForever/
├── setup.sh            One-command bootstrap (downloads everything)
├── gbdk/               GBDK-2020 v4.5.0 toolchain (git-ignored)
├── Emulicious/         Emulicious emulator (git-ignored)
├── docs/               MKDocs documentation site
├── games/              Game projects
│   ├── _template/      Starter skeleton (compiles out of the box)
│   ├── CharlieDog/     Top-down adventure game
│   └── RetroBoy/       Coin-collecting arcade game
└── references/         Cloned reference repos (git-ignored)
    ├── BlackCastle/    Complete multi-platform GBDK game
    ├── gb-studio/      GB Studio source with C engine
    ├── gbdk-2020/      GBDK source, libraries, and examples
    └── VWF/            Variable Width Font library for GBDK
```

## Setup from Scratch

### Prerequisites

| Tool | Install |
|------|---------|
| **git** | [git-scm.com/downloads](https://git-scm.com/downloads) |
| **make** | macOS: `xcode-select --install` / Linux: `sudo apt install build-essential` |
| **Java** | macOS: `brew install --cask temurin` / Linux: `sudo apt install default-jre` |

### Automated Setup

Clone the repo and run the setup script. It downloads GBDK-2020, Emulicious, and all reference repos:

```bash
git clone git@github.com:PlebeiusGaragicus/GameBoyForever.git
cd GameBoyForever
./setup.sh
```

The script is idempotent -- it skips anything already installed.

### Manual Setup

If you prefer to set things up manually, see the [Getting Started](docs/docs/getting-started.md) guide for step-by-step instructions.

## Build and Test

```bash
cp -r games/_template games/MyGame
cd games/MyGame
# Edit Makefile: set PROJECTNAME = mygame
make gb
java -jar ../../Emulicious/Emulicious.jar build/gb/mygame.gb
```

## Documentation

Serve the docs locally:

```bash
cd docs/
pip install -r requirements.txt
mkdocs serve
```

Then open [http://127.0.0.1:8000](http://127.0.0.1:8000).

## Links

- [GBDK-2020 Documentation](https://gbdk-2020.github.io/gbdk-2020/docs/api/)
- [GBDK-2020 Examples](https://github.com/gbdk-2020/gbdk-2020/tree/develop/gbdk-lib/examples)
- [Emulicious](https://emulicious.net/)
- [GB Studio](https://www.gbstudio.dev/)
- [Awesome Game Boy Dev](https://github.com/gbdev/awesome-gbdev)
