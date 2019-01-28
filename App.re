open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

module AnimatedText = {
  let component = React.component("AnimatedText");

  let make = (~delay, ~textContent, ()) =>
    component(slots => {
      let (translate, slots) =
        Hooks.animation(
          Animated.floatValue(50.),
          {
            toValue: 0.,
            duration: Seconds(0.5),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
          },
          slots,
        );

      let (opacityVal: float, _slots: React.Hooks.empty) =
        Hooks.animation(
          Animated.floatValue(0.),
          {
            toValue: 1.0,
            duration: Seconds(1.),
            delay: Seconds(delay),
            repeat: false,
            easing: Animated.linear,
          },
          slots,
        );

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Lato-Regular.ttf"),
          fontSize(24),
          marginHorizontal(8),
          opacity(opacityVal),
          transform([Transform.TranslateY(translate)]),
        ];

      <Text style=textHeaderStyle text=textContent />;
    });

  let createElement = (~children as _, ~delay, ~textContent, ()) =>
    React.element(make(~delay, ~textContent, ()));
};

module SimpleButton = {
  let component = React.component("SimpleButton");

  let make = () =>
    component(slots => {
      let (count, setCount, _slots: React.Hooks.empty) =
        React.Hooks.state(0, slots);
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
          fontFamily("Lato-Regular.ttf"),
          fontSize(20),
          margin(4),
        ];

      let textContent = "Click me: " ++ string_of_int(count);
      <Clickable onClick=increment>
        <View style=wrapperStyle>
          <Text style=textHeaderStyle text=textContent />
        </View>
      </Clickable>;
    });

  let createElement = (~children as _, ()) => React.element(make());
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
