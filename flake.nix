{ 
  description = "Tetris Game";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      buildInputs = [
        # General libraries
        pkgs.libGL
        
        # Build tools
        pkgs.cmake
        pkgs.gcc

        # Ncurses frontend (terminal UI)
        pkgs.ncurses

        # Raylib frontend (graphics)
        pkgs.pkg-config

        # Wayland dependencies (for Wayland support)
        pkgs.wayland
        pkgs.wayland-protocols
        pkgs.libxkbcommon
        pkgs.wayland-scanner

        # X11 dependencies (for X11 support)
        pkgs.xorg.libX11
        pkgs.xorg.libX11.dev
        pkgs.xorg.libXcursor
        pkgs.xorg.libXi
        pkgs.xorg.libXinerama
        pkgs.xorg.libXrandr

        # Uncomment below if you want to build Raylib with web support (Emscripten)
        # pkgs.emscripten
      ];
    };
  };
}