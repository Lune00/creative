function draw(){
    if( mouseIsPressed ) {
        fill(0);
    }
    else
        fill(255);
    square(mouseX, mouseY, 100);
}
