class Point{
 
  constructor(x,y,data){
    this.x = x;
    this.y = y;
    this.data = data;
  } 
  
  
  show(){
    stroke(255);
    strokeWeight(3);
    point(this.x,this.y);
  }
  
  highlight(){
    stroke('#33FF57');
    strokeWeight(4);
    point(this.x,this.y);
  }
  
}