open Revery;
open Revery.UI;
open Revery.UI.Components;

module AnimatedText = {
  let%component make = (~delay: float, ~textContent: string, ()) => {
    let%hook (translate, _, _) =
      Hooks.animation(
        Animated.floatValue(50.),
        Animated.options(
          ~toValue=0.,
          ~duration=Time.seconds(0.5),
          ~delay=Time.seconds(delay),
          (),
        ),
      );

    let%hook (opacityVal: float, _, _) =
      Hooks.animation(
        Animated.floatValue(0.),
        Animated.options(
          ~toValue=1.0,
          ~duration=Time.seconds(1.),
          ~delay=Time.seconds(delay),
          (),
        ),
      );

    let textHeaderStyle =
      Style.[
        color(Colors.white),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(24),
        transform([Transform.TranslateY(translate)]),
      ];

    <Opacity opacity=opacityVal>
      <Padding padding=8>
        <Text style=textHeaderStyle text=textContent />
      </Padding>
    </Opacity>;
  };
};

module SimpleButton = {
  let%component make = () => {
    let%hook (count, setCount) = React.Hooks.state(0);
    let increment = () => setCount(_ => count + 1);

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
    <Clickable onClick=increment>
      <View style=wrapperStyle>
        <Padding padding=4>
          <Text style=textHeaderStyle text=textContent />
        </Padding>
      </View>
    </Clickable>;
  };
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
        <AnimatedText delay=0.0 textContent="Welcome" />
        <AnimatedText delay=0.5 textContent="to" />
        <AnimatedText delay=1. textContent="Revery" />
      </View>
      <SimpleButton />
    </View>;

  let _ = UI.start(win, element);
  ();
};

App.start(init);
