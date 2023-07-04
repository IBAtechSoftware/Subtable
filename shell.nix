{ pkgs ? import <nixpkgs> { }, lib ? pkgs.lib }:
let
  mcc-env = (pkgs.callPackage ./vendor/compilecommands {}).wrap pkgs.stdenv;
in
(pkgs.mkShell.override { stdenv = mcc-env; }) rec {
  name = "sodium-env";
  buildInputs = with pkgs; [
    cmake
    ninja
    clang-tools
    gdb
  ];
}

