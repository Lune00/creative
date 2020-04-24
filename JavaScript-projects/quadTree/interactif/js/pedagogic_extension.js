//Helper functions to add some informations about the quadtree on the web page
//author : Paul Schuhmacher

console.log('pedagogic extension loaded');

function nbPointsSelected(rootNode, circularProbe) {
  let points = rootNode.query(circularProbe);
  return  points === undefined ? 0 : points.length;
}


function nbPointsLooked(rootNode, circleProbe) {
  let looked = rootNode.queryLooked(circleProbe) ;
  return looked === undefined ? 0 : looked.length;
}

function nbPointsTotal(rootNode){
  let n = rootNode.nbPoints();
  return n === undefined ? 0 : n ;
}

function updateUI(rootNode,circularProbe){
  
  let totalNPoints = nbPointsTotal(rootNode);
  let totalNPointsEvaluated = nbPointsLooked(rootNode, circularProbe);
  let totalNPointsSelected = nbPointsSelected(rootNode, circularProbe);

  let pourcentageEvaluated;
  let pourcentageSelected;

  if (totalNPoints === 0) {
    pourcentageEvaluated = 0;
    pourcentageSelected = 0;
  } else {
    pourcentageEvaluated = (totalNPointsEvaluated / totalNPoints) * 100;
    pourcentageSelected = (totalNPointsSelected / totalNPoints) * 100;
  }

//TODO : separer vue et donnees

  document.getElementById('nbPointsTotal').innerHTML = totalNPoints;
  document.getElementById('nbChildren').innerHTML = rootNode.nbNodes() + 1;

  document.getElementById('nbPoitnsEvaluated').innerHTML = totalNPointsEvaluated + " (" + Number.parseFloat(pourcentageEvaluated).toPrecision(3) + "%)";

  document.getElementById('nbPoitnsSelected').innerHTML = totalNPointsSelected + " (" + Number.parseFloat(pourcentageSelected).toPrecision(3) + "%)";
  
}

//Extension of the Node class to add some functions/state for pedagogic reasons only

class NodePedagogic extends Node {

  constructor(x, y, w, h, depth) {
    super(x, y, w, h, depth);

    this.intersected = false;

  }


  nbNodes() {
    let n = 0;
    for (let i = 0; i != this.children.length; i++) {
      if (this.children[i] instanceof Node) {
        n += 1;
        n += this.children[i].nbNodes();
      }
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

  Intersected(circleProbe) {

    let boundingBox = {
      x: this.x,
      y: this.y,
      w: this.w,
      h: this.h
    };

    if (!circleProbe.intersects(boundingBox))
      this.intersected = false;
    else
      this.intersected = true;


    this.children.forEach(child => {
      if (child instanceof Node)
        child.Intersected(circleProbe)
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

  showNode() {
    push();
    rectMode(CENTER);

    if (this.intersected) {
      fill(10);
    } else {
      fill(0);
    }
    stroke(150);
    strokeWeight(0.5);
    rect(this.x, this.y, 2 * this.w, 2 * this.h);
    pop();
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


}
