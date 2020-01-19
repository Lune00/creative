//Plusieurs categorie (code couleur) :
// none (jamais considéré), considere(openList), visite(closedList), path(parti du plus court chemin)

//Todo: pick up nice complementary colors later
nodeCategories = {
    none: 'white',
    considere: 'blue',
    visite: 'green',
    path: 'red'
};

//x => col
//y => row
const initGrid =() => {
    let grid = [];

    if(!parameters.nbNodesPerRow() || !parameters.nbNodesPerCol())
        return grid;

    for(let i = 0 ; i !== parameters.nbNodesPerCol(); i++){
        grid[i] = [];
        for(let j = 0 ; j!== parameters.nbNodesPerRow(); j++){
            let x = i * parameters.nodeSizePx;
            let y = j * parameters.nodeSizePx;
            grid[i][j] = new Node(x, y,  true, nodeCategories.none );
        }
    }

    console.log("Initialisation of the grid: done");
    return grid;
};

//TODO: still mutating the grid array...
const setDefaultStartingEndingPoints = (grid) => {
    //Default start and end position
    grid[2][1].isStart = true;
    grid[5][4].isEnd = true;
    return grid;
};

function drawGrid(){
    for(let i = 0; i !== parameters.nbNodesPerCol(); i++){
        for(let j = 0; j !== parameters.nbNodesPerRow(); j++) {
            grid[i][j].draw();
        }
    }
}

class Node{
    constructor(x, y, walkable, category  ) {
        this.x = x;
        this.y = y;
        this.walkable = walkable;
        this.category = category;
        this.isStart = false;
        this.isEnd = false;
        this.colTemp = 255;
        this.strokeWeight = 3;
    }

    //Render node as square
    draw = () =>{
        stroke(0);
        strokeWeight(this.strokeWeight);
        fill(this.colTemp);
        rect(this.x, this.y, parameters.nodeSizePx, parameters.nodeSizePx);
    };

    isClicked =() => {
        console.log("clicked!", this.x, this.y);

        //TMP
        if(this.isStart)
            console.log("Starting point");

        if(this.isEnd)
            console.log("Ending point");

        if(this.colTemp === 255){
            this.colTemp = 150;
        }
        else
            this.colTemp = 255;
    };
}

console.log("Node loaded");

