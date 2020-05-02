//Manage activation/desactivation of demos (only one demo active at a time)
(function() {
  $('.switch-demo').change(function() {
    if (this.checked) {
      $('.switch-demo').not(this).bootstrapToggle('off');
      activateDemo(this.id);
    } else {
      desactivateDemo(this.id);
    }
  })
})();

//Auto activation/desactivation with mouse click demo
(function() {
  $('.myCanvas').on('click', (event) => {
    // //Activer le switch correspondant
    const mapingSwitch = main.map_switch_canvas.get(event.target.id);
    if (mapingSwitch) {
      $('#' + mapingSwitch).bootstrapToggle('on');
    }
  })
})();

const activateDemo = id => {
  if (id === 'switch-demo01') {
    document.getElementById('resetButton').disabled = false;
    if (!main.p5demo01._loop) {
      main.p5demo01.loop();
    }

  } else if (id === 'switch-demo02') {
    document.getElementById('resetButton-demo02').disabled = false;
    if (!main.p5demo02._loop) {
      main.p5demo02.loop();
    }
  }
};

const desactivateDemo = id => {
  if (id === 'switch-demo01') {
    document.getElementById('resetButton').disabled = true;
    main.p5demo01.noLoop();
  } else if (id === 'switch-demo02') {
    document.getElementById('resetButton-demo02').disabled = true;
    main.p5demo02.noLoop();
  }

};


//Main
const main = (() => {
  console.log('start app');
  let main = {};

  //Map canvas to switch
  main.map_switch_canvas = (() => {
    let map = new Map();
    map.set('defaultCanvas0', 'switch-demo01');
    map.set('defaultCanvas1', 'switch-demo02');
    return map;
  })();

  //Start demo01 and init its UI
  // main.p5demo01 = new p5(demo01, 'canvas-demo01-insert-querry');
  main.p5demo01 = new p5(demo01, 'canvas-demo01-insert-querry');
  uiApp01.init();

  main.p5demo02 = new p5(demo02, 'canvas-demo02-depth');
  uiApp02.init();

  //init with p5demo01
  $('.switch-demo01').bootstrapToggle('on');

  return main;
})();
