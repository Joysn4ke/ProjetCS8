# The Cursed Island's Treasure Hunt

A terminal-based adventure game where you navigate through a perilous island, avoiding traps and pirates while searching for hidden treasure.

![Game Preview](https://img.shields.io/badge/Game-Terminal%20Based-blue)
![Language](https://img.shields.io/badge/Language-C-orange)
![Version](https://img.shields.io/badge/Version-1.0-green)

## 🏝️ Game Overview

In "The Cursed Island's Treasure Hunt," you control an adventurer navigating a grid-based island to find a hidden treasure. Your journey won't be easy - the island is filled with deadly traps and a relentless pirate who will hunt you down. Use strategy, quick reflexes, and good luck to find the treasure before losing all your health!

## 🎮 Game Features

- **Terminal-based gameplay** with colored grid visualization
- **Grid-based movement** using keyboard controls (z/q/s/d or arrow keys)
- **Health system** - lose health when stepping on traps or encountering the pirate
- **Enemy AI** - a pirate that chases you when you're in sight, otherwise moves randomly
- **Hidden traps** - randomly placed dangers that damage you when stepped on
- **State machine architecture** for robust game logic

## 🛠️ Technical Implementation

The game is built with a focus on software engineering principles:

- **Modular programming** - separating game logic into distinct components
- **State machine design** - managing game states and transitions cleanly
- **Dynamic memory management** - proper allocation and deallocation of resources
- **Defensive programming** - using assertions and error checking

## 📋 Project Structure

The codebase is organized into modular components:

- **Common** - Configuration and shared utility functions
- **Game** - Main game logic and state machine implementation
- **Map** - Grid representation and rendering
- **Player** - Player entity and movement
- **Pirate** - Enemy entity with basic AI
- **Trap** - Hazards that damage the player
- **Treasure** - The objective to be found

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make (for building with Makefile)
- Terminal that supports ANSI color codes

### Building and Running

```bash
# Clone the repository
git clone https://github.com/yourusername/cursed-island-treasure.git
cd cursed-island-treasure

# Build the game
make

# Run the game
./game
```

## 🎲 How to Play

- Use `z` (or Up arrow) to move up
- Use `s` (or Down arrow) to move down
- Use `q` (or Left arrow) to move left
- Use `d` (or Right arrow) to move right
- Press `l` to quit the game

### Game Legend

- `j` - Player
- `P` - Pirate
- `T` - Treasure (visible in cheat mode)
- `t` - Trap (visible in cheat mode)

### Game Objectives

1. Find the treasure without depleting your health
2. Avoid or strategically handle the pirate
3. Be careful of hidden traps

## 🖥️ State Machine Design

The game uses a state machine architecture to manage gameplay flow:

```
S_INIT → S_ACQUISITION_CLAVIER → S_DEPLACEMENT → S_VERIFICATION_VICTOIRE → S_GAME_OVER
```

- **S_INIT**: Game initialization
- **S_ACQUISITION_CLAVIER**: Waiting for keyboard input
- **S_DEPLACEMENT**: Processing player movement
- **S_VERIFICATION_VICTOIRE**: Checking win/loss conditions
- **S_GAME_OVER**: Game end state

## ⚙️ Configuration

You can modify game parameters in `Common.h`:

- `LINE` & `COLUMN`: Grid dimensions (default: 10x10)
- `NBTRAP`: Number of traps (default: LINE-1)
- `HEALTHPLAYER`: Player's starting health (default: NBTRAP+1)
- `CHEAT`: Enable cheat mode to see traps and treasure (1=on, 0=off)

## 🧪 Future Enhancements

- Multiple levels with increasing difficulty
- Additional enemy types with different behaviors
- Power-ups and special abilities
- Save/load game functionality
- High score tracking

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgements

- Developed as an educational project for advanced C programming
- Inspired by classic roguelike games and adventure titles
