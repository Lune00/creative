//Quadtree source-code (point, probe, Node) including p5.js library functions and variables for visualisation
//Author : Paul Schuhmacher

class Point {
  constructor(x, y, data) {
    this.x = x;
    this.y = y;
    this.data = data;
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

//Node is divided in 4 children: [NW,NE,SW,SE] => [0,1,2,3]
//A node can contains only points (it is a leaf) or only nodes (it is a branch)

class Node {

  constructor(x, y, w, h, depth) {
    //Rectangular area : (x,y) position of the center, (w,h) half width/height
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;

    this.children = [
      [],
      [],
      [],
      []
    ];
    //Max children
    this.nChildrenMax = this.children.length;
    this.length = 1;
    this.isBranch = false;
    //Depth:
    if (!depth)
      this.depth = 0;
    else
      this.depth = depth;

  }

  insert(point) {

    if (!this.contains(point))
      return;

    let index = this.index(point);

    if (this.children[index] instanceof Node) {
      this.children[index].insert(point);
      return;
    } else {

      //If it's a branch, then it has already been divided and we should turn this child into a leaf
      if (this.isBranch) {
        this.children[index] = this.getNewNode(index);
        this.children[index].insert(point);
        return;
      }

      //If it's not a branch then it's a leaf and we add attach the point to it
      this.children[index].push(point);

      //Check if this leaf has reached max capacity, if it has, the leaf turns into a branch
      if (this.hasReachedMaxCapacity())
        this.branch();
    }
  }


  branch() {
    //Because only a Leaf can branch, we are garantuee that children are arrays of points
    //Get all points attached to the current node
    this.children.forEach((points, index) => {
      //If a child contains points turn it into a Leaf
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
  index(point) {
    return this.index_horizontal(point.x) + 2 * this.index_vertical(point.y);
  }

  index_horizontal(x) {
    return Math.floor((x - (this.x - this.w)) / this.w);
  }

  index_vertical(y) {
    return Math.floor((y - (this.y - this.h)) / this.h);
  }

  getNewNode(child) {
    if (child === 0)
      return new Node(this.x - this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (child === 1)
      return new Node(this.x + this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (child === 2)
      return new Node(this.x - this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (child === 3)
      return new Node(this.x + this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
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
}


//Data representation
//TODO: refactor
class Particle {

  constructor(x, y, r, tetha = 0) {

    this.x = x;
    this.y = y;
    this.r = r;

    this.vx = 1 * Math.cos(tetha);
    this.vy = 1 * Math.sin(tetha);

    this.overlap = false;

  }

  move(width, height) {
    this.x += this.vx;
    this.y += this.vy;
    this.bounce(width, height);
  }

  //TODO: refactor and move outside
  bounce(width, height) {

    let xright = this.x + this.r;
    let xleft = this.x - this.r;
    let ytop = this.y + this.r;
    let ybottom = this.y - this.r;

    if (xleft < 0 || xright > width)
      this.vx *= -1;
    if (ybottom < 0 || ytop > height)
      this.vy *= -1;

  }

  highlight() {
    this.overlap = true;
  }

  // isOverlaping(other) {
  //   return dist(this.x, this.y, other.x, other.y) < this.r + other.r;
  // }
}
