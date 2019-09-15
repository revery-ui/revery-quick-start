open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

let animatedText = {
  let component = React.component("AnimatedText");

  (~children as _: list(React.syntheticElement), ~delay, ~textContent, ()) =>
    component(hooks => {
      let (translate, hooks) =
        Hooks.animation(
          Animated.floatValue(50.),
          Animated.options(
            ~toValue=0.,
            ~duration=Seconds(0.5),
            ~delay=Seconds(delay),
            (),
          ),
          hooks,
        );

      let (opacityVal: float, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          Animated.options(
            ~toValue=1.0,
            ~duration=Seconds(1.),
            ~delay=Seconds(delay),
            (),
          ),
          hooks,
        );

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(24),
          transform([Transform.TranslateY(translate)]),
        ];

      (
        hooks,
        <Opacity opacity=opacityVal>
          <Padding padding=8>
            <Text style=textHeaderStyle text=textContent />
          </Padding>
        </Opacity>,
      );
    });
};

let simpleButton = {
  let component = React.component("SimpleButton");

  (~children as _: list(React.syntheticElement), ()) =>
    component(hooks => {
      let (count, setCount, hooks) = React.Hooks.state(0, hooks);
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
        ];

      let textContent = "Click me: " ++ string_of_int(count);
      (
        hooks,
        <Clickable onClick=increment>
          <View style=wrapperStyle>
            <Padding padding=4>
              <Text style=textHeaderStyle text=textContent />
            </Padding>
          </View>
        </Clickable>,
      );
    });
};

let init = app => {
  let _ = Revery.Log.listen((_, msg) => print_endline("LOG: " ++ msg));

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

  let element =
    <View style=containerStyle>
      <View style=innerStyle>
        <animatedText delay=0.0 textContent="Welcome" />
        <animatedText delay=0.5 textContent="to" />
        <animatedText delay=1. textContent="Revery" />
      </View>
      <simpleButton />
    </View>;

  let _ = UI.start(win, element);
  ();
};

App.start(init);
