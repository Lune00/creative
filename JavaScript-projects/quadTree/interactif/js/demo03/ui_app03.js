const modelDemoQuadTreeInteractions = {
  frameRate: 0,
  timeConstructionQuadtree: 0,
  totalTimeQuadtreeAlgorithm: 0,
  totalTimeNaiveAlgorithm: 0,


  updateFrameRate() {
    setInterval(() => {
      this.frameRate = main.p5demo03.frameRate();
    }, 1000);
  },

  update: function() {}

}

const uiApp03 = {

  model: modelDemoQuadTreeInteractions,

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
          console.log('here');
          document.getElementById('nbParticulesRange').disabled = false;
          document.getElementById('showDetectionZoneCheckbox').disabled = true;
          document.getElementById('showQuadTreeCheckbox').disabled = true;
          main.p5demo03.algorithm = main.p5demo03.setAlgorithm('naive');
        });
      } else if (radio.id === "quadtree") {
        radio.addEventListener('click', () => {
          document.getElementById('nbParticulesRange').disabled = false;
          document.getElementById('showDetectionZoneCheckbox').disable = false;
          document.getElementById('showQuadTreeCheckbox').disable = false;
            main.p5demo03.algorithm = main.p5demo03.setAlgorithm('quadtree');
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
  },

  update: function() {
    this.model.update();

    //FrameRate
    let frameRate = Number.parseFloat(this.model.frameRate).toPrecision(2);
    let frameRateSpan = document.getElementById('frameRate');
    frameRateSpan.innerHTML = frameRate;
    if (frameRate > 40)
      frameRateSpan.style.color = 'green';
    else if (frameRate > 20)
      frameRateSpan.style.color = 'orange';
    else
      frameRateSpan.style.color = 'red';
  }

}
