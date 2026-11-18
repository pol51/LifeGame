# LifeGame

This is Conway's Game of Life. It uses C++, Qt6 and CMake.

## Build

You need CMake 3.16 or newer, a C++17 compiler, and Qt6 Widgets.

```
cmake -S . -B build
cmake --build build
```

The program is written to `bin/LifeGame`.

## Controls

| Input | Action |
| --- | --- |
| Left click | Make a cell alive |
| Right click | Make a cell dead |
| Middle click | Show the HUD (text overlay) |
| `+` | Next generation |
| `*` | Clear the board |
| `Alt` + `Enter` | Full screen |
| `Alt` + `G` | Grid on or off |

## Code layout

- `src/engine`: the game logic, with no Qt code. It is called CasesEngine. It was designed with UML in BOUML. The model files are in `CasesEngine`.
- `src/lifeWidget.*`: the board widget. It draws with QPainter.
- `src/QtHud.*`: the text overlay.
- `src/winGOL.*` and `ui/GOL.ui`: the main window.
