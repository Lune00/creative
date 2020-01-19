//P5JS MAIN LOOP
console.log("App loaded");

function draw(){
    drawGrid();
}

const indexesInsideCanvas = (x ,y) =>{
    if( x < parameters.nbNodesPerCol() && y < parameters.nbNodesPerRow())
        return true;
    else
        return false;
};

const isCursorInsideCanvas = () => {
    if( mouseX < parameters.canvasWidth && mouseY < parameters.canvasHeight)
        return true;
    else
        return false;
};

//TODO Only within canvas! Not the case for the moment
function mousePressed(){

    if( isCursorInsideCanvas()){

        let x = Math.floor( mouseX / parameters.nodeSizePx);
        let y = Math.floor( mouseY / parameters.nodeSizePx);

        console.log("mouse pressed on x=",x," y=",y);
        grid[x][y].isClicked();
    }
}

function mouseOver(){

    let x = Math.floor( mouseX / parameters.nodeSizePx);
    let y = Math.floor( mouseY / parameters.nodeSizePx);

    if( isCursorInsideCanvas())
        grid[x][y].highlight();

}




