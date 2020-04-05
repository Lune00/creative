class Ennemy {

  constructor(pos, vel, size, player, behaviorOnLimits) {
    this.pos = pos;
    this.vel = vel;
    this.size = size;
    
    
    //Pointer on the player
    this.player = player;
    
    
    //Behavior of an ennemy (bounce, follow player, accelerate)
    //Mayybe we have to refine that later in more parameters
    //How it bounces, following player?, does it shoot?
    
    
    //Behavior on limits (bounce, quit (continue), periodic)
    this.behaviorOnLimits = behaviorOnLimits;
    
    
    this.hasEnteredArena = false;
  }

  show() {
    circle(this.pos.x, this.pos.y, this.size);
  }

  update(dt) {

    //Check if has entered the screen visible 'arena'
    if (!this.hasEnteredArena) {
      this.hasEnteredArena = this.isInside();
    }

    //Behavior when inside the arena
    if (this.hasEnteredArena)
      //When ennemy reaches the limits => behavior
      if (!this.isInside()) {
        this.behaveOnLimits();
      }

    this.updateVelocity(dt);
    this.updatePosition(dt);
  }

  
  behaveOnLimits(){
    
     if (this.behaviorOnLimits === 
         EnnemyParameters.behaviorsOnLimits.bounce)
          this.bounce();
    
  }

  
  updateVelocity(dt) {
    //this.vel.mult(1 + this.acc * dt );
  }

  updatePosition(dt) {
    this.pos.add(p5.Vector.mult(this.vel, dt));
  }


  isInside() {

    let xright = this.pos.x + this.size / 2;
    let xleft = this.pos.x - this.size / 2;
    let ytop = this.pos.y + this.size / 2;
    let ybottom = this.pos.y - this.size / 2;


    return xleft > 0 && xright < Config.getWidthVisibleScreen() && ybottom > 0 && ytop < Config.getHeightVisibleScreen();
  }

  bounce() {

    let xright = this.pos.x + this.size / 2;
    let xleft = this.pos.x - this.size / 2;
    let ytop = this.pos.y + this.size / 2;
    let ybottom = this.pos.y - this.size / 2;


    if (xleft < 0 || xright > Config.getWidthVisibleScreen())
      this.vel.x *= -1;
    else if (ybottom < 0 || ytop > Config.getHeightVisibleScreen())
      this.vel.y *= -1;
    else
      return;
  }

}