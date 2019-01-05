open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

module AnimatedText = (
  val component((render, ~delay, ~textContent, ~children, ()) =>
        render(
          () => {
            let opacity: float =
              useAnimation(
                Animated.floatValue(0.),
                {
                  toValue: 1.0,
                  duration: Seconds(1.),
                  delay: Seconds(delay),
                  repeat: false,
                  easing: Animated.linear,
                },
              );

            let translate: float =
              useAnimation(
                Animated.floatValue(50.),
                {
                  toValue: 0.,
                  duration: Seconds(0.5),
                  delay: Seconds(delay),
                  repeat: false,
                  easing: Animated.linear,
                },
              );

            let textHeaderStyle =
              Style.make(
                ~color=Colors.white,
                ~fontFamily="Lato-Regular.ttf",
                ~fontSize=24,
                ~marginHorizontal=8,
                ~opacity,
                ~transform=[TranslateY(translate)],
                (),
              );

            <text style=textHeaderStyle> textContent </text>;
          },
          ~children,
        )
      )
);

module SimpleButton = (
  val component((render, ~children, ()) =>
        render(
          () => {
            let (count, setCount) = useState(0);

            let increment = () => setCount(count + 1);

            let wrapperStyle =
              Style.make(
                ~backgroundColor=Color.rgba(1., 1., 1., 0.1),
                ~border=Style.Border.make(~width=2, ~color=Colors.white, ()),
                ~margin=16,
                (),
              );

            let textHeaderStyle =
              Style.make(
                ~color=Colors.white,
                ~fontFamily="Lato-Regular.ttf",
                ~fontSize=20,
                ~margin=4,
                (),
              );

            let textContent = "Click me: " ++ string_of_int(count);
            <Clickable onClick=increment>
              <view style=wrapperStyle>
                <text style=textHeaderStyle> textContent </text>
              </view>
            </Clickable>;
          },
          ~children,
        )
      )
);

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let render = () =>
    <view
      style={Style.make(
        ~position=LayoutTypes.Absolute,
        ~justifyContent=LayoutTypes.JustifyCenter,
        ~alignItems=LayoutTypes.AlignCenter,
        ~bottom=0,
        ~top=0,
        ~left=0,
        ~right=0,
        (),
      )}>
      <view
        style={Style.make(~flexDirection=Row, ~alignItems=AlignFlexEnd, ())}>
        <AnimatedText delay=0.0 textContent="Welcome" />
        <AnimatedText delay=0.5 textContent="to" />
        <AnimatedText delay=1. textContent="Revery" />
      </view>
      <SimpleButton />
    </view>;

  UI.start(win, render);
};

App.start(init);
