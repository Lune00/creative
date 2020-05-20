import demo01 from './demo01/app01.js';
import {uiApp01} from './demo01/ui_app01.js';

import demo02 from './demo02/app02.js';
import {uiApp02} from './demo02/ui_app02.js';

import demo03 from './demo03/app03.js';
import {uiApp03} from './demo03/ui_app03.js';

//Main
export const main = (() => {

  let main = {};

  //Map canvas to switch
  main.map_switch_canvas = (() => {
    let map = new Map();
    map.set('defaultCanvas0', 'switch-demo01');
    map.set('defaultCanvas1', 'switch-demo02');
    map.set('defaultCanvas2', 'switch-demo03');
    return map;
  })();

  main.start = function() {
    console.log('start app');
    //Start demo01 and init its UI
    // main.p5demo01 = new p5(demo01, 'canvas-demo01-insert-querry');
    main.p5demo01 = new p5(demo01, 'canvas-demo01-insert-querry');
    uiApp01.init();

    main.p5demo02 = new p5(demo02, 'canvas-demo02-depth');
    uiApp02.init();

    main.p5demo03 = new p5(demo03, 'canvas-demo03-collisions');
    uiApp03.init();

    //init with p5demo01
    $('#switch-demo01').bootstrapToggle('on');
  };

  return main;
})();

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

  } else if (id === 'switch-demo03') {
    document.getElementById('resetButton-demo03').disabled = false;
    if (!main.p5demo03._loop) {
      main.p5demo03.loop();
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
  } else if (id === 'switch-demo03') {
    document.getElementById('resetButton-demo03').disabled = true;
    main.p5demo03.noLoop();
  }
};


main.start();
