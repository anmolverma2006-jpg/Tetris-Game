# Tetris Game (SFML & C++)

A classic arcade-style Tetris game built using C++ and the Simple and Fast Multimedia Library (SFML). The game features a clean, retro design complete with pixel font overlays, grid layout alignment, and scoring.

## Features

- **Retro Aesthetic**: Powered by the classic arcade "Press Start 2P" pixel font.
- **Visual Grid Overlay**: Clean, subtle cell outlines representing the entire $10 \times 20$ Tetris board.
- **Score HUD Card**: A styled semi-transparent black card overlay in the top-left tracking your current score.
- **Game Over Dialog Box**: A centered, high-contrast overlay dialog containing final scores and restart directions.
- **Automatic Post-Build Setup**: Custom CMake configurations to copy essential fonts and SFML runtime DLLs next to your build executable.

## Controls

| Key | Action |
| :--- | :--- |
| `Left Arrow` | Move piece left |
| `Right Arrow` | Move piece right |
| `Up Arrow` | Rotate piece |
| `Down Arrow` | Soft drop piece |
| `Spacebar` | Hard drop (instantly drops piece to bottom) |
| `R Key` | Restart game (only available on Game Over screen) |

## Prerequisites

To build and run the game, you will need:
- **C++ Compiler** supporting C++17 or higher
- **CMake** (version 3.14 or higher)
- **SFML 2.6.1** dependencies (automatically fetched and configured during CMake configuration)

## Build Instructions

1. **Configure CMake**:
   Generate the build files by running the following command from the project root directory:
   ```bash
   cmake -B build
   ```

2. **Compile the Game**:
   Build the executable:
   ```bash
   cmake --build build
   ```

3. **Run**:
   Run the compiled executable from the build output directory:
   - On Windows/Command Prompt/PowerShell:
     ```powershell
     ./build/my_game.exe
     ```
