
const modelDemoQuadTreeDepth = {
  update: function(rootNode, circularProbe) {
  }
}


const uiApp02 = {

  model: modelDemoQuadTreeDepth,

  getNbGaussianPoints: function() {
    return parseInt(document.getElementById("nbPointsGaussian").value);
  },
  getProbeSize: function() {
    return parseInt(document.getElementById('sliderProbeSize').value);
  },

  init: function() {
    document.getElementById('sliderProbeSize').addEventListener('change', function() {
      circularProbe.r = parseInt(this.value);
    });

    document.getElementById('resetButton').addEventListener('click', function() {
      rootNode.clear();
      ui.update(rootNode, circularProbe);
    });

    for (let radio of document.getElementsByName("insertionModeGroup")) {
      if (radio.id === 'normal') {
        radio.addEventListener('click', function() {
          insertMode.mode = 'normal'
          document.getElementById("nbPointsGaussian").disabled = true;
          document.getElementById("nbPointsGaussianValue").value = "";
        });
      } else if (radio.id === 'gaussian') {
        radio.addEventListener('click', function() {
          insertMode.mode = 'gaussian'
          document.getElementById("nbPointsGaussian").disabled = false;
          document.getElementById("nbPointsGaussianValue").value = document.getElementById("nbPointsGaussian").value;
        });
      }
    }
  },

  update: function(rootNode, circularProbe) {
    this.model.update(rootNode, circularProbe);
  }

}
