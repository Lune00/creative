class Player {
  
  constructor() {
    this.pos = createVector(PlayerParameters.startPlayerX, PlayerParameters.startPlayerY);
    this.vel = createVector(0, 0);
    this.d = PlayerParameters.size;
    this.pointer = createVector(0, 0);
    this.weapon = getWeapon(this, 'default');
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
    circle(this.pointer.x, this.pointer.y, this.d * 0.1);
    pop();
  }

  update(dt) {
    this.clock += dt;
    this.fire();
    this.weapon.update(dt);
    this.updateDirection();
    this.updateVelocity(dt);
    this.updatePosition(dt);
  }

  updateDirection() {
    this.pointer.x = mouseX - this.pos.x;
    this.pointer.y = mouseY - this.pos.y;
    this.pointer.setMag(this.d * 0.4);
  }

  updatePosition(dt) {
    this.pos.x += this.vel.x * dt;
    this.pos.y += this.vel.y * dt;
    //this.pos.add(p5.Vector.mult(this.vel, dt));
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