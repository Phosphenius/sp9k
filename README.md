# SP9k

A bullet hell/space shooter game made in C++ and SFML as a learning project.

## Scope of this project
The goal is to learn C++ and SFML while also making a finished, playable game. To make this goal achievable, only a very small set of features will be implemented: 
 - Only one type of player, enemy bullet/weapon, level/stage and boss.
 - A very limited UI/menu
 - Possibly simple particle effects
 - Sound effects and music
 
## Requirements
 - SFML 2.5
 - C++17 compiler (only GCC >= 9.1 tested)

## Build
```sh
cmake .
make
```

## Build for release
```sh
cmake . -DCMAKE_BUILD_TYPE=Release
make
```

