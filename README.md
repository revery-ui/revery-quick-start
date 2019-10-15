[![Build Status](https://dev.azure.com/revery-ui/revery/_apis/build/status/revery-ui.revery-quick-start?branchName=master)](https://dev.azure.com/revery-ui/revery/_build/latest?definitionId=4?branchName=master)

# revery-quick-start

---

__Clone and run for a quick way to see Revery in action.__

This is a minimal Revery application to get you started.

The most important file here is:
- `App.re` - This is the core application code, responsible for __creating a window__ and __rendering__.

A Revery application also needs these files:
- `package.json` - [esy configuration]() - lists the OCaml/Reason dependencies.
- `dune` / `dune-project` - build configuration files used by [Dune](https://dune.readthedocs.io/en/latest/).
- `.opam` - metadata used by the build system.

For JS, we bundle several assets (an `index.html` and JS files in `assets_js`).

### Prerequisites

- Install [Git](https://git-scm.com/)
- Install [Esy](https://esy.sh/) __0.5.6+__

### Native Build

- `esy install`
- `esy build`

The binary will be in the `_build/install/default/bin` - you can run it like:

- `_build/install/default/bin/App`

or with esy:

- `esy run`

```
# Clone the repository
git clone https://github.com/revery-ui/revery-quick-start
# Go into the repository
cd revery-quick-start
# Install dependencies
esy install
# Build dependencies
esy build
# Run the app
esy run
```

> __NOTE:__ The first build will take a while - building the OCaml compiler and dependencies takes time! Subsequent builds, though, should be very fast.

### JavaScript build

- `esy '@js' install`
- `esy '@js' build`

You can run and test the JS build with:
- `esy '@js' run`

This will start up a local web server.


### Releasing

To create packages for distribution, follow these steps:

- `npm install -g revery-packager`

From the `revery-quick-start` folder, run:

- `revery-packager`

Once complete, there will be application packages available in the `_release` folder.

### Resources

- Check out the [official reason docs](https://reasonml.github.io/docs/en/what-and-why) to learn more about reason
- Visit the Reason [discord channel](https://discordapp.com/invite/reasonml) and say hi!

### Next steps

Here's a few challenges to see if you've got the basics:

- Change the text from 'Hello World' to something more interesting!
- Add an Image component (Hint - you'll need to add the resource to the `dune` file, too)
- Respond to user input
- Create a frameless window

### License

[MIT License](LICENSE)

Revery-quick-start also includes some assets (font files, etc) that have their own licensing terms. For these, see [ThirdPartyLicenses.txt](ThirdPartyLicenses.txt)
