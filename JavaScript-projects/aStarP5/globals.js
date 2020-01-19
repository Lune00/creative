const parameters = {
    nodeSizePx: 100,
    canvasHeight: 600,
    canvasWidth: 800,
    nbNodesPerRow(){
        return this.canvasHeight / this.nodeSizePx;
    },
    nbNodesPerCol(){
        return this.canvasWidth / this.nodeSizePx;
    }
};
//2D grid representing the map (a 2D array of Node)
let grid = [];
console.log("Globals loaded");


