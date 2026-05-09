# nix-bazel

A hands-on learning exercise for Nix + Bazel interop. The application code (a
tiny C++17 moving-average signal library plus CLI) is deliberately minimal — it
exists as a vehicle for the build configuration written around it. The
interesting work lives in the build files, not the C++.

## Phases

### Phase 1 — Bazel-native baseline 

Working Bazel build using bzlmod, pulling GoogleTest from the Bazel Central
Registry and using whatever C++ toolchain the host happens to have.

```bash
bazelisk build //...
bazelisk test  //...
echo "1 2 3 4 5" | bazelisk run //src/cli:cli -- 3
# → 1 1.5 2 3 4
```

### Phase 2 — Nix-managed toolchain via `rules_nixpkgs` 

Host clang replaced with a clang/lld/sysroot provisioned from nixpkgs, pinned
by `flake.lock`. The build is now hermetic with respect to the toolchain;
deleting `/usr/bin/clang` would not break it.

```bash
nix develop                      # bazelisk on PATH, devshell active
bazelisk build //...             # uses Nix-provided toolchain via platform-based resolution
bazelisk aquery 'mnemonic("CppCompile", //src/signal:signal)' --output=text
# → cc_wrapper.sh resolves into /nix/store/...-clang-wrapper-16.0.6/...
```