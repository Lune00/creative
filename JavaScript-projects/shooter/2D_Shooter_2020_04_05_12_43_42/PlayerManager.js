//Player parameters
const PlayerParameters = {
  startPlayerX: Config.getWidthVisibleScreen() / 2,
  startPlayerY: Config.getHeightVisibleScreen() / 2,
  size: 50,
}



const PlayerManager = {

  player: {},

  initPlayer: function() {
    this.player = new Player();
  },

  updatePlayer: function(dt) {
    this.player.update(dt);
  },

  showPlayer: function() {
    this.player.show();
  },

  getPlayer: function() {
    return this.player;
  },

}