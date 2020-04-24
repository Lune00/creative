//Quadtree : demo insertion and inspection around a point within a circular range
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher

console.log('sketch loaded');


var insertMode = (function() {

  let insertMode = {};

  insertMode.mode = 'normal';

  insertMode.insertNormal = function(rootNode, circularProbe) {
    rootNode.insert(new Point(circularProbe.x, circularProbe.y));

  }

  insertMode.insertGaussian = function(rootNode, circularProbe) {
    let nbPoints = ui.getNbGaussianPoints();
    for (let i = 0; i != nbPoints; i++) {
      rootNode.insert(new Point(randomGaussian(circularProbe.x, circularProbe.r / 3), randomGaussian(circularProbe.y, circularProbe.r / 3)));
    }
  }
  insertMode.insert = function() {
    if (this.mode === 'normal')
      return this.insertNormal;
    else if (this.mode === 'gaussian')
      return this.insertGaussian;
  }

  return insertMode;

})();

//Global variables:
//Starting node of the quadtree
let rootNode;
//Circular probe to inspect the quadtree
let circularProbe;

function setup() {

  canvasQuadTreedemo01 = createCanvas( 1024, 600 );
  canvasQuadTreedemo01.parent('canvasQuadTreedemo01');
  //Init rooNode with screen dimensions
  rootNode = new NodePedagogic(width / 2, height / 2, width / 2, height / 2);
  //Init the circular probe to select points
  circularProbe = new CircularProbe(width / 2, height / 2, ui.getProbeSize());

  ui.init(rootNode, circularProbe, insertMode);
}

//Insert on click event
function mousePressed() {
  if (mouseX > 0 && mouseX < width && mouseY > 0 && mouseY < height) {
    insertMode.insert()(rootNode, circularProbe);
    ui.update(rootNode, circularProbe);
  }
}


function draw() {

  background(0);

  //Move probe around
  circularProbe.moveTo(mouseX, mouseY);

  ui.update(rootNode, circularProbe);

  //For pedagogical reasons only
  rootNode.isIntersected(circularProbe);

  //Show quadtree
  rootNode.show();

  //Show probe
  circularProbe.show();

  //Candidates points => For pedagogical reasons only
  let looked = rootNode.queryLooked(circularProbe);

  if (looked !== undefined)
    for (let p of looked) {
      //Highlight looked points
      p.highlight(colors.colorPointLooked);
    }

  //Selected points
  let points = rootNode.query(circularProbe);

  if (points !== undefined) {
    for (let p of points) {
      //Highlight selected points
      p.highlight(colors.colorPointSelected);
    }
  }

}
