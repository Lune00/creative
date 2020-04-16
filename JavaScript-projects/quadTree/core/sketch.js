//Quadtree implementation with selection exemple
//Quadtree with four max children (node or point) 
//source: https://jimkang.com/quadtreevis/
//Author : paul schuhmacher


//Rajouter un swith Gaussian ou Single Point (action de l'insert au clik)

let rootNode;
let circularProbe;

function setup() {

  createCanvas(800, 600);

  //Init rooNode with screen dimensions
  rootNode = new Node(width / 2, height / 2, width / 2, height / 2);

  //Init the circular probe to select points
  circularProbe = new Circle(width / 2, height / 2, 50);
}

function draw() {

  background(0);

  //Move probe around
  circularProbe.moveTo(mouseX, mouseY);

  //Show quadtree
  rootNode.show();

  //Show probe
  circularProbe.show();

  //Select probed points
  let points = rootNode.query(circularProbe);

  //Highlight selected points
  for (let p of points) {
    p.highlight();
  }

}

//Insert random points
function mousePressed() {
  insertRandomGaussianPoints(rootNode)
}

//Reset quadtree
function keyPressed() {
  if (keyCode === RETURN) {
    rootNode.clear();
  }
}


function insertRandomGaussianPoints(node) {
  for (let i = 0; i != 50; i++) {
    node.insert(new Point(randomGaussian(mouseX, 50), randomGaussian(mouseY, 50)));
  }
}