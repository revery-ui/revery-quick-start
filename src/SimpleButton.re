// Revery holds all the primitives e.g. <View>, Colors and more
open Revery;

// All styling-related functions exist in the Revery.UI-module
open Revery.UI;

// All Revery-provided non-primitive UI-components like <Button>, <Clickable> reside in
// Revery.UI.Components
open Revery.UI.Components;

module Constants = {
  let boxShadowActiveTransparency = 0.0;
  let boxShadowHoverTransparency = 0.3;
  let boxShadowNotHoveredTransparency = 0.15;
};

module Styles = {
  open Style;

  let button = boxShadowTransparency => [
    backgroundColor(Color.hex(Theme.darkBlue)),
    boxShadow(
      ~yOffset=6.,
      ~xOffset=0.,
      ~blurRadius=16.,
      ~color=Color.rgba(0., 0., 0., boxShadowTransparency),
      ~spreadRadius=12.,
    ),
    paddingHorizontal(24),
    paddingVertical(12),
    borderRadius(10.),
  ];

  let buttonText = [backgroundColor(Colors.red), color(Colors.white)];
};

let%component make = (~text, ~onClick, ()) => {
  let%hook (boxShadowTransparency, setBoxShadowTransparency) =
    Hooks.state(Constants.boxShadowNotHoveredTransparency);

  let%hook transitionedBoxShadowTransparency =
    Hooks.transition(~duration=Time.ms(150), boxShadowTransparency);

  let updateShadowTransparency = (_event, ~newOpacity) => {
    setBoxShadowTransparency(_prevTransparency => newOpacity);
  };

  <View
    onMouseUp={updateShadowTransparency(
      ~newOpacity=Constants.boxShadowHoverTransparency,
    )}
    onMouseDown={updateShadowTransparency(
      ~newOpacity=Constants.boxShadowActiveTransparency,
    )}
    onMouseEnter={updateShadowTransparency(
      ~newOpacity=Constants.boxShadowHoverTransparency,
    )}
    onMouseLeave={updateShadowTransparency(
      ~newOpacity=Constants.boxShadowNotHoveredTransparency,
    )}>
    <Clickable onClick>
      <View style={Styles.button(transitionedBoxShadowTransparency)}>
        <Text fontSize=16. style=Styles.buttonText text />
      </View>
    </Clickable>
  </View>;
};
