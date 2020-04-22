class Point {

  constructor(x, y, data) {
    this.x = x;
    this.y = y;
    this.data = data;
  }


  show() {
    stroke(255);
    strokeWeight(3);
    point(this.x, this.y);
  }

  highlight(color) {
    stroke(color);
    strokeWeight(4);
    point(this.x, this.y);
  }

}

class Circle {

  constructor(x, y, r) {
    this.x = x;
    this.y = y;
    this.r = r;
  }

  moveTo(x, y) {
    this.x = x;
    this.y = y;
  }

  show() {
    if (mouseX > 0 && mouseX < width && mouseY > 0 && mouseY < height) {
      stroke('#5733FF');
      strokeWeight(1.5);
      noFill();
      circle(this.x, this.y, 2 * this.r);
    }
  }

  contains(point) {
    return (this.x - point.x) * (this.x - point.x) + (this.y - point.y) * (this.y - point.y) <= this.r * this.r;
  }


  //Only for axis-aligned rectangle
  intersects(rectangle) {

    let dx = Math.abs(this.x - rectangle.x);
    let dy = Math.abs(this.y - rectangle.y);
    let w = rectangle.w;
    let h = rectangle.h;
    let r = this.r;

    if (dx > w + r)
      return false;
    if (dy > h + r)
      return false;

    if (dx < w)
      return true;
    if (dy < h)
      return true;

    let cornerDistance = (dx - w) * (dx - w) + (dy - h) * (dy - h);
    return cornerDistance <= r * r;
  }

}

//Definitions:
//Quadrant: space of the Node divided in 4 quadrants: [NW,NE,SW,SE] => [0,1,2,3]
//Children: each Node has 4 children max. A child take cares of what happens
//in the quadrant it operates on. Child can be an array of points or another Node

class Node {

  constructor(x, y, w, h) {

    //Rectangular area : (x,y) position of the center, (w,h) : half width/height
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;

    //4 children max : either an array of points, either a Node
    this.children = [
      [],
      [],
      [],
      []
    ];

    //NW
    // this.children[0] = [];
    // //NE
    // this.children[1] = [];
    // //SW
    // this.children[2] = [];
    // //SE
    // this.children[3] = [];

    //Max children
    this.nChildrenMax = 4;

  }


  insert(point) {

    //If not in the node
    if (!this.contains(point))
      return;

    //Determines in which quadrant of the node the point is
    let region = this.getRegion(point);

    //Si la region est deja une node enfant il faut inserer dans la node enfant
    if (region instanceof Node) {
      region.insert(point);
      return;
    }
    //Else, Add point to current node
    else {
      //Add the point to the region
      region.push(point);

      //Check if node has reached max capacity (accross all regions) (max nb of children)
      if (this.hasReachedMaxCapacity())
        this.split(region);
    }
  }


  split(region) {
    //We need to subdivise this region where the new point has arrived 
    let childNode = this.getNewNode(this.children.indexOf(region));

    //Push points from current node to the child node   
    for (let p of region) {
      childNode.insert(p);
    }

    //Region point now to a children node
    this.setRegionToNode(this.children.indexOf(region), childNode);
  }

  setRegionToNode(index, children) {
    this.children[index] = children;
  }

  contains(point) {
    return point.x > this.x - this.w && point.x < this.x + this.w &&
      point.y > this.y - this.h && point.y < this.y + this.h;
  }


  //Region: 
  //NW = (0,0) == 0
  //NE = (1,0) == 1
  //SW = (0,1) == 2
  //SE = (1,1) == 3
  getRegion(point) {
    let indexX = Math.floor((point.x - (this.x - this.w)) / this.w);
    let indexY = Math.floor((point.y - (this.y - this.h)) / this.h);
    return this.children[indexX + 2 * indexY];
  }

  nbChildren() {
    let n = 0;
    for (let i = 0; i != this.children.length; i++) {
      if (this.children[i] instanceof Node)
        n += 1
      else
        n += this.children[i].length;
    }
    return n;
  }

  hasReachedMaxCapacity() {
    return this.nbChildren() > this.nChildrenMax;
  }


  getNewNode(region) {
    if (region === 0)
      return new Node(this.x - this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 1)
      return new Node(this.x + this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 2)
      return new Node(this.x - this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 3)
      return new Node(this.x + this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
  }


  clear() {
    this.children.forEach((child, index) => {
      this.children[index] = [];
    });
  }


  //Returns all points contains in the circular probe
  query(circleProbe, points) {

    if (!points) {
      points = [];
    }

    let boundingBox = {
      x: this.x,
      y: this.y,
      w: this.w,
      h: this.h
    };

    if (!circleProbe.intersects(boundingBox))
      return;

    this.children.forEach(child => {

      if (child instanceof Node)
        child.query(circleProbe, points);
      else
        child.forEach(p => {
          if (circleProbe.contains(p))
            points.push(p);
        });

    });

    return points;
  }

  show() {
    this.showNode();
    this.showNodeContent();
  }

  showNode() {
    push();
    rectMode(CENTER);
    noFill();
    stroke(150);
    strokeWeight(0.5);
    rect(this.x, this.y, 2 * this.w, 2 * this.h);
    pop();
  }

  showNodeContent() {

    this.children.forEach(child => {
      if (child instanceof Node)
        child.show();
      else
        child.forEach(p => p.show());
    });

  }

}




