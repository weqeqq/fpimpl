{
  description = "Fast PImpl Implementation";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };
  outputs =
    { nixpkgs, utils, ... }:
    utils.lib.eachDefaultSystem (
      system: with import nixpkgs { inherit system; }; rec {
        packages = rec {
          fpimpl = stdenv.mkDerivation {
            pname = "FPImpl";
            version = "0.1.1";
            src = ./.;

            nativeBuildInputs = [ cmake ];
          };
          default = fpimpl;
        };
        devShells = rec {
          fpimpl = mkShell {
            inputsFrom = [ packages.fpimpl ];
            packages = [ pkgs.fish ];
            shellHook = "exec fish";
          };
          default = fpimpl;
        };
      }
    );
}
