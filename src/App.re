open Revery;
open Revery.UI;
open Revery.UI.Components;

module Theme = {
  let lightBlue = "#F6F9FF";
  let reveryBlue = "#2667FF";
};

module AnimatedText = {
  module Styles = {
    open Style;

    let text = (~yOffset) => [
      color(Color.hex(Theme.reveryBlue)),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(16.),
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
      <Padding padding=4>
        <Text style={Styles.text(~yOffset)} text />
      </Padding>
    </Opacity>;
  };
};

module SimpleButton = {
  module Styles = {
    open Style;

    let button = boxShadowTransparency => [
      backgroundColor(Color.hex(Theme.reveryBlue)),
      boxShadow(
        ~yOffset=8.,
        ~xOffset=0.,
        ~blurRadius=16.,
        ~color=Color.rgba(0., 0., 0., boxShadowTransparency),
        ~spreadRadius=12.,
      ),
      paddingHorizontal(24),
      paddingVertical(12),
      borderRadius(10.),
    ];

    let buttonText = [
      color(Colors.white),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(16.),
    ];
  };

  let%component make = (~text, ~onClick, ()) => {
    let%hook (boxShadowTransparency, setBoxShadowTransparency) =
      Hooks.state(0.0);

    let%hook transitionedBoxShadowTransparency =
      Hooks.transition(
        ~initialValue=0.0,
        ~duration=Time.ms(150),
        ~easing=Easing.ease,
        boxShadowTransparency,
      );

    <View
      onMouseEnter={_ => setBoxShadowTransparency(_prevTransparency => 0.15)}
      onMouseLeave={_ => setBoxShadowTransparency(_prevTransparency => 0.0)}>
      <Clickable onClick>
        <View style={Styles.button(transitionedBoxShadowTransparency)}>
          <Text style=Styles.buttonText text />
        </View>
      </Clickable>
    </View>;
  };
};

let%component main = () => {
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

    let animatedTextWrapper = [flexDirection(`Row), marginBottom(24)];

    let text = [
      marginTop(24),
      color(Color.hex(Theme.reveryBlue)),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(16.),
    ];
  };

  let%hook (count, setCount) = React.Hooks.state(0);
  let increment = () => setCount(count => count + 1);

  <View style=Styles.container>
    <View style=Styles.animatedTextWrapper>
      <AnimatedText delay={Time.ms(0)} text="Welcome" />
      <AnimatedText delay={Time.ms(500)} text="to" />
      <AnimatedText delay={Time.ms(1000)} text="Revery" />
    </View>
    <SimpleButton text="Increment" onClick=increment />
    <Text
      style=Styles.text
      text={"Times clicked: " ++ string_of_int(count)}
    />
  </View>;
};

let init = app => {
  Revery.App.initConsole();

  Timber.App.enable();
  Timber.App.setLevel(Timber.Level.perf);

  let win =
    App.createWindow(
      app,
      "Hello Revery!",
      ~createOptions=
        WindowCreateOptions.create(
          ~backgroundColor=Color.hex(Theme.lightBlue),
          ~width=320,
          ~height=512,
          (),
        ),
    );

  let _update: Revery.UI.renderFunction = UI.start(win, <main />);
  ();
};

App.start(init);
