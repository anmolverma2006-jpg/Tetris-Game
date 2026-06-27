# 🕹️ C++ SFML Tetris Game

```text
 _____ _____ _____ ____  _ ____  
|_   _| ____|_   _|  _ \(_)/ ___| 
  | | |  _|   | | | |_) | |\___ \ 
  | | | |___  | | |  _ <| | ___) |
  |_| |_____| |_| |_| \_\_|____/  
                                  
```

A modern C++ recreation of the classic, nostalgic arcade game **Tetris** powered by the **Simple and Fast Multimedia Library (SFML)**. This project focuses on highly readable code, retro-pixel aesthetics, and a smooth rendering system.

---

## 🚀 Features & Visual Highlights

- **Arcade Typography**: Leverages the classic 8-bit **"Press Start 2P"** font from Google Fonts, giving the HUD and screens a retro vibe.
- **Translucent HUD Score Overlay**: Rather than cluttering the board, the score is cleanly placed in a semi-transparent top-left panel that protects visibility while keeping text highly legible.
- **Aligned Game Over Screen**: An overlay dims the board when the game finishes, popping up a structured dialog box showing final statistics with dynamically centered text alignments.
- **Board Guidelines**: A subtle $10 \times 20$ dark grid overlay is rendered on the background to help players align their drops.
- **Zero-Configuration Build**: SFML dependencies and the custom retro font are downloaded and configured automatically using CMake. No local library installations are required.

---

## 🎮 How to Play & Controls

### Objective
Clear as many horizontal lines of blocks as possible. Blocks (Tetrominoes) fall from the top of the screen. When a line is fully filled, it disappears, and you receive **100 points**. The game ends when new blocks can no longer spawn at the top of the grid.

### Gameplay Key Bindings

| Input Key | Action | Details |
| :--- | :--- | :--- |
| `Left Arrow` ⬅️ | **Move Left** | Slide the falling piece one cell to the left. |
| `Right Arrow` ➡️ | **Move Right** | Slide the falling piece one cell to the right. |
| `Up Arrow` ⬆️ | **Rotate** | Rotate the falling piece $90^\circ$ clockwise. |
| `Down Arrow` ⬇️ | **Soft Drop** | Increase the gravity pull of the piece, sliding it down faster. |
| `Spacebar` ⎵ | **Hard Drop** | Instantly snap the piece to its landing spot at the bottom. |
| `R Key` 🇷 | **Restart** | Resets the score and board once the Game Over dialog is displayed. |

---

## 🛠️ Code Architecture

The game is structured as a single-file application (`main.cpp`) to keep things simple and highly portable, relying on key helper algorithms:

### 1. Board & Piece Representation
- The board is modeled as a standard 2D integer array: `int board[20][10]`. Empty cells are `0`, and filled cells store an ID (`1` to `7`) corresponding to the color index of the tetromino.
- Tetromino matrices are represented as flat 1D arrays of size 16 ($4 \times 4$ grids).

### 2. Math-based Rotation System
Instead of hardcoding rotated layouts, rotation is computed mathematically inside `rotateIndex()`:
```cpp
int rotateIndex(int x, int y, int rotation) {
    switch (rotation % 4) {
        case 0: return y * 4 + x;           // 0 degrees
        case 1: return 12 + y - (x * 4);     // 90 degrees
        case 2: return 15 - (y * 4) - x;     // 180 degrees
        case 3: return 3 - y + (x * 4);      // 270 degrees
    }
    return 0;
}
```

### 3. Collision Checker
Before executing any movement or rotation, the program runs `checkCollision()` to verify if the piece intersects with either the board boundaries (bottom, left, right walls) or existing placed blocks. If a collision is predicted, the action is blocked.

### 4. Dynamic Text Centering
To keep text aligned regardless of how many digits the score has, the screen uses SFML's local bounds API:
```cpp
scoreText.setOrigin(scoreText.getLocalBounds().left + scoreText.getLocalBounds().width / 2.f, 0.f);
scoreText.setPosition(150.f, y_coordinate);
```

---

## 📂 Project Structure

```
├── CMakeLists.txt         # CMake build configuration script
├── main.cpp               # C++ Game source code
├── PressStart2P.ttf       # 8-bit retro arcade font
├── .gitignore             # Configured git exclusions (ignores build artifacts)
└── README.md              # Project documentation
```

---

## ⚙️ Compilation & Setup Guide

### Prerequisites
Make sure you have the following installed on your machine:
- A modern C++ compiler supporting **C++17** (MSVC on Windows, GCC/Clang on macOS/Linux).
- **CMake** (version 3.14 or higher).

### 1. Generate Build Configuration
CMake is configured to download SFML directly from Github via `FetchContent`. Run the following command from the project root:
```bash
cmake -B build
```
This downloads and prepares SFML for your target compiler.

### 2. Build the Executable
Compile the project:
```bash
cmake --build build
```
*Note: A post-build script in `CMakeLists.txt` automatically copies the required Windows runtime libraries (`.dll` files) and the `PressStart2P.ttf` font file to your output directory next to `my_game.exe`.*

### 3. Run the Game
Execute the compiled binary from the project root:
```powershell
./build/my_game.exe
```

---

## 🔧 Troubleshooting

- **Failed to Load Font**: If the text is missing, ensure that `PressStart2P.ttf` exists in the executable's directory. If CMake failed to copy it, manually copy `PressStart2P.ttf` from the source root folder into the `build/` directory.
- **SFML DLLs Missing (Windows)**: If running `my_game.exe` reports missing `.dll` files, run `cmake --build build` again or manually copy the `.dll` files generated under `build/_deps/sfml-build/lib/` to your executable directory.

---

## 🗺️ Roadmap & Planned Upgrades
- [ ] **Level System**: Speed up block drops as the score increases.
- [ ] **Next Piece Preview**: Introduce a panel showing the next tetromino.
- [ ] **Hold Piece**: Enable players to store a block for later use.
- [ ] **Audio**: Add retro sound effects for drops, rotations, and line clears.
