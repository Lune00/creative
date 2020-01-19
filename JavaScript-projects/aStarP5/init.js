let canvas = null;

//P5JS
function setup(){
    canvas = createCanvas( parameters.canvasWidth, parameters.canvasHeight );
    canvas.parent('p5sketch');
    background(255);
    centerCanvas();
    console.log("Setup done");
    grid = initGrid();
    grid = setDefaultStartingEndingPoints(grid);
}

//Un peu d'adaptatif
window.onresize = windowResized =() => {
    console.log("window resized");
    centerCanvas();
};

//Recenter on resizewindow event
//Todo : une gestion propre de la redimmension
const centerCanvas = () => {
    const x = (window.innerWidth - width) / 2;
    const y = (window.innerHeight - height) / 2;
    canvas.position(x, y);
};
