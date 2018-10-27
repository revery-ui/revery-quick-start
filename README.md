# revery-quick-start

---

__Clone and run for a quick way to see Revery in action.__

This is a minimal Revery application to get you started.

The most important file here is:
- `app.re` - This is the core application code, responsible for creating a window and rendering.

A Revery application also needs these files:
- `package.json` - lists the OCaml/Reason dependencies.
- `dune` - build configuration file.

## To Use

#### Prerequisites

- Install [Git](https://git-scm.com/)
- Install [Esy](https://esy.sh/)

#### Build

```
# Clone the repository
git clone https://github.com/bryphe/revery-quick-start
# Go into the repository
cd revery-quick-start
# Install dependencies
esy install
# Build dependencies
esy build
# Run the app
_build/install/default/app.exe
```

## License

[MIT License](LICENSE)
