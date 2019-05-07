open Revery;
open Revery.UI;

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let _ = UI.start(win, <View />);
  ();
};

App.start(init);
