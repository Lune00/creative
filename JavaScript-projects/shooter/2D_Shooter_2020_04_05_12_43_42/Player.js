class Player {

  constructor() {
    
    this.pos = new p5.Vector(PlayerParameters.startPlayerX, PlayerParameters.startPlayerY);
    this.vel = new p5.Vector(0, 0);
    
    this.d = PlayerParameters.size;
    
    //Shooting direction
    this.shootingDirection = new p5.Vector(0, 0);
    this.weapon = getWeapon(this, 'default');
    
    
    //State dashing:
    this.dashing = false;
    this.dashingDirection = 'undefined';
    this.dashingTime = 0;
  }

  show() {
    push();
    stroke(255);
    fill(0);
    strokeWeight(4);

    circle(this.pos.x, this.pos.y, this.d);
    pop();
    this.showDirection();
    this.weapon.showBullets();
  }

  showDirection() {
    push();
    translate(this.pos.x, this.pos.y);
    fill(255, 0, 0);
    strokeWeight(2);
    circle(this.shootingDirection.x, this.shootingDirection.y, this.d * 0.1);
    pop();
  }

  update(dt) {
    
    //Manage weapong and bullets
    this.fire();
    this.weapon.update(dt);

    //Manage movement integration
    
    //If dashing, do not update velocity with input or inertia
    //but set velocity
    if (this.dashing) {

      this.dashingTime += dt;

      //Dashing time
      if (this.dashingTime < Dasher.dashingTimeSeconds) {
        this.dash();
        //Reset dashing, no dashing state
      } else {
        this.dashing = false;
        this.dashingDirection = 'undefined';
        this.dashingTime = 0;
      }
      //If not dashing, update with input or inertia
    } else {
      this.updateDirection();
      this.updateVelocity(dt);
    }

    //Update position
    this.updatePosition(dt);
  }

  updateDirection() {
    this.shootingDirection.x = mouseX - this.pos.x;
    this.shootingDirection.y = mouseY - this.pos.y;
    this.shootingDirection.setMag(this.d * 0.4);
  }

  updatePosition(dt) {
    this.pos.x += this.vel.x * dt;
    this.pos.y += this.vel.y * dt;
  }

  dash() {
    switch (this.dashingDirection) {
      case 'up':
        this.vel.y = -Physics.vmax * 2;
        break;
      case 'down':
        this.vel.y = Physics.vmax * 2;
        break;
      case 'left':
        this.vel.x = -Physics.vmax * 2;
        break;
      case 'right':
        this.vel.x = Physics.vmax * 2;
        break;
    }
  }

  //Movement
  updateVelocity(dt) {

    if (keyIsDown(Controls.upCode)) {
      this.vel.y += -Physics.acc;
    } else if (keyIsDown(Controls.downCode)) {
      this.vel.y += Physics.acc;
    } else {
      this.vel.y -= Math.sign(this.vel.y) * Physics.acc / Physics.drag;
      //Decelerate in y direction
      if (Math.abs(this.vel.y) < Physics.vmin)
        this.vel.y = 0
    }

    if (keyIsDown(Controls.leftCode)) {
      this.vel.x += -Physics.acc;
    } else if (keyIsDown(Controls.rightCode)) {
      this.vel.x += Physics.acc;
    } else {
      this.vel.x -= Math.sign(this.vel.x) * Physics.acc / Physics.drag;
      //Decelerate in x direction
      if (Math.abs(this.vel.x) < Physics.vmin)
        this.vel.x = 0;
    }

    if (this.vel.mag() > Physics.vmax) {
      this.vel.setMag(Physics.vmax);
    }
  }

  resetPosition() {
    this.pos.x = PlayerParameters.startPlayerX;
    this.pos.y = PlayerParameters.startPlayerY;
    this.vel.setMag(0);
  }

  fire() {
    if (mouseIsPressed) {
      this.weapon.fire();
    }
  }
}