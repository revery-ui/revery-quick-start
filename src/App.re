open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  open Style;

  let text = [marginTop(24), color(Color.hex(Theme.darkBlue))];
};

let%component main = () => {
  let%hook (count, setCount) = React.Hooks.state(0);

  let increment = () => setCount(count => count + 1);

  <Center>
    <Padding padding=24>
      <Row>
        <AnimatedText delay={Time.ms(0)} text="Welcome" />
        <AnimatedText delay={Time.ms(500)} text="to" />
        <AnimatedText delay={Time.ms(1000)} text="Revery" />
      </Row>
    </Padding>
    <SimpleButton text="Increment" onClick=increment />
    <Text
      fontSize=16.
      style=Styles.text
      text={"Times clicked: " ++ string_of_int(count)}
    />
  </Center>;
};

let consoleReporter = Timber.Reporter.console(~enableColors=true, ());
let init = app => {
  Revery.App.initConsole();

  Timber.App.enable(consoleReporter);
  Timber.App.setLevel(Timber.Level.perf);

  let win =
    App.createWindow(
      app,
      "Hello Revery!",
      ~createOptions=
        WindowCreateOptions.create(
          ~backgroundColor=Color.hex(Theme.lightBlue),
          ~width=512,
          ~height=384,
          (),
        ),
    );

  let _update: Revery.UI.renderFunction = UI.start(win, <main />);
  ();
};

App.start(init);
