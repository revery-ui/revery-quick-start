open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

module AnimatedText = {
  let component = React.component("AnimatedText");

  let createElement = (~children as _, ~delay, ~textContent, ()) =>
    component(hooks => {
      let (translate, hooks) =
        Hooks.animation(
          Animated.floatValue(50.),
          {
            toValue: 0.,
            duration: Seconds(0.5),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
          },
          hooks,
        );

      let (opacityVal: float, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          {
            toValue: 1.0,
            duration: Seconds(1.),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
          },
          hooks,
        );

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(24),
          marginHorizontal(8),
          opacity(opacityVal),
          transform([Transform.TranslateY(translate)]),
        ];

      (hooks, <Text style=textHeaderStyle text=textContent />);
    });
};

module SimpleButton = {
  let component = React.component("SimpleButton");

  let createElement = (~children as _, ()) =>
    component(hooks => {
      let (count, setCount, hooks) =
        React.Hooks.state(0, hooks);
      let increment = () => setCount(count + 1);

      let wrapperStyle =
        Style.[
          backgroundColor(Color.rgba(1., 1., 1., 0.1)),
          border(~width=2, ~color=Colors.white),
          margin(16),
        ];

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(20),
          margin(4),
        ];

      let textContent = "Click me: " ++ string_of_int(count);
      (hooks, <Clickable onClick=increment>
        <View style=wrapperStyle>
          <Text style=textHeaderStyle text=textContent />
        </View>
      </Clickable>);
    });
};

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let containerStyle =
    Style.[
      position(`Absolute),
      justifyContent(`Center),
      alignItems(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
    ];

  let innerStyle = Style.[flexDirection(`Row), alignItems(`FlexEnd)];

  let render = () =>
    <View style=containerStyle>
      <View style=innerStyle>
        <AnimatedText delay=0.0 textContent="Welcome" />
        <AnimatedText delay=0.5 textContent="to" />
        <AnimatedText delay=1. textContent="Revery" />
      </View>
      <SimpleButton />
    </View>;

  UI.start(win, render);
};

App.start(init);
