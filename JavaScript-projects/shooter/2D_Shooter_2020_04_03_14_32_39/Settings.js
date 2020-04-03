//App parameters

//Two screens size to manage events outside the visible screen
//Visible screen (what the player sees, where the player can move)
//Total screen : larger than visible screen : dimension visible screen + bandwidth. Bullets die outside it, ennemies pop in it

const Config = {
  fps: 50,
  getWidthVisibleScreen: function() {
    return 800;
  },
  getHeightVisibleScreen: function() {
    return 600;
  },
  //Extra band width around visible screen => total screen
  getBandWidth: function() {
    return 200;
  },
  getWidthTotalScreen: function() {
    return this.getWidthVisibleScreen() + this.getBandWidth();
  },

  getHeightTotalScreen: function() {
    return this.getHeightVisibleScreen() + this.getBandWidth();
  }
}


//Controls:
//TODO : function that maps key to its keycode
const Controls = {
  up: 'z',
  down: 's',
  left: 'q',
  right: 'd',
  //Tmp keycode of 'zsqd'
  upCode: 90,
  downCode: 83,
  leftCode: 81,
  rightCode: 68
}


// TODO : Idee: construire un array qui retient les inputs sur un horizon
// de x secondes et leur temps. On peut s'en servir ensuite pour constuire
// les dash, jouer avec etc au lieu de tous ces timers....

