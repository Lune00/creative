//Quadtree : demo insertion and inspection around a point within a circular range
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher

const demo01 = (sketch) => {

  let rootNode;
  let circularProbe;

  sketch.setup = function() {

    console.log('setup demo01');

    sketch.createCanvas(1024, 600);

    rootNode = new NodePedagogic(sketch.width / 2, sketch.height / 2, sketch.width / 2, sketch.height / 2);

    circularProbe = new CircularProbe(sketch.width / 2, sketch.height / 2, uiApp01.getProbeSize());
  }

  sketch.draw = function() {

    sketch.background(0);

    uiApp01.update();

    //Move probe around
    circularProbe.moveTo(sketch.mouseX, sketch.mouseY);

    //Highlight inspected nodes
    rootNode.isIntersected(circularProbe);

    //Show quadtree
    apiP5.showNodeAndHighlightIntersectedLeafs(sketch, rootNode);

    //Show probe
    apiP5.showCircularProbe(sketch, circularProbe);

    //Candidates points => For pedagogical reasons only
    let looked = rootNode.queryLooked(circularProbe);

    if (looked !== undefined)
      for (let p of looked) {
        apiP5.showPoint(sketch, p, colors.colorPointLooked);
      }

    let points = rootNode.query(circularProbe);

    if (points !== undefined) {
      for (let p of points) {
        apiP5.showPoint(sketch, p, colors.colorPointSelected);
      }
    }
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

  sketch.changeCircularProbeSize = function(r) {
    console.log('change', r);
    circularProbe.r = r;
  }

  sketch.reset = function() {
    rootNode.clear();
  }

  sketch.numberOfPoints = function() {
    let n = rootNode.nbPoints();
    return n === undefined ? 0 : n;
  }

  sketch.numberOfPointsSelected = function() {
    let points = rootNode.query(circularProbe);
    return points === undefined ? 0 : points.length;
  }

  sketch.numberOfCandidatesPoints = function() {
    let looked = rootNode.queryLooked(circularProbe);
    return looked === undefined ? 0 : looked.length;
  }

  sketch.numberOfBranchsAndLeafs = function() {
    return rootNode.nbBranch();
  }

}
