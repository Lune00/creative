const modelDemoQuadTreeInteractions = {

  update: function() {

  }

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
        });
      } else if (radio.id === "quadtree") {
        radio.addEventListener('click', () => {
          document.getElementById('nbParticulesRange').disabled = false;
          document.getElementById('showDetectionZoneCheckbox').disable = false;
          document.getElementById('showQuadTreeCheckbox').disable = false;
        });
      }
    }
    document.getElementById('output-nbParticules').value = document.getElementById('nbParticulesRange').value;
    document.getElementById('nbParticulesRange').addEventListener('input', function() {
      document.getElementById('output-nbParticules').value = this.value;
    });
  },

  update: function() {
    model.update();
  }

}
