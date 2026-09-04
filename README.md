# Inventory Management System (C++)

Console-based inventory and store simulation written in C++.

## Build

From repository root (`/home/runner/work/inventory-management-system-c-kacper1910kociszewski/inventory-management-system-c-kacper1910kociszewski`):

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/kacper\ kamil/Project/inventory_app
```

## Tests

```bash
ctest --test-dir build --output-on-failure
```

## Notes

- The project now uses RAII (`std::unique_ptr`) for inventory ownership.
- Navigation bounds use dynamic equipment sizes (no hardcoded row/column limits).
- Linux and Windows key input are handled through a cross-platform input abstraction.
