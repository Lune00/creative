let canvas = null;

function setup(){
    console.log("welcome in a p5.js project!");
    canvas = createCanvas(800,600);
    canvas.parent('p5sketch');
    background(255, 0, 200);
    background(255);
};

//Un peu d'adaptatif
window.onresize = windowResized =() => {
    console.log("window resized");
    centerCanvas();
};

//Recenter on resizewindow event
const centerCanvas = () => {
    const wFactor = window.innerWidth / width ;
    const hFactor = window.innerHeight / height ;
    console.log(wFactor);
    const x = (window.innerWidth - width) / 2;
    const y = (window.innerHeight - height) / 2;
    canvas.position(x, y);
    //Todo : une gestion propre de la redimmension
};
