var colors = {
  colorPointSelected: '#33FF57',
  colorPointLooked: '#FF5733'
}

var myModel = {

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
    this.pourcentageEvaluated =  this.totalNPoints === 0 ? 0 : (this.totalNPointsEvaluated / this.totalNPoints) * 100;
    this.pourcentageSelected =  this.totalNPoints === 0 ? 0 : (this.totalNPointsSelected / this.totalNPoints) * 100;
  }
}


function getNbGaussianPointsUI() {
  return parseInt(document.getElementById("nbPointsGaussian").value);
}

function getProbeSizeUI() {
  return parseInt(document.getElementById('sliderProbeSize').value);
}


function initUI(rootNode, circularProbe, insertMode) {

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

}


//A separer en deux fonctions
function updateUI(rootNode, circularProbe) {
  //Update model
  myModel.update(rootNode, circularProbe);
  //Update view
  document.getElementById('nbPointsTotal').innerHTML = myModel.totalNPoints;
  document.getElementById('nbChildren').innerHTML = rootNode.nbNodes() + 1;
  document.getElementById('nbPoitnsEvaluated').innerHTML = myModel.totalNPointsEvaluated + " (" + Number.parseFloat(myModel.pourcentageEvaluated).toPrecision(3) + "%)";
  document.getElementById('nbPoitnsSelected').innerHTML = myModel.totalNPointsSelected + " (" + Number.parseFloat(myModel.pourcentageSelected).toPrecision(3) + "%)";

}
