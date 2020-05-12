//Quadtree : demo insertion and inspection of the depth
//Author : Paul Schuhmacher

const demo02 = (sketch) => {

  let rootNode;
  let circularProbe;

  sketch.setup = function() {

    console.log('setup demo02');

    sketch.createCanvas(1024, 600);
    sketch.background(0);

    rootNode = new NodePedagogic(sketch.width / 2, sketch.height / 2, sketch.width / 2, sketch.height / 2);
    circularProbe = new CircularProbe(sketch.width / 2, sketch.height / 2, 250);
  }

  sketch.draw = function() {
    sketch.background(0);
    circularProbe.moveTo(sketch.mouseX, sketch.mouseY);
    //apiP5.showPoint(sketch, circularProbe, 'white' );

    rootNode.depthUnderCursor(circularProbe);
    apiP5.showNodeWithDepth(sketch,rootNode);




  }

  //Interace with UI

  sketch.insertNormal = function() {
    rootNode.insert(new Point(circularProbe.x, circularProbe.y));
  }

  sketch.insertGaussian = function(nbPoints) {
    for (let i = 0; i != nbPoints; i++) {
      rootNode.insert(new Point(sketch.randomGaussian(circularProbe.x, circularProbe.r / 3), sketch.randomGaussian(circularProbe.y, circularProbe.r / 3)));
    }
  }

  sketch.reset = function() {
    if (rootNode)
      rootNode.clear();
  }

}
