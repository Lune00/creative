class Weapon {
  constructor(owner, fireRate, dmgByBullet, bulletSize, bulletSpeed, bulletAcceleration, pattern) {
    this.fireRate = fireRate;
    this.dmgByBullet = dmgByBullet;
    this.bulletSize = bulletSize;
    this.bulletSpeed = bulletSpeed;
    this.bulletAceleration = bulletAcceleration;
    this.pattern = pattern;
    this.bullets = [];
    this.bulletPeriod = 1 / fireRate;
    this.owner = owner;
    this.clock = 0.0;
    //Bullets re enter periodically the window (how many times?)
    this.periodicBullets = false;
  }

  update(dt) {
    this.clock += dt;
    this.updateBullets(dt);
  }
  
  updateBullets(dt) {
    this.destroyBulletsOffScreen(); //Optimisation : pas necessaire de le faire a each frame
    this.updateBulletsPositions(dt);
  }

  fire() {
    //If time elapsed since last shoot > bulletPeriod : shoot
    if (this.clock > this.bulletPeriod) {
      let posBullet = p5.Vector.add(this.owner.pos, this.owner.shootingDirection);
      let bullet = new Bullet(posBullet, this.owner.shootingDirection.copy(), this.bulletSpeed, this.bulletAceleration) ;
      this.bullets.push(bullet);
      this.clock = 0;
    }

  }
  
  updateBulletsPositions(dt){
    for (let i = 0; i != this.bullets.length; i++) {
         this.bullets[i].update(dt);
    }    
  }

  showBullets() {
    for (let i = 0; i != this.bullets.length; i++) {
      this.bullets[i].show();
    }
  }

  destroyBulletsOffScreen() {
    //Destroy bullets outside screen
    this.bullets = this.bullets.filter( bullet => bullet.isInsideScreen());
  }


}
  // constructor(owner, fireRate, dmgByBullet, bulletSize, bulletSpeed, bulletAcceleration, pattern)

function getWeapon(owner, type) {
  switch (type) {
    case 'default':
      return new Weapon(owner, 15, 1, 10, 20, 1, 'straight');
    default:
      return getWeapon(owner, 'default');
  }
}