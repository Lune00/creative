function setup() {
  createCanvas(Config.getWidthVisibleScreen(), Config.getHeightVisibleScreen());
  frameRate(Config.fps);

  //Init ennemies
  PlayerManager.initPlayer();
  EnnemyManager.addNEnnemy(10, PlayerManager.getPlayer(), 'default');
  
}

//Add player manager
function draw() {
  background(100);
  
  Dasher.tic(deltaTimeMiliSeconds());
  //Check collisions : solve

  //Update
  PlayerManager.updatePlayer(deltaTimeSeconds());
  EnnemyManager.updateEnnemies(deltaTimeSeconds());

  //Show
  PlayerManager.showPlayer();
  EnnemyManager.showEnnemies();


  if (frameCount % 200 === 0) {
    //debug();
  }

}

function debug() {
  console.log('bullets shoot : ', PlayerManager.player.weapon.bullets.length, millis() / 1000);
}


function deltaTimeSeconds() {
  return deltaTime / 1000;
}

function deltaTimeMiliSeconds(){
  return deltaTime;
}

function keyPressed() {
  //SPACE BAR
  if (keyCode === 32) {
    PlayerManager.getPlayer().resetPosition();
  }
  Dasher.processInput(keyCode);
}


function mousePressed() {}