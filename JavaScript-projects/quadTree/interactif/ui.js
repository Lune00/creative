function nbPointsSelected(rootNode, circularProbe) {
  let points = rootNode.query(circularProbe);
  return points === undefined ? 0 : points.length;
}

function nbPointsLooked(rootNode, circleProbe) {
  let looked = rootNode.queryLooked(circleProbe);
  return looked === undefined ? 0 : looked.length;
}

function nbPointsTotal(rootNode) {
  let n = rootNode.nbPoints();
  return n === undefined ? 0 : n;
}

function getNbGaussianPointsUI() {
  return parseInt(document.getElementById("nbPointsGaussian").value);
}

function getProbeSizeUI() {
  return document.getElementById('sliderProbeSize').value;
}


var colors = {
  colorPointSelected: '#33FF57',
  colorPointLooked: '#FF5733'
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

  let totalNPoints = nbPointsTotal(rootNode);
  let totalNPointsEvaluated = nbPointsLooked(rootNode, circularProbe);
  let totalNPointsSelected = nbPointsSelected(rootNode, circularProbe);

  let pourcentageEvaluated;
  let pourcentageSelected;

  if (totalNPoints === 0) {
    pourcentageEvaluated = 0;
    pourcentageSelected = 0;
  } else {
    pourcentageEvaluated = (totalNPointsEvaluated / totalNPoints) * 100;
    pourcentageSelected = (totalNPointsSelected / totalNPoints) * 100;
  }

  //TODO : separer vue et donnees (model)

  document.getElementById('nbPointsTotal').innerHTML = totalNPoints;
  document.getElementById('nbChildren').innerHTML = rootNode.nbNodes() + 1;
  document.getElementById('nbPoitnsEvaluated').innerHTML = totalNPointsEvaluated + " (" + Number.parseFloat(pourcentageEvaluated).toPrecision(3) + "%)";
  document.getElementById('nbPoitnsSelected').innerHTML = totalNPointsSelected + " (" + Number.parseFloat(pourcentageSelected).toPrecision(3) + "%)";

}
