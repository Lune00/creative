class Ennemy{
 
  constructor(pos, vel, size, player, behavior){
    this.pos = pos;
    this.vel = vel;
    this.size = size;
    //Pointer on the player
    this.player = player;
    //Behavior of an ennemy (bounce, follow player, accelerate)
    //Mayybe we have to refine that later in more parameters
    //How it bounces, following player?, does it shoot?
    this.behavior = behavior;
    this.isInsideVisibleScreen = false;
  }
  
  show(){
    circle(this.pos.x, this.pos.y, this.size);
  }
  
  update(dt){
    this.updateVelocity(dt);
    this.updatePosition(dt);
  }
  
  
  updateVelocity(dt){
   //this.vel.mult(1 + this.acc * dt );
  }
  
  updatePosition(dt){
    this.pos.add( p5.Vector.mult(this.vel, dt));
  }
  
}


