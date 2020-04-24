const colors = {
  colorPointSelected: '#33FF57',
  colorPointLooked: '#FF5733'
}

const modelDemoQuadTreeCreationInspection = {

  totalNPoints: 0,
  totalNPointsEvaluated: 0,
  totalNPointsSelected: 0,
  pourcentageEvaluated: 0,
  pourcentageSelected: 0,

  updateTotalNPoints: function(rootNode) {
    let n = rootNode.nbPoints();
    this.totalNPoints = n === undefined ? 0 : n;
  },

  updateTotalNPointsSelected: function(rootNode, circularProbe) {
    let points = rootNode.query(circularProbe);
    this.totalNPointsSelected = points === undefined ? 0 : points.length;
  },

  updateTotalNPointsEvaluated: function(rootNode, circularProbe) {
    let looked = rootNode.queryLooked(circularProbe);
    this.totalNPointsEvaluated = looked === undefined ? 0 : looked.length;
  },

  update: function(rootNode, circularProbe) {
    this.updateTotalNPoints(rootNode);
    this.updateTotalNPointsEvaluated(rootNode, circularProbe);
    this.updateTotalNPointsSelected(rootNode, circularProbe);
    this.pourcentageEvaluated = this.totalNPoints === 0 ? 0 : (this.totalNPointsEvaluated / this.totalNPoints) * 100;
    this.pourcentageSelected = this.totalNPoints === 0 ? 0 : (this.totalNPointsSelected / this.totalNPoints) * 100;
  }
}


const ui = {

  model: modelDemoQuadTreeCreationInspection,

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
      updateUI(rootNode, circularProbe);
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

    document.getElementById('nbPointsGaussian').addEventListener('input', function() {
      document.getElementById('nbPointsGaussianValue').value = this.value;
    });

    document.getElementById('groupNbPoitnsEvaluated').style.color = colors.colorPointLooked;
    document.getElementById('groupNbPoitnsSelected').style.color = colors.colorPointSelected;
  },

  update: function(rootNode, circularProbe) {

    this.model.update(rootNode, circularProbe);
    document.getElementById('nbPointsTotal').innerHTML = this.model.totalNPoints;
    document.getElementById('nbChildren').innerHTML = rootNode.nbNodes() + 1;
    document.getElementById('nbPoitnsEvaluated').innerHTML = this.model.totalNPointsEvaluated + " (" + Number.parseFloat(this.model.pourcentageEvaluated).toPrecision(3) + "%)";
    document.getElementById('nbPoitnsSelected').innerHTML = this.model.totalNPointsSelected + " (" + Number.parseFloat(this.model.pourcentageSelected).toPrecision(3) + "%)";
  }

}
