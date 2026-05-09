# nix-bazel-refresh

A hands-on learning exercise for Nix + Bazel interop. The application code (a tiny
C++17 moving-average signal library plus CLI) is deliberately minimal — it exists
as a vehicle for the build configuration written around it. The interesting work
lives in the build files, not the C++.

## Phases

The build configuration is intended to be developed in five phases. Each phase
builds on the previous one. No build files are checked in yet — that is the
exercise.

1. **Bazel-native baseline.** Stand up a working Bazel build using bzlmod,
   pulling GoogleTest from the Bazel Central Registry and using whatever C++
   toolchain the host happens to have. Goal: `bazel test //...` green with no
   Nix involved.
2. **Nix-managed toolchain via `rules_nixpkgs`.** Replace the host toolchain with
   one provisioned from nixpkgs so the compiler, linker, and sysroot are pinned
   by the flake. Bazel still drives the build; Nix supplies the tools.
3. **Wrap the build in a Nix derivation.** Make `nix build` produce the binary
   by invoking Bazel inside a derivation. This is where the Nix sandbox's
   network restrictions collide with Bazel's repository fetches; the phase is
   really about confronting and resolving that.
4. **SBOM generation from the build graph.** Use Bazel's dependency graph
   (e.g. `bazel cquery` / aspects) to emit an SPDX or CycloneDX SBOM as a
   build artifact, and surface it from the Nix derivation.
5. **Optional: `bazel-remote` cache as a Nix-managed service.** Run a remote
   cache locally via Nix (systemd service or `nix run`) and point Bazel at it,
   to feel out the operational story for shared caching.

## What's intentionally missing

All build configuration is omitted on purpose. There is no `MODULE.bazel`,
`BUILD.bazel`, `.bazelrc`, `.bazelversion`, `flake.nix`, `flake.lock`, or
wrapping derivation in this repo — writing those is the learning exercise.
The C++ tree (`src/signal/`, `src/cli/`) is the fixed input; everything else
gets built up phase by phase.
