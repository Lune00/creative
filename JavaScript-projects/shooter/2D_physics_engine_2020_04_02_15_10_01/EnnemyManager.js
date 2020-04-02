const EnnemyManager = {
 
  ennemies: [],
  
  addEnnemy: function(player, type) {
    let ennemy = getEnnemy(player,type);
    this.ennemies.push(ennemy);
  },
  
  
  addNEnnemy: function(n, player, type){
    for(let i = 0 ; i!= n; i++){
      this.addEnnemy(player,type);
    }
  },
  
  removeEnnemy: function(ennemy){
    
  },
  
  updateEnnemies: function(dt){
    for(let i = 0; i!= this.ennemies.length; i++){
     this.ennemies[i].update(dt);
    }
  },
  
  showEnnemies: function(){
    for(let i = 0; i!= this.ennemies.length; i++){
     this.ennemies[i].show();
    }
  }
  
}

function getEnnemy(player, type){
 
  //Initial position (outside visble screen, on the edge)
  let pos = generateEnnemyInitialPosition();
  //Initial direction (pointing to visible screen region)
  let dir = generateEnnemyInitialDirection(pos).normalize();
  let vel = p5.Vector.mult(dir, EnnemyParameters.speedDefault);
  
  switch (type) {
    case 'default':
      return new Ennemy(pos, vel, EnnemyParameters.sizeDefault, player, 'bouncing');
    default:
      return getEnnemy(player, 'default');
  }
  
}

//Return initial direction pointing toward a random point
//in the visible screen within a predefined region
//Take the position of the ennemy as a parameter
function generateEnnemyInitialDirection(pos){

  //Take a random point inside the target
  let u = random(0, Config.getHeightVisibleScreen() / 2);
  let tetha = random(0, 2 * PI);
  
  //Translate to the center of the screen
  let xTargetPoint = u * cos(tetha) + Config.getWidthVisibleScreen() / 2;
  let yTargetPoint = u * sin(tetha) + Config.getHeightVisibleScreen() / 2;
  
  //Target point : where the initial direciton of the ennemy point to
  let posTargetPoint = new p5.Vector(xTargetPoint, yTargetPoint);
  
  return p5.Vector.sub(posTargetPoint, pos);
}


function generateEnnemyInitialPosition(){
  
  let r = int(random(0, 4));
  let x;
  let y;
  
  //Random position on the edge of the outside screen
  switch (r) {
    case 0:
      x = random(-Config.getBandWidth(), Config.getWidthTotalScreen() );
      y = -Config.getBandWidth();
      break;
    case 1:
      x = Config.getWidthTotalScreen();
      y = random(-Config.getBandWidth(), Config.getHeightTotalScreen());
      break;
    case 2:
      x = random(-Config.getBandWidth(), Config.getWidthTotalScreen());
      y = Config.getHeightTotalScreen();
      break;
    case 3:
      x = -Config.getBandWidth();
      y = random(-Config.getBandWidth(), Config.getHeightTotalScreen());
      break;
  } 
  
  return new p5.Vector(x,y);
}