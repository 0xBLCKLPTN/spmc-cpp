{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
      gcc
      cmake
      pkg-config
      wayland-scanner
      wayland-protocols
      wayland
      libxkbcommon
      glfw
      glew
      bat
      SDL2
    ];
    buildInputs = with pkgs; [
      openssl
      zlib
      glfw
      libiconv
    ];
  }
