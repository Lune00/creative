var player;

function setup() {
  createCanvas(Config.getWidthVisibleScreen(), Config.getHeightVisibleScreen());
  frameRate(Config.fps);
  
  //Init player
  player = new Player();
  //Init ennemies
  EnnemyManager.addNEnnemy(25, player,'default');
}

function draw() {
  background(100);
  player.update(deltaTimeSeconds());
  EnnemyManager.updateEnnemies(deltaTimeSeconds());
  player.show();
  EnnemyManager.showEnnemies();

  if(frameCount % 100 === 0){
    debug(); 
  }
  
}

function debug(){
  console.log('bullets shoot : ', player.weapon.bullets.length, millis()/1000);
}


function deltaTimeSeconds() {
  return deltaTime / 1000;
}

function keyPressed() {
  //SPACE BAR
  if (keyCode === 32) {
    player.resetPosition();
  }
}


function mousePressed(){
}