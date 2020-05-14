//Quadtree : demo insertion and inspection around a point within a circular range
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher

const demo03 = (sketch) => {

  let rootNode;
  let probe;
  let particles = [];
  let nParticles;
  let rmax;
  let width;
  let height;
  let showQuadtree = false;
  let showDetectionZones = false;

  let algorithm;

  sketch.setup = function() {

    console.log('setup demo03');
    sketch.createCanvas(1024, 600);
    sketch.background(0);

    rmax = 0;

    width = sketch.width;
    height = sketch.height;
    nParticles = uiApp03.getNbParticles();

    for (let i = 0; i != nParticles; i++) {
      particles[i] = new Particle(sketch.random(10, width - 10), sketch.random(10, height - 10), 8, sketch.random(2 * sketch.PI));
      rmax = rmax > particles[i].r ? rmax : particles[i].r;
    }

    algorithm = sketch.useQuadTree;

    probe = new CircularProbe(0, 0, 2 * rmax);
    rootNode = new Node(width / 2, height / 2, width / 2, height / 2);

  };


  sketch.useNaive = function() {
    console.log('use naive');
  };

  sketch.useQuadTree = function() {
    console.log('use quadtree');

    let p = new Point(0, 0);

    //Update
    for (let i = 0; i != particles.length; i++) {
      particles[i].overlap = false;
      particles[i].move(sketch.width, sketch.height);
      rootNode.insert(new Point(particles[i].x, particles[i].y, particles[i]));
    }

    if (showQuadtree)
      apiP5.showNodeWithoutPoints(sketch, rootNode);

    //Detect collisions and render
    for (let i = 0; i != particles.length; i++) {

      let current = particles[i];
      probe.moveTo(current.x, current.y);
      let neighbors = rootNode.query(probe);

      if (showDetectionZones)
        apiP5.showParticleDetectionZone(sketch, probe);

      for (let n of neighbors) {
        //TODO
        // if (n.data != current && current.isOverlaping(n.data)) {
        //   current.highlight();
        // }
      }
      apiP5.showParticle(sketch, particles[i], 'blue');
    }

  };



  sketch.draw = function() {


    sketch.background(0);
    rootNode.clear();
    uiApp03.update();

    algorithm();



  };

  //Interace with UI
  sketch.setNumberOfParticles = function(nbParticles) {

    //Remove add particles where nbParticles = nParticles
    if (nbParticles > particles.length) {
      let nbParticlesToAdd = nbParticles - particles.length;
      for (let i = 0; i != nbParticlesToAdd; i++) {
        particles.push(new Particle(sketch.random(10, width - 10), sketch.random(10, height - 10), sketch.random(8, rmax), sketch.random(2 * sketch.PI)));
      }
    } else if (nbParticles < particles.length) {
      let nbParticlesToRemove = particles.length - nbParticles;
      particles.splice(0, nbParticlesToRemove);
    }
  };

  sketch.showQuadTree = function(show) {
    showQuadtree = show;
  };

  sketch.showDetectionZones = function(show) {
    showDetectionZones = show;
  };

  sketch.setAlgorithm = function(algo) {
    if (algo === 'naive')
      algorithm = sketch.useNaive;
    else if (algo === 'quadtree')
      algorithm = sketch.useQuadTree;
  }

}
