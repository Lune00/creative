//Quadtree source-code (point, probe, Node) including p5.js library functions and variables for visualisation
//Author : Paul Schuhmacher

//Point (leaf of the quadTree) : user data can be attached to it through the data property
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


//A circular probe used to inspects the quadtree
class CircularProbe {

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


  //Only for canvas axis-aligned rectangle
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

//Node divided in 4 children: [NW,NE,SW,SE] => [0,1,2,3] : node is a branch of the quadtree
//Children: each Node has 4 children (may be empty).
//A child can be an array of points (leaves) or another Node (branch)

class Node {

  constructor(x, y, w, h) {

    //Rectangular area : (x,y) position of the center, (w,h) half width/height
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;

    //4 children : either an array of points, either a Node. Initalised with empty arrays
    // NW
    // this.children[0] = [];
    // NE
    // this.children[1] = [];
    // SW
    // this.children[2] = [];
    // SE
    // this.children[3] = [];
    this.children = [
      [],
      [],
      [],
      []
    ];
    //Max children
    this.nChildrenMax = 4;

    //Size HACK
    this.length = 1;

    this.isBranch = false;

  }

  insert(point) {

    if (!this.contains(point))
      return;

    let child = this.childContainingPoint(point);

    if (child instanceof Node) {
      child.insert(point);
      return;
    } else {

      //If it'as a branch, then it has been divised and we should turn this child into a node (leaf)
      if (this.isBranch) {
        let index = this.children.indexOf(child);
        this.children[index] = this.getNewNode(index);
        this.children[index].insert(point);
        return;
      }

      //If it's not a branch then it's a leaf and we add attach the point to it
      child.push(point);

      //Check if this leaf has reached max capacity, if it has, the leaf turns into a branch
      if (this.hasReachedMaxCapacity())
        this.branch();
    }
  }


  branch() {

    //On recupere tous les points présents et on les insere dans des feuilles
    this.children.forEach((child, index) => {
      let points = child;

      //Si y'a des points on cree des feuilles, sinon on laisse
      if (points.length !== 0) {
        this.children[index] = this.getNewNode(index);
        for (let p of points)
          this.children[index].insert(p);
      }

    });

    this.isBranch = true;
  }


  contains(point) {
    return point.x > this.x - this.w && point.x < this.x + this.w &&
      point.y > this.y - this.h && point.y < this.y + this.h;
  }


  //Child:
  //NW = (0,0) == 0
  //NE = (1,0) == 1
  //SW = (0,1) == 2
  //SE = (1,1) == 3
  childContainingPoint(point) {
    let indexX = Math.floor((point.x - (this.x - this.w)) / this.w);
    let indexY = Math.floor((point.y - (this.y - this.h)) / this.h);
    return this.children[indexX + 2 * indexY];
  }

  getNewNode(child) {
    if (child === 0)
      return new Node(this.x - this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2);
    else if (child === 1)
      return new Node(this.x + this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2);
    else if (child === 2)
      return new Node(this.x - this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2);
    else if (child === 3)
      return new Node(this.x + this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2);
  }

  nbChildren() {
    return this.children.reduce((acc, child) => acc + child.length, 0);
  }

  hasReachedMaxCapacity() {
    return this.nbChildren() > this.nChildrenMax;
  }

  clear() {
    this.isBranch = false;
    this.children.forEach((child, index) => {
      this.children[index] = [];
    });
  }


  //Returns all points contained within the circular probe
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

  //Todo: could be optimise by removing the if
  showNodeContent() {
    this.children.forEach(child => {
      if (child instanceof Node)
        child.show();
      else
        child.forEach(p => p.show());
    });
  }
}
