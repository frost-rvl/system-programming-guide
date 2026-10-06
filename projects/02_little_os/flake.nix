{
  description = "An i686-elf cross compiler";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/26.05";
  };

  outputs = { self, nixpkgs }:
    let
      lib = nixpkgs.lib;

      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "aarch64-darwin"
      ];

      forEachSupportedSystem = f:
        lib.genAttrs supportedSystems (
          system:
          f {
            inherit system;
            pkgs = import nixpkgs {
              inherit system;
              config.allowUnfree = true;
            };
          }
        );
    in
    {
      devShells = forEachSupportedSystem (
        { pkgs, system }:
        {
          default = pkgs.mkShell {
            nativeBuildInputs = 
            (with pkgs.pkgsCross.i686-embedded.buildPackages; [
              gcc
              binutils
            ])
            ++ (with pkgs; [
              nasm
              gnumake
              cdrkit /* to install genisoimage */
            ])
            ++ pkgs.lib.optionals pkgs.stdenv.isLinux (with pkgs; [
              grub2
            ]);
          };
        }
      );

    };
}
