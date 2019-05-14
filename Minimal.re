open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let _ = UI.start(win, <View />);
};

App.start(init);
