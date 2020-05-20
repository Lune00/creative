//Quadtree : demo insertion and inspection around a point within a circular range
//source: https://jimkang.com/quadtreevis/
//Author : Paul Schuhmacher
import NodePedagogic from '../pedagogic_extension.js';
import {Node, CircularProbe, Point, Particle} from '../quadTree.js';
import {uiApp03} from './ui_app03.js';
import * as apiP5 from '../api_render.js';


export default function demo03(sketch){

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
  let timeConstructionQuadtree = 0;
  let timeComputeInteractions = 0;
  //Game loop
  let previous = 0.;
  let lag = 0.;

  sketch.setup = function() {

    console.log('setup demo03');
    sketch.createCanvas(1024, 600);
    sketch.background(0);

    rmax = 0;

    width = sketch.width;
    height = sketch.height;
    nParticles = uiApp03.getNbParticles();

    for (let i = 0; i != nParticles; i++) {
      particles[i] = new Particle(sketch.random(10, width - 10), sketch.random(10, height - 10), sketch.random(8, 12), sketch.random(2 * sketch.PI));
      rmax = rmax > particles[i].r ? rmax : particles[i].r;
    }

    algorithm = sketch.useQuadTree;

    probe = new CircularProbe(0, 0, 2 * rmax);
    rootNode = new Node(width / 2, height / 2, width / 2, height / 2);

  };


  sketch.useNaive = function() {
    //Nx(N-1)/2


    for(let i = 0 ; i!= particles.length; i++){
      particles[i].overlap = false;
    }
    let tstart = performance.now();
    for (let i = 0; i != particles.length-1; i++) {

      let current = particles[i];

      for (let j = i + 1; j != particles.length; j++) {

        if (sketch.overlap(current, particles[j])) {
          current.overlap = true;
          particles[j].overlap = true;
        }
      }

      if (showDetectionZones)
        apiP5.apiP5.showParticleDetectionZone(sketch, current);

      apiP5.apiP5.showParticle(sketch, current);
    }

    let tend = performance.now();
    timeComputeInteractions = tend - tstart;

  };

  sketch.useQuadTree = function() {

    let p = new Point(0, 0);

    //Update
    let t0 = performance.now();
    for (let i = 0; i != particles.length; i++) {
      rootNode.insert(new Point(particles[i].x, particles[i].y, particles[i]));
    }
    let t1 = performance.now();

    timeConstructionQuadtree = t1 - t0;

    if (showQuadtree)
      apiP5.apiP5.showNodeWithoutPoints(sketch, rootNode);

    //Detect collisions

    let tstart = performance.now();
    for (let i = 0; i != particles.length; i++) {

      let current = particles[i];
      probe.moveTo(current.x, current.y);
      let neighbors = rootNode.query(probe);

      if (showDetectionZones)
        apiP5.apiP5.showParticleDetectionZone(sketch, probe);

      current.overlap = false;
      for (let n of neighbors) {
        if (n.data != current && sketch.overlap(current, n.data)) {
          current.overlap = true;
          break;
        }
      }
    }
    let tend = performance.now();
    timeComputeInteractions = tend - tstart + timeConstructionQuadtree;

  };

  sketch.deltaTimeSeconds = function() {
    return sketch.deltaTime / 1000;
  }

  sketch.draw = function() {
    sketch.background(0);

    sketch.update();

    //render
    for (let i = 0; i != particles.length; i++) {
      apiP5.apiP5.showParticle(sketch, particles[i]);
    }
  };

  sketch.update = function(dt) {
    rootNode.clear();
    uiApp03.update();
    //move
    for (let i = 0; i != particles.length; i++) {
      particles[i].move(sketch.width, sketch.height);
    }
    algorithm();

  }


  sketch.overlap = function(particleA, particleB) {
    return sketch.dist(particleA.x, particleA.y, particleB.x, particleB.y) < particleA.r + particleB.r;
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

  sketch.getTimeConstructionQuadTree = function() {
    return timeConstructionQuadtree;
  }

  sketch.getTimeToComputeInteractions = function() {
    return timeComputeInteractions;
  }

}
