# 🎮 Tetris Game (C++ with ncurses or raylib)

A modern C++ implementation of the classic Tetris game, featuring modular rendering backends with support for either **ncurses** (terminal) or **raylib** (graphical window). Built with **C++23**, **CMake**, and clean code practices.

<!-- ![Tetris gameplay preview](assets/tetris-demo.gif) -->

## 🏁 Quick Start

```bash
git clone https://github.com/felixcool200/tetris.git
cd tetris
mkdir build && cd build
cmake -DSCREEN_TYPE=raylib ..
make
./Tetris.out
```

---

## 🧱 Features

- 🎮 Classic Tetris gameplay
- 🔌 Modular design with pluggable rendering backends
- 🚀 Built using CMake and modern C++23 features
- 🧼 Compiler warnings treated as errors for code quality

---

## 🖥️ Supported Platforms

- ✅ Linux (fully tested)
- ⚠️ macOS (raylib preferred; terminal mode may require tweaks)
- ⚙️ Windows (via WSL or raylib with MinGW)

---

## 🛠 Requirements

### General

- CMake ≥ 3.14
- C++23 compatible compiler  
  (e.g. `g++-13` or newer, `clang++-17` or newer)

### Backend Options

#### 1. 🖼️ raylib (graphical mode)

✅ **No manual installation required**  
CMake will automatically fetch and build `raylib` from its GitHub repo using `FetchContent`.

#### 2. 📟 ncurses (terminal mode)

Install `ncurses` via your system’s package manager:

- **Debian/Ubuntu/Mint/PopOS**  
  ```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```

- **Arch/Manjaro**  
  ```bash
  sudo pacman -S ncurses
  ```

- **Fedora/RHEL/CentOS**  
  ```bash
  sudo yum install ncurses-devel
  ```

- **Other / From source**  
  [Install ncurses manually](https://ostechnix.com/how-to-install-ncurses-library-in-linux/)

---

## ⚙️ Build Instructions

### 1. Clone the repository

```bash
git clone https://github.com/felixcool200/tetris.git
cd tetris
```

### 2. Create a build directory

```bash
mkdir build
cd build
```

### 3. Configure with CMake

#### Using ncurses (default terminal version)

```bash
cmake -DSCREEN_TYPE=ncurses ..
```

#### Using raylib (graphical windowed version)

```bash
cmake -DSCREEN_TYPE=raylib ..
```

### 4. Compile the game

```bash
make
```

### 5. Run the game

```bash
./Tetris.out
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---
<!-- 
## 🚧 TODO

- [ ] High score system
- [ ] Sound effects (raylib)
- [ ] More visual polish for raylib mode

---
-->

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss your ideas.

---