//Main
const main = (() => {
  console.log('start app');
  let main = {};
  //Start demo01 and init its UI
  main.p5demo01 = new p5(demo01, 'canvas-demo01-insert-querry');
  uiApp01.init();

  main.p5demo02 = new p5(demo02, 'canvas-demo02-depth');
  uiApp02.init();

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

const activateDemo = id => {
  if (id === 'switch-demo01') {
    document.getElementById('resetButton').disabled = false;
    main.p5demo01.loop();
  } else if (id === 'switch-demo02') {
    document.getElementById('resetButton-demo02').disabled = false;
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
