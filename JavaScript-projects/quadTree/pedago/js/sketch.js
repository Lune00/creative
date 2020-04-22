//Quadtree implementation with selection exemple
//Quadtree with four max children (node or point) 
//source: https://jimkang.com/quadtreevis/
//Author : paul schuhmacher


//TODO: show looked points (print nb/nbTotal %)

//Global variables:
//Starting node of the quadtree
let rootNode;
//Circular probe to inspect the quadtree
let circularProbe;

//Insert function used depending on mode
let insertFunction;

//Colors:
let colorPointSelected = '#33FF57';
let colorPointLooked = '#FF5733';

function setup() {

  createCanvas(1024, 600);

  //Init rooNode with screen dimensions
  rootNode = new NodePedagogic(width / 2, height / 2, width / 2, height / 2);

  //Init the circular probe to select points
  circularProbe = new Circle(width / 2, height / 2, 100);

  //Event on slider
  let sliderProbeSize = document.getElementById('sliderProbeSize');
  sliderProbeSize.value = circularProbe.r;

  sliderProbeSize.addEventListener('change', function() {
    circularProbe.r = parseInt(this.value);
  });

  document.getElementById('resetButton').addEventListener('click', function() {
     rootNode.clear();
     updateUI(rootNode, circularProbe);
  });

  //Pointer vers la bonne fonction en fonction du mode (radio)
  insertFunction = insertNormal;

  for (let radio of document.getElementsByName("insertionModeGroup")) {

    if (radio.id === 'normal') {
      radio.addEventListener('click', setInsertToNormal);
    } else if (radio.id === 'gaussian') {
      radio.addEventListener('click', setInsertToRandomGaussianPoints);
    }
  }

  //Event listener to min/max nbPoints
  document.getElementById('nbPointsGaussian').addEventListener('input', function() {
    document.getElementById('nbPointsGaussianValue').value = this.value;
  });

  document.getElementById('groupNbPoitnsEvaluated').style.color = colorPointLooked;
  document.getElementById('groupNbPoitnsSelected').style.color = colorPointSelected;
}


function draw() {

  background(0);

  updateUI(rootNode, circularProbe);

  //Move probe around
  circularProbe.moveTo(mouseX, mouseY);

  //For pedagogical reasons only
  rootNode.Intersected(circularProbe);

  //Show quadtree
  rootNode.show();

  //Show probe
  circularProbe.show();

  let points = rootNode.query(circularProbe);

  //For pedagogical reasons only
  let looked = rootNode.queryLooked(circularProbe);
  if (looked !== undefined)
    for (let p of looked) {
      //Highlight looked points
      p.highlight(colorPointLooked);
    }

  if (points !== undefined) {
    for (let p of points) {
      //Highlight selected points
      p.highlight(colorPointSelected);
    }
  }

}

function insertNormal() {
  rootNode.insert(new Point(mouseX, mouseY));
}

function insertRandomGaussianPoints() {
  let nbPoints = parseInt(document.getElementById("nbPointsGaussian").value);
  for (let i = 0; i != nbPoints; i++) {
    rootNode.insert(new Point(randomGaussian(mouseX, circularProbe.r / 3), randomGaussian(mouseY, circularProbe.r / 3)));
  }
}

function setInsertToNormal() {
  insertFunction = insertNormal;
  document.getElementById("nbPointsGaussian").disabled = true;
  document.getElementById("nbPointsGaussianValue").value = "";
}

function setInsertToRandomGaussianPoints() {
  insertFunction = insertRandomGaussianPoints;
  document.getElementById("nbPointsGaussian").disabled = false;
  document.getElementById("nbPointsGaussianValue").value = document.getElementById("nbPointsGaussian").value;
}

//Insert on click event
function mousePressed() {
  if (mouseX > 0 && mouseX < width && mouseY > 0 && mouseY < height) {
    insertFunction();
    updateUI(rootNode, circularProbe);
  }
}

