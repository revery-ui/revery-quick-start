open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  open Style;

  Font.Family.default;
  let text = (~yOffset) => [
    color(Color.hex(Theme.reveryBlue)),
    transform([Transform.TranslateY(yOffset)]),
  ];
};

let%component make = (~delay: Time.t, ~text: string, ()) => {
  let%hook (yOffset, _state, _reset) =
    Hooks.animation(
      Animation.animate(Time.ms(500))
      |> Animation.delay(delay)
      |> Animation.ease(Easing.ease)
      |> Animation.tween(50., 0.),
    );

  let%hook (animatedOpacity, _state, _reset) =
    Hooks.animation(
      Animation.animate(Time.ms(750))
      |> Animation.delay(delay)
      |> Animation.ease(Easing.ease)
      |> Animation.tween(0., 1.),
    );

  <Opacity opacity=animatedOpacity>
    <Padding padding=6>
      <Text fontSize=16. style={Styles.text(~yOffset)} text />
    </Padding>
  </Opacity>;
};
