import {
  main
} from '../main.js'

const modelDemoQuadTreeInteractions = {
  frameRate: 0,
  timeConstructionQuadtree: 0,
  totalTimeInteractions: 0,
  pourcentageConstructionInteractions: 0,

  updateFrameRate() {
    setInterval(() => {
      this.frameRate = main.p5demo03.frameRate();
    }, 1000);
  },

  updateTimeConstructionQuadTree() {
    setInterval(() => {
      this.timeConstructionQuadtree = main.p5demo03.getTimeConstructionQuadTree();
    }, 1000);
  },

  updateTimeComputeInteractions() {
    setInterval(() => {
      this.totalTimeInteractions = main.p5demo03.getTimeToComputeInteractions();
    }, 1000);
  },

  updatePourcentage() {
    if (this.totalTimeInteractions && this.totalTimeInteractions != 0)
      this.pourcentageConstructionInteractions = this.timeConstructionQuadtree / this.totalTimeInteractions * 100;
  },

  update() {
    this.updatePourcentage();
  }
}

export const uiApp03 = {

  model: modelDemoQuadTreeInteractions,
  mode: 'quadtree',

  getNbParticles: function() {
    return parseInt(document.getElementById('nbParticulesRange').value);
  },

  init: function() {
    document.getElementById('resetButton-demo03').addEventListener('click', () => {
      main.p5demo03.reset();
      this.update();
    });

    for (let radio of document.getElementsByName("algorithme")) {
      if (radio.id === "naive") {
        radio.addEventListener('click', () => {
          document.getElementById('nbParticulesRange').disabled = false;
          document.getElementById('showDetectionZoneCheckbox').disabled = true;
          document.getElementById('showQuadTreeCheckbox').disabled = true;
          main.p5demo03.algorithm = main.p5demo03.setAlgorithm('naive');
          this.mode = 'naive';

        });
      } else if (radio.id === "quadtree") {
        radio.addEventListener('click', () => {
          document.getElementById('nbParticulesRange').disabled = false;
          document.getElementById('showDetectionZoneCheckbox').disabled = false;
          document.getElementById('showQuadTreeCheckbox').disabled = false;
          main.p5demo03.algorithm = main.p5demo03.setAlgorithm('quadtree');
          this.mode = 'quadtree';
        });
      }
    }
    document.getElementById('output-nbParticules').value = document.getElementById('nbParticulesRange').value;
    document.getElementById('nbParticulesRange').addEventListener('input', function() {
      document.getElementById('output-nbParticules').value = this.value;
      main.p5demo03.setNumberOfParticles(Number.parseInt(this.value));
    });

    document.getElementById('showQuadTreeCheckbox').addEventListener('click', function() {
      main.p5demo03.showQuadTree(this.checked);
    });

    document.getElementById('showDetectionZoneCheckbox').addEventListener('click', function() {
      main.p5demo03.showDetectionZones(this.checked);
    });

    this.model.updateFrameRate();
    this.model.updateTimeConstructionQuadTree();
    this.model.updateTimeComputeInteractions();
  },

  update: function() {

    if (this.mode === 'quadtree')
      this.model.update();

    document.getElementById('timeToBuildQuadtree').innerHTML = Number.parseFloat(this.model.timeConstructionQuadtree).toPrecision(2);
    document.getElementById('timeToComputeInteractions').innerHTML = Number.parseFloat(this.model.totalTimeInteractions).toPrecision(3);
    document.getElementById('pourcentage').innerHTML = Number.parseFloat(this.model.pourcentageConstructionInteractions).toPrecision(3);
    //FrameRate
    let frameRate = Number.parseFloat(this.model.frameRate).toPrecision(2);
    let frameRateSpan = document.getElementById('frameRate');
    frameRateSpan.innerHTML = frameRate;
    if (frameRate > 30)
      frameRateSpan.style.color = 'green';
    else if (frameRate > 10)
      frameRateSpan.style.color = 'orange';
    else
      frameRateSpan.style.color = 'red';
  }

}
