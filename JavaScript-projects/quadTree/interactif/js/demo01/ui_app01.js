import {main} from '../main.js'

export const colors = {
  colorPointSelected: '#33FF57',
  colorPointLooked: '#FF5733'
}

const modelDemoQuadTreeCreationInspection = {

  totalNPoints: 0,
  totalNPointsEvaluated: 0,
  totalNPointsSelected: 0,
  pourcentageEvaluated: 0,
  pourcentageSelected: 0,
  totalBranchs: 0,
  totalLeafs: 0,

  updateTotalNPoints: function() {
    this.totalNPoints = main.p5demo01.numberOfPoints();
  },

  updateTotalNPointsSelected: function() {
    this.totalNPointsSelected = main.p5demo01.numberOfPointsSelected();
  },

  updateTotalNPointsEvaluated: function() {
    this.totalNPointsEvaluated = main.p5demo01.numberOfCandidatesPoints();
  },

  updateBranchAndLeaf: function() {
    let result = main.p5demo01.numberOfBranchsAndLeafs();
    this.totalBranchs = result.nbBranch;
    this.totalLeafs = result.nbLeaf;
  },

  update: function() {
    this.updateTotalNPoints();
    this.updateTotalNPointsEvaluated();
    this.updateTotalNPointsSelected();
    this.updateBranchAndLeaf();
    this.pourcentageEvaluated = this.totalNPoints === 0 ? 0 : (this.totalNPointsEvaluated / this.totalNPoints) * 100;
    this.pourcentageSelected = this.totalNPoints === 0 ? 0 : (this.totalNPointsSelected / this.totalNPoints) * 100;
  }
}


export const uiApp01 = {

  model: modelDemoQuadTreeCreationInspection,

  getNbGaussianPoints: function() {
    return parseInt(document.getElementById("nbPointsGaussian").value);
  },
  getProbeSize: function() {
    return parseInt(document.getElementById('sliderProbeSize').value);
  },

  init: function() {

    document.getElementById('canvas-demo01-insert-querry').addEventListener('click', () => {
      if (document.getElementById('normal').checked) {
        main.p5demo01.insertNormal();
      } else
        main.p5demo01.insertGaussian(this.getNbGaussianPoints());
    });

    document.getElementById('sliderProbeSize').addEventListener('change', () => {
      main.p5demo01.changeCircularProbeSize(this.getProbeSize());
    });

    document.getElementById('resetButton').addEventListener('click', () => {
      main.p5demo01.reset();
    });

    for (let radio of document.getElementsByName("insertionModeGroup")) {
      if (radio.id === 'normal') {
        radio.addEventListener('click', function() {
          document.getElementById("nbPointsGaussian").disabled = true;
          document.getElementById("nbPointsGaussianValue").value = "";
        });
      } else if (radio.id === 'gaussian') {
        radio.addEventListener('click', function() {
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

  update: function() {

    this.model.update();
    document.getElementById('nbPointsTotal').innerHTML = this.model.totalNPoints;
    document.getElementById('nbBranch').innerHTML = this.model.totalBranchs;
    document.getElementById('nbLeaf').innerHTML = this.model.totalLeafs;
    document.getElementById('nbPoitnsEvaluated').innerHTML = this.model.totalNPointsEvaluated + " (" + Number.parseFloat(this.model.pourcentageEvaluated).toPrecision(3) + "%)";
    document.getElementById('nbPoitnsSelected').innerHTML = this.model.totalNPointsSelected + " (" + Number.parseFloat(this.model.pourcentageSelected).toPrecision(3) + "%)";
  },

}
