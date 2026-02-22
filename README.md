# GameBoyForever

AI agents building original Game Boy Color games in C using [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020).

## Purpose

This repo is a workspace for AI coding agents to design, implement, and test Game Boy Color games. The `references/` folder contains complete working projects (BlackCastle, gb-studio, gbdk-2020) that agents study to learn GBDK patterns, APIs, and build conventions before writing new games. All ROMs are built as CGB-only (Game Boy Color exclusive).

## Repo Structure

```
GameBoyForever/
├── docs/               MKDocs documentation site
│   ├── mkdocs.yml      Site configuration
│   └── docs/           Markdown pages
├── games/              Game projects
│   ├── _template/      Starter skeleton for new games
│   ├── CharlieDog/     Top-down adventure game
│   └── RetroBoy/       Coin-collecting arcade game
└── references/         Cloned reference repos (git-ignored)
    ├── BlackCastle/    Complete multi-platform GBDK game
    ├── gb-studio/      GB Studio source with C engine
    └── gbdk-2020/      GBDK toolchain, libraries, and examples
```

## Quick Start

### 1. Install GBDK-2020

Download the latest release from [gbdk-2020 releases](https://github.com/gbdk-2020/gbdk-2020/releases) and unzip it. Set the `GBDK_HOME` environment variable to the unzipped directory.

On macOS, unquarantine the binaries:

```bash
cd /path/to/gbdk/bin && xattr -d com.apple.quarantine *
```

### 2. Install Emulicious

[Emulicious](https://emulicious.net/) is a free Game Boy emulator with built-in debugging tools. It is **not** bundled with GBDK and must be installed separately. Download from [emulicious.net/downloads](https://emulicious.net/downloads/). Requires Java.

### 3. Create a New Game

```bash
cp -r games/_template games/MyGame
cd games/MyGame
# Edit Makefile: set PROJECTNAME = mygame
make gb
```

Open `build/gb/mygame.gb` in Emulicious to test.

### 4. Clone References (if needed)

```bash
cd references/
git clone --recurse-submodules git@github.com:PlebeiusGaragicus/gb-studio.git
git clone https://github.com/gbdk-2020/gbdk-2020.git
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
