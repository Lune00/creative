//Definitions:
//Quadrant: space of the Node divided in 4 quadrants: [NW,NE,SW,SE] => [0,1,2,3]
//Children: each Node has 4 children max. A child take cares of what happens
//in the quadrant it operates on. Child can be an array of points or another Node

class Node {

  constructor(x, y, w, h, depth) {

    //Rectangular area : (x,y) position of the center, (w,h) : half width/height
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;

    //4 children max : either an array of points, either a Node
    this.children = [];

    //NW
    this.children[0] = [];
    //NE
    this.children[1] = [];
    //SW
    this.children[2] = [];
    //SE
    this.children[3] = [];

    //Max children
    this.nChildrenMax = 4;
  }


  insert(point) {

    //If not in the node
    if (!this.inside(point))
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
      if (this.full())
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

  inside(point) {
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

  nbPoints() {

    let n = 0;
    for (let i = 0; i != this.children.length; i++) {

      if (this.children[i] instanceof Node)
        n += this.children[i].nbPoints();
      else
        n += this.children[i].length;
    }

    return n;
  }

  full() {
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
    for (let i = 0; i !== 4; i++) {
      this.children[i] = [];
    }
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

    for (let child of this.children) {

      if (child instanceof Node)
        child.query(circleProbe, points);
      else {
        for (let p of child) {
          if (circleProbe.contains(p))
            points.push(p);
        }
      }
    }
    return points;
  }

  debug() {
    //console.log('show', this.children);
    console.log('nb of children =', this.nbChildren());
    console.log('nb of points =', this.nbPoints());
  }

  show() {

    push();
    rectMode(CENTER);
    stroke(150);
    strokeWeight(0.5);
    noFill();
    rect(this.x, this.y, 2 * this.w, 2 * this.h);
    pop();

    for (let child of this.children) {

      if (child instanceof Node)
        child.show();
      else {
        for (let p of child) {
          p.show(this.depth);
        }
      }
    }

  }

}
