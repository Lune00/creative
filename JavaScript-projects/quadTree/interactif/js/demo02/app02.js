//Quadtree : demo insertion and inspection around a point within a circular range and show depth
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher

//Global variables:
const app02 = {
  rootNode: undefined,
  circularProbe: undefined
}

function setup() {
console.log('setup demo02');
  canvasQuadTreedemo02 = createCanvas( 1024, 600 );
  canvasQuadTreedemo02.parent('canvas-demo02-depth');
  //Init rooNode with screen dimensions
  app02.rootNode = new NodePedagogic(width / 2, height / 2, width / 2, height / 2);
  //Init the circular probe to select points
  app02.circularProbe = new CircularProbe(width / 2, height / 2, uiApp02.getProbeSize());

  uiApp02.init(app02.rootNode, app02.circularProbe, insertMode);
}

//Insert on click event
function mousePressed() {
  if (mouseX > 0 && mouseX < width && mouseY > 0 && mouseY < height) {
    insertMode.insert()(app02.rootNode, app02.circularProbe);
    uiApp02.update(app02.rootNode, app02.circularProbe);
  }
}


function draw() {

  background(0);

  //Move probe around
  app02.circularProbe.moveTo(mouseX, mouseY);

  uiApp02.update(app02.rootNode, app02.circularProbe);

  //For pedagogical reasons only
  app02.rootNode.isIntersected(app02.circularProbe);

  //Show quadtree
  app02.rootNode.show();

  //Show probe
  app02.circularProbe.show();

  //Candidates points => For pedagogical reasons only
  let looked = app02.rootNode.queryLooked(app02.circularProbe);

  if (looked !== undefined)
    for (let p of looked) {
      //Highlight looked points
      p.highlight(colors.colorPointLooked);
    }

  //Selected points
  let points = app02.rootNode.query(app02.circularProbe);

  if (points !== undefined) {
    for (let p of points) {
      //Highlight selected points
      p.highlight(colors.colorPointSelected);
    }
  }

}
