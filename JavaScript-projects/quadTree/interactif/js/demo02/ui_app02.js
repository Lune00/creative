const modelDemoQuadTreeDepth = {


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

  update: function() {},
}
