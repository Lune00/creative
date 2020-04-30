//API to render using p5
//sketch : p5 template instanciation
const apiP5 = {

  showPoint: function(sketch, point, color) {
    sketch.stroke(color);
    sketch.strokeWeight(3);
    sketch.point(point.x, point.y);
  },

  showCircularProbe: function(sketch, circularProbe) {
    if (sketch.mouseX > 0 && sketch.mouseX < sketch.width && sketch.mouseY > 0 && sketch.mouseY < sketch.height) {
      sketch.stroke('#5733FF');
      sketch.strokeWeight(1.5);
      sketch.noFill();
      sketch.circle(circularProbe.x, circularProbe.y, 2 * circularProbe.r);
    }
  },

//TODO : refactor later these 2 functions
  showNode: function(sketch, node) {
    sketch.push();
    sketch.rectMode(sketch.CENTER);
    sketch.noFill();
    sketch.stroke(150);
    sketch.strokeWeight(0.5);
    sketch.rect(node.x, node.y, 2 * node.w, 2 * node.h);
    sketch.pop();

    node.children.forEach(child => {
      if (child instanceof Node)
        this.showNode(sketch, child);
      else
        child.forEach(p => this.showPoint(sketch, p, 'white'));
    });
  },

  showNodeAndHighlightIntersectedLeafs: function(sketch, node) {
    sketch.push();
    sketch.rectMode(sketch.CENTER);

    if (node.intersected) {
      sketch.fill(100);
    } else {
      sketch.fill(0);
    }
    sketch.stroke(150);
    sketch.strokeWeight(0.5);
    sketch.rect(node.x, node.y, 2 * node.w, 2 * node.h);
    sketch.pop();

    node.children.forEach(child => {
      if (child instanceof Node)
        this.showNodeAndHighlightIntersectedLeafs(sketch, child);
      else
        child.forEach(p => this.showPoint(sketch, p, 'white'));
    });
  }
}
