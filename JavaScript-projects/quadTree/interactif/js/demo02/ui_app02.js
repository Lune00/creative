const modelDemoQuadTreeDepth = {
  maxDepth: 0,
  depthUnderCursor: 0,
  totalNPoints: 0,

  updateMaxDepth: function() {
    this.maxDepth = main.p5demo02.getMaxDepth();
  },

  updateTotalNPoints: function() {
    this.totalNPoints = main.p5demo02.numberOfPoints();
  },

  updateDepthUnderCursor: function(){
    // this.depthUnderCursor = main.p5demo02.getDepthUnderCursor();
    //Directly updated from pedagogic_extension depthUnderCursor (j'avais la flemme)
  },

  update: function() {
    this.updateMaxDepth();
    this.updateDepthUnderCursor();
    this.updateTotalNPoints();
  }
}

const uiApp02 = {

  model: modelDemoQuadTreeDepth,

  getNbGaussianPoints: function() {
    return parseInt(document.getElementById("nbPointsGaussian-demo02").value);
  },

  init: function() {

    document.getElementById('canvas-demo02-depth').addEventListener('click', () => {
      if (document.getElementById('normal-demo02').checked) {
        main.p5demo02.insertNormal();
      } else
        main.p5demo02.insertGaussian(this.getNbGaussianPoints());
    });

    document.getElementById('resetButton-demo02').addEventListener('click', () => {
      main.p5demo02.reset();
      this.update();
    });

    for (let radio of document.getElementsByName("insertionModeGroup-demo02")) {
      if (radio.id === 'normal-demo02') {
        radio.addEventListener('click', function() {
          document.getElementById("nbPointsGaussian-demo02").disabled = true;
          document.getElementById("nbPointsGaussianValue-demo02").value = "";
        });
      } else if (radio.id === 'gaussian-demo02') {
        radio.addEventListener('click', function() {
          document.getElementById("nbPointsGaussian-demo02").disabled = false;
          document.getElementById("nbPointsGaussianValue-demo02").value = document.getElementById("nbPointsGaussian-demo02").value;
        });
      }
    }

    document.getElementById('nbPointsGaussian-demo02').addEventListener('input', function() {
      document.getElementById('nbPointsGaussianValue-demo02').value = this.value;
    });
  },

  update: function() {
    this.model.update();
      document.getElementById('nbPointsTotal-demo02').innerHTML = this.model.totalNPoints;
    document.getElementById('depth_max').innerHTML = this.model.maxDepth;
    document.getElementById('depth_current').innerHTML = this.model.depthUnderCursor;
  },
}
