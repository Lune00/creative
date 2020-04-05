
//Monitor control input to detect dash movements and initiate dash state
const Dasher = {
  //Interval in miliseconds between two keyboard inputs to detect dash
  intervalMiliseconds: 250,
  //Time during which player is dashing (velocity set to a value, direction lock)
  dashingTimeSeconds: 0.2,
  
  //Dashing speed:
  dashingSpeed: Physics.vmax * 2,
  
  upTimer: 0,
  downTimer: 0,
  leftTimer: 0,
  rightTimer: 0,
  
  tic: function(dt) {
    this.upTimer += dt;
    this.leftTimer += dt;
    this.rightTimer += dt;
    this.downTimer += dt;
  },
  //Call in keyPressed global function
  processInput: function(keyCode) {
    
    if (keyCode === Controls.upCode) {
      if(this.upTimer < this.intervalMiliseconds){
        PlayerManager.player.dashing = true;
        PlayerManager.player.dashingDirection = 'up';
      }
     this.upTimer = 0;
    }
    
    if (keyCode === Controls.downCode) {
      if(this.downTimer < this.intervalMiliseconds){
        PlayerManager.player.dashing = true;
        PlayerManager.player.dashingDirection = 'down';
      }
     this.downTimer = 0;
    }
    
     if (keyCode === Controls.leftCode) {
      if(this.leftTimer < this.intervalMiliseconds){
        PlayerManager.player.dashing = true;
        PlayerManager.player.dashingDirection = 'left';
      }
     this.leftTimer = 0;
    }
    
    if (keyCode === Controls.rightCode) {
      if(this.rightTimer < this.intervalMiliseconds){
        PlayerManager.player.dashing = true;
        PlayerManager.player.dashingDirection = 'right';
      }
     this.rightTimer = 0;
    }
    
  }
}