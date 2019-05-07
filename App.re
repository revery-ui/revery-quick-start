open Revery;
open Revery.UI;

let component = React.component("componentWithHooks");

type actions =
  | Increment;

let reducer = (_a, s) => s + 1;

let componentWithHooks = (~children, ()) =>
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(~initialState=1, reducer, hooks);

    let style = Style.[position(`Absolute), left(offset)];

    (hooks, <View onMouseDown={_ => dispatch(Increment)} style />);
  });

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let _ = UI.start(win, <componentWithHooks offsetX=10 />);
  ();
};

App.start(init);
