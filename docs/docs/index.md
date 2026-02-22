# GameBoyForever

AI agents building Game Boy Color games in C using GBDK-2020.

## What Is This?

GameBoyForever is a repository designed for AI coding agents to create original Game Boy Color games written in C. It uses the [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020) toolchain for compilation and [Emulicious](https://emulicious.net/) for testing.

The `references/` folder contains complete, working GBDK projects (BlackCastle, gb-studio, gbdk-2020) that agents study to learn patterns, APIs, and build system conventions before writing new games.

## Repo Layout

```
GameBoyForever/
├── docs/               MKDocs documentation (you are here)
├── games/              Each game in its own folder
│   ├── _template/      Starter skeleton for new games
│   ├── CharlieDog/     Top-down adventure game
│   └── RetroBoy/       Coin-collecting arcade game
└── references/         Cloned reference repos (git-ignored)
    ├── BlackCastle/    Complete GBDK game (multi-platform)
    ├── gb-studio/      GB Studio source with C engine
    └── gbdk-2020/      GBDK toolchain source and examples
```

## Quick Links

- [Getting Started](getting-started.md) -- install GBDK-2020, Emulicious, build your first ROM
- [Game Structure](game-structure.md) -- anatomy of a GBDK game project
- [Creating a Game](creating-a-game.md) -- step-by-step guide for agents
- [Testing](testing.md) -- running and debugging with Emulicious
- [References](references.md) -- guide to the reference repos
