class Circle {

  constructor(x, y, r) {
    this.x = x;
    this.y = y;
    this.r = r;
  }

  moveTo(x,y){
    this.x = x;
    this.y = y;
  }
  
  show() {
    stroke('#5733FF');
    strokeWeight(1.5);
    noFill();
    circle(this.x, this.y, 2 * this.r);
  }
  
  contains(point){
   return  (this.x-point.x) * (this.x-point.x) + (this.y-point.y) * (this.y-point.y) <= this.r * this.r;
  }

  
  //Only for axis-aligned rectangle
  intersects(rectangle) {
    
    let dx = Math.abs(this.x - rectangle.x);
    let dy = Math.abs(this.y - rectangle.y);
    let w = rectangle.w;
    let h = rectangle.h;
    let r = this.r;

    if(dx > w + r) 
      return false;
    if(dy > h + r)
      return false;

    if(dx < w)
      return true;
    if(dy < h)
      return true;
    
    let cornerDistance = (dx-w)*(dx-w) + (dy-h)*(dy-h);
    return cornerDistance <= r * r ; 
  }
  
}