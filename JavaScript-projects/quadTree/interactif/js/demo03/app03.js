//Quadtree : demo insertion and inspection around a point within a circular range
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher

const demo03 = (sketch) => {

  let rootNode;
  let probe;
  let particles = [];

  sketch.setup = function() {

    console.log('setup demo03');
    sketch.createCanvas(1024, 600);
    sketch.background(0);

    let rmax = 0;

    let width = sketch.width;
    let height = sketch.height;

    for (let i = 0; i != 200; i++) {
      particles[i] = new Particle(sketch.random(10, width - 10), sketch.random(10, height - 10), 8, sketch.random(2 * sketch.PI));
      rmax = rmax > particles[i].r ? rmax : particles[i].r;
    }

    probe = new CircularProbe(0, 0, 2 * rmax);
    rootNode = new Node(width / 2, height / 2, width / 2, height / 2);

    console.log('init done');
  }

  sketch.draw = function() {

    sketch.background(0);
    rootNode.clear();

    let p = new Point(0, 0);

    //Update
    for (let i = 0; i != particles.length; i++) {
      particles[i].overlap = false;
      particles[i].move(sketch.width, sketch.height);
      rootNode.insert(new Point(particles[i].x, particles[i].y, particles[i]));
    }


    apiP5.showNode(sketch,rootNode);
    //Detect collisions and render
    for (let i = 0; i != particles.length; i++) {

      let current = particles[i];
      probe.moveTo(current.x, current.y);
      let neighbors = rootNode.query(probe);

      apiP5.showCircularProbe(sketch, probe);

      for (let n of neighbors) {
        // if (n.data != current && current.isOverlaping(n.data)) {
        //   current.highlight();
        // }
      }
      //apiP5.showParticle(sketch, particles[i], 'blue');
    }

  }

  //Interace with UI

}
