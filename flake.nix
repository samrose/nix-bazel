{
  description = "smoothlib - bazel build with nix-managed C++ toolchain";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";

  outputs = { self, nixpkgs }:
    let
      forAllSystems = f: nixpkgs.lib.genAttrs [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" ] (system:
        f { pkgs = import nixpkgs { inherit system; }; });
    in
    {
      devShells = forAllSystems ({ pkgs }: {
        default = pkgs.mkShell {
          packages = [ pkgs.bazelisk pkgs.nixpkgs-fmt ];
        };
      });
    };


}
