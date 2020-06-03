[![Build Status](https://dev.azure.com/revery-ui/revery/_apis/build/status/revery-ui.revery-quick-start?branchName=master)](https://dev.azure.com/revery-ui/revery/_build/latest?definitionId=4?branchName=master)

# Revery Quick Start

This is a minimal Revery application to get you started.

## Prerequisites

See the [requirements for building Revery](https://github.com/revery-ui/revery/wiki/Building-&-Installing)

## Getting started

```
# Clone the repository
git clone https://github.com/revery-ui/revery-quick-start

# Go into the repository
cd revery-quick-start

# Install dependencies
esy install

# Build dependencies
esy build
```

> **NOTE:** The first build will take a while - building the OCaml compiler and dependencies takes time! Subsequent builds, though, should be very fast.

Once built, the application binary will be in the `_build/install/default/bin` - you can run it like:

- `_build/install/default/bin/App`

or using esy with the script specified in [package.json](package.json#L8):

- `esy run`

## What are all these files?

The most important files are:

- [`src/App.re`](./src/App.re) - This is the core application code, responsible for **creating a window** and **rendering**.
- [`src/SimpleButton.re`](./src/SimpleButton.re) - A simple button with hover and active-styling.
- [`src/AnimatedText.re`](./src/AnimatedText.re) - A component showcasing some neat animations.
- [`src/Theme.re`](./src/Theme.re) - A module holding some colors etc.

A Revery application also needs the following files:

- [`package.json`](package.json) - [esy configuration](https://esy.sh/docs/en/configuration.html) - lists the Reason/OCaml dependencies.
- `dune` / `dune-project` - build configuration files used by [Dune](https://dune.readthedocs.io/en/latest/).
- `.opam` - metadata used by the build system.

## Releasing

To create packages for distribution, follow these steps:

- `npm install -g revery-packager`

From the `revery-quick-start` folder, run:

- `revery-packager`

Once complete, there will be application packages available in the `_release` folder.

## Resources

- Check out the [Reason-documentation](https://reasonml.org) to learn more about Reason
- Visit the Reason [Discord-channel](https://discordapp.com/invite/reasonml) and say hi!

## Next steps

Here's a few challenges to see if you've got the basics:

- Add an Image component
- Respond to user input
- Create a frameless window

## License

[MIT License](LICENSE)
