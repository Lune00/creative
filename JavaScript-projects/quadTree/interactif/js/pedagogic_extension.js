//Derived class from Node to add some informations about the quadtree on the web page
//author : Paul Schuhmacher

console.log('pedagogic extension loaded');

//Extension of the Node class to add some functions/state for pedagogic reasons only
class NodePedagogic extends Node {

  constructor(x, y, w, h, depth) {
    super(x, y, w, h, depth);
    this.intersected = false;
    this.over = false;
  }

  nbBranch(tree) {

    if (!tree) {
      tree = {};
      tree.nbBranch = 0;
      tree.nbLeaf = 0;
    }

    if (this.isBranch)
      tree.nbBranch++;
    else {
      tree.nbLeaf++;
    }


    for (let i = 0; i != this.children.length; i++) {
      if (this.children[i] instanceof Node)
        this.children[i].nbBranch(tree)
    }

    return tree;
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

  depthUnderCursor(circularProbe) {

     if (this.contains(new Point(circularProbe.x, circularProbe.y)) && !this.isBranch){
        this.over = true;
        modelDemoQuadTreeDepth.depthUnderCursor = this.depth; //coupling
     }

     else
       this.over = false;

     this.children.forEach(child => {
       if (child instanceof Node)
         child.depthUnderCursor(circularProbe)
     });

   }

  //Returns all points looked in the circular probe
  queryLooked(circleProbe, points) {

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
        child.queryLooked(circleProbe, points);
      else
        child.forEach(p => {
          points.push(p);
        });

    });

    return points;
  }

  //Override getNewNode from Node
  getNewNode(region) {
    if (region === 0)
      return new NodePedagogic(this.x - this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 1)
      return new NodePedagogic(this.x + this.w / 2, this.y - this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 2)
      return new NodePedagogic(this.x - this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
    else if (region === 3)
      return new NodePedagogic(this.x + this.w / 2, this.y + this.h / 2, this.w / 2, this.h / 2, this.depth + 1);
  }



  getMaxDepth(depthData) {

    if(!depthData){
      depthData = {};
      depthData.maxDepth = 0;
    }
    for (let i = 0; i != this.children.length; i++) {
      if (this.children[i] instanceof Node && this.children[i].isBranch)
        this.children[i].getMaxDepth(depthData)
      else {
        if (this.children[i].depth) {
          depthData.maxDepth = depthData.maxDepth > this.children[i].depth ? depthData.maxDepth : this.children[i].depth;
        }
      }
    }

    return depthData.maxDepth;
  }

  isIntersected(circleProbe) {

   let boundingBox = {
     x: this.x,
     y: this.y,
     w: this.w,
     h: this.h
   };

   if (circleProbe.intersects(boundingBox) && !this.isBranch)
     this.intersected = true;
   else
     this.intersected = false;

   this.children.forEach(child => {
     if (child instanceof Node)
       child.isIntersected(circleProbe)
   });
 }

}
