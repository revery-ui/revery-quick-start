open Revery;
open Revery.UI;
open Revery.UI.Components;

module AnimatedText = {
  module Styles = {
    open Style;

    let text = (~yOffset) => [
      color(Colors.white),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(24.),
      transform([Transform.TranslateY(yOffset)]),
    ];
  };

  let%component make = (~delay: Time.t, ~text: string, ()) => {
    let%hook (yOffset, _state, _reset) =
      Hooks.animation(
        Animation.animate(Time.ms(500))
        |> Animation.delay(delay)
        |> Animation.ease(Easing.easeOut)
        |> Animation.tween(50., 0.),
      );

    let%hook (animatedOpacity, _state, _reset) =
      Hooks.animation(
        Animation.animate(Time.seconds(1))
        |> Animation.delay(delay)
        |> Animation.ease(Easing.easeOut)
        |> Animation.tween(0., 1.),
      );

    <Opacity opacity=animatedOpacity>
      <Padding padding=8>
        <Text style={Styles.text(~yOffset)} text />
      </Padding>
    </Opacity>;
  };
};

module SimpleButton = {
  module Styles = {
    open Style;

    let button = [
      backgroundColor(Color.rgba(1., 1., 1., 0.1)),
      border(~width=2, ~color=Colors.white),
      margin(16),
    ];

    let text = [
      color(Colors.white),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(20.),
    ];
  };

  let%component make = () => {
    let%hook (count, setCount) = React.Hooks.state(0);
    let increment = () => setCount(count => count + 1);

    let text = "Click me: " ++ string_of_int(count);
    <Clickable onClick=increment>
      <View style=Styles.button>
        <Padding padding=4> <Text style=Styles.text text /> </Padding>
      </View>
    </Clickable>;
  };
};

let main = () => {
  module Styles = {
    open Style;

    let container = [
      position(`Absolute),
      justifyContent(`Center),
      alignItems(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
    ];

    let inner = [flexDirection(`Row), alignItems(`FlexEnd)];
  };

  <View style=Styles.container>
    <View style=Styles.inner>
      <AnimatedText delay={Time.ms(0)} text="Welcome" />
      <AnimatedText delay={Time.ms(500)} text="to" />
      <AnimatedText delay={Time.ms(1000)} text="Revery" />
    </View>
    <SimpleButton />
  </View>;
};

let init = app => {
  Revery.App.initConsole();

  Timber.App.enable();
  Timber.App.setLevel(Timber.Level.perf);

  let win = App.createWindow(app, "Welcome to Revery!");

  let _: Revery.UI.renderFunction = UI.start(win, <main />);
  ();
};

App.start(init);
