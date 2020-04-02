class Bullet{
 
  constructor(pos, direction, speed, acceleration){
    this.pos = pos;
    this.vel = direction.mult(speed);
    this.acc = acceleration;
    this.size = BulletParameters.sizeDefault;
  }
  
  show(){
    push();
    fill(255);
    ellipse(this.pos.x, this.pos.y, this.size, this.size );
    pop();
  }
  
  update(dt){
    this.updateVelocity(dt);
    this.updatePosition(dt);
  }
  
  
  updateVelocity(dt){
   this.vel.mult(1 + this.acc * dt );
  }
  
  updatePosition(dt){
    this.pos.add( p5.Vector.mult(this.vel,dt));
  }
  
  
  //TODO: to be changed with QuadTree representation
  
  isInsideScreen(){
    return this.pos.x < Config.getWidthTotalScreen() && this.pos.x > -Config.getBandWidth() && this.pos.y < Config.getHeightTotalScreen() && this.pos.y > -Config.getBandWidth() ;
  }
  
}  